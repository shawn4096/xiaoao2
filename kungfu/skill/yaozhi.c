//yaozhi.c
//yaozhi.c  ҩֲ��
//δ�������ҩ�������置���ж�������
//��ҩ zhiyao
//���� dandao
//���� poison
//ҽ�� medicine
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
		return notify_fail("������ϸ����ҩֲ�����ܵ�ʱ��ͻȻ���ú���ȱ����Щʲô������\n");
	}
	return 1;
}