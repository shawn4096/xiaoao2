//liangyi-jue
//by sohu@xojh

inherit SKILL;
void init();

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
	if(me->query_int() < 60)
		return notify_fail("正两仪决乃是极其风雅之事，你悟性低于60，似乎太过于俗气了些。\n");
    if((int)me->query("shen") < -200000 )
		return notify_fail("你杀人如麻，倘若不能先平息了心头魔念，哪里又会学习两仪心法？\n");
	if((int)me->query_skill("liangyi-jue", 1) >= 200 && !me->query("quest/kl/lyj/liangyi/pass"))
		return notify_fail("你因不知道反两仪的原理，正两仪只能再学习到这个程度了。\n");
	if((int)me->query_skill("liangyi-jue", 1) >= 220)
		return notify_fail("你的正两仪只能再学习到这个程度了。\n");
	//if(me->query("family/master_name") != "何足道" ||me->query("family/master_id") != "he zudao"  )
		//return notify_fail("你的师傅不是何足道，无法修习两仪诀？\n");


	return 1;
}

int practice_skill(object me)
{
	return notify_fail("两仪决只能靠学(learn)来提高。\n");
}
