// wuxue.c 迅雷剑 perform 一剑无血
// cck 13/6/97
//edit by sohu
//源自冯锡范招式
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int remove_wuxue(object target);

int perform(object me, object target)
{
        object weapon;
        string msg;
        string msg1;
	
		int skill,damage;
		skill=me->query_skill("xunlei-jian",1);
		damage=skill+me->query_skill("xuantian-wuji",1)+me->query_skill("jingmai-xue",1);
		damage=damage*3+random(damage);

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「一剑无血」只能在战斗中对对手使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if( (int)me->query_skill("xunlei-jian", 1) < 350 )
                return notify_fail("你的迅雷剑法不够娴熟，不会使用「一剑无血」。\n");

		if(!me->query("quest/kl/xlj/wuxue/pass"))
                return notify_fail("你尚未学会「一剑无血」绝技。\n");

		if( me->query_skill_mapped("sword")!="xunlei-jian" )
			//||me->query_skill_mapped("parry")!="xunlei-jian" 
                return notify_fail("你没能激发迅雷剑，不能使用「一剑无血」。\n");
		if( (int)me->query_con() < 50 )
                return notify_fail("「一剑无血」需要高根骨，你的后天根骨不够50，不能使用「一剑无血」。\n");

        if( (int)me->query("neili", 1) < 1500 )
                return notify_fail("你现在内力太弱，不能使用「一剑无血」。\n");
        if( (int)me->query("jingli", 1) < 1000 )
                return notify_fail("你现在精力太弱，不能使用「一剑无血」。\n");         
             
		if( target->query_temp("xlj/wuxue") )
                return notify_fail("对方已经中了你的「一剑无血」招式。\n");
        msg = HIC "$N内力运转如意，力透剑尖，一阵颤动，剑势顿时笼罩$n的周身大穴。使出迅雷剑"HIR"「一剑无血」"HIC"的绝技！\n" NOR;
//        msg1 = BBLU+HIY "$N长啸一声，剑锋回指,姿势怪异但却潇洒无比。\n" NOR;
        message_vision(msg, me, target);
		if (random(me->query_skill("sword",1))>target->query_skill("parry",1)/2
		||random(me->query_skill("force",1))>target->query_skill("force",1)/2)
		{
			message_vision(HIR "$n一时大意，为$N剑尖透出的气劲锁住经脉要穴，顿时气机不畅！\n" NOR,me,target);
			if (!random(3))
			{
				target->apply_condition("no_perform",1);
			}else target->apply_condition("no_exert",1);

			target->add_busy(2+random(2));
			target->apply_condition("neishang",10+random(4));
			if (random(me->query_con(1))>target->query_con(1)/3)
			{
				message_vision(RED "$N这一剑对$n造成极大的暗伤，外表丝毫看不出来，但力透经脉，将$n重创！\n" NOR,me,target);
				target->receive_wound("qi",damage,me);
				//target->receive_damage("qi",damage*2,me);
				if (wizardp(me))
					write("damage="+damage);
			}
			me->add_temp("apply/sword",skill/3);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			me->add_temp("apply/sword",-skill/3);
			target->set_temp("xlj/wuxue",skill);
			if (objectp(target))
				call_out("remove_wuxue",10-(int)skill/150,target);

		}else me->start_busy(1);	
		
        me->add("neili", -250);
        me->add("jingli", -150);

        return 1;
}
int remove_wuxue(object target)
{
	if (!objectp(target)) return 1;
		target->delete_temp("xlj/wuxue");	
	return 1;
}

string perform_name() {return RED"一剑无血"NOR;}

int help(object me)
{
    write(HIY"\n迅雷剑法「一剑无血」："NOR"\n");
    write(@HELP
	一剑无血乃是昆仑派高手冯锡范独门绝技，依靠强大的内功气劲
	运使于剑法之中，力透剑间，以气机锁定对方经脉，外表看不出
	任何伤害，但经脉却会受到重创，虽不至于死，但也半残，端的
	是狠辣的绝招，此招需要跟冯锡范请教。
	此招命中于基本内功修为，基本剑法修为有关，如果根骨不低会
	随机出现对对方凶狠的杀招。功力越是深厚，出招频次越高。

	指令：perform wuxue
	
要求：
	玄天无极等级 350 级以上；
	迅雷剑法等级 350 级以上；
	基本剑法等级 350 级以上，
	当前内力要求 1500 以上，
	当前精力要求 1000 以上，
	当前有效根骨 50 以上；
	激发剑法为迅雷剑；
	内功不限；
	需手持剑类武器。    

HELP
	);
	return 1;
}

