// By KinGSo@���� 2006��4��26�� ����
// powerup.c �����񹦼���
//KinGSo 06.12.29���help
#include <ansi.h>

inherit F_CLEAN_UP;
string exert_name(){ return HBRED HIC"����ս��"NOR; }

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ���þ������������Լ���ս������\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("�������������\n");

	if ((int)me->query_temp("powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_vision(HIR "$N" HIR "΢һ������������񹦣�������"
		        "�����ڵ���֮�У����澭�����鲼ȫ��\n" NOR, me);

	me->add_temp("apply/attack", skill / 4);
	me->add_temp("apply/parry", skill / 9);
	me->add_temp("apply/dodge", skill / 9);
       me->add_temp("apply/damage", skill / 4);
	me->set_temp("powerup", 1);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("powerup"))
        {
	        me->add_temp("apply/attack", - (amount  / 4));
	        me->add_temp("apply/parry", - (amount / 9));
	        me->add_temp("apply/dodge", - (amount / 9));
               me->add_temp("apply/damage", - (amount / 4));
	        me->delete_temp("powerup");
	        tell_object(me, "��ľ�����������ϣ��������ջص��\n");
        }
}

int help(object me)
{
	write(HBRED HIC"\n�����񹦡�����ս������"NOR"\n");
        write(@HELP
       ���ǿ��һ���书���˹���Ч�����ˡ�




	Ҫ��  
                ��ǰ����  1000 ���ϣ�
                
                

               
HELP
        );
        return 1;
}


