inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>
#include <combat.h> 

int perform(object me, object target)
{
	int damage,p;
	string msg,msg2;
        
	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("�����ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( me->query_temp("weapon"))
		return notify_fail("�����������޷�ʹ�á����ơ���\n");   

	if( (int)me->query_skill("chuanyun-tui",1) < 100 )
		return notify_fail("��Ĵ����ȷ���Ϊ���㣬ʹ���������ơ���\n");
	
	if( (int)me->query("max_neili") < 1000 )
		return notify_fail("�㹦��̫��������ʹ�������ơ���\n");
	
	if( (int)me->query("neili") < 800 )
		return notify_fail("����������̫��������ʹ�������ơ���\n");
	
	if( (int)me->query("jingli") < 500 )
		return notify_fail("�������޾���ɣ�����ʹ�������ơ���\n");

	if (me->query_skill_prepared("leg") != "chuanyun-tui")
		return notify_fail("��û��ʹ�ô����ȣ������޷�ʹ�������ơ���\n");
    
	if(me->query_temp("klpfm/chuanyun"))
      return notify_fail("����ʱ����ʹ�á����ƾ������ˡ�\n");  
                
		message_vision(HIW"\n$NͻȻ�������ת���������𣡵���һ���߳���״�������ơ���������������������\n"NOR,me,target);
		damage  = (int)me->query_skill("leg");
		damage += (int)me->query_str()*10;
		damage += (int)me->query_dex()*10;
		damage += (int)me->query("jiali");
		damage  = damage*2+random(damage);
	if (damage>4000) damage=3000+random(1000);
	if (!userp(me)&&userp(target))
	{
		damage=damage/2;
	}
    if( random(me->query_skill("chuanyun-tui",1))> (int)target->query_skill("parry",1)/2
		  ||random(me->query_dex(1))>target->query_dex(1)/2) 
	{
		message_vision(HIY"$nһʱ���죬��$N�Ľż������ؿڴ�Ѩ����ʱ��Ѫ���費����\n"NOR, me,target);
		target->add_busy(1+random(2));
	//	damage *= 2;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/5, me);
		p = (int)target->query("qi")*100/(int)target->query("max_qi");
		msg = HIR"������ص�����$n���ؿڣ�$n��ʱ��Ѫ���磬��󵹷ɳ�ȥ��\n"NOR;
		msg += "( $n"+eff_status_msg(p)+" )\n"; 
		message_vision(msg, me, target);
		if(userp(me) && me->query("env/damage")) 
			tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"�㹥���˺���\n"NOR);
		if(userp(target)&& target->query("env/damage")) 
			tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR);
		//Ů�Ը����˺�
		if(me->query("gender")=="Ů��") {
			damage=damage/2+random(damage)/2;
			target->receive_damage("qi", damage, me);
			//target->receive_wound("qi", damage/2, me);
			p = (int)target->query("qi")*100/(int)target->query("max_qi");
			msg = HIW"$N��״�������˲��ȹ�׻γ�һ������ȣ�����"HIY"�������ȡ�"HIW"����ʽ��������$n��Ҫ��֮����\n"NOR;
			msg += damage_msg(damage, "����");
			msg += "( $n"+eff_status_msg(p)+" )\n"; 
			message_vision(msg, me, target);
			if(userp(me) && me->query("env/damage")) 
				tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"�㹥���˺���\n"NOR); 
			if(userp(target)&& target->query("env/damage")) 
				tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR);
		}
	
	
	}
	else {
		message_vision(HIC"\n$n�������ǣ�ͻȻ���һ���յ������ȥ��������һ���亹��\n"NOR, me,target);	
		me->start_busy(random(2));		
	}
		
		me->add("neili", -150);
		me->add("jingli", -50);

		me->start_perform(3,"�����ƾ�����");
		return 1;
}

string perform_name(){ return HIW"�� ��"NOR; }

int help(object me)
{
        write(HIW"\n������֮�����ơ���"NOR"\n\n");
        write(@HELP
	�����������������µ��������似��ƾ��������
	ɽ�ϱ���ѩ�������͵ĸ߳��ȷ���������������
	�ȵ�����ص���Ѹ�����������͡�������������
	�ǵļ��ܡ����ȷ��������ƿ��Ի�����
	�������似�ȼ������йأ�����Ů�Ա�������
	�������ƣ��˺�����������йء�

	ָ�perform leg.chuanyun

Ҫ��
	��ǰ����   800 ���ϣ�
	�������  1000 ���ϣ�
	��ǰ����   500 ���ϣ�
	�����ȵȼ� 100 ���ϣ�
	�����ȷ�Ϊ�����ȣ�
	���ȷ�Ϊ�����ȣ�
	�����ޱ�����

HELP
        );
        return 1;
}
