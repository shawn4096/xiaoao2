// sancai.c  ���ϵ�

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HIG"���ϵ�"NOR; }

int perform(object me, object target)
{
	object weapon;
	int damage, ap, dp, p,skill;
	string msg;
	skill=me->query_skill("liuhe-daofa",1);
	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("�����ϵ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if( (int)me->query_skill("liuhe-daofa", 1) < 300 )
		return notify_fail("������ϵ���������죬�޷�ʹ�����ϵ���\n");

	if ( me->query_skill_mapped("parry") != "liuhe-daofa"
	|| me->query_skill_mapped("blade") != "liuhe-daofa")
		return notify_fail("�������޷�ʹ�����ϵ���\n");

//	if( (int)me->query_skill("huntian-qigong", 1) < 300 )
//		return notify_fail("��Ļ������������ߡ�\n");

	if((int)me->query("max_neili",1) < 3500 )
		return notify_fail("���������Ϊ�������޷�ʹ�á����ϵ�����\n");

    if( (int)me->query("neili", 1) < 500 )
		return notify_fail("����������̫��������ʹ�á����ϵ�����\n");
	if( (int)me->query("jingli", 1) < 500 )
		return notify_fail("�����ھ���̫��������ʹ�á����ϵ�����\n");

	message_vision(HIG"\n$NΧ��$n���±�����ɣ�������֮�⣬$n����ǰ�����Ҷ�����Ӱ,$Nʩչ���е���������������������\n"NOR,me,target);

	me->add_temp("apply/attack",skill/5);
	me->add_temp("apply/damage",skill/6);
	if (objectp(target)&&me->is_fighting())
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"), random(3)?1:3);
	if (objectp(target)&&me->is_fighting())
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"), random(3)?1:3);
	if (objectp(target)&&me->is_fighting())
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"), random(3)?1:3);
	if (objectp(target)&&me->is_fighting())
	{
		weapon->unequip();
		if (me->query("gender")=="Ů��" && me->query_skill_prepared("strike")=="lianhua-zhang")
		{
		   message_vision(HIC"\n$N���ֵ��ƻ�ת�����������ƻ�������˳�ƻ��������ʷ׳ʡ�\n"NOR,me,target);				
		   COMBAT_D->do_attack(me,target, me->query_temp("weapon"), me->query("gender")=="Ů��"?3:1);
		   COMBAT_D->do_attack(me,target, me->query_temp("weapon"), me->query("gender")=="Ů��"?3:1);
		 }
		 if (me->query("gender")=="����" && me->query_skill_prepared("hand")=="suohou-shou")
		{
		   message_vision(HIC"\n$N�����к�Ȼ���������ֵ�һ���������ã�Ϯ��$n���ʺ�\n"NOR,me,target);				
		   target->add_busy(2);
		   COMBAT_D->do_attack(me,target, me->query_temp("weapon"), random(2)?1:3);
		 }

	}
	if (objectp(target)&&me->is_fighting())
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"), me->query("gender")=="Ů��"?3:1);

	me->add_temp("apply/attack",-skill/5);
	me->add_temp("apply/damage",-skill/6);

	me->start_busy(1+random(2));
	me->start_perform(6, "���ϵ�");
	me->add("neili",-300);
	me->add("jingli",-200);
	return 1;
}
int help(object me)
{
        write(CYN"\n�������ϵ������ϵ�����"NOR"\n");
        write(@HELP
	���ϵ�Ҳ��ؤ���ⳤ�Ͼ�ѧ��������������֮�⣬��������
	��������֮��ʩչ���þ���ʩչ�����������У����м���
	���ֹ��������籩��,������磬���ֶԷ���
	Ů������������ƻ����������ƣ������������������ǣ��
	���ơ�

	ָ��: perform blade.liuhe

Ҫ��  
	������� 3500 ���ϣ�
	��ǰ���� 500 ���ϣ�
	��ǰ���� 500 ���ϣ�
	�������� 300 �����ϣ�
	���ϵ��� 300 �����ϣ�
	�ڹ����ޣ�
	�����������ϵ���
	�����м����ϵ���
	�ֳֵ�������
HELP
        );
        return 1;
}
                                                                                                                                                    