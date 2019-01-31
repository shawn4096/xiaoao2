//lihua.c �����滨��

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
		return notify_fail("�����滨��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if(me->query_skill("qiufeng-chenfa",1) < 200)
		return notify_fail("��ġ���糾������������죬����ʹ�ñ����滨����\n");
	if(me->query_skill("whip",1) < 200)
		return notify_fail("��ġ������޷�����������죬����ʹ�ñ����滨����\n");
	if(me->query_skill("force",1) < 200)
		return notify_fail("��ġ������ڹ�����������죬����ʹ�ñ����滨����\n");
	
	if( !weapon 
	|| weapon->query("skill_type") != "whip"
	|| me->query_skill_mapped("whip") != "qiufeng-chenfa" 
	|| me->query_skill_mapped("parry") != "qiufeng-chenfa" ) 
		return notify_fail("�������޷�ʹ����糾��֮�����滨����\n");


	if( me->query("neili") < 500 )
		return notify_fail("�����������500��\n");
	if( me->query("jingli") < 500 )
		return notify_fail("��ľ�������500��\n");

	if( me->query("max_neili") < 2000 )
		return notify_fail("��������������2000��\n");
	if( me->query("max_jingli") < 1500 )
		return notify_fail("��������������1500��\n");
	
	message_vision(HIY "\n$N��ʹ��糾���������滨���������������е�"+weapon->query("name")+HIY"չ����һ����滨��ģ�������$nʹ�����У�\n"NOR,me,target);
	
	
	if(random(me->query("combat_exp") )> target->query("combat_exp")/2
		||random(me->query_dex(1)) > target->query_dex(1)/2)
	{
		message_vision(HIC "\n���$p��$Pɨ���沿��һ�ɴ�����������ʱ$p��ð���ǣ�\n" NOR,me,target);
		target->receive_damage("qi",damage,me);
		if (me->query("gender")=="����") target->receive_wound("qi",damage/6,me);
		else target->receive_wound("qi",damage/3,me);
	
	}
	else {
		message_vision(HIW "����$p������$P�ı����滨��������һԾ��㿪�ˡ�\n" NOR,me,target);
	}
	me->set_temp("qfcf/baoyu",1);
	if (me->query("gender")=="Ů��")
		skill=skill+me->query_skill("xiantian-gong",1)/5; 

	me->add_temp("apply/attack",skill/3);
	me->add_temp("apply/damage",skill/5);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if (me->query_skill_mapped("leg")=="yuanyang-lianhuantui"
		||me->query_skill_prepared("leg")=="yuanyang-lianhuantui")
	{
		weapon->unequip();
		message_vision(HIR"$N�����е�"+weapon->query("name")+HIR"һ�գ������ڿն���һ������$n��\n"NOR,me,target);
		me->add_temp("apply/leg",skill/4);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/leg",-skill/4);
		weapon->wield();
	}

	me->add_temp("apply/attack",-skill/3);
	me->add_temp("apply/damage",-skill/5);
	me->delete_temp("qfcf/baoyu");

	me->add("jingli", -100);
	me->add("neili", -150);
	me->start_perform(4,"�����滨��");
    return 1;
}

string perform_name(){ return HIR"�����滨չ"NOR; }

int help(object me)
{
        write(HIG"\n����糾����֮�������滨չ����"NOR"\n\n");
        write(@HELP
	����糾������ȫ��������似��������Ϊ���ҳ��õ���
	���е��������߽���֮�ʣ�����������������������
	���޷�ʹ�á����е�������ƾ���似�������������У�Ҳ
	��������֮�á�
	�����滨չ�������з�����Ȼ��ɨ��ȥ���������й��С�
	ͬʱ��������ȷ����ȷ��Ḩ������һ�С�
    
ָ�perform whip.lihua
		
Ҫ��  
	��ǰ�������� 500 ���ϣ�
	����������� 2000 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	��������� 1500 ���ϣ�
	��糾���ȼ� 200 ���ϣ�
	�����޷��ȼ� 200 ����:
	�����ڹ��ȼ� 200 ����:
	�����޷�Ϊ��糾����
	�����м�Ϊ��糾����
	�����ȷ�Ϊԧ�������ˣ�
	���ȷ�Ϊԧ�������ˣ�
	���ֱֳ����������

HELP
        );
        return 1;
}
