// xing.c 星光点点
// cre by sohu@xojh

#include <ansi.h>
//#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg,*limbs;

        int i,damage,p; 
        i = me->query_skill("xingyi-zhang", 1); 
		
		if( !target ) target = offensive_target(me);
        if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("「星光点点」只能在战斗中对对手使用。\n");
      
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("使用「星光点点」时双手必须空着！\n");
        if(me->query("max_neili")<1400)
                return notify_fail("你的最大内力不够，无法使用「星光点点」！\n");
        if( (int)me->query_skill("xingyi-zhang", 1) < 100 )
                return notify_fail("你的星移掌不够娴熟，不会使用「星光点点」。\n");

        if( (int)me->query_skill("shenyuan-gong", 1) < 100 )
                return notify_fail("你的神元功等级不够，不能使用「星光点点」。\n");

        if( (int)me->query_dex() < 20 )
                return notify_fail("你的身法不够强，不能使用「星光点点」。\n");

        if (me->query_skill_prepared("strike") != "xingyi-zhang"
        || me->query_skill_mapped("strike") != "xingyi-zhang")
                return notify_fail("你现在无法使用「星光点点」进行攻击。\n");                                                                                
        if (me->query_skill_mapped("parry") != "xingyi-zhang"
         && me->query_skill_mapped("parry") != "douzhuan-xingyi")
                return notify_fail("你现在招架不对，无法使用「星光点点」进行攻击。\n");  

        if( (int)me->query("neili") < 700 )
                return notify_fail("你现在内力太弱，不能使用「星光点点」。\n");
        
		message_vision(HIC "\n$N长吸一口真气，神元功周身流转，双掌一排,在周身形成漫天的掌影罩向$n,犹如星星般在$n周围闪烁不定！\n"+
			HIC"$n感觉宛如看到漫天的繁星点点。正是南慕容星移掌绝技"HIW"星光点点"HIC"」\n" NOR,me, target);
       
		message_vision(HIW"\n$N左手向虚空招引，右掌一招「"HIC"星光点点"HIW"」向$n拍去，漫天的繁星仿佛受到招引，倏的凝聚成数点星光，击向$n！\n"NOR,me,target);
		
		if(random(i) > target->query_skill("parry",1)/2
		 ||random(me->query_str())>target->query_str()/2)
		{
           damage = i+me->query_skill("strike",1)+me->query_skill("shenyuan-gong",1)+me->query_skill("douzhuan-xingyi",1);
           damage =4*damage;
		   damage = damage+random(damage);
          // if(target->query_skill("parry",1) - 50 > i)
            // damage = damage/2;
          // if(target->query_skill("parry",1) >i*2)
             // damage = random(1000);

			  damage = damage+random(damage);
           limbs = target->query("limbs");
		
		   if (userp(target)&& damage > 3000) damage = 3000;
		   if (wizardp(me))
           {
			   message_vision("damage="+damage+"\n",me);
           }
		   if (damage>3500) damage=3500+random(1000);
		 
		   if(damage > 3000)
              message_vision(HIY"\n突然之间，$n任脉数穴一痛，宛如被一掌拍上，这一下剧痛让$n眼前金星乱冒！\n"NOR,me,target);            
           if (damage<3000) damage=3000;
           
		   target->receive_damage("qi", damage, me);
		   target->apply_condition("neishang",3+random(2));
           target->receive_wound("qi", damage/2, me);
           //打对方内力
		         //     target->set_temp("last_damage_from", "星移掌打死")

		   target->add("neili", -damage/5);
           
           p = (int)target->query("qi")*100/(int)target->query("max_qi");

           msg = damage_msg(damage, "内伤");
           msg += "( $n"+eff_status_msg(p)+" )\n";
          
		   message_vision(msg, me, target);
           

		   if(userp(me) && me->query("env/damage"))
	          tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR);
           
		   if(userp(target)&& target->query("env/damage"))
	          tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);
           //me->start_busy(1);
           me->add("jingli", -20);
           if (userp(target)) target->add_busy(1);
		   else target->add_busy(2);
		   
		   if (!userp(target) && me->query_temp("sy/shenyuan"))
				target->add_busy(2);		   
        }        
        else {
          
           tell_object(me, HIY"可是"+target->query("name")+"看破了你的企图，斜跃避开了攻击。\n"NOR);

		   me->start_busy(2);         
        }
		me->add_temp("apply/damage",i/6);
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
		me->add_temp("apply/damage",-i/6);
		me->add("neili", -150);
        me->add("jingli", -100);
        me->start_busy(random(1));
		
		me->start_perform(3,"星光点点");
        return 1;
}

string perform_name(){ return HIY"星光点点"NOR; }
int help(object me)
{
        write(HIC"\n星移掌法之"+HIY+"「星光点点」"NOR"\n\n");
        write(@HELP
	当年慕容复在江湖历练时早期使用的招式，利用自身
	的优势在瞬间凝聚全身功力。以星光为引，以神元功
	为基，陡然间爆发一股强悍的掌力，毙敌于掌下。臂
	力和技能与命中有很大关系。

	指令：perform strike.xing

要求：  
	当前内力需求 700 以上；
	最大内力需求 1400 以上；
	当前精力需求 500 以上；
	星移掌法等级 100 以上；
	神元功法等级 100 以上；
	基本掌法等级 100 以上；
	后天身法要求 20  以上；
	激发掌法为星移掌；
	激发招架为星移掌或斗转星移；
                
HELP
        );
        return 1;
}
