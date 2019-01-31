// sanshi.c 三尸脑神毒
// cre by sohu@xojh 投丹毒
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
       object co;

       if( !target ) target = offensive_target(me);

       if( !target || !me->is_fighting(target) )
            return notify_fail("「三尸脑神毒」只能在战斗中对对手使用。\n");

       if( objectp(me->query_temp("weapon")) )
            return notify_fail("你必须空手才能使用「三尸脑神毒」！\n");

       if( (int)me->query_skill("mantian-huayu", 1) < 250 )
            return notify_fail("你的漫天花雨还不够娴熟，使不出「三尸脑神毒」绝技。\n");
       if( (int)me->query("neili") < 2500 )
            return notify_fail("你的内力不够，使不出「三尸脑神毒」绝技。\n");
	   if( (int)me->query("jingli") < 1500 )
            return notify_fail("你的精力不够，使不出「三尸脑神毒」绝技。\n");
       if (me->query_skill_mapped("force") != "tianmo-gong" )
          if(me->query_skill_mapped("force") != "xixing-dafa")
                return notify_fail("你所使用的特殊内功不对。\n"); 
                
       if(!me->query_skill("xixing-dafa", 1))
          if(me->query_skill("tianmo-gong", 1) < 250)
                return notify_fail("以你现在的内功修为还使不出「三尸脑神毒」。\n");  

       if((int)me->query_skill("poison",1)<120)
            return notify_fail("你毒计不够无法使用三尸脑神毒。\n"); 
       
	   co=present("sanshi dan",me);       

       if (!co)
           return notify_fail("你身上没有三尸脑神丹，如何使用三尸脑神毒!\n");     

       if (me->query_skill_prepared("hand") != "tianmo-shou"
        || me->query_skill_mapped("throwing") != "mantian-huayu"
        || me->query_skill_mapped("parry") != "mantian-huayu")
           return notify_fail("你现在无法使用「三尸脑神毒」！\n");                                                                                 

       if( (int)me->query("max_neili") < 1500) 
           return notify_fail("你内力太弱，使不出「三尸脑神毒」。\n");      

       if( (int)me->query("neili") < 1000)
           return notify_fail("你现在真气太弱，使不出「三尸脑神毒」。\n");

       message_vision(HIB"\n$N从口袋中摸出一粒三尸脑神丹，趁$n张口大喝之际，猛然掷出，一道虹影飞向$n的口中！\n"NOR,me,target);
       call_out("destroying", 1, co);
       if (!target->is_killing(me))
          me->kill_ob(target);
       me->add("neili", - (250 + me->query_skill("force")));
       if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/2
        && me->query_str() > (int)target->query_dex()/2){ 
           message_vision(HIG"\n$n见此怪异的招数，一时间手足无措，躲闪无及，下意识的吞下了这粒药丸。\n"NOR, me, target);
           me->add("max_neili", -random(1));
		   me->add("neili", -random(1000));
	       if (userp(target))
		      me->add_condition("killer", 90);
           target->set_temp("last_damage_from", "三尸脑神毒入脑");
		   target->apply_condition("sansi_poison", 5+random(3));
           target->receive_wound("jing",random(2000),me);
		   message_vision(HIC"$n一口吞下毒丹，心中不禁惴惴不安，大脑中宛如有小虫子在蠕动的感觉，心中不由大骇！\n"NOR,me,target);
		   target->apply_condition("no_exert",1);

           return 1;  
       }
       else if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/3
         || random(me->query("neili")) > target->query("neili")/2){
          message_vision(HIB"\n$n见事不好，连忙纵身直起，三尸脑神丹从身下掠过，没有打中。\n"NOR,me,target);
          tell_object(target,HIB"\n你虽然及时避开了毒尸，但一股腥臭气入鼻，你已中了三尸脑神毒了。\n"NOR);
          me->add("neili", -400);
	      if (userp(target))
		     me->add_condition("killer", 15);
          target->apply_condition("sansi_poison", 3+random(3));
          me->start_busy(1);
          target->add_busy(1);
          return 1;
      }
      message_vision(HIB"\n$n胸有成竹，一声长啸，双掌连环劈出，把这粒毒丹荡向来路。\n"NOR,me,target);
      tell_object(me,HIB"\n不好，三尸毒丹反弹向你，你虽然躲开，但毒气也侵入你的身体。\n"NOR);
      me->set_temp("last_damage_from", "三尸脑神毒入脑");
      me->receive_damage("qi", 2500,me);
      me->receive_wound("qi", 1500,me);
      me->add("neili", -300);
      me->apply_condition("sansi_poison", random(3));
      me->start_perform(2,"三尸脑神毒");
      return 1;
}

void destroying(object obj)
{
        destruct(obj);
}
string perform_name(){ return HIB"三尸脑神毒"NOR; }

int help(object me)
{
        write(HIC"\n漫天花雨"+HIB"「三尸脑神毒」"NOR"\n");
        write(@HELP
	漫天花雨乃是日月神教历经多年征战后所总结提炼出来的
	一门武技，先后经由多位门主长老和教主不断精研所形成
	的一门外门武学，漫天花雨绝技若是与暗器配合，效果尤
	佳因日月神教中高手如云，能人辈出，曾由一位善于用毒
	和制药的大师将毒计演化到天魔掌中，从尸体中提炼出一
	种叫做【三尸脑神毒】的奇毒，借用特殊暗器手法施展后，
	毒丹将会施展飞掷绝技，落入对方口中，当然若对方功力
	高深，也可以反弹回，请玩家慎用。另外请注意：施展此
	招须身带三尸脑神丹。
	
	指令：perform throwing.sanshi
	
要求：
	天魔功或吸星大法要求：  250
	漫天花雨要求：250
	基本内功要求：250
	基本暗器要求；150
	当前内力状态: 2500
	当前精力要求：1500
	毒计要求大于；120

HELP
        );
        return 1;
}
