// fanpi.c ������ɽ
// cre by sohu@xojh
#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return RED"������ɽ"NOR; }

int perform(object me, object target)
{
	object weapon;
	int damage, ap, dp, p;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("��������ɽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if( (int)me->query_skill("nanshan-dao", 1) < 100 )
		return notify_fail("�����ɽ����������죬�޷�ʹ�÷�����ɽ��\n");

	if ( me->query_skill_mapped("parry") != "nanshan-dao"
	|| me->query_skill_mapped("blade") != "nanshan-dao")
		return notify_fail("�������޷�ʹ�÷�����ɽ��\n");

	if( (int)me->query_skill("force", 1) < 100 )
		return notify_fail("��Ļ����ڹ������ߡ�\n");
	if( (int)me->query_skill("blade", 1) < 100 )
		return notify_fail("��Ļ������������ߡ�\n");

	if((int)me->query("max_neili",1) < 1400 )
		return notify_fail("���������Ϊ�������޷�ʹ�á�������ɽ����\n");

    if( (int)me->query("neili", 1) < 500 )
		return notify_fail("����������̫��������ʹ�á�������ɽ����\n");
	
	message_vision(RED "\n$N����һ�ݣ���ǰ�벽�����һ��������һ������$n�����ţ�������ɽ�������⡸������ɽ���ľ�����\n"NOR,me,target);

	ap = me->query("combat_exp", 1) / 10000 ;
	dp = target->query("combat_exp", 1)/ 10000 ;

	if ( random(ap + dp) > dp
		||random(me->query_skill("blade",1))>target->query_skill("parry",1)/2){
		damage = me->query_skill("blade",1) * 4;
		damage += me->query_skill("force",1) * 4;
		damage = damage + random(damage);
		
		if (damage > 2500) damage = 2500+random(damage-2500)/100;
		
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		if (wizardp(me)) write("damage="+damage);
		
		me->add("neili", -250);
		me->add("jingli", -80);
		msg = HIR"\nֻ��$N���С�������ɽ������ʽ������$nһʱ���飬��һ�����ڶ�ͷ����ʱ��Ѫ���磡\n"NOR;
	
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
		message_vision(HIY"����$p���з�����Ц������������ɽ���ڰ���ɱ�����ѵ����κε����ң�\n"NOR, me,target);
		me->add("neili", -200);
		me->add_busy(1);
		//message_vision(msg, me, target);
		}	
	me->add_busy(1+random(2));
	me->start_perform(2, "������ɽ");
	
	return 1;
}
int help(object me)
{
        write(CYN"\n��ɽ����֮��������ɽ����"NOR"\n");
        write(@HELP
	��ɽ���ǽ����߹���ɽ������ϣ�ʵľ���֮һ��
	������ɽ���м�Ϊ���죬����ַ���ʤ����һ��
	���󣬶�ʱ��Է���Ѫ���ǳ�������

	ָ�perform blade.fanpi

Ҫ��  
	����������� 1400 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	��ɽ�����ȼ� 100 ���ϣ�
	�����ڹ��ȼ� 100 ���ϣ�
	���������ȼ� 100 ���ϣ�
	����������ɽ����
	�����м���ɽ����

HELP
        );
        return 1;
}
                                                                                                                                                    