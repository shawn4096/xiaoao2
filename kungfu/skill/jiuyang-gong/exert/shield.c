// By KinGSo@���� 2006��4��26�� ����
// shield.c ����������
//By kingso 06.12.29����help
#include <ansi.h>
string exert_name(){ return HBRED HIB"��������"NOR; }
inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ���þ������������Լ��ķ�������\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("jiuyang-gong", 1) < 40)
                return notify_fail("��ľ����񹦵ȼ�������\n");

        if ((int)me->query_temp("shield"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force")+ me->query_skill("parry") + me->query_skill("dodge");
        me->add("neili", -100);
        me->receive_damage("qi", 0);

        message_vision(HIR "$N" HIR "Ĭ������񹦵Ŀھ�����"
                            "ǿ����ǿ������ɽ�ԡ����������ᣬ"
                            "�����մ󽭡���\nɲ�Ǽ�ֻ��$N" 
                        HIR "ȫ����ʱ���ֳ�һ����͵ľ�������$P"
                        HIR "ȫȫ���֡�\n" NOR, me);

        me->add_temp("apply/armor", skill / 2);
        me->set_temp("shield", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 2 :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("shield"))
        {
                me->add_temp("apply/armor", -amount);
                me->delete_temp("shield");
                tell_object(me, "��ľ�����������ϣ��������ջص��\n");
        }
}

int help(object me)
{
	write(HBRED HIB"\n�����񹦡�������������"NOR"\n");
        write(@HELP
       ǿ��֮���Ļ���������Ч��ǿ��




	Ҫ��  
                ��ǰ����  1000 ���ϣ�
               
                

               
HELP
        );
        return 1;
}

