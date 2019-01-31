// lianhuan.c ԧ��������
// by sohu@xojh

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
int perform(object me, object target)
{

	int i,damage,p;
	string msg;
	if( !target ) target = offensive_target(me);

     if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
		return notify_fail("��ԧ�������ȡ�ֻ����ս���жԶ���ʹ�á�\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("ʹ�á�ԧ�������ȡ�ʱ˫�ֱ�����ţ�\n");

	if( (int)me->query_skill("shaolin-tantui", 1) < 250 )
		return notify_fail("���ԧ���������Ȳ�����죬����ʹ�á�ԧ�������ȡ���\n");

	if( (int)me->query_skill("yijin-jing", 1) < 250 )
		return notify_fail("����׽�ȼ�����������ʹ�á�ԧ�������ȡ���\n");

	if (me->query_skill_mapped("force") != "yijin-jing")
		return notify_fail("��Ŀǰ���ڹ��޷�֧����ʹ�á�ԧ�������ȡ����й�����\n");  
	if (me->query_skill("leg",1)<250)
		return notify_fail("��Ŀǰ�Ļ����ȷ�����100����֧����ʹ�á�ԧ�������ȡ����й�����\n");  
		
	if( (int)me->query_dex() < 50 )
		return notify_fail("���������50������ʹ�á�ԧ�������ȡ���\n");

	if (me->query_skill_prepared("leg") != "shaolin-tantui"
	|| me->query_skill_mapped("leg") != "shaolin-tantui")
		return notify_fail("�������޷�ʹ�á�ԧ�������ȡ����й�����\n");  
											       
	if( (int)me->query("max_neili") < 2500 )
		return notify_fail("�������������̫��������ʹ�á�ԧ�������ȡ���\n");
	if( (int)me->query("neili") < 500 )
		return notify_fail("��Ŀǰ����̫�٣�����ʹ�á�ԧ�������ȡ���\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("�����ھ���̫�٣�����ʹ�á�ԧ�������ȡ���\n");


	message_vision(RED"\n$Nһ��������ʮ��·���ȷ��Ӽ��£��ȵ�����ԧ�������ȡ����������ڿ��У�˫��������������$n�����߳����ȣ�\n" NOR,me, target);
	
		
	me->set_temp("sltt/lianhuan", 1);
	me->add("neili", -180);
	if (target->is_busy())
	{
		i = (int)me->query_skill("ruying-suixingtui", 1)+(int)me->query_skill("yijin-jing", 1)/3;
	}else 	i = (int)me->query_skill("ruying-suixingtui", 1)+(int)me->query_skill("yijin-jing", 1)/5;

	me->add_temp("apply/attack",i);
    me->add_temp("apply/damage",i/4);
    me->add_temp("apply/dodge", i);


	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
	if (me->query_skill_mapped("hand")=="fengyun-shou"
		&&me->query_skill_prepared("hand")=="fengyun-shou"
		&&me->query_skill_mapped("leg")=="shaolin-tantui"
		&&me->query_skill_prepared("leg")=="shaolin-tantui")
	{
		message_vision(HIY"$N�ۼ�$n�������û��������ʩչ�������־������������ȷ�Ϯ��$n���ؿڣ�\n"NOR,me,target);
		me->add_temp("apply/attack",i/4);
		me->add_temp("apply/damage",i/6);
		me->add_temp("apply/hand",i/4);
		//me->prepared_skill("");
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		me->add_temp("apply/attack",-i/4);
		me->add_temp("apply/damage",-i/6);
		me->add_temp("apply/hand",-i/4);

	}
//	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
	

	
	me->add_temp("apply/attack",- i);
    me->add_temp("apply/damage",- i/4);
    me->add_temp("apply/dodge", -i);

		message_vision(HIC "\n$Nһ�������꣬���н��ƻ�������ƮƮ���ڵ��ϡ�\n" NOR,me);

		me->delete_temp("sltt/lianhuan");

		me->start_perform(4,"��ԧ�������ȡ�");

		return 1;
}


string perform_name(){ return HIY"ԧ��������"NOR; }
int help(object me)
{
        write(HIC"\n���ֵ���֮��ԧ�������ȡ�������"NOR"\n");
        write(@HELP
	���ֵ���Ϊ���������ȷ������ü�ʵ���ȹ���ǿ�����������
	��������У��öԷ�������Է��߳�һ�ž���ɱ�У�����ַ�
	��ʤ�������޿ɶ㣬�˵��������ǳ���ԧ��������˼��˫����
	�棬�����߳���
		
	ע�⣺�����ֵ��ȡ����ȷ����������˺�����Ӱ�����ȵı���
		��������ԧ���������������������ȷ����мǣ�

	ָ�perform leg.tantui

Ҫ��  
	����������� 2500 ���ϣ�      
	��ǰ�������� 500  ����
	��ǰ�������� 500  ���ϣ�  
	���ֵ��˵ȼ� 250 ���ϣ�
	�׽���ȼ� 250 ���ϣ�
	�����ȷ��ȼ� 250 ���ϣ�	
	�����ȷ�Ϊ����ԧ�������ȣ�
	�����м�Ϊ����ԧ�������ȣ�
	�����ޱ�����
	��Ч������С��50��
                
HELP
        );
        return 1;
}
