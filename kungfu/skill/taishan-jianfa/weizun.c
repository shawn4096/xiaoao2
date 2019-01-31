// weizun.c  ����Ϊ��
// Last Modified by winder on Aug. 25 2001

#include <ansi.h>
inherit F_SSERVER;
#define PNAME "������Ϊ��"
int perform(object me,object target)
{
	string msg;
	object weapon;
	
	int skill,i,attack_time;

	if( !objectp(target) ) target = offensive_target(me);
	
	if( !target || !target->is_character() || target == me ||	
	  	!me->is_fighting(target) ||
  	!living(target) || target->query_temp("noliving") )
		return notify_fail("����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		
	if (!objectp(weapon = me->query_temp("weapon")) ||
		(string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");



	if( (int)me->query_skill("taishan-jianfa", 1) < 400 )
		return notify_fail("���̩ɽ������Ϊ������ʹ����������Ϊ�𡹡�\n");

	if( (int)me->query_skill("force", 1) < 400 )
		return notify_fail("��Ļ����ڹ���Ϊ������ʹ����������Ϊ�𡹡�\n");

	if( me->query("neili") < 1300 )
		return notify_fail("��������������޷���������Ϊ��\n");

	if( me->query("max_neili") < 4000 )
		return notify_fail("���������Ϊ�������޷���������Ϊ��\n");


	skill = me->query_skill("taishan-jianfa",1);
	message_vision(HIW"$Nʹ��̩ɽ�����ġ�����Ϊ�𡹣�����Ȼ�ӿ죬����һת���������������������\n" NOR, me);

	me->add("neili", -100);
	attack_time = 5 + random(3);
	
	me->add_temp("apply/attack",skill/4);
	me->add_temp("apply/damage",skill/5);

	for(i = 0; i < attack_time; i++)
	{
		if (!objectp(target)) break;
		COMBAT_D->do_attack(me,target,me->query_temp("weapon"),3);
	}
	me->add_temp("apply/attack",-skill/4);
	me->add_temp("apply/damage",-skill/5);

	return 1;
}
string name() {return HIR"����Ϊ��"NOR; }

int help(object me)
{
        write(HIG"\n̩ɽ����֮"+HIW"������Ϊ�𡹣�"NOR"\n\n");
        write(@HELP
	̩ɽ������֮��������������̩ɽ���������־�������
	�����������ն���Ϊ����֮����̩ɽ������ɡ��˽���
	���ƹ�׾���أ�����ʽȴ�������ͣ��ڲ�����������
	ʤ����������Ϊ���Ǵ������ͬ�����������У�Ѹ����
	�ȡ�Ϊ̩ɽ����������ʽ��
	
	ָ�perform sword.weizun

Ҫ��
	��ǰ�������� 500 ���ϣ�
	����������� 1500 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	̩ɽ�����ȼ� 400 ���ϣ�
	̩ɽ�ķ��ȼ� 400 ���ϣ�
	��������Ϊ̩ɽ������
	�����м�Ϊ̩ɽ������
	�����ڹ�Ϊ̩ɽ�ķ���
	
HELP
        );
        return 1;
}
