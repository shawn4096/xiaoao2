// zhiyao.c

inherit SKILL;

string type() { return "knowledge"; }
string type2() { return "worker"; }

void skill_improved(object me)
{
}

int valid_learn(object me)
{
	int lvl;
	
	if(me->query_skill("zhiyao",1)>220)
	{
		lvl = me->query("forging2/zhiyao");
		if(!lvl || lvl < (me->query_skill("zhiyao",1)-220)/10 )
		return notify_fail("你在仔细领悟制药技能的时候突然觉得好象缺少了些什么东西。\n");
	}
	return 1;
}
