// SANJUE �׹�����צ
// By Spiderii �ʵ����
#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

int perform(object me, object target)
{
	int skill,skill1, i;
	skill = (int)me->query_skill("jiuyin-baiguzhua", 1);
	
	if (me->query_skill("jiuyin-zhengong",1)>180)
		skill = (int)me->query_skill("jiuyin-baiguzhua", 1)+(int)me->query_skill("jiuyin-zhengong", 1);
	if (me->query_skill("poison",1)>=150)
		skill = (int)me->query_skill("jiuyin-baiguzhua", 1)+(int)me->query_skill("poison", 1);

	if( !target ) target = offensive_target(me);

    if( !objectp(target) || !me->is_fighting(target) || !necessary(target) )
		return notify_fail("���׹�����צ��ֻ����ս����ʹ�á�\n");

	if( me->query_temp("weapon"))
		return notify_fail("������������ô��ʹ�á��׹�����צ����\n");   

	if(me->query_skill("jiuyin-baiguzhua", 1) < 350 )
		return notify_fail("��ľ����׹�צ��������죬ʹ�������׹�����צ��������\n");
	if(me->query_skill("claw", 1) < 350)
		return notify_fail("��Ļ���צ����������죬ʹ�������׹�����צ��������\n");
	if(me->query_skill("force", 1) < 350)
		return notify_fail("��Ļ����ڹ���������죬ʹ�������׹�����צ��������\n");
	if ( me->query_skill_mapped("claw") != "jiuyin-baiguzhua"
		|| me->query_skill_prepared("claw") != "jiuyin-baiguzhua")
		return notify_fail("�������޷�ʹ�á��׹�����צ����\n");

	if( (int)me->query("max_neili") < 5000  )
		return notify_fail("�������������̫����ʹ�������׹�����צ����\n");      

	if( (int)me->query("neili") < 1500 )
		return notify_fail("����������̫����ʹ�������׹�����צ����\n");
	if( (int)me->query("jingli") < 800 )
		return notify_fail("�����ھ���̫����ʹ�������׹�����צ����\n");
	if (me->query_skill_mapped("claw")!="jiuyin-baiguzhua"
		||me->query_skill_prepared("claw")!="jiuyin-baiguzhua")
                return notify_fail("����δ���������׹�צ��\n");
/*
    if( me->query("shen") > -1000000 && me->query("PKS") < 10 )
 
		if( me->query("GKS") < me->query("BKS") && !me->query("no_pk") )
			return notify_fail("�㲻���ݶ����޷�ʹ�����׹�����צ���ľ�����\n");*/

	message_vision(RED"\n$NͻȻ�ֽ�һ������������׹�צ������ȫ������籬������ž���죬�ֱ�ͻȻ�������ߣ�\n"NOR,me);
	message_vision(BLU"\n$N������ɭɭ����һ�ɾ�������$n�ӳ����У����в���$n��ͷ�ǣ�\n"NOR,me);

	
	if(wizardp(me)) tell_object(me,sprintf("Jiuyin Debug:i=%d \n",i));					
	
	me->add_temp("apply/attack", skill/3);
	me->add_temp("apply/damage", skill/5);
	
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

    if(me->is_fighting(target)) 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);

    if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	me->add_temp("apply/attack", -skill/3);
	me->add_temp("apply/damage", -skill/5);

	me->start_perform(4, "�׹�����צ");
	me->add("neili", -400);
	me->add("jingli", -150);
	me->start_busy(random(2));
	return 1;
}

string perform_name(){ return HBWHT+RED"�׹�����צ"NOR; }

int help(object me)
{
        write(RED"\n�����׹�צ֮���׹�����צ����"NOR"\n\n");
        write(@HELP
	�����׹�צ���Ǿ����澭�¾�Ĺ���Ϊһ������
	�����Ѽ������书�����ɣ����ھ��ף�����������
	��֮����������÷������˲������Ͼ��书��ֻƾ
	���˴�Ħ���� ����ָ�������޼᲻�ƣ��ݵ����ԣ�
	�紩���� ����������ͷ����ϰ���Ź��򡣵��˹�
	���������ף���������������Ҳ�ɾ�����׹�צ��
	�պ�������
	
	�׹�צ�������У�����ֱָ�Է���ͷ�Բ�λ���˵�
	���޼᲻�ݣ�צצ��ǣ�
	
	perform claw.sanjue

Ҫ��  
	��ǰ���������� 1500 ���ϣ�
	������������� 5000 ���ϣ�
	��ǰ���������� 800 ���ϣ�
	�����׹�צ�ȼ� 350 ���ϣ�
	����צ���ĵȼ� 350 ���ϣ�
	�����ڹ��ĵȼ� 350 ���ϣ�
	����צ��Ϊ�����׹�צ��                
	��צ��Ϊ�����׹�צ��
	�����ޱ�����	

HELP
        );
        return 1;
}
