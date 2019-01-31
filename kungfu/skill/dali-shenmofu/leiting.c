// leiting �������
// edited by sohu 2013

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me);

int perform(object me, object target)
{
	object weapon;
	string msg;
	int damage, p, ap, dp;
	//int focus = me->query_temp("ss/focus");
	int j;
	        
	if( !target ) target = offensive_target(me);

	if( !objectp(target) ||!living(target)|| !me->is_fighting(target) )
		return notify_fail("�����������ֻ����ս����ʹ�á�\n");
        
	if( (int)me->query_skill("dali-shenmofu", 1) < 250 )
		return notify_fail("��Ĵ�����ħ����������죬�޷�ʹ���������������\n");

	if (me->query_skill_mapped("force") != "tianmo-gong" )
       if(me->query_skill_mapped("force") != "xixing-dafa")
                return notify_fail("����ʹ�õ������ڹ����ԡ�\n"); 

    if(me->query_skill("xixing-dafa", 1)<250)
       if(me->query_skill("tianmo-gong", 1) < 250)
                return notify_fail("�������ڵ��ڹ���Ϊ��������ʹ�����������������\n");  

	if (!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "axe"
	|| me->query_skill_mapped("axe") != "dali-shenmofu"
	|| me->query_skill_mapped("parry") != "dali-shenmofu" )
		return notify_fail("���޷�ʹ��������ħ��ͷ�ġ������������\n");

	if (me->query_temp("dlf/leiting"))
		return notify_fail("������ʹ�á��������������Ϣһ�°ɡ�\n"); 
                
	if( (int)me->query("max_neili") < 2000)
		return notify_fail("���������Ϊ̫��޷�ʹ���������������\n");
                
	if( (int)me->query("neili") < 1000)
		return notify_fail("����������̫����ʹ�����������������\n");
	
	j = me->query_skill("dali-shenmofu", 1);
	
	if ( me->query_skill("dali-shenmofu", 1) > 350 )
		j = to_int( j/3* j/ 275.0);

	//j += focus * 5;
			
	me->set_temp("dlf/leiting",1);
	me->add_temp("apply/attack",j/2 );
	me->add_temp("apply/damage", j/2);
	
	//target->set_temp("combat_msg/dodge",HIY"��Ȼ�䣬һ����Ӱ��˸��$n˲����󻬳����࣬�����ֻص���ԭ�ء�\n"NOR );
			
	//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER );
	
	//target->delete_temp("combat_msg/dodge");
	me->add_temp("apply/damage", -j / 2);
	me->add_temp("apply/attack",-j / 2 );
	
		
	msg = HBRED"\n$N���һ����ȫ���������е����ұ�֮�ϣ������е�"+weapon->query("name")+HBRED"��Բ�����糵�֣�ȫ������$n���˳�ȥ��\n"
	+"��һ�����󸫳�����ȴѸ���ޱȣ�������������������������ͼһ�ж�����!\n"NOR;

	ap = me->query("combat_exp", 1) / 1000 * me->query_skill("axe",1);
	dp = target->query("combat_exp",1 ) / 1000 * target->query_skill("dodge",1);

	if ( target->is_busy()||!userp(target))
		dp -= dp/2;

	if( random( ap + dp) > dp ) {
		msg += HIR"\n$n�����д�����ħ�������������ʽ���ƣ�����һײ����ʱ������Ѫ���������\n"NOR;
		damage = me->query_skill("axe",1) + me->query_skill("force",1)+ me->query_skill("dali-shenmofu",1);
		damage = damage * 5;
		damage += random(damage);

		if( damage > 6000) 
			damage = 6000 + (damage- 6000)/10;
       
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/2, me);

		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
		me->add("neili", -350);
		me->add("jingli", -150);
	} 
     else {
		msg += HIW"ͻȻ֮�䣬��Ӱ���Σ�$n��󻬳����࣬��ʱ�ֻص���ԭ�ء�\n"NOR;
		me->add("neili", -100);
		me->add("jingli", -80);
	}
	message_vision(msg, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add("neili", -100);
	me->add("jingli", -80);
	me->delete_temp("dlf/leiting");
	me->start_perform(3, "�������");
	me->start_busy(random(2));
        return 1;
}

string perform_name(){ return HBYEL+RED"�������"NOR; }

int help(object me)
{
        write(HBYEL+RED"\n������ħ��֮�������������"NOR"\n\n");
        write(@HELP
		
        Ҫ��  ��ǰ���� 1000 ���ϣ�
                ������� 2500 ���ϣ�
                ��ǰ���� 1000 ���ϣ�
                ������ħ���ȼ� 250 ���ϣ�
                ��Ч�ڹ��ȼ� 250 ���ϣ�
                ��������Ϊ������ħ����
                �����м�Ϊ������ħ����
                �����ڹ�Ϊ��ħ�������Ǵ󷨣�
                ���ֱֳ�����

HELP
        );
        return 1;
}
