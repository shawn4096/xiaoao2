//taoma.c
//
//by sohu
//�Ʊ��ӳ�Բ������Է�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int i;
	object weapon;
	weapon= me->query_temp("weapon");

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if(me->query_skill("jinlong-bianfa",1) < 150)
		return notify_fail("��ġ������޷�����������죬����ʹ������������\n");
	if(me->query_skill("whip",1) < 150)
		return notify_fail("��ġ������޷�����������죬����ʹ������������\n");
	if( !weapon 
		|| weapon->query("skill_type") != "whip"
		|| me->query_skill_mapped("whip") != "jinlong-bianfa" 
		|| me->query_skill_mapped("parry") != "jinlong-bianfa" ) 
		return notify_fail("�������޷�ʹ������������\n");

	if( me->query("neili") < 500 )
		return notify_fail("�����������500��\n");
	if( me->query("jingli") < 500 )
		return notify_fail("��ľ�������500��\n");

	if( me->query("max_neili") < 1500 )
		return notify_fail("��������������1500��\n");
	if( me->query("max_jingli") < 1300 )
		return notify_fail("��������������1300��\n");
	if (me->query("gender")=="����")
		i=3;
	if (me->query("gender")=="Ů��")
		i=2;
	if( target->is_busy() )
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");
	
	message_vision(HIW "\n$N��Ȼ�����е�"+weapon->query("name")+HIW"ʹ���������޷��������������Ĺ����γ�һ��ԲȦ����$n��\n"NOR,me,target);

	if(random(me->query("combat_exp") )> target->query("combat_exp")/i
		||random(me->query_dex(1)) > target->query_dex(1)/i)
	{
		message_vision(HIY "\n���$p��$Pһ������ס���ӣ���ʱ������ת��\n" NOR,me,target);
		target->add_busy((int)me->query_skill("jinlong-bianfa",1)/100);
		target->apply_condition("no_exert",1);
		target->receive_damage("qi",3000,me);
	}
	else {
		message_vision(HIW "����$p������$P����������������һԾ��㿪�ˡ�\n" NOR,me,target);
		me->start_perform(2,"��������");
		me->add_busy(1);
	}
	//message_vision(msg, me, target);

	me->add("jingli", -100);
	me->add("neili", -200);
    return 1;
}

string perform_name(){ return HIG"��������"NOR; }

int help(object me)
{
        write(HIG"\n�����޷�֮��������������"NOR"\n\n");
        write(@HELP
	�������޷����ǽ����߹ֺ����ԵĶ����似��������һ��
	���������Խ������޷�����������������������ס������
	Ҳ�����Դ˼����ˡ�
    
	ָ�perform whip.taoma
		
Ҫ��  
	��ǰ�������� 500 ���ϣ�
	����������� 1500 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	��������� 1300 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	�����޷��ȼ� 150 ���ϣ�
	�����޷��ȼ� 150 ����:
	�����޷�Ϊ�����޷���
	�����м�Ϊ�����޷���
	���ֱֳ����������

HELP
        );
        return 1;
}