// Last Modified by winder on Aug. 25 2001
// 18pan.c ̩ɽʮ���� 

#include <ansi.h>
inherit F_SSERVER;

int perform(object me,object target)
{
	string msg;
	object weapon;

	int skill;

	if( !objectp(target) ) target = offensive_target(me);
	
	if( !target || !target->is_character() || target == me ||	
	  	!me->is_fighting(target) ||
  	!living(target) || target->query_temp("noliving") )
		return notify_fail("����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		
	if (!objectp(weapon = me->query_temp("weapon")) ||
		(string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");



	if( (int)me->query_skill("taishan-jianfa", 1) < 200 )
		return notify_fail("���̩ɽ������Ϊ������ʹ������̩ɽʮ���̡���\n");

	if( (int)me->query_skill("force", 1) < 200 )
		return notify_fail("��Ļ����ڹ���Ϊ������ʹ������̩ɽʮ���̡���\n");

	if( me->query("neili") < 300 )
		return notify_fail("��������������޷�����̩ɽʮ���̣�\n");

	if( me->query("max_neili") < 400 )
		return notify_fail("���������Ϊ�������޷�����̩ɽʮ���̣�\n");

	if( target->is_busy() )
		return notify_fail(target->name()+"�Ѿ��Թ˲�Ͼ�ˣ��ŵ������ɣ�\n");

	skill = me->query_skill("taishan-jianfa",1);
	msg = CYN "$Nʹ��̩ɽʮ���̽���֮����ʽ��һ�ѽ�����ʮ�˵���Ӱ��\n";
	//me->start_busy(1);
	me->add("neili",-100);
	if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/3 )
	{
		msg += HIY"���$n�������������ã�\n" NOR;
		target->add_busy(skill/150);
	} else
	{
		msg += HIC"����$n������$N�Ľ��У�һš��Ծ���˽�Ӱ��\n" NOR;
		msg += HIY"$Nȴһ��ʧȥƽ�⣬�������˱�����\n" NOR;
		me->start_busy(3);
	}
	 message_vision(msg, me, target);

        return 1;
}
string name() {return HIG"̩ɽʮ����"NOR; }

int help(object me)
{
        write(HIG"\n̩ɽ����֮"+HIW"��̩ɽʮ���̡���"NOR"\n\n");
        write(@HELP
	̩ɽ������֮��������������̩ɽ���������־�������
	�����������ն���Ϊ����֮����̩ɽ������ɡ��˽���
	���ƹ�׾���أ�����ʽȴ�������ͣ��ڲ�����������
	ʤ������̩ɽʮ���������Խ��������̩ɽ֮�������
	֮�⣬��������ס��
	
	ָ�perform sword.shibapan

Ҫ��
	��ǰ�������� 500 ���ϣ�
	����������� 1500 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	̩ɽ�����ȼ� 200 ���ϣ�
	̩ɽ�ķ��ȼ� 200 ���ϣ�
	���������ȼ� 200 ���ϣ�
	�����Ṧ�ȼ� 200 ���ϣ�
	��������Ϊ̩ɽ������
	�����м�Ϊ̩ɽ������
	�����ڹ�Ϊ̩ɽ�ķ���
	
HELP
        );
        return 1;
}
