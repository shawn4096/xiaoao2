//qingxu.c ��������

//
//by sohu
//���׷�Ĺ���

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int skill,damage;
	object weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);
	skill=me->query_skill("qingxu-bian",1);
	damage=skill*me->query_dex()+random(skill);
	if (damage>4000) damage=4000+random(1000);
	
	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("����޷�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if(me->query_skill("qingxu-bian",1) < 200)
		return notify_fail("��ġ��������ࡹ��������죬����ʹ������޷���\n");
	if(me->query_skill("whip",1) < 200)
		return notify_fail("��ġ������޷�����������죬����ʹ������޷���\n");
	if(me->query_skill("force",1) < 200)
		return notify_fail("��ġ������ڹ�����������죬����ʹ������޷���\n");
	
	if( !weapon 
	|| weapon->query("skill_type") != "whip"
	|| me->query_skill_mapped("whip") != "qingxu-bian" 
	|| me->query_skill_mapped("parry") != "qingxu-bian" ) 
		return notify_fail("�������޷�ʹ�÷�������֮����޷���\n");


	if( me->query("neili") < 500 )
		return notify_fail("�����������500��\n");
	if( me->query("jingli") < 500 )
		return notify_fail("��ľ�������500��\n");

	if( me->query("max_neili") < 2000 )
		return notify_fail("��������������2000��\n");
	if( me->query("max_jingli") < 1500 )
		return notify_fail("������������1500��\n");
	
	message_vision(HIY "\n$N��ʹ����޷����������ࡹ�����������е�"+weapon->query("name")+HIY"�������£��Ƴ�����ԲȦ������$n��\n"NOR,me,target);
	
	
	if(random(me->query("combat_exp") )> target->query("combat_exp")/2
		||random(me->query_dex(1)) > target->query_dex(1)/2)
	{
		message_vision(HIC "\n���$p��$Pɨ���沿��һ�ɴ�����������ʱ$p��ð���ǣ�\n" NOR,me,target);
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/3,me);
	}
	else {
		message_vision(HIW "����$p������$P������޷�������һԾ��㿪�ˡ�\n" NOR,me,target);
	}
	me->set_temp("qxb/qingxu",1);


	me->add_temp("apply/attack",skill/3);
	me->add_temp("apply/damage",skill/5);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->delete_temp("qxb/qingxu");

	if (me->query_skill_mapped("cuff")=="duanjia-quan"
		&&me->query_skill_prepared("cuff")=="duanjia-quan")
	{
		weapon->unequip();
		message_vision(HIR"$N�����е�"+weapon->query("name")+HIR"һ�գ�������ϣ����μ�ȭһ���������ϵ���ʽϮ��$n��\n"NOR,me,target);
		me->add_temp("apply/cuff",me->query_skill("duanjia-quan")/4);
		me->add_temp("apply/damage",me->query_skill("duanjia-quan")/4);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/damage",-me->query_skill("duanjia-quan")/4);
		me->add_temp("apply/cuff",-me->query_skill("duanjia-quan")/4);
		weapon->wield();
	}


	me->add_temp("apply/attack",-skill/3);
	me->add_temp("apply/damage",-skill/5);

	me->add("jingli", -100);
	me->add("neili", -150);
	me->start_perform(4,"����޷�");
    return 1;
}

string perform_name(){ return HIM"��������"NOR; }

int help(object me)
{
        write(HIG"\n����޷�֮���������ࡹ��"NOR"\n\n");
        write(@HELP
	���������Ǵ���ҳ����׷�Ĺ��򣬵��׷��Ǵ�����������Ϥ
	�����Ļ������Խ��޷����ĵú;������뵽����޷��У�����
	���ص������Ļ����֡�
    
	ָ�perform whip.fengqi
		
Ҫ��  
	��ǰ�������� 500 ���ϣ�
	����������� 2000 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	��������� 1500 ���ϣ�
	����޷��ȼ� 200 ���ϣ�
	�����޷��ȼ� 200 ����:
	�����ڹ��ȼ� 200 ����:
	�����޷�Ϊ����޷���
	�����м�Ϊ����޷���
	����ȭ���ұ�ȭ��Ϊ�μ�ȭ��
	���ֱֳ����������

HELP
        );
        return 1;
}
