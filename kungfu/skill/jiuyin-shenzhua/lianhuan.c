// lianhuan
// By sohu@xojh
//��������

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

int perform(object me, object target)
{
	int skill,i,j;
	skill = (int)me->query_skill("jiuyin-shenzhua", 1);
	
	if (me->query_skill("jiuyin-zhengong",1)>180)
		skill = (int)me->query_skill("jiuyin-shenzhua", 1)+(int)me->query_skill("jiuyin-zhengong", 1);
	if (me->query_skill("poison",1)>=150)
		skill = (int)me->query_skill("jiuyin-shenzhua", 1)+(int)me->query_skill("poison", 1);

	if( !target ) target = offensive_target(me);

    if( !objectp(target) || !me->is_fighting(target) || !necessary(target) )
		return notify_fail("����������צ��ֻ����ս����ʹ�á�\n");

	if( me->query_temp("weapon"))
		return notify_fail("������������ô��ʹ�á���������צ����\n");   

	if(me->query_skill("jiuyin-shenzhua", 1) < 500 )
		return notify_fail("��ľ�����צ��������죬ʹ��������������צ��������\n");
	if(me->query_skill("claw", 1) < 500)
		return notify_fail("��Ļ���צ����������죬ʹ��������������צ��������\n");
	if(me->query_skill("force", 1) < 500)
		return notify_fail("��Ļ����ڹ���������죬ʹ��������������צ��������\n");
	if ( me->query_skill_mapped("claw") != "jiuyin-shenzhua"
		|| me->query_skill_prepared("claw") != "jiuyin-shenzhua")
		return notify_fail("�������޷�ʹ�á���������צ����\n");

	if( (int)me->query("max_neili") < 15000  )
		return notify_fail("�������������̫����ʹ��������������צ����\n");      

	if( (int)me->query("neili") < 2000 )
		return notify_fail("����������̫����ʹ��������������צ����\n");
	if( (int)me->query("jingli") < 1000 )
		return notify_fail("�����ھ���̫����ʹ��������������צ����\n");

	message_vision(HBRED+HIY"\n$N���������������ȣ����������צ������ȫ������籬������ž���죬�ֱ�ͻȻ�������ߣ�\n"NOR,me);
	message_vision(YEL"\n$N˫צ�������籩�꣬����������˲��ӳ���ʽ��\n"NOR,me);

	
	if (me->query_skill("jiuyin-zhengong",1)>500)
	{
		j=9;
		skill=skill+me->query_skill("jiuyin-zhengong",1)/5;
		me->add_temp("apply/claw", skill/3);

	}else j=5;
	me->add_temp("apply/attack", skill/3);
	me->add_temp("apply/damage", skill/4);

/*	
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(objectp(target) && me->is_fighting()) 		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

*/
	for (i=0; i<=j ;i++ )
	{
		if(objectp(target) && me->is_fighting()) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	}
	me->add_temp("apply/attack", -skill/3);
	me->add_temp("apply/damage", -skill/4);
	if (me->query_skill("jiuyin-zhengong",1)>500)
	{
	
		me->add_temp("apply/claw", -skill/3);

	}
	me->start_perform(6, "��������צ");
	me->add("neili", -1200);
	me->add("jingli", -800);
	me->add_busy(random(1)+1);
	return 1;
}

string perform_name(){ return HBGRN+HIW"��������צ"NOR; }

int help(object me)
{
        write(RED"\n������צ֮����������צ����"NOR"\n\n");
        write(@HELP
	������צ���Ǿ����澭�Ͼ�Ĺ���Ϊһ�����˻���
	���������Ǽ�������צ���Ĵ�ȫ������似��������
	צʩչ��צ���������������Ĺ���������ſ̣���
	�Թ�ĹҲ��������
	
	��������צ����������������������צ���������ˡ�
	
	perform claw.lianhuan

Ҫ��  
	��ǰ���������� 2000 ���ϣ�
	������������� 15000 ���ϣ�
	��ǰ���������� 1000 ���ϣ�
	������צ�ĵȼ� 500 ���ϣ�
	����צ���ĵȼ� 500 ���ϣ�
	�����ڹ��ĵȼ� 500 ���ϣ�
	����צ��Ϊ������צ��                
	��צ��Ϊ������צ��
	�����ޱ�����	

HELP
        );
        return 1;
}
