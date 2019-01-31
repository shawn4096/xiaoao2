// leiting ����һ��
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
	int focus = me->query_temp("ss/focus");
	int j;
	        
	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("������һ����ֻ����ս����ʹ�á�\n");
        
	if( (int)me->query_skill("songshan-jian", 1) < 220 )
		return notify_fail("�����ɽ������������죬�޷�ʹ��������һ������\n");
	
	if( (int)me->query_skill("force", 1) < 220 )
		return notify_fail("��Ļ����ڹ���������죬�޷�ʹ��������һ������\n");

	if( (int)me->query_skill("hanbing-zhenqi", 1) < 220 )
		return notify_fail("��ĺ��������ȼ����������޷�ʹ��������һ������\n");

	if (me->query_skill_mapped("force") != "hanbing-zhenqi")
		return notify_fail("��Ŀǰ���ڹ��޷�ʹ��������һ������\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("sword") != "songshan-jian"
	|| me->query_skill_mapped("parry") != "songshan-jian" )
		return notify_fail("���޷�ʹ��������һ������\n");

	if (me->query_temp("ss/leiting"))
		return notify_fail("���ʹ���꡸����һ��������Ϣһ�°ɡ�\n"); 
                
	if( (int)me->query("max_neili") < 2500)
		return notify_fail("���������Ϊ̫��޷�ʹ��������һ������\n");
                
	if( (int)me->query("neili") < 1000)
		return notify_fail("����������̫����ʹ����������һ������\n");
	
	j = me->query_skill("songshan-jian", 1);
	
	if ( j > 350 )
		j = to_int( j/4* j/ 350.0);

	j += focus * 5;
			
	me->set_temp("ssj/leiting",1);
	me->add_temp("apply/attack",focus * 10 );
	me->add_temp("apply/damage", (int)j/3);
	target->set_temp("combat_msg/dodge",CYN"ͻȻ֮�䣬��Ӱ���Σ�$n��󻬳����࣬��ʱ�ֻص���ԭ�ء�\n"NOR );
			
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER );
	
	target->delete_temp("combat_msg/dodge");
	me->add_temp("apply/damage", -(int)j/3);
	me->add_temp("apply/attack",-focus * 10 );
	
	me->delete_temp("ssj/leiting");
		
	msg = YEL"\n$N��������������������ƳԱ��˷�ķ���һ�㣬ȫ���������е����ұ�֮�ϣ�ȫ������$n�̳���\n"NOR;

	ap = me->query("combat_exp", 1) / 100000+ focus * 10;
	dp = target->query("combat_exp",1 ) / 100000 ;

	if ( target->is_busy()||!userp(target))
		dp -= dp/3;

	if( random( ap + dp) > dp 
		||random(me->query_skill("sword",1))>target->query_skill("dodge",1)/3) {
		msg += HIR"$n����������һ�����ͻ�����һײ����ʱ������Ѫ���������\n"NOR;
		damage = me->query_skill("sword",1) + me->query_skill("force",1);
		damage = damage * (focus+1);
		damage += random(damage);

		if( damage > 4500) 
			damage = 4500 + (damage- 4500)/100;

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
		msg = replace_string( msg, "$w", weapon->query("name"));
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
		me->add("neili", -350);
		me->add("jingli", -150);
	} 
       else {
		msg += CYN"ͻȻ֮�䣬��Ӱ���Σ�$n��󻬳����࣬��ʱ�ֻص���ԭ�ء�\n"NOR;
		me->add("neili", -100);
		me->add("jingli", -80);
	}
	message_vision(msg, me, target);
	//COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add("neili", -500);
	me->add("jingli", -350);
	me->start_perform(3, "����һ��");
	me->start_busy(random(2));
    return 1;
}

string perform_name(){ return HBWHT+HIG"����һ��"NOR; }

int help(object me)
{
        write(HBYEL+RED"\n��ɽ����֮������һ������"NOR"\n\n");
        write(@HELP
	��ɽ�����С��ڰ�·�����·��֮�ƣ��ܹ�ʮ��·���̿����Ľ���
	Ӧ�о��С���������������ħ��ʮ�������Ȼ�ս��ɽ����������
	�ĺ������˴��������ɽ�������ྪ�����������ɸ��ֶ����š�
	��ɽ�������������Ἧ���ɲд�����ϣ����������ǵõĽ��в�
	�۴־�������¼�����������һ�����ס�
	����һ����ʽ����ɽ�ɵľ���֮һ�����ǽ��Լ�������������һ
	�㣬����ɽ�鱬����һ�беУ�������Ҫǿ�������֧�֡�
	
	ָ�perform sword.leiting
		
Ҫ��
	��ǰ�������� 1000 ���ϣ�
	����������� 2500 ���ϣ�
	��ǰ�������� 1000 ���ϣ�
	��ɽ�����ȼ� 220 ���ϣ�
	���������ȼ� 220 ���ϣ�
	��Ч�ڹ��ȼ� 220 ���ϣ�
	��������Ϊ��ɽ������
	�����м�Ϊ��ɽ������
	�����ڹ�Ϊ����������
	���ֱֳ�����

HELP
        );
        return 1;
}
