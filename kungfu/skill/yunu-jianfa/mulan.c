//  mulan.c 木兰回射 
//Created by sohu@xojh 2014/9

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return HBRED"木兰回射"NOR;}

int perform(object me,object target)
{
    object weapon;
    int i;
    i = me->query_skill("yunu-jianfa", 1);
    if( !target ) target = offensive_target(me);
     
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("「木兰回射」只能对战斗中的对手使用。\n");

    if((int)me->query_skill("force", 1) < 150 )
                return notify_fail("你的基本内功不够娴熟，无法支持「木兰回射」。\n");

    if( (int)me->query_skill("yunu-jianfa", 1) < 150 ) 
                return notify_fail("你的玉女剑法还未练成，不能使用「木兰回射」！\n");

    if((int)me->query_skill("sword", 1) < 150 )
                return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用「木兰回射」。\n");

    if((int)me->query_skill("dodge", 1) < 150 )
                return notify_fail("你的基本轻功不够娴熟，不能使用「木兰回射」。\n");
	if((int)me->query_dex() < 40 )
                return notify_fail("你的后天身法不够，不能使用「木兰回射」。\n");
    if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "yunu-jianfa"
        || me->query_skill_mapped("parry") != "yunu-jianfa")
                return notify_fail("你手里无剑，如何使用「木兰回射」？\n");
                
    if((int)me->query("max_neili") < 1200 )
                return notify_fail("你的内力修为不够，不能使用「木兰回射」！\n");

    if((int)me->query("neili") < 500 )
                return notify_fail("你现在真气不足，不能使用「木兰回射」！\n");

    if((int)me->query("jingli") < 300 )
                return notify_fail("你现在太累了，不能使用「木兰回射」！\n");
    if((int)me->query("ynjf/mulan")  )
                return notify_fail("你正在使用「木兰回射」！\n");
      
    message_vision(HIR"\n$N纵身前跃，奔跑之际，将手中的"+weapon->query("name")+HIR"突然挺剑向背后刺出攻向$n的胸口！\n"NOR, me,target);
    message_vision(HIR"\n正是玉女剑法中一招"HIC"「木兰回射」"HIR"绝技！\n"NOR, me,target);
        
    me->add("neili", -100);
    me->add("jingli",-50);
    me->set_temp("ynjf/mulan",1);

  
    if (random(me->query("combat_exp"))>target->query("combat_exp")/2
		|| random(me->query_dex(1))>target->query_dex(1)/2)
    {  
	    message_vision(HIY"\n\n$n正追赶之际，不妨被$N这招「木兰回射」一剑刺中胸口，鲜血迸溅！\n"NOR,me,target);
		if (userp(target))
		{		
			target->receive_damage("qi",3000+random(1000),me);
			target->receive_wound("qi",1000+random(500),me);
		}
		else {
			target->receive_damage("qi",4000+random(2000),me);
			target->receive_wound("qi",2000+random(1000),me);
		}
		target->apply_condition("no_exert",1);
		if (!userp(target)) target->add_busy(3);
		me->add_temp("apply/damage",i/6);
		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if (me->query_skill("yunu-jianfa",1)>200 && me->is_fighting())
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/damage",-i/6);
	            	
    }else
	{
		message_vision(HIC"\n\n$n脚下急忙后退，堪堪躲过此招，吓了一声冷汗。\n"NOR,me,target);
		me->add_busy(1);
	}
	
    me->delete_temp("ynjf/mulan");
    
	me->start_perform(3,"「木兰回射」");
    
	return 1;
}


int help(object me)
{
	write(WHT"\n玉女剑法之"HBRED"「木兰回射」："NOR"\n");
	write(@HELP
	玉女剑法独特绝招，因古墓多为女子，所以玉女剑法
	不已力胜，而是靠剑招精妙凌厉，剑式轻柔灵动致胜
	身形清雅潇洒,姿态飘飘若仙,带著三分飘逸风姿，皓
	腕轻挥。
	木兰回射，在奔跑躲闪之际，从背后出剑，刺中对方

	perform sword.mulan
	
要求：
	当前内力要求 500 以上；
	当前精力要求 300 以上；
	最大内力要求 1200 以上
	玉女剑法等级 150 以上；
	玉女心经等级 150 以上；
	基本内功等级 150 以上；
	基本身法等级 150 以上；
	基本剑法等级 150 以上；
	有效身法等级 40  以上；
	激发剑法为玉女剑法；
	激发招架为玉女剑法；
	手持剑类兵器。
HELP
	);
	return 1;
}