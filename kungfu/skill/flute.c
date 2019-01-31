// Flute.c

inherit SKILL;

string type() { return "knowledge"; }
string type2() { return "music"; }


int valid_learn(object me)
{
	if(me->query_int() < 32)
		return notify_fail("音乐乃是极其风雅之事，你似乎太过于俗气了些。\n");
        if((int)me->query("shen") < -200000 )

	return notify_fail("你杀人如麻，倘若不能先平息了心头魔念，哪里又会有心思研究音乐？\n");
	if((int)me->query_skill("art", 1) >= 200 )
		return notify_fail("你不能再学习音乐技能了。\n");
	return 1;
}

int practice_skill(object me)
{
	return notify_fail("音乐技能只能靠学(learn )或read 来提高。\n");
}
