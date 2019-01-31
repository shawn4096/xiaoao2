// By KinGSo@舞林 2006年4月26日 早上
// powerup.c 九阳神功加力
//KinGSo 06.12.29添加help
#include <ansi.h>

inherit F_CLEAN_UP;
string exert_name(){ return HBRED HIC"提升战力"NOR; }

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("你只能用九阳神功来提升自己的战斗力。\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("你的内力不够。\n");

	if ((int)me->query_temp("powerup"))
		return notify_fail("你已经在运功中了。\n");

	skill = me->query_skill("force");
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_vision(HIR "$N" HIR "微一凝神，运起九阳神功，将真气"
		        "凝聚在丹田之中，沿奇经八脉遍布全身！\n" NOR, me);

	me->add_temp("apply/attack", skill / 4);
	me->add_temp("apply/parry", skill / 9);
	me->add_temp("apply/dodge", skill / 9);
       me->add_temp("apply/damage", skill / 4);
	me->set_temp("powerup", 1);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("powerup"))
        {
	        me->add_temp("apply/attack", - (amount  / 4));
	        me->add_temp("apply/parry", - (amount / 9));
	        me->add_temp("apply/dodge", - (amount / 9));
               me->add_temp("apply/damage", - (amount / 4));
	        me->delete_temp("powerup");
	        tell_object(me, "你的九阳神功运行完毕，将内力收回丹田。\n");
        }
}

int help(object me)
{
	write(HBRED HIC"\n九阳神功「提升战力」："NOR"\n");
        write(@HELP
       大大强于一般武功的运功，效果惊人。




	要求：  
                当前内力  1000 以上；
                
                

               
HELP
        );
        return 1;
}


