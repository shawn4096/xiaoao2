// Flute.c

inherit SKILL;

string type() { return "knowledge"; }
string type2() { return "music"; }


int valid_learn(object me)
{
	if(me->query_int() < 32)
		return notify_fail("�������Ǽ������֮�£����ƺ�̫����������Щ��\n");
        if((int)me->query("shen") < -200000 )

	return notify_fail("��ɱ�����飬����������ƽϢ����ͷħ������ֻ�����˼�о����֣�\n");
	if((int)me->query_skill("art", 1) >= 200 )
		return notify_fail("�㲻����ѧϰ���ּ����ˡ�\n");
	return 1;
}

int practice_skill(object me)
{
	return notify_fail("���ּ���ֻ�ܿ�ѧ(learn )��read ����ߡ�\n");
}
