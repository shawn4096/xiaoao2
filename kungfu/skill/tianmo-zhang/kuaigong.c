//kuaigong.c 疾攻
//cre by sohu@xojh,源自任我行少林寺一战
//当即急攻数掌，劈到第四掌时，猛觉收掌时右臂微微一麻，内力运转，不甚舒畅，不由得大惊
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
       int i,j,skill;
       j=me->query_skill("tianmo-zhang",1)/100;
	   if (j<3) j=3;
	   skill=me->query_skill("tianmo-zhang",1);
       if( !target ) target = offensive_target(me);

       if( !target || !me->is_fighting(target) )
            return notify_fail("「快攻绝技」只能在战斗中对对手使用。\n");

       if( objectp(me->query_temp("weapon")) )
            return notify_fail("你必须空手才能使用「天魔掌」！\n");

       if( (int)me->query_skill("tianmo-zhang", 1) < 250 )
            return notify_fail("你的天魔掌还不够娴熟，使不出「疾攻」绝技。\n");

       if (me->query_skill_mapped("force") != "tianmo-gong" )
          if(me->query_skill_mapped("force") != "xixing-dafa")
                return notify_fail("你所使用的特殊内功不对。\n"); 
                
       if(!me->query_skill("xixing-dafa", 1))
          if(me->query_skill("tianmo-gong", 1) < 250)
                return notify_fail("以你现在的内功修为还使不出「快攻绝技」。\n");       

       if (me->query_skill_prepared("strike") != "tianmo-zhang"
        || me->query_skill_mapped("strike") != "tianmo-zhang"
        || me->query_skill_mapped("parry") != "tianmo-zhang")
           return notify_fail("你现在无法使用「疾攻」！\n");                                                                                 

       if( (int)me->query("max_neili") < 2500) 
           return notify_fail("你内力太弱，使不出「快攻绝技」。\n");      

       if( (int)me->query("neili") < 1000)
           return notify_fail("你现在真气太弱，使不出「快攻绝技」。\n");

       message_vision(HIB"\n$N渐觉$n的招式稍形缓慢，心中一喜，当即向$n疾攻数招！\n"NOR,me,target);
   
       me->add("neili", -350);
  
         message_vision(HIR"\n$n见$N缓慢出招的掌法忽变，宛如疾风暴雨般攻了过来，顿时手足无措，躲闪无及，正击在$n的身上。\n"NOR, me, target);
         me->add_temp("apply/attack",skill/3);
		 me->add_temp("apply/damage",skill/4);
		 target->add_busy(1+random(2));
		 for (i = 0; i < j; i++)
         {
                if (!me->is_fighting(target))
                        break;
				if (!random(4)&& target->is_busy())
				{
                  message_vision(HIY"\n$n一不小心为$N掌法打中，“哇”地一声吐出一口鲜血！\n"NOR, me, target);
                  target->receive_damage("qi", 1000+random(3000),me);
                  target->receive_wound("qi", 500+random(1000),me);
				}
                COMBAT_D->do_attack(me, target, 0, random(3)?3:1);
        }
		// me->add("max_neili", -50);
	     
		 me->add_temp("apply/attack",-skill/3);
		 me->add_temp("apply/damage",-skill/4);
      
      me->start_perform(4,"快攻绝技");
      return 1;
}

string perform_name(){ return HIR"快攻绝技"NOR; }

int help(object me)
{
        write(HIC"\n天魔掌"+HIR"「快攻绝技」"NOR"\n");
        write(@HELP
	天魔掌乃是日月神教历代高手千锤百炼的空手武技，乃是门下弟子平常
	习练的主要空手武技。后来任我行在少林与方证大师一战，天魔掌的奥
	妙方为人所知。快攻就是抓住对方的缝隙和招式破绽，快速攻击对方数
	招，令对手应不暇接。

	指令：perform strike.kuaigong
	
要求：
	天魔功要求：  250
	天魔掌要求：  250
	基本内功要求：250
	基本掌法要求；250
	当前内力状态: 1000
	最大内力要求：2500
		

HELP
        );
        return 1;
}
