// songyan-jue.c ��ɽ����Ҫ�ĸ���ѡ��
// �����趨200�����򺮱������󣬿���ͻ�Ƶ�220


inherit SKILL;
void init();

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
	if(me->query_int() < 32)
		return notify_fail("����֮������ɽ�����ƺ�̫����������Щ��\n");
    if((int)me->query("shen") > -10000 )
		return notify_fail("��ɽ�������ľ����ĺ�����-100k����������ƣ������ֻ�����˼���ڻ��ͨ�ķ���\n");
	if((int)me->query_skill("songyang-jue", 1) >= 200 && !me->query("quest/ss/hbzq/pass"))
		return notify_fail("�㲻����ѧϰ�������İ����ˡ�\n");
	if((int)me->query_skill("songyang-jue", 1) >= 220 )
		return notify_fail("���Ѿ��ڻ��ͨ���������壬�޷��ٽ����ˡ�\n");
	return 1;
}

int practice_skill(object me)
{
	return notify_fail("������ֻ�ܿ��������������ߡ�\n");
}
