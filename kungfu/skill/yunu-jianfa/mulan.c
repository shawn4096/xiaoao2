//  mulan.c ľ������ 
//Created by sohu@xojh 2014/9

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return HBRED"ľ������"NOR;}

int perform(object me,object target)
{
    object weapon;
    int i;
    i = me->query_skill("yunu-jianfa", 1);
    if( !target ) target = offensive_target(me);
     
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("��ľ�����䡹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if((int)me->query_skill("force", 1) < 150 )
                return notify_fail("��Ļ����ڹ�������죬�޷�֧�֡�ľ�����䡹��\n");

    if( (int)me->query_skill("yunu-jianfa", 1) < 150 ) 
                return notify_fail("�����Ů������δ���ɣ�����ʹ�á�ľ�����䡹��\n");

    if((int)me->query_skill("sword", 1) < 150 )
                return notify_fail("��Ļ�������������죬�����ڽ�����ʹ�á�ľ�����䡹��\n");

    if((int)me->query_skill("dodge", 1) < 150 )
                return notify_fail("��Ļ����Ṧ������죬����ʹ�á�ľ�����䡹��\n");
	if((int)me->query_dex() < 40 )
                return notify_fail("��ĺ���������������ʹ�á�ľ�����䡹��\n");
    if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "yunu-jianfa"
        || me->query_skill_mapped("parry") != "yunu-jianfa")
                return notify_fail("�������޽������ʹ�á�ľ�����䡹��\n");
                
    if((int)me->query("max_neili") < 1200 )
                return notify_fail("���������Ϊ����������ʹ�á�ľ�����䡹��\n");

    if((int)me->query("neili") < 500 )
                return notify_fail("�������������㣬����ʹ�á�ľ�����䡹��\n");

    if((int)me->query("jingli") < 300 )
                return notify_fail("������̫���ˣ�����ʹ�á�ľ�����䡹��\n");
    if((int)me->query("ynjf/mulan")  )
                return notify_fail("������ʹ�á�ľ�����䡹��\n");
      
    message_vision(HIR"\n$N����ǰԾ������֮�ʣ������е�"+weapon->query("name")+HIR"ͻȻͦ���򱳺�̳�����$n���ؿڣ�\n"NOR, me,target);
    message_vision(HIR"\n������Ů������һ��"HIC"��ľ�����䡹"HIR"������\n"NOR, me,target);
        
    me->add("neili", -100);
    me->add("jingli",-50);
    me->set_temp("ynjf/mulan",1);

  
    if (random(me->query("combat_exp"))>target->query("combat_exp")/2
		|| random(me->query_dex(1))>target->query_dex(1)/2)
    {  
	    message_vision(HIY"\n\n$n��׷��֮�ʣ�������$N���С�ľ�����䡹һ�������ؿڣ���Ѫ�Ž���\n"NOR,me,target);
		if (userp(target))
		{		
			target->receive_damage("qi",3000+random(1000),me);
			target->receive_wound("qi",1000+random(500),me);
		}
		else {
			target->receive_damage("qi",4000+random(2000),me);
			target->receive_wound("qi",2000+random(1000),me);
		}
		target->apply_condition("no_exert",1);
		if (!userp(target)) target->add_busy(3);
		me->add_temp("apply/damage",i/6);
		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if (me->query_skill("yunu-jianfa",1)>200 && me->is_fighting())
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/damage",-i/6);
	            	
    }else
	{
		message_vision(HIC"\n\n$n���¼�æ���ˣ�����������У�����һ���亹��\n"NOR,me,target);
		me->add_busy(1);
	}
	
    me->delete_temp("ynjf/mulan");
    
	me->start_perform(3,"��ľ�����䡹");
    
	return 1;
}


int help(object me)
{
	write(WHT"\n��Ů����֮"HBRED"��ľ�����䡹��"NOR"\n");
	write(@HELP
	��Ů�������ؾ��У����Ĺ��ΪŮ�ӣ�������Ů����
	������ʤ�����ǿ����о�����������ʽ�����鶯��ʤ
	������������,��̬ƮƮ����,��������Ʈ�ݷ��ˣ��
	����ӡ�
	ľ�����䣬�ڱ��ܶ���֮�ʣ��ӱ�����������жԷ�

	perform sword.mulan
	
Ҫ��
	��ǰ����Ҫ�� 500 ���ϣ�
	��ǰ����Ҫ�� 300 ���ϣ�
	�������Ҫ�� 1200 ����
	��Ů�����ȼ� 150 ���ϣ�
	��Ů�ľ��ȼ� 150 ���ϣ�
	�����ڹ��ȼ� 150 ���ϣ�
	�������ȼ� 150 ���ϣ�
	���������ȼ� 150 ���ϣ�
	��Ч���ȼ� 40  ���ϣ�
	��������Ϊ��Ů������
	�����м�Ϊ��Ů������
	�ֳֽ��������
HELP
	);
	return 1;
}