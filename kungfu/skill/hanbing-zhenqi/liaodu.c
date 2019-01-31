// liaodu.c, �ƶ�
// Lklv add help at 2001.10.06

#include <ansi.h>
inherit F_SSERVER;

string exert_name(){ return HIY"�ƶ���"NOR; }

int exert(object me,object target)
{
	string msg;
	if( me->is_fighting())
		return notify_fail("ս�����˹���������\n");

	if ( me->query_skill("hanbing-zhenqi", 1) < 250)
		return notify_fail("��ĺ���������Ϊ��������\n");
	if ( me->query_skill("medicine", 1) < 100)
		return notify_fail("��ı���������Ϊ��������\n");

	if ( me->query("neili") < 1000 )
		return notify_fail("�������������\n");

	if ( !target) target = me;

	if ( target != me ) {
		if (!target) return notify_fail("��ҪΪ˭���ƺ�������\n");

		if ( !target->query_condition("cold_poison"))
			return notify_fail("��ֻ��Ϊ"+target->name(1)+"���ƺ�������\n");
		if ( target->is_busy() || target->is_fighting())
			return notify_fail(target->name(1)+"��æ���ء�\n");
		msg = HIB"$N���ڵ��ϣ����������һ��������ʼΪ$n�˹��ƶ���\n" NOR;
		message_vision(msg, me, target);
		target->clear_condition("cold_poison");
		target->add_busy(2+random(3));
	}
	else {
		if(!me->query_condition("cold_poison"))
			return notify_fail("��ֻ�����ƺ�������\n");
		msg = HIB"$N���ڵ��ϣ����������һ��������ʼ�˹��ƶ���\n"NOR;
		message_vision(msg, me);
		me->clear_condition("cold_poison");
	}
	me->add("neili", -500);
	me->start_busy(2 + random(3));
	return 1;
}

int help(object me)
{
	write("\n��������֮���ƶ�������\n\n");
        write(@HELP
	���ƺ������Ĳ������ţ�����������������������һ��
	�ڹ����ţ������ź��ĵ��Ӳ��ô��ڡ��������ڹ�����
	���似�Ϻ�ʹ�öԷ��в���������˺�����ƾ�˼���
	�Ի��⡣
	
	ָ�yun liaodu

Ҫ��
	��������  250  �����ϣ�
	��������  100  �����ϣ�
	��ǰ����  1000 ���ϡ�

HELP
        );
        return 1;
}
