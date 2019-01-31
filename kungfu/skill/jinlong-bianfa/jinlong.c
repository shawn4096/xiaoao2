//jinlong.c ������ʽ
//
//by sohu
//��������

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int skill;
	object weapon = me->query_temp("weapon");
	skill=me->query_skill("jinlong-bianfa",1);
	
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("��������ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if(me->query_skill("jinlong-bianfa",1) < 150)
		return notify_fail("��ġ������޷�����������죬����ʹ�á�������ʽ����\n");
	if(me->query_skill("whip",1) < 150)
		return notify_fail("��ġ������޷�����������죬����ʹ�á�������ʽ����\n");
	if( !weapon 
		|| weapon->query("skill_type") != "whip"
		|| me->query_skill_mapped("whip") != "jinlong-bianfa" 
		|| me->query_skill_mapped("parry") != "jinlong-bianfa" ) 
		return notify_fail("�������޷�ʹ�á�������ʽ����\n");

	if( me->query("neili") < 500 )
		return notify_fail("�����������500��\n");
	if( me->query("jingli") < 500 )
		return notify_fail("��ľ�������500��\n");

	if( me->query("max_neili") < 1500 )
		return notify_fail("��������������1500��\n");
	if( me->query("max_jingli") < 1300 )
		return notify_fail("��������������1300��\n");

	
	message_vision(HIG"\n$N���һ����������������������"+weapon->query("name")+HIW"����˦������ԲȦ���������$n��\n"NOR,me,target);
	me->add_temp("apply/attack",skill/3);
	me->add_temp("apply/damage",skill/5);
	me->add_temp("apply/whip",skill/5);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	
	me->add_temp("apply/attack",-skill/3);
	me->add_temp("apply/damage",-skill/5);
	me->add_temp("apply/whip",-skill/5);

	me->add("jingli", -100);
	me->add("neili", -200);
	me->start_perform(4,"������ʽ");
    return 1;
}

string perform_name(){ return HIY"������ʽ"NOR; }

int help(object me)
{
        write(HIG"\n�����޷�֮��������ʽ����"NOR"\n\n");
        write(@HELP
	�������޷����ǽ����߹ֺ����ԵĶ����似��������һ��
	���������Խ������޷�����������������������ס������
	Ҳ�����Դ˼����ˡ���������ʽ��Ϊ���������Է����С�
    
	ָ�perform whip.jinlong
		
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