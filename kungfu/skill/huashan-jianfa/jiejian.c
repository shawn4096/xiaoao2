// This program is a part of NITAN MudLIB
// jiejian.c ��ɽ�������ؽ�ʽ��
// edit by sohu@xojh

#include <ansi.h>

inherit F_SSERVER;

#define JIE "��" HIB "�ؽ�ʽ" NOR "��"

int perform(object me, object target)
{
	object weapon;
    int level,skill;
	string msg;
	skill = me->query_skill("huashan-jianfa", 1);
	level=skill/250;
	if (! target) target = offensive_target(me);
	

	if (! target || ! me->is_fighting(target))
		return notify_fail(JIE "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if (!me->query("quest/hs/hsjf/jiejian/pass"))
		return notify_fail("��ֻ����˵�����У���δ�����ͨ�����������г�����̸��а��\n");
	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
		
	if (skill < 350)
		return notify_fail("��Ļ�ɽ����������죬�޷�ʩչ" JIE " ��\n");

    if (me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("��û�м�����ɽ�������޷�ʩչ" JIE "��\n");

    if (me->query("neili") < 1000)
                return notify_fail("�����������������޷�ʹ��" JIE "��\n");
	if (me->query("jingli") < 600)
                return notify_fail("�����������������޷�ʹ��" JIE "��\n");
    if (!living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
	//message_vision();

    msg = HIW "\n����$N" HIW "����"+weapon->query("name")+HIW"һ�գ�ʹ����ɽ��������֮"
              "��" HIG "�ؽ�ʽ" HIW "����ת��֮�������޷죬һ"
              "\n���ȳ�������ԴԴ��к�������Ծ̲����������Ѹ"
              "Ȼ����$n" HIW "��\n" NOR;

    me->add("neili", -150);
	me->add("jingli", -100);
	if (random(skill) > (int)target->query_skill("parry", 1) / 2
		||random(me->query_int(1))>target->query_int(1)/2)
    {
		msg += HIR "���$p" HIR "�᲻�������������˼�����һʱ���޷����֣�\n" NOR;
		target->add_busy(level);
		
	} else {
                if (objectp(weapon = target->query_temp("weapon")))
        		msg += CYN "����$p" CYN "ʶ����$P" CYN "�����⣬"
                               "�Թ˽����е�" + weapon->query("name") +
                               CYN "\n���һ�Ź⻨��$P"
                               CYN "һ��֮����Ҳ������ȥ��\n" NOR;
                else
                        msg += CYN "����$p" CYN "˫�ִ�����ģ���$P"
                               CYN "������һһ�ܿ���\n" NOR;

				me->add_busy(1);
	}
	message_vision(msg, me, target);
	
	return 1;
}

string perform_name() {return HBBLU+HIW"�ؽ�ʽ"NOR;}

int help(object me)
{
	write(WHT"\n��ɽ������"HIB"�ؽ�ʽ"WHT"����"NOR"\n");
	write(@HELP
    �ؽ�ʽԭ���ǻ�ɽ��ͨ����ʽ���������̺��Ľ������ǰ���
	���������ڻ�ɽ��ɽ��ָ������壬������������һ��ʹ��
	ֱ���ؽ�ʽ����Ϊ�������ã���һ�������ﲮ���Ʒ�����ʽ
	���������׻�ɽ�����İ��壬���н�ʹ�ö����������
	ע�⣺�������к͸����似�ȼ��Լ������йء�
	    
	ָ�perform swrod.jiejian

Ҫ��
	��ɽ�����ȼ� 350 ����
	������ϼ�� 350 ��
	���������ȼ� 350 ��
	�����Ṧ�ȼ� 350 ����
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 600  ���ϡ�
	����������ɽ������
	�����мܻ�ɽ����
	�ֳֽ���������
HELP
	);
	return 1;
}
