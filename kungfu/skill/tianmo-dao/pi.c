// pi.c ������ɽ�������������ɵķ�ŭ�Ͳ���
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

	if( (int)me->query_skill("tianmo-dao", 1) < 100 )
		return notify_fail("�����ħ��������죬�޷�ʹ�õ�����ɽ��\n");

	if ( me->query_skill_mapped("parry") != "tianmo-dao"
	|| me->query_skill_mapped("blade") != "tianmo-dao")
		return notify_fail("�������޷�ʹ�õ�����ɽ��\n");

	if( (int)me->query_skill("tianmo-gong", 1) < 100 )
		return notify_fail("�����ħ�������ߡ�\n");

	if((int)me->query("max_neili",1) < 1400 )
		return notify_fail("���������Ϊ�������޷�ʹ�á�������ɽ����\n");

    if( (int)me->query("neili", 1) < 500 )
		return notify_fail("����������̫��������ʹ�á�������ɽ����\n");
	
	message_vision(RED "\n$N������������������˾������²������ϼӿ죬�γ�һ���������ĵ�����Ȼ����Ȼ������$n��\n"NOR,me,target);

	ap = me->query("combat_exp", 1) / 10000 ;
	dp = target->query("combat_exp", 1)/ 10000 ;

	if ( random(ap + dp) > dp
		||random(me->query_skill("blade",1))>target->query_skill("parry",1)/2){
		damage = me->query_skill("blade",1) * 4;
		damage += me->query_skill("force",1) * 4;
		damage +=me->query_skill("tianmo-gong",1)*4;
		damage = damage + random(damage);
		
		if (damage > 4500) damage = 4500+random(damage-4500)/100;
		
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		if (wizardp(me)) write("damage="+damage);
		
		me->add("neili", -250);
		me->add("jingli", -80);
		msg = HIR"\nֻ��$N��Ȼ��Ծ���գ�ʩչһ�С�������ɽ����$nֻ��һ�����������ĵ������������һ�������ؿڣ���ʱ��Ѫ���磡\n"NOR;
	
	   if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
	   	}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
	   message_vision(msg, me, target);
	 
	   if (me->is_fighting()
		   &&random(me->query("combat_exp")) > target->query("combat_exp")/2
		   ||random(me->query_int())>target->query_int()/3)
		{
              message_vision(CYN "$N����$n���˴��У�����Ǳ����ħ�����������������ֵ�˲������У�\n" NOR, me,target);
             // COMBAT_D->do_attack(me,target, me->query_temp("weapon"), me->query("gender")=="Ů��"?3:1);
              COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 3);
	     } else  message_vision(YEL "$nս�������쳣�ḻ��������$N����ͼ�������㿪$N������ɱ����\n" NOR, me,target);
		
	}
	else {
		message_vision(HIY"����$p���з�����Ц������������ħ���ڰ���ɱ�����ѵ����κε����ң�\n"NOR, me,target);
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
        write(CYN"\n��ħ����֮��������ɽ����"NOR"\n");
        write(@HELP
	��ħ����������̵ľ���֮һ�����������쳣��������ɽ
	���ǽ���һλ���϶�������ʽ���ټ��Ϻ��������ɵĲ���
	֮����������Ϊ������ɽ��
	ע�⣺�����뾭��ֵ�ͼ����й�,���Ը��߻��ٳ�һ��
	
	ָ�perform blade.pi

Ҫ��  
	����������� 1400 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	��ħ�����ȼ� 100 ���ϣ�
	��ħ�����ȼ� 100 ���ϣ�
	����������ħ����
	�����м���ħ����

HELP
        );
        return 1;
}
                                                                                                                                                    