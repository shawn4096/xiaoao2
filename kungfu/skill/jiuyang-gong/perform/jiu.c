// By KinGSo@���� 2006��4��25�� ����

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

#define JIU "��" HIR "���ػ���" NOR "��"
string perform_name(){ return HBRED "���ػ���"NOR; }

 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
 
        if( !target ) target = offensive_target(me);

        if( !objectp(target) 
        || !target->is_character() 
        || !me->is_fighting(target) 
        || !living(target))
                return notify_fail(JIU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(JIU "ֻ�ܿ���ʩչ��\n");
                
        if (me->query("max_neili") < 6000)
                return notify_fail("�����������Ϊ�����������޷�ʹ��" JIU "��\n");

        if (me->query_skill("jiuyang-gong", 1) < 350)
                return notify_fail("��ľ����񹦻�������죬����ʩչ" JIU "��\n");

        if (me->query_skill_mapped("cuff") != "jiuyang-gong")
                return notify_fail("������û�м���������Ϊȭ�ţ�����ʩչ" JIU "��\n");

        if (me->query_skill_mapped("force") != "jiuyang-gong")
                return notify_fail("������û�м���������Ϊ�ڹ�������ʩչ" JIU "��\n");

        if (me->query_skill_prepared("cuff") != "jiuyang-gong")
                return notify_fail("������û��׼��ʹ�þ����񹦣�����ʩչ" JIU "��\n");

        if ((int)me->query("neili") < 2000)
                return notify_fail("��������������޷�����" JIU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "���һ������ʱһ�ɺƵ��ޱȵ����������ڱŷ���˫��"
              "��Ȼ��������$n" HIR "�������ȥ��\n" NOR;

        ap = me->query_skill("cuff") + (me->query("con") * 10);
        dp = target->query_skill("parry") + (target->query("con") * 10);

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 15;
                msg += HIR "$n" HIR "ֻ����Χ���������ޱȣ��ּ�����������"
                       "�Լ�Ϯ�����ٸ�ͷ��Ŀѣ����֪����εֵ���\n" NOR;
        } else
        {
                msg += HIY "$n" HIY "ֻ��$N" HIY "�����������Լ�Ϯ������"
                       "æǿ������ǿ�ֵ���\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        me->add_temp("apply/damage", count);
        me->add_temp("apply/attack", count);

        me->add("neili", -2000);

        for (i = 0; i < 9; i++)
        {
                if (!target) break;
                if ( !me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 3);
        }

        me->start_busy(1 + random(2));
        me->add_temp("apply/damage", -count);
        me->add_temp("apply/attack", -count);     
        me->start_perform(5,"�����ػ�����");
        return 1;
}
int help(object me)
{
	write(HBRED"\n�����񹦡����ػ�������"NOR"\n");
        write(@HELP
       ����һ��������������ֻ������
       ���˻���һ��֮�����ʩչ��ս
       ����ͬʱ�������������������
       �������ţ��˵������Ρ�

	Ҫ��  �������  6000 ���ϣ�
                ��ǰ����  2000 ���ϣ�
                �����񹦵ȼ� 350 ���ϣ�
                �����ڹ�Ϊ�����񹦡�
                ����������Ϊȭ����
                ׼��ʹ�þ����񹦡�
HELP
        );
        return 1;
}

