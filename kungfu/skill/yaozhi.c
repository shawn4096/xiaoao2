//yaozhi.c
//yaozhi.c  药植术
//未来大的种药基地在苗疆，有毒王处理
//制药 zhiyao
//炼丹 dandao
//练毒 poison
//医疗 medicine
inherit SKILL;

string type() { return "knowledge"; }
string type2() { return "worker"; }

void skill_improved(object me)
{
}

int valid_learn(object me)
{
	int lvl;
	
	if(me->query_skill("yaozhi",1)>220)
	{
		lvl = me->query("forging2/yaozhi");
		if(!lvl || lvl < (me->query_skill("yaozhi",1)-220)/10 )
		return notify_fail("你在仔细领悟药植术技能的时候突然觉得好象缺少了些什么东西。\n");
	}
	return 1;
}
