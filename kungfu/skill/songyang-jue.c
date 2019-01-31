// songyan-jue.c 嵩山派重要的辅助选项
// 初级设定200，参悟寒冰真气后，可以突破到220


inherit SKILL;
void init();

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
	if(me->query_int() < 32)
		return notify_fail("五岳之首在嵩山，你似乎太过于俗气了些。\n");
    if((int)me->query("shen") > -10000 )
		return notify_fail("嵩山剑讲究的就是心狠手辣-100k，你如此面善，哪里又会有心思来融会贯通心法？\n");
	if((int)me->query_skill("songyang-jue", 1) >= 200 && !me->query("quest/ss/hbzq/pass"))
		return notify_fail("你不能再学习嵩阳诀的奥义了。\n");
	if((int)me->query_skill("songyang-jue", 1) >= 220 )
		return notify_fail("你已经融汇贯通嵩阳诀奥义，无法再进步了。\n");
	return 1;
}

int practice_skill(object me)
{
	return notify_fail("嵩阳诀只能靠读书或领悟来提高。\n");
}
