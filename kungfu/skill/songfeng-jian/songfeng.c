//songfeng.c �ɷ��糱

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
		return notify_fail("�ɷ��糱ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( me->query_skill("songfeng-jian", 1) < 100 )
		return notify_fail("�������ɾ����ɷ��糱������̫ǳ���޷�ʹ���ɷ��糱������\n");

	if( me->query_skill("sword", 1) < 100 )
		return notify_fail("��Ļ�����������̫ǳ���޷�ʹ���ɷ��糱������\n");

	if( me->query_skill("force", 1) < 100 )
		return notify_fail("��Ļ����ڹ�����̫ǳ���޷�ʹ���ɷ��糱������\n");
                
	if( me->query("max_neili") < 1000 )
		return notify_fail("�������̫ǳ���޷�ʹ���ɷ��糱������\n");

	if( me->query("neili") < 800 )
		return notify_fail("����������㣬�޷�ʹ���ɷ��糱������\n");


	if (!objectp(weapon = me->query_temp("weapon")) 
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "songfeng-jian"
	|| me->query_skill_mapped("parry") != "songfeng-jian" )
		return notify_fail("��ʹ��������ɾ����ɷ��糱����ô?\n");

	j = me->query_skill("songfeng-jian", 1);

	message_vision(HIG"\n$N����һ��ζ������������֣�һ�����ȵĽ��������Ž����糱��Ĺ�����\n" NOR,me,target);
	
	//����NPC����
		
		me->add_temp("apply/attack", j/4);
	    
		me->add_temp("apply/sword",  j/5);
	    me->add_temp("apply/damage", j/5);

	me->set_temp("sfj/songfeng",j);
	
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
	//2
	if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
    //3
	if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	//4,,,,250���ٳ�һ��
    if(me->is_fighting(target) && (int)me->query_skill("songfeng-jian", 1) > 250 )
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    //5,,,300���ٳ�һ��������
	
if(me->is_fighting(target)&&me->query_skill("songfeng-jian",1)>300)
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/attack",-j/4);
	me->add_temp("apply/sword",  -j /5);
	me->add_temp("apply/damage", -j/5 );
    me->delete_temp("sfj/songfeng");
	me->add("neili", -350);
	me->add("jingli", -150);
	me->start_busy(1+random(2));
	me->start_perform(3+random(2), HIB"�ɷ��糱"NOR);
	message_vision(HIG"\n$N�⼸�к����޴��������ɷ��糱��ʩչ��󣬳���һ�����������չ���\n" NOR,me);

	return 1;
}

string perform_name(){ return HIG"�ɷ��糱"NOR; }