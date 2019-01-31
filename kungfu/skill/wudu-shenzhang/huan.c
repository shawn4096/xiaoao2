#include <ansi.h>
#include <combat.h>

#define HUAN "��" HIG "ǧ�����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

   //  if (userp(me) && ! me->query("can_perform/wudu-shenzhang/huan"))
              //  return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(HUAN "ֻ�ܿ���ʩչ��\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");
		if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("������Ʒ�������죬����ʩչ" HUAN "��\n");
        if ((int)me->query_skill("wudu-shenzhang", 1) < 200)
                return notify_fail("���嶾���Ʋ�����죬����ʩչ" HUAN "��\n");
		if (me->query("max_neili") < 1500)
                return notify_fail("�������������㣬����ʩչ���������ơ���\n");
		if (me->query("neili") < 500)
                return notify_fail("��ĵ�ǰ�������㣬����ʩչ���������ơ���\n");
		if (me->query("jingli") < 500)
                return notify_fail("��ĵ�ǰ�������㣬����ʩչ���������ơ���\n");
		if (me->query_dex(1) < 50)
                return notify_fail("��ĵ�ǰ�������㣬����ʩչ���������ơ���\n");
        if (me->query_skill_prepared("strike") != "wudu-shenzhang"
			||me->query_skill_mapped("strike") != "wudu-shenzhang")
                return notify_fail("��û��׼���嶾���ƣ�����ʩչ" HUAN "��\n");

        if (me->query_skill("dodge",1) < 200)
                return notify_fail("����Ṧ��Ϊ����������ʩչ" HUAN "��\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("�����ڵ���������������ʩչ" HUAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = me->query_skill("wudu-shenzhang", 1) + me->query_skill("dodge", 1) / 2;

        dp = target->query_skill("dodge",1);

        msg = HIC "\n$N" HIC "������Ȼ��죬ʹ�����С�" HIG "ǧ�����" HIC "����"
              "˫�Ʋ����ĳ���\n��ʽ��Ӱ��ã���ʵ�Ѳ⣬��ͼ����$n" HIC "�Ĺ�"
              "�ơ�\n" NOR;

        message_vision(msg, me, target);

        if (random(ap) > dp / 2)
        {
				msg = HIY "$n" HIY "ֻ��$N" HIY "˫��Ʈ����������"
                      "����������������$N" HIY "���Ʒ�֮�С�\n" NOR;
				message_vision(msg, me, target);

                target->start_busy(2+random(4));
               	me->start_busy(1);
                me->add("neili", -80);
        } else
        {
                msg = CYN "$n" CYN "����$N" CYN "���޹���֮�⣬��"
                      "�Ǵ󵨷�������$N" CYN "���о������⡣\n" NOR;
				message_vision(msg, me, target);

                me->start_busy(2);
                me->add("neili", -30);
        }
		me->start_perform(2,"ǧ�����");
        return 1;
}
string perform_name(){ return HIG"ǧ�����"NOR; }

int help(object me)
{
   write(WHT"\n�嶾����֮��"HIG"ǧ�����"WHT"����"NOR"\n");
   write(@HELP
	��Ĺ�ɵ�����Ī�����ѧ�������ɹ�Ĺ������
	��������Ī�����嶾�ش��ж���������Ʒ���
	���Ʒ���������ս����Ī��ºų������ӣ���
	����Ϊ�����ĺ����������������Ʒ�֮������
	���Ʒ������ʩչ������ʱ���Ϻ��о綾����
	�ж���ʱ���˿ڻ������ɰ���ָӡ����ʱ��
	����ɫ���ڡ���ʹ������	
	ǧ������ǽ���Ĺ���������Ʒ��ӵ����£�Χ
	�ƶ��ֿ��ٱ��ܣ����ڽ��Է���ס��

	perform strike.huan
	
Ҫ��
	�������Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	�嶾���Ƶȼ� 200 ���ϣ�
	�����Ʒ��ȼ� 200 ���ϣ�
	��Ч�����ȼ� 50  ���ϣ�
	�����ұ��Ʒ�Ϊ�嶾���ƣ�	
	
HELP
   );
   return 1;
}