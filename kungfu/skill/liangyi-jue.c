//liangyi-jue
//by sohu@xojh

inherit SKILL;
void init();

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
	if(me->query_int() < 60)
		return notify_fail("�����Ǿ����Ǽ������֮�£������Ե���60���ƺ�̫����������Щ��\n");
    if((int)me->query("shen") < -200000 )
		return notify_fail("��ɱ�����飬����������ƽϢ����ͷħ������ֻ�ѧϰ�����ķ���\n");
	if((int)me->query_skill("liangyi-jue", 1) >= 200 && !me->query("quest/kl/lyj/liangyi/pass"))
		return notify_fail("����֪�������ǵ�ԭ��������ֻ����ѧϰ������̶��ˡ�\n");
	if((int)me->query_skill("liangyi-jue", 1) >= 220)
		return notify_fail("���������ֻ����ѧϰ������̶��ˡ�\n");
	//if(me->query("family/master_name") != "�����" ||me->query("family/master_id") != "he zudao"  )
		//return notify_fail("���ʦ�����Ǻ�������޷���ϰ���Ǿ���\n");


	return 1;
}

int practice_skill(object me)
{
	return notify_fail("���Ǿ�ֻ�ܿ�ѧ(learn)����ߡ�\n");
}
