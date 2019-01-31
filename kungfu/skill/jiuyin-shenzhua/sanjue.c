#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me, int improve);

int perform(object me, object target)
{
	int skill, j;

	skill = (int)me->query_skill("jiuyin-shenzhua", 1);

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("����������צ��ֻ����ս����ʹ�á�\n");

	if( me->query_temp("weapon"))
		return notify_fail("������������ô��ʹ�á���������צ����\n");   

	if( skill < 160 )
		return notify_fail("��ľ�����צ������죬ʹ������������צ��\n");

	if(me->query_skill("jiuyin-zhengong",1) < 160 )
		return notify_fail("��ľ����湦������죬ʹ������������צ��\n");

	if(me->query_skill("jiuyin-shenfa",1) < 160 )
		return notify_fail("��ľ�����������죬ʹ������������צ��\n");

	if (me->query_skill_mapped("parry") != "jiuyin-shenzhua" 
	|| me->query_skill_prepared("claw") != "jiuyin-shenzhua" )
		return notify_fail("�������޷�ʹ�á���������צ����\n");

	if( (int)me->query("max_neili") < 2000)
		return notify_fail("����������̫����ʹ��������������צ����\n");      

	if( (int)me->query("neili") < 1500 )
		return notify_fail("����������̫����ʹ��������������צ����\n");

	message_vision(HIR"\n$N�ֱ�ͻȻ�쳤����$nץȥ��\n"NOR,me,target);
	message_vision(HIR"$N��ʹ���ƺ��ǽ����г����ľ����澭��������������׹�צ��ֻ������������������ǿ����\n"NOR,me,target);

	j = skill/3;
	if ( skill > 300)
		j = to_int(skill/300.0 * skill/4.0);

	me->add_temp("apply/attack", j);
	me->add_temp("apply/claw", j/2);
	me->add_temp("apply/damage", j/2);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(me->is_fighting(target)) 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	me->add_temp("apply/attack", -j);
	me->add_temp("apply/claw", -j/2);
	me->add_temp("apply/damage", -j/2);

	me->add("neili", -400);
	me->add("jingli", -150);
	me->start_perform(3, "��������צ");
	me->start_busy(random(2));
	return 1;
}

string perform_name(){ return HIR"��������צ"NOR; }

int help(object me)
{
        write(HIR"\n������צ֮����������צ����"NOR"\n\n");
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
	����צ��Ϊ������צ��                
	��צ��Ϊ������צ��
	�����ޱ�����	
HELP
        );
        return 1;
}
