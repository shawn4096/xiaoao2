// huanmo-wubu ��ħ�貽

inherit SKILL;

string *dodge_msg = ({
"$nһʽ����Ӱ��涡�����Žż�����ҽ���շ�����������������ˮ�㻬�����ࡣ\n",
"$nһʽ����Ӱ���ء���������ת��˫�Űϵض��𣬶�ʱ������$N���������ơ�\n",
"$nһʽ������˭��֪��������˫������߳����ţ���ʱ�䵽$N���Ͽա�\n",
"$nһʽ����ħ�ȶ�����ͻȻ������ǰ�ˣ���������ĳ���$N����$N������롣\n",
"$nһʽ����������������������ȫ��Χ��$N������ת����$N��æ���ң�$n���䵽����Զ�ĵط���\n",
"$nһʽ������������˫����յ�أ������ݷ����У���$Nͷ����Ծ������\n",
"$nһʽ����ħ��ͷ����˫�����������ƣ�����������Ʈ����ʱ����$N���������ơ�\n",
"$nһʽ���˼����ġ������������ݰ㼱ת�������γ�һ�������У���$N������䡣\n",
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me)
{
	if ( me->query_skill("tianmo-gong", 1) < 20)
		return notify_fail("�����ħ���ȼ�̫���ˡ�\n");
	return 1;
}

string query_dodge_msg()
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( (int)me->query("jingli") < 30 )
		return notify_fail("�������̫���ˣ���������ħ�貽��\n");
	me->receive_damage("jingli", random(30));
	return 1;
}
