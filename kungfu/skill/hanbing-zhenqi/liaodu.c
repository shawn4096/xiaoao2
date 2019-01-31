// liaodu.c, 疗毒
// Lklv add help at 2001.10.06

#include <ansi.h>
inherit F_SSERVER;

string exert_name(){ return HIY"疗毒诀"NOR; }

int exert(object me,object target)
{
	string msg;
	if( me->is_fighting())
		return notify_fail("战斗中运功？找死吗？\n");

	if ( me->query_skill("hanbing-zhenqi", 1) < 250)
		return notify_fail("你的寒冰真气修为还不够。\n");
	if ( me->query_skill("medicine", 1) < 100)
		return notify_fail("你的本草术理修为还不够。\n");

	if ( me->query("neili") < 1000 )
		return notify_fail("你的真气不够。\n");

	if ( !target) target = me;

	if ( target != me ) {
		if (!target) return notify_fail("你要为谁治疗寒冰毒。\n");

		if ( !target->query_condition("cold_poison"))
			return notify_fail("你只能为"+target->name(1)+"治疗寒冰毒。\n");
		if ( target->is_busy() || target->is_fighting())
			return notify_fail(target->name(1)+"正忙着呢。\n");
		msg = HIB"$N坐在地上，深深的吸了一口气，开始为$n运功疗毒。\n" NOR;
		message_vision(msg, me, target);
		target->clear_condition("cold_poison");
		target->add_busy(2+random(3));
	}
	else {
		if(!me->query_condition("cold_poison"))
			return notify_fail("你只能治疗寒冰毒。\n");
		msg = HIB"$N坐在地上，深深的吸了一口气，开始运功疗毒。\n"NOR;
		message_vision(msg, me);
		me->clear_condition("cold_poison");
	}
	me->add("neili", -500);
	me->start_busy(2 + random(3));
	return 1;
}

int help(object me)
{
	write("\n寒冰真气之「疗毒诀」：\n\n");
        write(@HELP
	治疗寒冰毒的不二法门，寒冰真气乃是至阴至寒的一种
	内功法门，非掌门核心弟子不得传授。将这门内功加载
	在武技上后，使得对方有不经意间中了寒毒。凭此技可
	以化解。
	
	指令：yun liaodu

要求：
	寒冰真气  250  级以上；
	本草术理  100  级以上；
	当前内力  1000 以上。

HELP
        );
        return 1;
}
