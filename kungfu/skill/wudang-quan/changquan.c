// shisan.c �䵱��ȭ����ȭʮ��ʽ������
// sohu@xojh
#include <ansi.h>

inherit F_SSERVER;



string perform_name(){ return WHT"��ȭʮ��ʽ"NOR; }

int perform(object me, object target)
{
	int damage, p, m, force, ap ,dp;
	float at;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target) )
		return notify_fail("����ȭʮ��ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( me->query_skill("wudang-quan", 1) < 100 )
		return notify_fail("�䵱��ȭ�ĵȼ��������������ʹ�á���ȭʮ��ʽ����\n");
	if( me->query_skill("cuff", 1) < 100 )
		return notify_fail("����ȭ���ȼ��������������ʹ�á���ȭʮ��ʽ����\n");
	if( me->query_skill("yinyun-ziqi", 1) < 100 )
		return notify_fail("�������ȼ��������������ʹ�á���ȭʮ��ʽ����\n");

	if(me->query_skill_mapped("force") != "yinyun-ziqi"
	  ||me->query_skill_mapped("cuff") != "wudang-quan"
	  || me->query_skill_prepared("cuff") != "wudang-quan") 
		return notify_fail("����ڹ���ȭ�����ԣ��������ʹ�á���ȭʮ��ʽ���־���\n");

	if( (int)me->query("neili", 1) < 500 )
		return notify_fail("����������������ǿ��ʹ�á���ȭʮ��ʽ���־�ֻ���˵����Լ���\n");
	if( (int)me->query("jingli", 1) < 500 )
		return notify_fail("�����ھ���������ǿ��ʹ�á���ȭʮ��ʽ���־�ֻ���˵����Լ���\n");
	
	if( me->query_temp("weapon") )
		return notify_fail("���ȷ������е�������˵�ɣ���\n");

	msg = WHT"\n$N�����䵱��ȭ�С���ȭʮ��ʽ������ʹ������������ˮ��\n"NOR;


	ap = me->query_skill("wudang-quan",1);
	dp = target->query_skill("parry",1);

	if( random( ap + dp) > dp 
		|| random(me->query_str(1))>target->query_str(1)/2 )
	{
			
			msg += HIC"\n$Nȭ����������ʽ��Ȼ��ȴ��Ϊʵ�ã�����$n�������ˣ�\n"NOR;
			target->add_busy(1);
			damage = (int)me->query_skill("wudang-quan",1) * me->query_str(1)/5;


			if( userp(target)&&damage>3000 ) damage = 3000;
			

			target->receive_damage("qi", damage, me);
			target->receive_wound("qi", damage/(2+random(2)), me);


			p = (int)target->query("eff_qi")*100/(int)target->query("max_qi");

			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		

	}
	else{
		msg += HIY"$p���������У�\n"NOR;
		me->start_busy(random(2));
		msg+=HIR"$N�ۼ�����û�д��У�������������������ϣ��������У�\n"NOR;
		//message_vision(msg, me, target);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		
	}
	message_vision(msg, me, target);
	me->start_perform(2, "����ȭʮ��ʽ��");
	me->add("neili", -100);
	me->add("jingli", -50);

	return 1;
}

int help(object me)
{
	write(WHT"\n�䵱��ȭ֮"HIC"����ȭʮ��ʽ����"NOR"\n");
	write(@HELP
	�䵱��ȭ�Ǵ�����ʦ�����������ֻ����似
	�ݻ�������Ϊ�䵱�������似������������
	���˲����ݻ����γɵ��͵ĳ�ȭʮ��ʽ����
	�ܽ�����ȭ��Ҫ�����ӳ���������ǿ����
	�ɴ��γ�һ�ż���ʵս��ȭ����
	
	ָ�perform cuff.shisan

Ҫ��	
	��ǰ����Ҫ�� 500 ���ϣ�
	�������Ҫ�� 1200 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	�䵱��ȭ�ȼ� 100 ���ϣ�
	�������ȼ� 100 ���ϣ�
	����ȭ���ȼ� 100 ���ϣ�
	��ѧ�ķ��ȼ� 100 ����
	�����Ʒ�Ϊ�䵱��ȭ��
	�����м�Ϊ�䵱��ȭ��
	�����ڹ�Ϊ��������
	�ҿ���
HELP
	);
	return 1;
}
