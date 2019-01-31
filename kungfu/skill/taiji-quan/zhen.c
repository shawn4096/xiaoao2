// zhen.c ̫��ȭ�����־�
// snowman
#include <ansi.h>

inherit F_SSERVER;

string *taiji_msg = ({"ʮ����","����Ʊ�","������","Ұ�����","б����","����","����","��ͨ��"});

string perform_name(){ return HBRED+HIY"���־�"NOR; }

int perform(object me, object target)
{
	int damage, p, m, force, ap ,dp;
	int tnl,snl;
	float at;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target) )
		return notify_fail("�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( me->query_skill("taiji-quan", 1) < 450 )
		return notify_fail("̫��ȭ���������ⲻ�ϣ���̫��ȭ�����������������ʹ�á����־���\n");

	if( userp(me) && (me->query_skill_mapped("force") != "yinyun-ziqi"
	 || me->query_skill_prepared("cuff") != "taiji-quan") )
		return notify_fail("����ڹ���ȭ�����ԣ��������ʹ�á����־���\n");

	if( (int)me->query("neili", 1) < 5000 )
		return notify_fail("����������������ǿ��ʹ�á����־�ֻ���˵����Լ���\n");

	if( me->query_temp("weapon") )
		return notify_fail("���ȷ������е�������˵�ɣ���\n");

	msg = CYN "\nͻȻ��$Nһ�С�"+taiji_msg[random(sizeof(taiji_msg))]+"����˫������������һ��ԲȦ�ѽ�$n��ס��̫��ȭ��"RED"����"CYN"�־��漴ʹ����\n"NOR;

	force = me->query_skill("force",1) + target->query_skill("yinyuan-ziqi",1);

	ap = me->query("combat_exp", 1)/ 100000 * me->query_skill("force",1);
	dp = target->query("combat_exp", 1)/100000 * target->query_skill("force",1);

	if( random( ap + dp) > dp 
		|| random(me->query_int(1))>target->query_int(1)/3 )
	{
			if( me->query("neili") < target->query("neili")*3/2 ) 
			{
				me->start_busy(2);
				target->add_busy(2);
				me->add("jingli", -force/10);
				me->add("neili", -force/2);
                       	target->add("jingli", -force/10);
                       	target->add("neili", -force/2);
				msg += HIY"ֻ����ž����һ����$p��$P����������ƴ�������������˼�����\n"NOR;
				me->start_perform(2, "����");
				message_vision(msg, me, target);
				return 1;
			}
			me->start_busy(random(2));

			damage = (int)me->query_skill("taiji-quan",1) * 4+force;
			//��ֹ��0 by renlai
			if (target->query("neili")>0) tnl=target->query("neili");
				else tnl=1;
			if (me->query("neili")>0) snl=me->query("neili");
			else snl=0;
			at = snl / tnl;
                
			if( at < 1 ) {
				if(at < 0.5) damage /= 2;
				damage /= 2;
			}
			else damage = to_int(damage * at);

			if( me->query_skill("taiji-quan", 1) > 450 ) 
			m = 4000 + ( me->query_skill("taiji-quan", 1) - 300 ) * 10 + random(200);
			else m = 4000;

			if( !userp(me) ) m = 4000;

			if( damage > m ) damage = m + (damage-m)/20;
			if( damage > 8000 ) damage = 10000 + (p-8000)/50;
			if( wizardp(me) ) tell_object(me, "��ġ�"RED"���־�"NOR"������Ϊ�� "+damage+"��\n"NOR);

			if( wizardp(me) && (string)me->query("env/combat")=="verbose")
			tell_object(me, "M_neili = "+me->query("neili")+ " T_neili = "+target->query("neili")+" Damage = "+damage+"\n");

			target->receive_damage("qi", damage, me);
			target->receive_wound("qi", damage/(2+random(2)), me);
			target->receive_damage("neili", damage/2);
            target->receive_damage("jing",-(me->query_int(1)+ me->query_con(1))* 3,me );

			me->add("neili", -400);
			me->add("jingli", -150);
			me->start_perform(2, "����");

			if( damage >= me->query_skill("taiji-quan", 1) * 8 )
				msg += "̫��֮�����಻�ϣ�������ȥ�пգ�һ��ԲȦδ�꣬�ڶ���ԲȦ����������һ�죬$pһ����ͷ���ʶϣ�\n";
			if( damage >= me->query_skill("taiji-quan", 1) * 10 ){
				msg += "$N���������������־�ʹ��ʱ���಻�ϣ����ſ�����������$pȫ�������ͷҲ��һһ�ʶϣ�\n";
			target->receive_wound("jing", damage/(2+random(2)), me);
			}
			p = (int)target->query("eff_qi")*100/(int)target->query("max_qi");

			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
	else{
		msg += HIY"$pһ�����ԣ�����һ�󼱹���$P��ʱ��æ���ң���Ҳ���������У�\n"NOR;
		me->start_busy(random(2));
		me->add("jingli", -50);
		me->add("neili", -150);
		me->start_perform(2, "����");
	}
	message_vision(msg, me, target);
	if (me->query("taiji/pass"))
	{
		target->set_temp("must_be_hit",1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		target->delete_temp("must_be_hit");
	}
	
	return 1;
}

int help(object me)
{
	write(WHT"\n̫��ȭ��֮"HBRED+HIY"�����־�����"NOR"\n");
	write(@HELP
	̫��ȭ��֮�����־������ǽ�̫��ȭ���������ںϺ��
	һ�ֹ����似�����ص��ǣ�ͨ��̫��ȭ���ھ��ŷ�����̫��
	������Ȼ���������ԶԷ����ڹ��;����Լ���Ѫ����ɼ���
	�˺���ע�⣬�ͱ������ڹ�������ֵ�Լ����Ծ��й�ϵ��
	
	ָ�perform cuff.zhen

Ҫ��	
	��ǰ���� 5000 ���ϣ�      
	��ǰ���� 2000 ���ϣ�
	̫��ȭ�� 450  ���ϣ�
	������ 450  ���ϣ�
	����̫��ȭ�����ޱ�����
HELP
	);
	return 1;
}
