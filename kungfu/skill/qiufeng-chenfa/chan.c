//chan.c
//���𳾵ķ�������
//by sohu
//ΪŮ����趨,Դ���ﲻ�����𴦻�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int i;
	object weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("�������ƾ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if(me->query_skill("qiufeng-chenfa",1) < 150)
		return notify_fail("��ġ���糾������������죬����ʹ�÷������ƾ���\n");
	if(me->query_skill("whip",1) < 150)
		return notify_fail("��ġ������޷�����������죬����ʹ�÷������ƾ���\n");
	if( !weapon 
		|| weapon->query("skill_type") != "whip"
		|| me->query_skill_mapped("whip") != "qiufeng-chenfa" 
		|| me->query_skill_mapped("parry") != "qiufeng-chenfa" ) 
		return notify_fail("�������޷�ʹ�÷������ƾ���\n");

	if( me->query("neili") < 500 )
		return notify_fail("�����������500��\n");
	if( me->query("jingli") < 500 )
		return notify_fail("��ľ�������500��\n");

	if( me->query("max_neili") < 1500 )
		return notify_fail("��������������1500��\n");
	if( me->query("max_jingli") < 1300 )
		return notify_fail("������������1300��\n");
	if( target->is_busy() )
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");
	if (me->query("gender")=="����") i=2;
	if (me->query("gender")=="Ů��") i=3;
	
	message_vision(HIW "\n$N��Ȼ�����е�"+weapon->query("name")+HIW"ʹ������糾�����ķ������ƾ��Ĺ����γ�һ��ԲȦ����$n���ʺ�\n"NOR,me,target);

	if(random(me->query("combat_exp") )> target->query("combat_exp")/i
		||random(me->query_dex(1)) > target->query_dex(1)/i)
	{
		message_vision(HIY "\n���$p��$Pһ��Ȧס���ӣ���ʱ��Ѫһ�͡�\n" NOR,me,target);
		target->add_busy(1+(int)me->query_skill("qiufeng-chenfa",1)/100);
		target->apply_condition("no_exert",1);
		if (me->query("per")>27 && me->query("gender")=="Ů��" )
		{
			message_vision(HIG "\n$nֻ��$N������Ů�·������޲��ɷ����ʱһ㶣�������Щ�ٻ���\n"NOR,me,target);
			target->add_busy(1);
		}
		//target->
	}
	else {
		message_vision(HIW "����$p������$P�ķ������ƾ�������һԾ��㿪�ˡ�\n" NOR,me,target);
		me->start_perform(1,"�������ƾ�");
	}
	//message_vision(msg, me, target);

	me->add("jingli", -100);
	me->add("neili", -200);
    return 1;
}

string perform_name(){ return HIW"�������ƾ�"NOR; }

int help(object me)
{
        write(HIG"\n����糾����֮���������ƾ�����"NOR"\n\n");
        write(@HELP
	����糾������ȫ��������似��������Ϊ���ҳ��õ���
	���е��������߽���֮�ʣ�����������������������
	���޷�ʹ�á����е�������ƾ���似�������������У�Ҳ
	��������֮�á�
	�������ƾ����Գ��޵���ת֮�������Է���ס���Ӷ�����
	�Է��ж�����ʽ��һ���Է����ˣ��Ʊغ������ѡ�Ů����
	�����ƣ�����ò��Ů�ӡ�
    
ָ�perform whip.chan
		
Ҫ��  
	��ǰ�������� 500 ���ϣ�
	����������� 1500 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	��������� 1300 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	��糾���ȼ� 150 ���ϣ�
	�����޷��ȼ� 150 ����:
	�����޷�Ϊ��糾����
	�����м�Ϊ��糾����
	���ֱֳ����������

HELP
        );
        return 1;
}
