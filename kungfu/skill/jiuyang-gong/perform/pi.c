// By KinGSo@���� 2006��4��25�� ����
//2006.12.29���Help
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

#define PO "��" HIY "��������" NOR "��"
string perform_name(){ return HBRED HIW"��������"NOR; }


string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(PO "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" PO "��\n");

        if ((int)me->query_skill("jiuyang-gong", 1) < 260)
                return notify_fail("��ľ����񹦲�����죬����ʩչ" PO "��\n");

        if ((int)me->query_skill("force", 1) < 260)
                return notify_fail("����ڹ���������������ʩչ" PO "��\n");

        if ((int)me->query_skill("blade", 1) < 260)
                return notify_fail("��Ļ���������򲻹�������ʩչ" PO "��\n");

        if ((int)me->query("max_neili") < 5500)
                return notify_fail("���������Ϊ���㣬����ʩչ" PO "��\n");

        if (me->query("neili") < 2000)
                return notify_fail("��������������������ʩչ" PO "��\n");

        if (me->query_skill_mapped("blade") != "jiuyang-gong") 
                return notify_fail("��û�м���������Ϊ����������ʩչ" PO "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        message_vision(HBRED HIW "\n$N��Ȼ�������𣬰����һ����Х������ԴԴ������ӿ��" + weapon->name() + ""HBRED" "HIW",ɲ�Ǽ䵶â��Ŀ��������£�����$n��\n"NOR, me,target);

        me->add("neili", -150);
        ap = me->query_skill("blade") + me->query_skill("force", 1);
        dp = target->query_skill("parry") + target->query_skill("force", 1);

        me->start_perform(5,"���������졹");
    me->add("neili", -500);
        me->add_temp("apply/attack",  ap/8);
    //    me->add_temp("apply/damage",  ap/3);
        target->add_temp("apply/armor",  -ap/5);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    
        me->add_temp("apply/attack",  - ap/8);
    //    me->add_temp("apply/damage",  - ap/3);
        target->add_temp("apply/armor",  ap/5);

    me->start_busy(1);
    target->start_busy(1);
    return 1;
}

int help(object me)
{
	write(HBRED HIW"\n�����񹦡��������졹��"NOR"\n");
        write(@HELP
       ������������ʹ��ʱʩչ����
       ���ĵ�â�ɹᴩ���˵ķ���ֱ��
       �������壬������صĴ����

	Ҫ��  �������  5500 ���ϣ�
                ��ǰ����  2000 ���ϣ�
                �����񹦵ȼ� 260 ���ϣ�
                ���������ȼ� 260���ϣ�
                �����ڹ�Ϊ�����񹦡�
                ����������Ϊ������
               
HELP
        );
        return 1;
}


