// chou.c  �嶾�� ˦��

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return RED"��˦��"NOR; }

int perform(object me, object target)
{
	object weapon;
	int damage, ap, dp, p;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("��˦�项ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "whip")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if( (int)me->query_skill("wudu-bian", 1) < 100 )
		return notify_fail("����嶾�޲�����죬�޷�ʹ��˦�顣\n");

	if ( me->query_skill_mapped("parry") != "wudu-bian"
	|| me->query_skill_mapped("whip") != "wudu-bian")
		return notify_fail("�������޷�ʹ��˦�顣\n");

	if( (int)me->query_skill("tianmo-gong", 1) < 100 )
		if( (int)me->query_skill("xixing-dafa", 1) < 100 )
		return notify_fail("��������ڹ������ߡ�\n");

	if((int)me->query("max_neili",1) < 1400 )
		return notify_fail("���������Ϊ�������޷�ʹ�á�˦�项��\n");

    if( (int)me->query("neili", 1) < 500 )
		return notify_fail("����������̫��������ʹ�á�˦�项��\n");
	
	msg = CYN "\n$N��ɫ���䣬����Ʈ�����������󼲶�������"+weapon->query("name")+CYN"һ����˦�����$n����ա�\n"NOR;

	ap = me->query("combat_exp", 1) / 10000 ;
	dp = target->query("combat_exp", 1)/ 10000 ;
	if (me->query("gender")=="Ů��")
	{
		ap+=ap/2;
	}else ap=ap/2;
	if ( random(ap + dp) > dp
		||random(me->query_skill("whip",1))>target->query_skill("parry",1)/2)
	{
		damage = me->query_skill("whip",1)*2;
		damage += me->query_skill("force",1)*2;
		damage = damage*3 + random(damage);
		if (damage > 2500) damage = 2500+random(damage-2500)/100;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		me->add("neili", -250);
		me->add("jingli", -80);
		msg += HIR"\nֻ��$N��˸������˦�����ޡ�ž����һ��ɽ�죬$n����������Ϊ$Nһ�޳�������һ�����\n"NOR;
	
	   if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
	   	}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
	   message_vision(msg, me, target);
	   if (me->query("gender")=="Ů��")
	   {
			
			target->add_busy(1);
		}
	}
	else {
		msg = WHT"����$p���з�����Ц�����������嶾�����κε����ң�\n"NOR;
		me->add("neili", -100);
		message_vision(msg, me, target);
		}	
	me->start_busy(1+random(2));
	me->start_perform(3, "��˦��");
	
	return 1;
}
int help(object me)
{
        write(CYN"\n�嶾�޷�����˦�项��"NOR"\n");
        write(@HELP
	�嶾�޷������嶾�̸��ݽ�������������о���������һ��
	��ѧ�������鶯Ϭ�������ն������Ҵ������趯֮�ʣ�����
	�������������緢�������ǳ����������ħ�֣�������
	�������ʽ��
	ע�⣺�����뾭��ֵ����ʽ�ȼ��й�����Ů��������
	
	ָ�perform whip.shuaichou

Ҫ��
	��ǰ����Ҫ�� 500 ���ϣ�
	��ǰ����Ҫ�� 300 ���ϣ�
	�����޷�Ҫ�� 100 ���ϣ�
	���߱޷�Ҫ�� 100 ���ϣ�
	�������ȼ� 100 ���ϣ�
	�����޷�Ϊ���߱޷���
	�����м�Ϊ���߱޷���
	�ֱֳ���������

HELP
        );
        return 1;
}
                                                                                                                                                    