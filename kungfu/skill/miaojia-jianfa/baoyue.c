// baoyue.c ���б���
// Created by sohu@xojh 2015 

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
int baoyue_back(object me);

void remove_effect(object me);

int perform(object me, object target)
{
	object weapon;
	int focus;
	int j,ap,dp,damage,p;
	string msg;
	if (me->query_skill_mapped("force") == "lengquan-shengong")
		focus =me->query_skill("force",1)+ me->query_skill("lengquan-shengong",1);
	else focus =me->query_skill("force",1);
	
	        
	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("��ϴ�����б��¡�ֻ����ս����ʹ�á�\n");
        
	if( (int)me->query_skill("miaojia-jianfa", 1) < 350 )
		return notify_fail("�����ɽ������������죬�޷�ʹ����ϴ�����б��¡���\n");

	if( (int)me->query_skill("force", 1) < 350 )
		return notify_fail("��Ļ����ڹ��ȼ����������޷�ʹ����ϴ�����б��¡���\n");
	if( (int)me->query_skill("sword", 1) < 350 )
		return notify_fail("��Ļ��������ȼ����������޷�ʹ����ϴ�����б��¡���\n");
	

	if (!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "sword"
	//|| me->query_skill_mapped("parry") != "miaojia-jianfa"
	|| me->query_skill_mapped("sword") != "miaojia-jianfa" )
		return notify_fail("���޷�ʹ����ϴ�����б��¡���\n");

	if (me->query_temp("mjjf/baoyue"))
		return notify_fail("������ʹ�á�ϴ�����б��¡�����Ϣһ�°ɡ�\n"); 
    if (target->is_busy())
		return notify_fail("�Է��Ѿ���æ�����ˣ�����ʹ�����С�ϴ�����б��¡���\n"); 
           
	if( (int)me->query("max_neili") < 5000)
		return notify_fail("���������Ϊ̫��޷�ʹ����ϴ�����б��¡���\n");
                
	if( (int)me->query("neili") < 1000)
		return notify_fail("����������̫����ʹ������ϴ�����б��¡���\n");
	if( (int)me->query("jingli") < 1000)
		return notify_fail("�����ھ���̫����ʹ������ϴ�����б��¡���\n");

	j = me->query_skill("miaojia-jianfa", 1);
			
	me->set_temp("mjjf/baoyue",1);

	me->add_temp("apply/attack",j/2);
	me->add_temp("apply/damage", j/2);
	
	target->set_temp("combat_msg/dodge",HIY"ͻȻ֮�䣬����һ�Σ�$n��󻬳����࣬��ʱ���絯��һ���ص���ԭ�ء�\n"NOR );
			
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER );
	
	target->delete_temp("combat_msg/dodge");
	
	me->add_temp("apply/damage", -j / 2);
	me->add_temp("apply/attack",-j/2 );
	
		
	message_vision(RED"\n$n��֪$N���书���������������뻯��������Σ��֮�䣬$N˫��һ�������ⶸȻ�����Լ����ؿڡ�\n"
	                  +"$n���һ����ֻ��$N��������,�����ϵ�$N�ؿ�һ�������ǽ��������ϣ���Ȼ�����������������õ���$n�ؿڡ����Ѩ����\n"NOR,me,target);

	ap = me->query("combat_exp", 1) / 1000;
	dp = target->query("combat_exp",1 ) / 1000 ;
	
	if ( target->is_busy())
		dp -= dp/3;

	if( random( ap + dp) > dp 
		||random(me->query_skill("sword",1))>target->query_skill("parry",1)/2)
	{
		message_vision(HIR"\n$n�����С�ϴ�����б��¡��ķ�������һײ�����ζ�ʱ���ƣ�ͬʱ������Ѫ���������\n"NOR,me,target);
		damage = me->query_skill("sword",1) + focus;
		damage = damage * (int)me->query_str()/20;
		damage += random(damage);

		if( damage > 4500) 
			damage = 4500 + (damage- 4500)/5;

		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/2 + random(damage/2), me);
		
		target->add_busy(2);
		if (!userp(target))
			target->add_busy(2+random(2));
		
		if (random(2))
			target->apply_condition("no_exert",2);
		else target->apply_condition("no_perform",2);

		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg = COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg = COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->query("name"));
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
		me->add("neili", -350);
		me->add("jingli", -150);
	} 
      else {
		message_vision(CYN"ͻȻ֮�䣬��Ӱ���Σ�$n��󻬳����࣬��ʱ�ֻص���ԭ�ء�\n"NOR,me,target);
		me->add_busy(1);
		me->add("neili", -100);
		me->add("jingli", -80);
	}
	//message_vision(msg, me, target);
	call_out("baoyue_back",2,me);
	me->add("neili", -100);
	me->add("jingli", -80);
	if (me->query_skill("miaojia-jianfa",1)<350)
		me->start_perform(3, "ϴ�����б���");
	else if (me->query_skill("miaojia-jianfa",1)<450)
		me->start_perform(1, "ϴ�����б���");
	//me->start_busy(random(2));
    return 1; 
}
int baoyue_back(object me)
{
	if (!me) return 1;
	
	if (me->query_temp("mjjf/baoyue"))
	{
		me->delete_temp("mjjf/baoyue");
		message_vision(CYN"$N˫���ſ�������ϴ�����б��¡��������С�\n"NOR,me);
		return 1;

	}

}

string perform_name(){ return RED"ϴ�����б���"NOR; }

int help(object me)
{
        write(YEL"\n��ҽ���֮��ϴ�����б��¡���"NOR"\n\n");
        write(@HELP
	��ҽ������Ǵ�������޵��ֵ����˷�Ҵ�����
	�ý���ʤ������䣬�����쳣������û������
	ʵ�������в��ɶ�õ�һ���似��
	��ϴ�����б��¡������ù��Լ������ڹ�����
	��ǿ�����ھ����������ڻ��У��������ޣ����
	�����ڹ������Խ������жԷ�Ѩ����Ȼ��˳��
	������
	
	ָ��:perform sword.baoyue

Ҫ��
	��ǰ�������� 1000 ���ϣ�
	����������� 5000 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	��ҽ����ȼ� 350 ���ϣ�
	�����ڹ��ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	��������Ϊ��ҽ�����
	���ֱֳ�����

HELP
        );
        return 1;
}
