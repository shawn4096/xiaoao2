// huti.c

#include <ansi.h>

int exert(object me, object target)
{
	int skill;
	string msg;

	if (me->query_temp("hbzq/huti"))
		return notify_fail("你已经在使用「护体」了。\n");

	if (me->query_skill("hanbing-zhenqi",1) < 350)
		return notify_fail("你的「寒冰真气」功力不够，无法施用「护体」。\n");

	if (me->query("max_neili") < 1000)
		return notify_fail("你的内力不够，无法使用「护体」。\n");

	if (me->query("neili") < 500)
		return notify_fail("你的真气不够，无法使用「护体」。\n");

	me->add("neili", - 350);
	msg = HIB"$N默念寒冰决，周身寒气越来越浓，若隐若现，隐隐把自己整个人裹了起来,！\n"NOR;

    //增加一点huti 效果
	skill = me->query_skill("hanbing-zhenqi",1)/3;
	me->add_temp("apply/dodge", skill);
	me->add_temp("apply/parry", skill);
	me->set_temp("hbzq/huti", skill);

	call_out("remove_effect", 60, me);
	if (me->is_fighting())
		me->start_busy(1);
	me->start_exert(1, "「护体诀」");
	message_vision(msg, me);
	return 1;
}

void remove_effect(object me)
{
	int skill;
	if (!me || !me->query_temp("hbzq/huti"))
		return;
	skill = me->query_temp("hbzq/huti");
	me->add_temp("apply/dodge", -skill);
	me->add_temp("apply/parry", -skill);
	me->delete_temp("hbzq/huti");
	if (living(me) && ! me->is_ghost())
		message_vision(HIW"$N周身的寒气散尽，寒冰真气不再能起到保护的作用了。\n"NOR,me);
}

string exert_name()
{
	return HBBLU+HIW"护体诀"NOR;
}

int help(object me)
{
	write("\n寒冰真气之「护体诀」：\n\n"NOR);
	write(@HELP
	寒冰真气乃是五岳嵩山剑派的镇派武技，想当初左盟主在少林寺
	与日月神教教主任我行一战，以寒冰真气击退了任我行的进攻，
	名骚一时。若辅助以嵩山派的武技，效果更佳。350后小飞。450
	再飞，550后解开寒冰真气奥秘，寒冰真气威力释放。
	
	指令：yun huti

要求：
	寒冰真气等级 350 以上；
	最大内力需求 1000 以上；
	当前内力需求 500 以上。
	激发内功为寒冰真气；
HELP
	);
	return 1;
}
