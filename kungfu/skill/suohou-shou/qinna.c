// By sohu@xojh 锁喉擒拿手

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
          || environment(target)!= environment(me))return notify_fail("锁喉擒拿手只能在战斗中使用。\n");
          
		  weapon = me->query_temp("weapon");
		if (weapon)
			return notify_fail("「锁喉擒拿手」空手才能使用。\n");
		if (userp(me) 
			&& ! me->query("quest/gb/shs/qinna/pass"))
                return notify_fail("锁喉绝技需向马大元请教，你现在还不会使用「锁喉」这一招！\n");
        if( me->query_skill_mapped("parry") != "suohou-shou")
                return notify_fail("「锁喉擒拿手」必须在用锁喉掌法激发招架的情况下才能使用。\n");
        if( me->query_skill_prepared("hand") != "suohou-shou" )
                return notify_fail("你的手法不对，根本不能发挥出「锁喉擒拿手」的优势。\n");  

        if((int)me->query_skill("force", 1)  < 250 )
             return notify_fail("你的基本内功等级还不够，使不出「锁喉擒拿手」。\n");

        if((int)me->query_skill("suohou-shou",1) < 250 ) 
             return notify_fail("你的锁喉掌法等级不够，不会使用「锁喉擒拿手」。\n");


        if( me->query_temp("weapon"))
                return notify_fail("你先放下手中的武器再说吧？！\n");     

		if( target->is_busy())
                return notify_fail("对方自顾不暇，放手进攻吧！\n");
        if((int)me->query("neili") < 1500)
             return notify_fail("你的内力不够用来「锁喉擒拿手」。\n");

        if((int)me->query("jingli") < 500)
             return notify_fail("你的精力不够用来「锁喉擒拿手」。\n");
      
        message_vision(HIW"\n$N忽然手臂暴涨，擒、拿、指、戳，时而为鹰爪时而为虎抓，变化多端，向$n的周身抓去！\n" NOR, me, target);

        
        if (random(me->query_str(1)) > target->query_dex(1)/2 
			||random(me->query("combat_exp"))>target->query("combat_exp")/2){
              message_vision(HIC"\n$n闪身急避，怎料$N双手犹如附骨之蛆一般，一时不察，脉门要穴已被$N死死抓住。\n"NOR, me, target);
              target->add_busy(1+random(3));
		      //target->apply_condition("no_perform",1+random(1));
              //me->start_perform(5,"「锁喉擒拿手」");
           }
           else{
              message_vision( HIM"\n$n早已听说锁喉擒拿手的厉害之处，心中已有防备，猛地里身形急转，后退数步。\n"NOR, me, target);
              me->start_busy(1);
              me->start_perform(2,"「擒拿绝技」");
           }
		  me->add("neili",-250);
		  me->add("jingli",-200);
	
           return 1;

}

int help(object me)
{
        write(HIC"\n锁喉擒拿手法之「擒拿绝技」："NOR"\n\n");
        write(@HELP 
	锁喉擒拿手绝技，是丐帮马副帮主的成名绝技，是将锁喉
	与擒拿融合在一起的绝技。在双方对战过程中，既可以通
	过贴身擒拿术，点中对方的穴道或擒拿住对方的要害部位
	制敌，极端厉害，250后小飞。
	注意：命中和臂力以及战斗经验有关,需向马大元请教

	指令：perform hand.qinna
			
要求：  				
	当前内力 1500 以上；
	当前精力 500 以上；
	锁喉擒拿等级 250 以上；
	基本内功等级 250 以上；
	基本手法等级 250 以上；
	激发手法为锁喉擒拿手；
	激发招架为锁喉擒拿手；
	且空手
HELP
        );
        return 1;
}