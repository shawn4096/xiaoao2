//sao.c ɨ�־�
//���𳾵ķ�������
//by sohu
//ΪŮ����趨,Դ���ﲻ�����𴦻�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int skill,damage;
	object weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);
	skill=me->query_skill("qiufeng-chenfa",1);
	damage=skill*me->query_dex()+random(skill);
	if (damage>4000) damage=4000+random(1000);
	
	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("ɨ�־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if(me->query_skill("qiufeng-chenfa",1) < 100)
		return notify_fail("��ġ���糾������������죬����ʹ��ɨ�־���\n");

	if(me->query_skill("whip",1) < 100)
		return notify_fail("��ġ������޷�����������죬����ʹ�ñ����滨����\n");
	if(me->query_skill("force",1) < 100)
		return notify_fail("��ġ������ڹ�����������죬����ʹ�ñ����滨����\n");
	
	if( !weapon 
	|| weapon->query("skill_type") != "whip"
	|| me->query_skill_mapped("whip") != "qiufeng-chenfa" 
	|| me->query_skill_mapped("parry") != "qiufeng-chenfa" ) 
		return notify_fail("�������޷�ʹ��ɨ�־���\n");

	if( me->query("neili") < 500 )
		return notify_fail("�����������500��\n");
	if( me->query("jingli") < 500 )
		return notify_fail("��ľ�������500��\n");

	if( me->query("max_neili") < 1500 )
		return notify_fail("��������������1500��\n");
	if((int)me->query("max_jingli") <1300)
	{
		write("max_jingli="+me->query("max_jingli"));
		return notify_fail("������������1300!\n");
	}
//	if( target->is_busy() )
//		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");
	
	message_vision(HIY "\n$N��ʹ��糾����ɨ�־����������е�"+weapon->query("name")+HIY"��$n���沿˳��˦����\n"NOR,me,target);
	
	
	if(random(me->query("combat_exp") )> target->query("combat_exp")/2
		||random(me->query_dex(1)) > target->query_dex(1)/2)
	{
		message_vision(HIC "\n���$p��$Pɨ���沿��һ�ɴ�����������ʱ$p��ð���ǣ�\n" NOR,me,target);
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/3,me);
	    if(userp(me) && me->query("env/damage"))
        	tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage*4/3+ WHT"�㹥���˺���\n"NOR);
		
		if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage*4/3+ WHT"���˺���\n"NOR);

	}
	else {
		message_vision(HIW "����$p������$P��ɨ�־�������һԾ��㿪�ˡ�\n" NOR,me,target);
	}
	//message_vision(msg, me, target);
	me->add_temp("apply/attack",skill/3);
	me->add_temp("apply/damage",skill/5);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/attack",-skill/3);
	me->add_temp("apply/damage",-skill/5);

	me->add("jingli", -100);
	me->add("neili", -100);
	me->start_perform(3,"ɨ�־�");
    return 1;
}

string perform_name(){ return HIG"ɨ�־�"NOR; }

int help(object me)
{
        write(HIG"\n����糾����֮��ɨ�־�����"NOR"\n\n");
        write(@HELP
	����糾������ȫ��������似��������Ϊ���ҳ��õ���
	���е��������߽���֮�ʣ�����������������������
	���޷�ʹ�á����е�������ƾ���似�������������У�Ҳ
	��������֮�á�
	ɨ�־��������з�����Ȼ��ɨ��ȥ�����÷𳾵ļ�˳��
	�Է����š����к��˺������ҹ���
    
ָ�perform whip.sao
		
Ҫ��  
	��ǰ�������� 500 ���ϣ�
	����������� 1500 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	��������� 1300 ���ϣ�
	��糾���ȼ� 100 ���ϣ�
	�����޷��ȼ� 100 ����:
	�����ڹ��ȼ� 100 ����;
	�����޷�Ϊ��糾����
	�����м�Ϊ��糾����
	���ֱֳ����������

HELP
        );
        return 1;
}
