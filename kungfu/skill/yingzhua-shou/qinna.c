// By sohu@xojh 鹰爪擒拿手

#include <ansi.h>
string perform_name(){ return HIY"擒拿绝技"NOR; }
inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        if( !target )
             target = offensive_target(me);
        if( !target 
          || !me->is_fighting(target)
          || !objectp(target)
          || !living(target)
          || environment(target)!= environment(me))return notify_fail("鹰爪手只能在战斗中使用。\n");
          weapon = target->query_temp("weapon");

        if( userp(me) 
        &&( me->query_skill_mapped("parry") != "yingzhua-shou"))
                return notify_fail("「擒拿绝技」必须在用激发鹰爪手招架的情况下才能使用。\n");

        if( userp(me) && (me->query_skill_mapped("force") != "shenghuo-shengong"
        || me->query_skill_prepared("hand") != "yingzhua-shou") )
                return notify_fail("你的内功或掌法不对，根本不能发挥出「擒拿绝技」的优势。\n");  

        if((int)me->query_skill("shenghuo-shengong", 1)  < 180 )
             return notify_fail("你的圣火神功等级还不够，使不出「擒拿绝技」。\n");

        if((int)me->query_skill("yingzhua-shou",1) < 180 ) 
             return notify_fail("你的鹰抓功等级不够，不会使用「擒拿绝技」。\n");

		if(target->is_busy() ) 
             return notify_fail("对方自顾不暇，又何必去擒拿他？\n");
        if( me->query_temp("weapon"))
                return notify_fail("你先放下手中的武器再说吧？！\n");     


        if((int)me->query("neili") < 1500)
             return notify_fail("你的内力不够用来「擒拿绝技」。\n");

        if((int)me->query("jingli") < 500)
             return notify_fail("你的精力不够用来「擒拿绝技」。\n");
      
        message_vision(HIW"\n$N忽然手臂暴涨，擒、拿、指、戳，宛如鹰的爪子般的，变化多端，向$n的周身抓去！\n" NOR, me, target);

 
        if (random(me->query_str(1)) > target->query_dex(1)/2 
			||random(me->query("combat_exp"))>target->query("combat_exp")/2)
		{
              message_vision(HIY"\n$n闪身急避，怎料$N双手犹如附骨之蛆一般，一时不察，脉门要穴已被$N死死抓住。\n"NOR, me, target);
			  message_vision(RED"\n$n一阵剧痛传来，这鹰爪功着实厉害，竟然将$n的骨头都捏碎了。\n"NOR, me, target);
			  target->receive_damage("qi",2000+random(1000),me);
			  target->receive_wound("qi",500+random(500),me);
			  
              target->add_busy(2+random(3));		   
         }
           else{
              message_vision( HIM"\n$n早已听说鹰爪手的厉害之处，心中已有防备，猛地里身形急转，后退数步。\n"NOR, me, target);
              me->start_busy(1);
              me->start_perform(2,"「擒拿绝技」");
           }
           return 1;

}

int help(object me)
{
        write(HIC"\n鹰爪手法之「擒拿绝技」："NOR"\n\n");
        write(@HELP 
	鹰爪手绝技，是明教护教法白眉鹰王殷天正的成名绝技，
	是将擒拿格斗与近身搏击术融合在一起的绝技。在双方
	对战过程中，既可以通过贴身擒拿术，点中对方的穴道，
	又可以通过绝杀技一招致敌。
	
	指令:perform hand.qinna
				
要求：
	当前内力 1500 以上；
	当前精力 500 以上；
	鹰爪手功等级 180 以上；
	基本内功等级 180 以上；
	基本手法等级 180 以上；
	激发手法为鹰爪手；
	激发招架为鹰爪手；
	激发内功为圣火神功。
HELP
        );
        return 1;
}