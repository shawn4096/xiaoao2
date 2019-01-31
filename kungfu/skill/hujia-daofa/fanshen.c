// fanshen.c ���ӷ���
//Created by sohu
//���˷������������������浶���������������ǲ������ܣ����õ�����������ߣ��͵�ת��ˢ��һ����
//���гֱ����ұۣ��ֱ����ϣ��ֱ���ء����˳����Һ����ֵ�������һ�����������Թ�����
#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return HBRED"���ӷ���"NOR;}

int perform(object me,object target)
{
    object weapon;
    int i,damage;
	string msg;
    i = me->query_skill("hujia-daofa", 1);
    if( !target ) target = offensive_target(me);
   
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("�����ӷ�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if((int)me->query_skill("force", 1) < 250 )
                return notify_fail("��Ļ����ڹ�������죬�޷�֧�֡����ӷ�������\n");

    if( (int)me->query_skill("hujia-daofa", 1) < 250 ) 
                return notify_fail("��ĺ��ҵ�����δ���ɣ�����ʹ�á����ӷ�������\n");

    if((int)me->query_skill("blade", 1) < 250 )
                return notify_fail("��Ļ�������������죬����ʹ�á����ӷ�������\n");

    if((int)me->query_skill("dodge", 1) < 250 )
                return notify_fail("��Ļ����Ṧ������죬����ʹ�á����ӷ�������\n");

    if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "blade"
        || me->query_skill_mapped("blade") != "hujia-daofa")
        //|| me->query_skill_mapped("parry") != "hujia-daofa"
                return notify_fail("�������޵������ʹ�á����ӷ�������\n");
                 
    if((int)me->query("max_neili") < 5000 )
                return notify_fail("���������Ϊ����������ʹ�á����ӷ�������\n");

    if((int)me->query("neili") < 1000 )
                return notify_fail("�������������㣬����ʹ�á����ӷ�������\n");

    if((int)me->query("jingli") < 1000 )
                return notify_fail("������̫���ˣ�����ʹ�á����ӷ�������\n");
    if((int)me->query("hjdf/fanshen")  )
                return notify_fail("������ʹ�á����ӷ�������\n");
      
    message_vision(RED"\n$N�������������ǲ������ܣ�����$n��������ߣ��͵�ת��ˢ��һ����\n��Ȼʩչ�����ҵ���֮"HIG"�����ӷ�����"RED"����!\n"NOR, me,target);
        
    me->add("neili", -800);
    me->add("jingli",-500);
    me->set_temp("hjdf/fanshen",1);

  
    if (random(me->query("combat_exp"))>target->query("combat_exp")/2
		||random(me->query_dex(1))>target->query_dex(1)/2)
    {  
	
	    message_vision(HIR"\n\n$nȴ��$N��Ȼ���������е�"+weapon->query("name")+HIR"����$n�ұۣ�$n�ҽ�һ�����ֱ����ϣ�\n"NOR,me,target);
		//target->set_temp("must_be_hit",1);
		damage=i+me->query_skill("force",1)+me->query_skill("blade",1);
		damage=damage*me->query_dex(1)/10;
		
		if (userp(target) && damage >6000) damage=6000+random(1000);
		
		
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/4,me);
        if (wizardp(me)) write("damage="+damage);
       
		target->apply_conditon("broken_arm",1);

		msg = damage_msg(damage, "����");
		msg = replace_string(msg, "$w", weapon->query("name"));
		msg = replace_string(msg, "$l", "�ֱ�");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));        
    	
    } else
	{
		message_vision(HIC"$n����һ�������Ŷ�����У���ȴ����һ���亹��\n"NOR,me,target);
		target->apply_condition("no_exert",1);
		target->add_busy(1);
		me->add_busy(2);
		
	}
   
    me->delete_temp("hjdf/fanshen");
   // me->start_busy(1);
	me->start_perform(2+random(2),"�����ӷ�����");
    //target->start_busy(1);
    return 1;
}

int help(object me)
{
   write(YEL"\n���ҵ���֮��"HIG"���ӷ���"YEL"����"NOR"\n");
   write(@HELP
	���ҵ������Ǵ����ɶ�������һ���ļҴ�����������
	��һ�������˷�˴˼�����˶�Թ֮��ʹ�ú����
	�佭����ƾ��˵����ݺὭ�����˵��о�����
	���ӷ������������ø߳��������ƣ����ٷ�Ӧ��
	�����ݺ�۳ң�����˷���ʤ���䣬����һ��������
	����Է��ֱۣ�ʹ���Ƶ��˳ʶ���״̬���쳣�׺���
	ע�⣺���ӷ�����Ҫ��������������

	ָ�perform blade.fanshen

Ҫ��
	���ҵ��� 250 ����
	�������� 250 ����
	�����Ṧ 250 ����
	�����ڹ� 250 ����
	������� 5000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	��������Ϊ���ҵ�����
	�ֳֵ���������
HELP
   );
   return 1;
}