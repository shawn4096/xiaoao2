// sancai.c  �������ŵ�

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return CYN"�������ŵ�"NOR; }

int perform(object me, object target)
{
	object weapon;
	int damage, ap, dp, p;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("���������ŵ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if( (int)me->query_skill("liuhe-daofa", 1) < 100 )
		return notify_fail("������ϵ���������죬�޷�ʹ���������ŵ���\n");

	if ( me->query_skill_mapped("parry") != "liuhe-daofa"
	|| me->query_skill_mapped("blade") != "liuhe-daofa")
		return notify_fail("�������޷�ʹ���������ŵ���\n");

	if( (int)me->query_skill("huntian-qigong", 1) < 100 )
		return notify_fail("��Ļ������������ߡ�\n");

	if((int)me->query("max_neili",1) < 1400 )
		return notify_fail("���������Ϊ�������޷�ʹ�á��������ŵ�����\n");

    if( (int)me->query("neili", 1) < 500 )
		return notify_fail("����������̫��������ʹ�á��������ŵ�����\n");
	
	msg = CYN "\n$N��ɫ���䣬����Ʈ�����������󼲶���ǧ�������������Ʈѩ������ǵط���$n��\n"NOR;

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
		msg += HIR"ֻ��$N��̤������������ŵ����Ϊһ�ߣ�$nֻ��һ�����������������������������������Ѫ���������\n"NOR;
	
	   if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
	   	}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
	   message_vision(msg, me, target);
	   if (me->is_fighting()&&random(me->query("combat_exp")) > target->query("combat_exp")/2||random(me->query_int())>target->query_int()/3)
		{
              message_vision(HIY "$N����ƴɱ����ǳ��ḻ������$n���˴��У�����Ǳ�˻�����������$n�����������������У�\n" NOR, me,target);
              COMBAT_D->do_attack(me,target, me->query_temp("weapon"), me->query("gender")=="Ů��"?3:1);
              COMBAT_D->do_attack(me,target, me->query_temp("weapon"), me->query("gender")=="Ů��"?3:1);
	     } else  message_vision(HIY "$nս�������쳣�ḻ��������$N����ͼ�������㿪$N������ɱ����\n" NOR, me,target);
		
	}
	else {
		msg += CYN"����$p���з�����Ц�������������ϵ����ڰ����������ţ��ѵ����κε����ң�\n"NOR;
		me->add("neili", -100);
		message_vision(msg, me, target);
		}	
	me->start_busy(1+random(2));
	me->start_perform(2, "���ŵ�");
	
	return 1;
}
int help(object me)
{
        write(CYN"\n�������ϵ����������ŵ�����"NOR"\n");
        write(@HELP
	�������ŵ�����ؤ���ⳤ�Ͼ�ѧ��������������֮�⣬��
	Ϭ���ĵ����̺����С��þ�����Ҫ�ϸߵľ�����������
	����������Ů���������Ϊ���ơ�
	
	ָ�perform blade.sancai

Ҫ��  
	�������  1400 ���ϣ�
	��ǰ����  500 ���ϣ�
	�������ϵ��ȼ� 100 ���ϣ�
	���������ȼ� 100 ���ϣ�
HELP
        );
        return 1;
}
                                                                                                                                                    