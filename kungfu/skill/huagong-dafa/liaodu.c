// liaodu.c, �ƶ�
// by snowman
// Modified by darken@SJ

#include <ansi.h>

string exert_name(){ return CYN"�ƶ�"NOR; }
int exert(object me)
{
		//���ϸ��ж��ж�
		if(!mapp(me->query_conditions_by_type("poison")))
				return notify_fail("�����û���ж��ɡ�\n");
        if( me->is_fighting() )
                return notify_fail("ս�����˹���������\n");

        if ((int)me->query_skill("huagong-dafa", 1) < 200)
                return notify_fail("��Ļ�������Ϊ��������\n");

        if ((int)me->query_skill("poison", 1) < 200)
                return notify_fail("��Ļ���������Ϊ��������\n");

        if ((int)me->query_skill("medicine", 1) < 120)
                return notify_fail("��ı���������Ϊ��������\n");

        if ((int)me->query_skill("jingmai-xue", 1) < 120)
                return notify_fail("��ľ���ѧ��Ϊ��������\n");

        if( (int)me->query("neili") < 5000 )
                return notify_fail("�������������\n");
      
		//�����ǲ��ǿ��ԼӸ�СС�ķ�Ծ
		if (!me->is_fighting() && (int)me->query_skill("huagong-dafa", 1) > 350)
		{
			message_vision(CYN"$N���ڵ��ϣ����л����󷨣����ڶ���˲��������ɢ��\n" NOR, me);
			me->clear_conditions_by_type("poison");
			me->add("neili", -300);
			me->start_busy(2);
		}
		else if  (!me->is_fighting() && (int)me->query_skill("huagong-dafa", 1) < 350)
		{
			message_vision(CYN"$N���ڵ��ϣ�������һ���һ�󣬿�ʼ�˹��ƶ���\n" NOR, me);
			me->clear_conditions_by_type("poison");
			me->add("neili", -3000);
			me->add("max_neili", -random(2));
			me->start_busy(45-random(me->query("con")));
		}
        return 1;
}

int help(object me)
{
        write(BLU"\n������"CYN"���ƶ�����"NOR"\n");
        write(@HELP
	�����ɵĹ�����Ҫ����<��>�����¹������������������ζ
	���������������������쳣���������������޲�̸��ɫ�䡣
	���ƶ��ǽ��Լ����ж��Ի��⡣

	ָ�yun liaodu
	
Ҫ��:
	������ 200 ����
	����Ҫ�� 200 ����
	�������� 120 ����
	����ѧ�� 120 ����
	��ǰ���� 5000 �㣻
	�����ڹ�Ϊ�����󷨣�

        
HELP
        );
        return 1;
}

