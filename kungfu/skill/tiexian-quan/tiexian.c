//tiexian.c ��ȭ����
//by sohu
//�Ű���

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HIR"��ȭ����"NOR; }

int perform(object me, object target)
{
	object weapon;
	int damage, ap, dp, p;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("����ȭ���ߡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("�������ֲ��ܴ��С�\n");

	if( (int)me->query_skill("tiexian-quan", 1) < 100 )
		return notify_fail("�������ȭ��������죬�޷�ʹ����ȭ���ߡ�\n");

	if ( me->query_skill_mapped("cuff") != "tiexian-quan"
	|| me->query_skill_mapped("parry") != "tiexian-quan")
		return notify_fail("�������޷�ʹ����ȭ���ߡ�\n");

	if( (int)me->query_skill("force", 1) < 100 )
		return notify_fail("��Ļ����ڹ������ߡ�\n");
	if( (int)me->query_skill("cuff", 1) < 100 )
		return notify_fail("��Ļ���ȭ�������ߡ�\n");

	if((int)me->query("max_neili") < 3000 )
		return notify_fail("������������Ϊ�������޷�ʹ�á���ȭ���ߡ���\n");

    if( (int)me->query("neili", 1) < 500 )
		return notify_fail("�㵱ǰ����̫��������ʹ�á���ȭ���ߡ���\n");
	
	msg = CYN "\n$N��������һ��������Ȼ��ȵ�������ȭ���ߡ�����Ȼһȭ���������һ�����ߣ�\n"NOR;

	ap = me->query("combat_exp", 1) / 1000 * me->query_skill("blade");
	dp = target->query("combat_exp", 1)/ 1000 * target->query_skill("parry");

	if ( random(ap + dp) > dp ){
		damage = me->query_skill("blade") * 4;
		damage += me->query_skill("force") * 4;
		damage = damage + random(damage);
		if (damage > 4500) damage = 4500+random(damage-3500)/10;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		me->add("neili", -250);
		me->add("jingli", -80);
		msg += HIR"ֻ��$N��ȭ��Ϊһ�ߣ�$nֻ��һ�������������������������һȭ�����ؿڣ������Ѫ��\n"NOR;
	
	   if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
	   	}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
	   message_vision(msg, me, target);
			
	}
	else {
		msg += CYN"����$p���з�����Ц��������������ȭ���������Ǵ󣬵����κε����ң�\n"NOR;
		me->add("neili", -100);
		message_vision(msg, me, target);
		}	
	me->start_busy(1+random(2));
	me->start_perform(3, "��ȭ����");
	
	return 1;
}
int help(object me)
{
        write(CYN"\n����ȭ֮����ȭ���ߡ���"NOR"\n");
        write(@HELP
	����ȭ���ǽ�����������Ű����ľ�ѧ�����䳣��������
	��������ţ������������һ��������������ȭһ������
	���г��ߣ���Ϊ�ķ�������ͬʱҲ����һ���������Ĺ�Ч

	ָ�perform cuff.tiexian

Ҫ��  
	�����������  1400 ���ϣ�
	��ǰ��������  500  ���ϣ�
	����ȭ���ȼ� 250 ���ϣ�
	�����ڹ��ȼ� 250 ���ϣ�
	����ȭ���ȼ� 100 ���ϣ�
	����ȭ������ȭ��
	�����м�����ȭ��
	�����ұ�����ȭ��
HELP
        );
        return 1;
}
                                                                                                                                                    