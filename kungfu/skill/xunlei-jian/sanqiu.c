// sanqiu.c 迅雷剑 perform 一日三秋
// cck 13/6/97
//edit by sohu
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        string msg;
        string msg1;
	
		int skill;
		skill=me->query_skill("xunlei-jian",1);

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「一日三秋」只能在战斗中对对手使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if( (int)me->query_skill("xunlei-jian", 1) < 180 )
                return notify_fail("你的迅雷剑法不够娴熟，不会使用「一日三秋」。\n");
        if( (int)me->query_skill("sword", 1) < 180 )
                return notify_fail("你的基本剑法不够娴熟，不会使用「一日三秋」。\n");

        if( (int)me->query_skill("force", 1) < 180 )
                return notify_fail("你的基本内功等级不够，不能使用「一日三秋」。\n");
		if( me->query_skill_mapped("sword")!="xunlei-jian" )
			//||me->query_skill_mapped("parry")!="xunlei-jian" )
                return notify_fail("你没能激发迅雷剑，不能使用「一日三秋」。\n");
		if( (int)me->query_str() < 30 )
                return notify_fail("「一日三秋」需要高臂力，你的后天膂力不够30，不能使用「一日三秋」。\n");

        if( (int)me->query("neili", 1) < 250 )
                return notify_fail("你现在内力太弱，不能使用「一日三秋」。\n");
        if( (int)me->query("jingli", 1) < 200 )
                return notify_fail("你现在精力太弱，不能使用「一日三秋」。\n");         
             
		if( me->query_temp("xlj/sanqiu") )
                return notify_fail("你正在使用「一日三秋」。\n");
        msg = BBLU+HIC "$N突然欺身而进，每一剑均都化作绚烂剑光，宛如骄阳，而后以迅雷不及掩耳之势奋力向$n连续击出三剑。\n" NOR;
        msg1 = BBLU+HIY "$N长啸一声，剑锋回指,姿势怪异但却潇洒无比。\n" NOR;

        message_vision(msg, me, target);
	/*	if (!userp(target)) {
			skill=skill+me->query_skill("xuantian-wuji",1)/6;
			me->add_temp("apply/sword",skill/4);
			me->add_temp("apply/damage",skill/5);
			target->start_busy(1);
			//me->set_temp("xlj/sq",1);
		}*/
		me->add_temp("apply/attack",skill/4);
		//me->add_temp("apply/sword",skill/5);
		me->add_temp("apply/damage",skill/5);
		me->set_temp("xlj/sanqiu",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
//		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

		me->add_temp("apply/attack",-skill/4);
		//me->add_temp("apply/sword",-skill/5);
		me->add_temp("apply/damage",-skill/5);
        me->add("neili", -150);

        message_vision(msg1, me, target);
		me->start_perform(3,"「一日三秋」");   
		me->delete_temp("xlj/sanqiu");
		me->delete_temp("xlj/sq");
        return 1;
}

string perform_name() {return HIC"一日三秋"NOR;}

int help(object me)
{
    write(HIY"\n迅雷剑法「一日三秋」："NOR"\n");
    write(@HELP
	迅雷剑乃是昆仑的初级剑法，由何足道观悟天地变化所得。
	因昆仑山天高地寒，雷暴天气颇多，由此领悟剑法的快捷
	本意。
	一日三秋，是感慨时日如白驹过隙，匆匆而过所悟，迅捷
	三招快速攻击对方。乃是新手必备武技。
    
	指令：perform sanqiu
	
要求：
	迅雷剑法等级 180 级以上；
	基本剑法等级 180 级以上，
	基本内功等级 180 级以上，
	当前内力要求 250 以上，
	当前精力要求 200 以上，
	当前有效臂力 30 以上；
	激发剑法为迅雷剑法；
	内功不限；
	需手持剑类武器。    

HELP
	);
	return 1;
}

