//liangyi-jue
//by sohu@xojh

inherit SKILL;
void init();

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
	/*if(me->query_int() < 60)
		return notify_fail("反两仪决乃是极其风雅之事，你悟性低于60，似乎太过于俗气了些。\n");
    if((int)me->query("shen") < -200000 )
		return notify_fail("你杀人如麻，倘若不能先平息了心头魔念，哪里又会学习两仪心法？\n");*/

	if((int)me->query_skill("fanliangyi-jue", 1) > 200 )
		return notify_fail("反两仪诀只能再学习到这个程度了。\n");
	

	return 1;
}
int practice_skill(object me)
{
	return notify_fail("反两仪决只能靠跟跟华山二老处请教(ask)来提高。\n");
}
