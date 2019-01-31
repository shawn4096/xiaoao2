// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <combat.h>

#define SUO "��" HBWHT+HIR "ѩ��ǧɽ" NOR "��"

inherit F_SSERVER;


int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;
      //  string *limbs, limb;



        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(SUO "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(SUO "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("shentuo-zhang", 1) < 350)
                return notify_fail("������ѩɽ�ƻ�򲻹�������ʩչ" SUO "��\n");
        if ((int)me->query_skill("hamagong", 1) < 350)
                return notify_fail("���󡹦��򲻹�������ʩչ" SUO "��\n");
        if ((int)me->query_skill("strike", 1) < 350)
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
		if ((int)me->query_str() < 60)
                return notify_fail("��ĺ����������60������ʩչ" SUO "��\n");
        if (!living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
		if (!me->query("quest/bt/stxsz/hubei/pass"))
				return notify_fail("����δ�ܵ�����������ѩɽ�Ƶľ��裬����ʩչ" SUO "��\n");
		if (target->is_busy())
		{
			return notify_fail("�Է��Ѿ���æ����֮�У�������ô�Ѿ��ˣ�\n");
		}
        msg = HIW "$N" HIW "�������������н��������ĳ����ƣ�������ӿ���γ�һ���������У���ͼ��$n"HIW"���ڵ��ء�\n" NOR;
        me->add("neili", -100);

        ap =  me->query_skill("force",1);
        dp = target->query_skill("dodge",1);

        if (ap / 2 + random(ap) > dp
			||random(me->query_skill("strike",1))>target->query_skill("parry",1)/2)
        {
              msg +=HIR "��ʱ$n" HIR "�������ӿ����������ס�����β��ȣ�����ײײ��\n" NOR;
                                                   
               target->add_busy((int)me->query_skill("shentuo-zhang",1)/10);
               me->add("neili", -150);
				if (me->query_temp("hmg/powerup"))
				{				
					msg+=HIR "$N�����ͻȻ����һ�������ܵ����У��������죬��������֮����\n" NOR;

				}
				if ((int) me->query("combat_exp",1)/2 >=  random((int) target->query("combat_exp",1)))
				{
					damage = me->query_skill("shentuo-zhang",1)*me->query_str(1)/10;          

					if (damage >=1200) damage=1200;
					target->receive_damage("jing",-random(damage),me);
					target->apply_condition("no_exert",1);
					target->add_busy(2);

					msg+=HIB"$n����$N����������������������ͷʹ���ѣ��������˹�ȥ��\n"NOR;
				}

        } else	
        {
                msg += CYN "����$n" CYN "������$P"
                       CYN "����ͼ�����Զ㿪��\n"NOR;
                me->start_busy(1);
                me->add("neili", -50);
        }
        message_vision(msg,me,target);
		  
        return 1;
}

string perform_name(){ return HBWHT+HIB"ѩ��ǧɽ"NOR; }

int help(object me)
{
	write(HIC"\n����ѩɽ��֮��ѩ��ǧɽ����"NOR"\n");
	write(@HELP
	����ѩɽ�����ǰ���ɽׯ����ŷ����Ķ��ž���������
	���ӵ��ۿ�̬֮������ѩɽ����֮����ʩչ�����У���
	��ͨ�������ݵ���ѩ�����С�
	
	ָ�perform strike.xuesuo

Ҫ��
	��ǰ���������� 500 ���ϣ�
	��ǰ���������� 500 ���ϣ�
	����ѩɽ�Ƶȼ� 350 ���ϣ�
	��󡹦�ȼ�     350 ���ϣ�
	�����Ʒ��ĵȼ� 350 ���ϣ�
	�����������   50  ���ϣ�
	�����Ʒ�Ϊ����ѩɽ�ƣ�
	�����ڹ�Ϊ��󡹦
	�����ұ��ã�
HELP
	);
	return 1;
}

/**/