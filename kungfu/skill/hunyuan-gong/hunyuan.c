// powerup.c 混元劲

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用混元功来提升自己的战斗力。\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("你的真气不够。\n");
		if ((int)me->query("max_neili") < 1500)
                return notify_fail("你的最大内力不够。\n");
		if ((int)me->query_skill("force",1) < 120)
                return notify_fail("你的基本内功不够，无法使用混元劲。\n");
        if ((int)me->query_skill("hunyuan-gong",1) < 120)
                return notify_fail("你的混元功等级不够，无法使用混元劲。\n");

        if (me->query_temp("hy/powerup"))
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("hunyuan-gong",1);
        me->add("neili", -100);
        me->receive_damage("qi", 0);
        message_combatd(HIR "$N" HIR "微一凝神，运起混元功，全身劲气"
                        "暴涨,神态自若。\n" NOR, me);

        me->add_temp("apply/attack", skill / 3);
		me->add_temp("apply/damage", skill / 6);
        me->add_temp("apply/defense", skill / 3);
        me->set_temp("powerup", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 3 :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("powerup"), 1)
        {
                me->add_temp("apply/attack", -amount);
				me->add_temp("apply/damage", -amount / 2);
                me->add_temp("apply/defense", -amount);
                me->delete_temp("powerup");
                tell_object(me, "你的混元功运行完毕，将内力收回丹田。\n");
        }
}
string perform_name(){ return HIR"「混元劲」"NOR; }
int help(object me)
{
         write(MAG"\n混元功"+HIR"「混元劲」"NOR"\n");
        write(@HELP
	混元功乃是混元霹雳手成昆的成名绝技，功力强劲，最大威力是大幅提升
	武技命中和自身防御。中功者浑身会因为劲力反震造成全身红点，这乃是
	混元功的典型特征。
	要求：
		基本内功：  120
		混元功等级：120
		基本内力：  1000
		最大内力：  1500

HELP
        );
        return 1;
}
