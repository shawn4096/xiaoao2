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
		return notify_fail("������ϸ������ҩ���ܵ�ʱ��ͻȻ���ú���ȱ����Щʲô������\n");
	}
	return 1;
}
