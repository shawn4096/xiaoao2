//sheying.c 杯弓蛇影
//cre by sohu@xojh
 
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

 int perform(object me, object target)
 {
         string msg;
         object weapon;
         int jf,zf,sf,lvl;
         jf = me->query_skill("jinshe-jianfa", 1);
         zf = me->query_skill("jinshe-zhang", 1);
         sf = me->query_skill("wudu-yanluobu", 1);
         lvl=( jf + zf +sf ) /3;        
         weapon = me->query_temp("weapon");
 
         if( !target ) target = offensive_target(me);
        if( !target ) target = offensive_target(me);

        if( !target 
          || !me->is_fighting(target)
          || !objectp(target)
          || environment(target)!= environment(me))
                return notify_fail("「杯弓蛇影」只能在战斗中对对手使用。\n");
 
     //   if((int)me->query_temp("hmg_nizhuan") )
       //          return notify_fail("你逆运了九阴还乱舞什么啊,不怕走火入魔啊!\n");
 
        if (!weapon || weapon->query("skill_type") != "sword"
            || me->query_skill_mapped("sword") != "jinshe-jianfa")
                 return notify_fail("你必须在使用剑时才能使出「杯弓蛇影」！\n");
         if (me->query_skill_mapped("strike") != "jinshe-zhangfa"
			||me->query_skill_prepared("strike") != "jinshe-zhangfa")
                 return notify_fail("你必须激发金蛇掌法才能使出「杯弓蛇影」！\n");

         if(me->query_skill("jinshe-jianfa", 1) < 250 )
                 return notify_fail("你的金蛇剑法还不够娴熟，使不出「杯弓蛇影」绝技。\n");

         if( (int)me->query_skill("force",1) < 250 )
                 return notify_fail("你的基本内功等级不够，使不出「杯弓蛇影」绝技。\n");
         if( (int)me->query_skill("strike",1) < 250 )
                 return notify_fail("你的基本掌法等级不够，使不出「杯弓蛇影」绝技。\n");
         if( (int)me->query_skill("jinshe-zhangfa",1) < 250 )
                 return notify_fail("你的金蛇掌法等级不够，使不出「杯弓蛇影」绝技。\n");

         if( (int)me->query_dex() < 50)
                 return notify_fail("你的后天身法还不够50，使不出「杯弓蛇影」绝技。\n");        
              
         if( (int)me->query("max_neili") < 3000 )
                 return notify_fail("你现在内力太弱，使不出「杯弓蛇影」。\n");      
 
         if( (int)me->query("neili") < 500 )
                 return notify_fail("你现在真气不足，使不出「杯弓蛇影」。\n");
         if( (int)me->query("jingli") < 500 )
                 return notify_fail("你现在精力不足，使不出「杯弓蛇影」。\n");

         lvl = me->query_skill("jinshe-jianfa", 1);
      
         //weapon = me->query_temp("weapon");    

         message_vision(HIC"\n$N将手中"+weapon->query("name")+HIC"晃动，借助阳光反射，幻起一片剑光，宛如万蛇蠕动，正是「杯弓蛇影」绝技！\n"NOR,me);
            
			me->add_temp("apply/damage", lvl /6);
            me->add_temp("apply/attack", lvl /4);
       
	   if (random(me->query("combat_exp"))>target->query("combat_exp")/2
		   ||random(me->query_skill("dodge",1))>target->query_skill("dodge",1)/2)
	   {
			message_vision(HIY"\n$n一怔然间，恍然明白这正是传说中的「杯弓蛇影」，但却为$N金蛇剑法剑光所迷惑！\n"NOR,me,target);
			target->add_busy(2);
			if (!userp(target))
			{
				target->add_busy(2+random(1));
			}
			target->add_temp("apply/attack",-lvl/4);
			target->add_temp("apply/parry",-lvl/4);
			target->set_temp("jsjf/sheying",lvl);
			call_out("remove_effect",(int)lvl/100,target,lvl);

	   }
		
		if (me->is_fighting() && target->is_busy()) 
		{
			message_vision(HIR"\n$N眼见$n为剑光所迷惑，冷笑几声，瞬间劈出一剑二掌！\n"NOR,me,target);

            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            weapon->unequip(); 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			weapon->wield();
		
		 }else {
			message_vision(YEL"\n$N眼见$n并没有为剑光所惑，不得不将剑势一收，一掌拍了出去！\n"NOR,me,target);

            weapon->unequip();             
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			weapon->wield();
			me->start_busy(2);
		}
 			me->add_temp("apply/damage", -lvl /6);
            me->add_temp("apply/attack", -lvl /4);

           me->start_perform(4,"「杯弓蛇影」");
           me->add("neili", -300);
           me->add("jingli", -200);
		   return 1;
 }
int remove_effect(object target,int lvl)
{
	if (!target) return 0;
	
    if (!target->query_temp("jsjf/sheying")) return 0;
   
    target->add_temp("apply/attack",lvl/4);
	target->add_temp("apply/parry",lvl/4);
	message_vision(WHT"$N目光逐渐适应了这种眩晕，不适的状况得到恢复。\n"NOR,target);
	return 1;
}

int help(object me)
{
        write(HIY"\n金蛇剑法之「杯弓蛇影」："NOR"\n\n");
        write(@HELP
	金蛇郎君夏雪宜所流传下来的的绝世武功. 杯弓蛇影是利用
	蛇类剑型武器的阳光反射，从而迷惑对方双眼的一门绝技。
	对方若被剑光迷惑，则会随后攻击一剑一掌，若不中则会随
	后跟进一掌。
	
	指令：perform sword.sheying

要求：
	当前内力需求 500 以上；
	最大内力需求 3000 以上；
	后天身法大于 50 以上；
	金蛇剑法等级 250 级；
	金蛇掌法等级 250 级；
	基本掌法等级 250 级；
	基本剑法等级 250 级；
	基本内功等级 250 级；
	激发剑法为金蛇剑法；
	激发掌法为金蛇掌法；
	备掌法为金蛇掌法；
	持剑类武器，蛇形剑有特效

HELP
        );
        return 1;
}

string perform_name(){ return HIC"杯弓蛇影"NOR; }
