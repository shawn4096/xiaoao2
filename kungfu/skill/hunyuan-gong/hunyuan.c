// powerup.c ��Ԫ��

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ���û�Ԫ���������Լ���ս������\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("�������������\n");
		if ((int)me->query("max_neili") < 1500)
                return notify_fail("����������������\n");
		if ((int)me->query_skill("force",1) < 120)
                return notify_fail("��Ļ����ڹ��������޷�ʹ�û�Ԫ����\n");
        if ((int)me->query_skill("hunyuan-gong",1) < 120)
                return notify_fail("��Ļ�Ԫ���ȼ��������޷�ʹ�û�Ԫ����\n");

        if (me->query_temp("hy/powerup"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("hunyuan-gong",1);
        me->add("neili", -100);
        me->receive_damage("qi", 0);
        message_combatd(HIR "$N" HIR "΢һ���������Ԫ����ȫ������"
                        "����,��̬������\n" NOR, me);

        me->add_temp("apply/attack", skill / 3);
		me->add_temp("apply/damage", skill / 6);
        me->add_temp("apply/defense", skill / 3);
        me->set_temp("powerup", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 3 :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("powerup"), 1)
        {
                me->add_temp("apply/attack", -amount);
				me->add_temp("apply/damage", -amount / 2);
                me->add_temp("apply/defense", -amount);
                me->delete_temp("powerup");
                tell_object(me, "��Ļ�Ԫ��������ϣ��������ջص��\n");
        }
}
string perform_name(){ return HIR"����Ԫ����"NOR; }
int help(object me)
{
         write(MAG"\n��Ԫ��"+HIR"����Ԫ����"NOR"\n");
        write(@HELP
	��Ԫ�����ǻ�Ԫ�����ֳ����ĳ�������������ǿ������������Ǵ������
	�似���к������������й��߻�������Ϊ�����������ȫ����㣬������
	��Ԫ���ĵ���������
	Ҫ��
		�����ڹ���  120
		��Ԫ���ȼ���120
		����������  1000
		���������  1500

HELP
        );
        return 1;
}