// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <combat.h>

#define SUO "��" CYN "���տ���" NOR "��"

inherit F_SSERVER;


int perform(object me, object target)
{
        int ap, dp, damage;
        string msg, pmsg;
        string *limbs, limb;



        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(SUO "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(SUO "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("shentuo-zhang", 1) < 100)
                return notify_fail("������ѩɽ�ƻ�򲻹�������ʩչ" SUO "��\n");
        if ((int)me->query_skill("hamagong", 1) < 100)
                return notify_fail("���󡹦��򲻹�������ʩչ" SUO "��\n");
        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("������Ʒ���򲻹�������ʩչ" SUO "��\n");
		if (me->query_skill_mapped("strike") != "shentuo-zhang"
			||me->query_skill_prepared("strike") != "shentuo-zhang")
                return notify_fail("��û�м�������ѩɽ�ƣ�����ʩչ" SUO "��\n");
       if (me->query_skill_mapped("force") != "hamagong")
                return notify_fail("��û�м�����󡹦������ʩչ" SUO "��\n");

        if ((int)me->query("neili", 1) < 500)
                return notify_fail("�����ڵ��������㣬����ʩչ" SUO "��\n");
        if ((int)me->query("jingli", 1) < 500)
                return notify_fail("�����ڵľ������㣬����ʩչ" SUO "��\n");
		if ((int)me->query_str() < 50)
                return notify_fail("��ĺ����������50������ʩչ" SUO "��\n");
        if (!living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "һ����Ц��˫�ŷ�����һʽ"HIW"�����տ��㡹"HIR"����������$nӭ�ϣ�����������\n"
				HIY+"�����ĳ�һ�ƣ�����֮���ŷ���ŭ����ӿ��\n" NOR;
        me->add("neili", -100);

        ap =  me->query_skill("strike",1);
        dp = target->query_skill("parry",1);

        if (ap / 2 + random(ap) > dp
			||random(me->query_str(1))>target->query_str(1)/2)
        {
                damage = me->query_skill("shentuo-zhang",1)*me->query_str(1)/10;               


				target->add("qi",-damage*2,me);
				target->add("eff_qi",-damage,me);
				target->apply_condition("snake_poison",2+random(1));
				target->apply_condition("chanchu_poison",2+random(4));

                msg +=RED "��ʱֻ�������꡹һ�����죬$n"RED "��"
                        "�ؿ��߹Ǿ�Ȼ���˼�����\n" NOR;
                                                   
                //me->start_busy(1);
                me->add("neili", -50);
        } else 
        {
                msg += CYN "����$n" CYN "������$P"
                       CYN "����ͼ�����μ������㿪����һ�ơ�\n"NOR;
                me->start_busy(1);
                me->add("neili", -50);
        }
        message_vision(msg,me,target);
		me->start_busy(1);
		me->start_perfomr(3,"���տ���");
        return 1;
}

string perform_name(){ return CYN"���տ���"NOR; }

int help(object me)
{
	write(HIC"\n����ѩɽ��֮�����տ��㡹��"NOR"\n");
	write(@HELP
	����ѩɽ�����ǰ���ɽׯ����ŷ����Ķ��ž���������
	���ӵ��ۿ�̬֮������ѩɽ����֮����ʩչ�����У���
	���쳣�������ɽׯ�����ߺ͸�󡣬�����Ʒ����̺���
	�����󡶾��
	���տ������������շ������㣬����Է�����ʽ��һ��
	�ƵС�
	
	ָ�perform strike.shentuo

Ҫ��
	��ǰ���������� 500 ���ϣ�
	��ǰ���������� 500 ���ϣ�
	����ѩɽ�Ƶȼ� 100 ���ϣ�
	��󡹦�ȼ�     100 ���ϣ�
	�����Ʒ��ĵȼ� 100 ���ϣ�
	�����������   50  ���ϣ�
	�����Ʒ�Ϊ����ѩɽ�ƣ�
	�����ڹ�Ϊ��󡹦
	�����ұ��ã�
HELP
	);
	return 1;
}

