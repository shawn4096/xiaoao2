//qingfeng.c �������

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	int j;


	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) 
	|| !living(target))
		return notify_fail("�������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( me->query_skill("shangqing-jian", 1) < 100 )
		return notify_fail("���������ɾ����������������̫ǳ���޷�ʹ���������������\n");

	if( me->query_skill("sword", 1) < 100 )
		return notify_fail("��Ļ�����������̫ǳ���޷�ʹ���������������\n");

	if( me->query_skill("force", 1) < 100 )
		return notify_fail("��Ļ����ڹ�����̫ǳ���޷�ʹ���������������\n");
                
	if( me->query("max_neili") < 1000 )
		return notify_fail("�������̫ǳ���޷�ʹ���������������\n");

	if( me->query("neili") < 800 )
		return notify_fail("����������㣬�޷�ʹ���������������\n");


	if (!objectp(weapon = me->query_temp("weapon")) 
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "shangqing-jian"
	|| me->query_skill_mapped("parry") != "shangqing-jian" )
		return notify_fail("��ʹ����������ɾ��������������ô?\n");

	j = me->query_skill("shangqing-jian", 1);

	message_vision(HIC"\n$N����һ��ζ���������ɽ�֣�һ�����ȵĽ��������Ž����糱��Ĺ�����\n" NOR,me,target);
	
	//����NPC����
		
		me->add_temp("apply/attack", j/4);
	    
		me->add_temp("apply/sword",  j/5);
	    me->add_temp("apply/damage", j/5);

	me->set_temp("sqj/qingfeng",j);
	
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
	//2
	if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
    //3
	if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	//4,,,,250���ٳ�һ��
    if(me->is_fighting(target) && (int)me->query_skill("shangqing-jian", 1) > 250 )
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    //5,,,300���ٳ�һ��������
	
if(me->is_fighting(target)&&me->query_skill("shangqing-jian",1)>300)
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/attack",-j/4);
	me->add_temp("apply/sword",  -j /5);
	me->add_temp("apply/damage", -j/5 );
    me->delete_temp("sqj/qingfeng");
	me->add("neili", -350);
	me->add("jingli", -150);
	me->start_busy(1+random(2));
	me->start_perform(3+random(2), HIB"�������"NOR);
	message_vision(HIC"\n$N�⼸�к����޴������������ʩչ��󣬳���һ�����������չ���\n" NOR,me);

	return 1;
}

string perform_name(){ return HIG"�������"NOR; }