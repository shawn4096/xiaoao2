// liuxing.c  Ѫ���� [���Ǿ���]
// cre by sohu@xojh
//ͻȻ���һ����Ѫ����б����ɽ���������أӥ��Ϊ���ߣ����������ԡ�
#include <ansi.h>
#include <skill.h>
#include <combat.h>
#include <weapon.h>
inherit F_SSERVER;
 
string perform_name(){ return HIC"��"HIR"��"HIG"��"HIY"��"NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int jixue;
    //���Ǿ�������ս���Ϳ��Է��У���
       // if( !me->is_fighting() )
                //return notify_fail("�����Ǿ��졹ֻ����ս����ʹ�á�\n");
        if( !target ) target = offensive_target(me);
        if( !objectp(target))
                return notify_fail("����û������ˡ�\n");
        if(target==me)
                return notify_fail("�㲻�ܹ����Լ���\n");

        if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "blade")
                return notify_fail("�����Ǿ��졹��Ҫ�䱸��������ʹ�ã���ʹ�õ��������ԡ�\n");

        if((int)me->query_dex() < 35)
                return notify_fail("���������, Ŀǰ������ʹ���������! \n");

        if((int)me->query_skill("dodge",1) < 200)
                return notify_fail("��Ļ����Ṧ��Ϊ����, ����ʹ�á����Ǿ��졹��\n");
        if((int)me->query_skill("blade",1) < 200)
                return notify_fail("��Ļ���������Ϊ����, ����ʹ�á����Ǿ��졹��\n");

        if((int)me->query_skill("xuedao-jing",1) < 200)
                return notify_fail("���Ѫ������Ϊ������ Ŀǰ����ʹ�á����Ǿ��졹! \n");

        if((int)me->query_skill("xuedao-daofa",1) < 200)
                return notify_fail("���Ѫ��������Ϊ������ Ŀǰ����ʹ�á����Ǿ��졹! \n");

        if( me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("�����ʹ��Ѫ����������ʹ�á����Ǿ��졹�ľ�����\n");
		if ( me->query_skill_mapped("parry") != "xuedao-daofa" && me->query_skill_mapped("parry") != "jingang-liantishu")
             	return notify_fail("����мܲ��ԣ����뼤������ΪѪ������������������\n");

        if( me->query_skill_mapped("force") != "shenzhao-jing" && me->query_skill_mapped("force") != "xuedao-jing")
	    	  return notify_fail("��������ʹ�õ��ڹ�ͬ��Ѫ��������ִ�������ʹ�������Ǿ��졹�ľ�����\n");

        if( (int)me->query("max_neili") < 2000 )
                return notify_fail("������������Ϊ������\n");
        if((int)me->query("neili")<1000)
                return notify_fail("�������������\n"); 
        if((int)me->query("jingli")<600)
                return notify_fail("��ľ���������\n"); 

        if(me->query_temp("xddf/liuxing"))
                return notify_fail("������ʩչ�����Ǿ��졹��\n"); 


        
		msg =RED "\nͻȻ���һ����$N������"+weapon->query("name")+RED"��б����ɽ�����������һ�����������ȥ��\n"+
			"����Ѫ�����е�һ�С����Ǿ��졹������\n"NOR;
        message_vision(msg, me);
		//Ѫ������������ʱ������ɱ��Խ�࣬Ѫ����Խ��
		
		jixue=weapon->query_temp("xdj/jixue");
		if (jixue<1) jixue=1;
		if (jixue>5) jixue=5;
		
		//target=me->select_opponent();

		me->add("jingli",-100-random(200));
		me->add("neili",-50-random(200));
		
		//call_out("lx_attack",5-jixue,me,target,weapon);
		call_out("lx_attack",5-jixue,me,target,weapon);
		
		//me->start_perform(2,"���Ǿ���");
		me->set_temp("xddf/liuxing",1);
		return 1;

		      		
}
int lx_attack(object me,object target,object weapon)
{
	
	int damage,jixue;
	//����������δ���
	if (!me) return 0;
	
	jixue=me->query_temp("xdj/jixue");
	
	if (!objectp(target)||!weapon) 
	{
			message_vision(RED"$N����һ�У�"+weapon->query("name")+RED"�·��������һ���ַ��˻�����\n"NOR,me);
			me->add("jingli",-200);
			me->add("neili",-250);
			me->delete_temp("xddf/liuxing");
			return 1;
	}

	
	//target=me->select_opponent();
	damage=(me->query_skill("xuedao-jing",1)+me->query_skill("xuedao-jing",1))*jixue;
	damage=damage+random(damage);
	//npc����ɱ�ˣ��������
	if (userp(target)&&damage>3500) damage=3500+random(500);
	
	if (random(me->query_skill("blade",1))>target->query_skill("dodge",1)/2
		||random(me->query("combat_exp"))>target->query("combat_exp")/2)
	{
		message_vision(HIR"$n������ǰ��ɫ���һ����һ��"+weapon->query("name")+HIR"������������������������\n"NOR,me,target);
	//	tell_object(me,HIC"damage="+damage+NOR);
		
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/2,me);
		target->add_busy(1);
		if (objectp(target)&&me->is_fighting())
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	}
	else {
		message_vision(WHT"$n��æ��һ����¿�������Ȼ��ʽ�ѿ�Щ�����վ��Ƕ�����������\n"NOR,me,target);
		target->add_busy(2);
	}
	message_vision(RED"$N�������Ծ����У�����ץ�����У��������У�\n"NOR,me);
	me->delete_temp("xddf/liuxing");
	//me->start_perform(2,"���Ǿ���");
	return 1;

}
int help(object me)
{
	write(RED"\nѪ������֮�����Ǿ��졹��"NOR"\n\n");
        write(@HELP

	���Ǿ�������Ѫ����������似�����Ī��ĵ�������
	ƾ��߳��ļ��պ������ڹ����Ʒ��ţ�һ���ɳ���ɱ
	����������֮�⡣����Խ��񣬷����ٶ�Խ������Խ��
	��Ҫע����ǣ�Ѫ����������Ѫ��������Ѫ����Խ�࣬
	��������Խ�����Ǿ���Ĵ���ʱ��Խ�̡�
	
	ָ��: perform blade.liuxing

Ҫ��
	������� 2000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 600  ���ϣ�
	��ǰ�� 35   ���ϣ�
	Ѫ������ 200  �����ϣ�
	�������� 200  �����ϣ�
	Ѫ����   200  ������;
	��������Ѫ��������
	�����м�ΪѪ���������ջ�������
	�ֳֵ���������

HELP
        );
        return 1;
}