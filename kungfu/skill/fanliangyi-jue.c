//liangyi-jue
//by sohu@xojh

inherit SKILL;
void init();

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
	/*if(me->query_int() < 60)
		return notify_fail("�����Ǿ����Ǽ������֮�£������Ե���60���ƺ�̫����������Щ��\n");
    if((int)me->query("shen") < -200000 )
		return notify_fail("��ɱ�����飬����������ƽϢ����ͷħ������ֻ�ѧϰ�����ķ���\n");*/

	if((int)me->query_skill("fanliangyi-jue", 1) > 200 )
		return notify_fail("�����Ǿ�ֻ����ѧϰ������̶��ˡ�\n");
	

	return 1;
}
int practice_skill(object me)
{
	return notify_fail("�����Ǿ�ֻ�ܿ�������ɽ���ϴ����(ask)����ߡ�\n");
}
