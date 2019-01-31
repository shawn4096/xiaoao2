// by darken@SJ
// Lklv add help at 2001.10.06

#include <ansi.h>
inherit F_SSERVER;
string exert_name(){ return HIW"寒冰诀"NOR; }

int exert(object me)
{
	string msg;
	int lv;
	lv = me->query_skill("hanbing-zhenqi",1);

	if (!me->is_fighting())
		return notify_fail("你只能在战斗中使用「寒冰诀」。\n");
	
	if (me->query_temp("ss/hb"))
		return notify_fail("你正在使用「寒冰诀」。\n");

	if ((int)me->query_skill("hanbing-zhenqi",1) < 100)
		return notify_fail("以你目前的内功修为尚无法使用「寒冰诀」。\n");

	if ((int)me->query("max_neili") < 1000)
		return notify_fail("以你目前的内力修为尚无法使用「寒冰诀」。\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("你的内力不够。\n");

	msg = HIW"$N寒冰真气运转不绝，呼吸之间，一道若隐若现的寒气便开始在$N的周身流转。\n"NOR;
	if (me->query_skill("hanbing-zhenqi",1)>550 && me->query("quest/ss/hbzq/pass"))
	{
		msg+=HIB"$N寒冰真气已然大成，运转之际，带动周身寒气袭人，宛如实质,寒冰真气威力大增。\n"NOR;
		me->set_temp("hbzq/hanbing",1);
		me->add_temp("apply/strength",lv/20);
		me->add_temp("apply/attack",lv/5);
		me->add_temp("apply/damage",lv/6);
		me->add_temp("apply/sword",lv/6);
	}
	
	me->set_temp("ss/hb", lv);
	me->add("neili", -250);
	message_vision(msg, me);
	me->add_temp("apply/attack",lv/4);
    me->add_temp("apply/damage",lv/6);
	if ((int)me->query_skill("hanbing-zhenqi",1) < 350)
	{
		me->start_busy(random(2));
		//me->start_exert(1, "「寒冰诀」");
	}
	if ((int)me->query_skill("hanbing-zhenqi",1) < 450)
	{
		//me->start_busy(random(2));
		me->start_exert(1, "「寒冰诀」");
	}

	call_out("remove_effect", lv/5 + random(10), me);
	return 1;
}

void remove_effect(object me)
{
	int lv;
	if (!me || !me->query_temp("ss/hb")) return;

	lv = me->query_temp("ss/hb");
	me->add_temp("apply/attack",-lv/4);
    me->add_temp("apply/damage",-lv/6);
	if (me->query_temp("hbzq/hanbing")&&me->query("quest/ss/hbzq/pass"))
	{
		me->delete_temp("hbzq/hanbing");
		me->add_temp("apply/strength",-lv/20);
		me->add_temp("apply/attack",-lv/5);
		me->add_temp("apply/damage",-lv/6);
		me->add_temp("apply/sword",-lv/6);

	}
	message_vision(HIW"$N长吁一口气，寒冰真气慢了下来，手上的寒气渐渐的散去了。\n"NOR,me);

	me->delete_temp("ss/hb");
	return;
}

int help(object me)
{
	write("\n寒冰真气之「寒冰诀」：\n\n");
        write(@HELP
	寒冰真气乃是五岳嵩山剑派的镇派武技，想当初左盟主在少林寺
	与日月神教教主任我行一战，以寒冰真气击退了任我行的进攻，
	名骚一时。若辅助以嵩山派的武技，效果更佳。350后小飞。450
	再飞，550后解开寒冰真气奥秘，寒冰真气威力释放。
	
	指令：yun hanbing

要求：
	最大内力  1000 以上；
	当前内力  500  以上；
	寒冰真气  100  级以上；
	激发内功为寒冰真气；
HELP
        );
        return 1;
}