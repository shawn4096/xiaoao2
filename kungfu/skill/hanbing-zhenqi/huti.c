// huti.c

#include <ansi.h>

int exert(object me, object target)
{
	int skill;
	string msg;

	if (me->query_temp("hbzq/huti"))
		return notify_fail("���Ѿ���ʹ�á����塹�ˡ�\n");

	if (me->query_skill("hanbing-zhenqi",1) < 350)
		return notify_fail("��ġ����������������������޷�ʩ�á����塹��\n");

	if (me->query("max_neili") < 1000)
		return notify_fail("��������������޷�ʹ�á����塹��\n");

	if (me->query("neili") < 500)
		return notify_fail("��������������޷�ʹ�á����塹��\n");

	me->add("neili", - 350);
	msg = HIB"$NĬ�������������Խ��ԽŨ���������֣��������Լ������˹�������,��\n"NOR;

    //����һ��huti Ч��
	skill = me->query_skill("hanbing-zhenqi",1)/3;
	me->add_temp("apply/dodge", skill);
	me->add_temp("apply/parry", skill);
	me->set_temp("hbzq/huti", skill);

	call_out("remove_effect", 60, me);
	if (me->is_fighting())
		me->start_busy(1);
	me->start_exert(1, "���������");
	message_vision(msg, me);
	return 1;
}

void remove_effect(object me)
{
	int skill;
	if (!me || !me->query_temp("hbzq/huti"))
		return;
	skill = me->query_temp("hbzq/huti");
	me->add_temp("apply/dodge", -skill);
	me->add_temp("apply/parry", -skill);
	me->delete_temp("hbzq/huti");
	if (living(me) && ! me->is_ghost())
		message_vision(HIW"$N����ĺ���ɢ�������������������𵽱����������ˡ�\n"NOR,me);
}

string exert_name()
{
	return HBBLU+HIW"�����"NOR;
}

int help(object me)
{
	write("\n��������֮�����������\n\n"NOR);
	write(@HELP
	������������������ɽ���ɵ������似���뵱����������������
	��������̽���������һս���Ժ������������������еĽ�����
	��ɧһʱ������������ɽ�ɵ��似��Ч�����ѡ�350��С�ɡ�450
	�ٷɣ�550��⿪�����������أ��������������ͷš�
	
	ָ�yun huti

Ҫ��
	���������ȼ� 350 ���ϣ�
	����������� 1000 ���ϣ�
	��ǰ�������� 500 ���ϡ�
	�����ڹ�Ϊ����������
HELP
	);
	return 1;
}
