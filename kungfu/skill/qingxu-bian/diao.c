//diao.c
//����ʽ
//by sohu
//Ϊ�������ڱ��������似
//Դ����������׷�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int i,damage,skill;
	object weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("���ŵ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if(me->query_skill("qingxu-bian",1) < 140)
		return notify_fail("��ġ����ŵ�������������죬����ʹ�����ŵ�����\n");
	if(me->query_skill("whip",1) < 140)
		return notify_fail("��ġ������޷�����������죬����ʹ�����ŵ�����\n");
	if( !weapon 
		|| weapon->query("skill_type") != "whip"
		|| me->query_skill_mapped("whip") != "qingxu-bian" 
		|| me->query_skill_mapped("parry") != "qingxu-bian" ) 
		return notify_fail("�������޷�ʹ�����ŵ�����\n");

	if( me->query("neili") < 600 )
		return notify_fail("�����������500��\n");
	if( me->query("jingli") < 500 )
		return notify_fail("��ľ�������500��\n");

	if( me->query("max_neili") < 1500 )
		return notify_fail("��������������1500��\n");
	if( me->query("max_jingli") < 1300 )
		return notify_fail("������������1300��\n");
	if( target->is_busy() )
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");
	
	if (me->query("gender")=="����"&&me->query("quest/dl/qxb/diao/pass")) i=3;
	else i=2;
	skill=me->query_skill("qingxu-bianfa",1);
	damage=me->query_skill("qingxu-bianfa",1)+me->query_skill("whip",1);
	damage=damage*me->query_dex()/10;
	damage=damage+random(damage);
	
	if (damage>3000) damage=3000+random(500);
	if (me->query("quest/dl/qxb/diao/pass"))
	{
		if (damage>4000) damage=4000+random(1000);
	}
	message_vision(HIW "\n$N��Ȼ�����е�"+weapon->query("name")+HIW"һ˦��ʹ��������޷�����"HIR"���ŵ���"HIW"�Ĺ��򣬵��㹳˲�����$n���ʺ�\n"NOR,me,target);

	if(random(me->query("combat_exp") )> target->query("combat_exp")/i
		||random(me->query_dex(1)) > target->query_dex(1)/i)
	{
		message_vision(HIY "\n���$p��$Pһ��Ȧס���ӣ���ʱ��Ѫһ�͡�\n" NOR,me,target);
		target->add_busy(1);
		target->apply_condition("no_exert",1);
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/3,me);
        if(userp(me) && me->query("env/damage"))
				tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"�㹥���˺���\n"NOR);
			
		if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR);

		if (me->query("quest/dl/qxb/diao/pass") &&me->query("env/����޷�")=="����")
		{
			
			message_vision(RED "\n$n��������ϵĵ���ֱ�Ӵ̴��ʺ�\n"NOR,me,target);
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/3,me);
			if(userp(me) && me->query("env/damage"))
				tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"�㹥���˺���\n"NOR);
			
			if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR);

			if (!target->query_temp("qxb/diao"))
			{	
				message_vision(HIW "\n$N�����еı����׳�ԲȦ����$n�������ڣ�˳��һ������$n����������������\n"NOR,me,target);

				target->add_temp("apply/attack",-skill/5);
				target->add_temp("apply/parry",-skill/5);
				target->add_temp("apply/dodge",-skill/5);
				target->set_temp("qxb/diao",skill);
				call_out("remove_diao",20,target);
			}
			target->add_busy(2);
		}
		//target->
	}
	else {
		message_vision(HIW "����$p������$P�����ŵ���������һԾ��㿪�ˡ�\n" NOR,me,target);
		me->start_perform(1,"���ŵ���");
	}
	//message_vision(msg, me, target);
	//me->start_perform(1,"���ŵ���");
	message_vision(HIW"$N����һת��˲�仯�����ǣ�����$n�沿������ʤ����\n"NOR,me,target);
	me->add_temp("apply/damage",skill/5);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if (me->query("quest/dl/qxb/diao/pass")&&me->query("env/����޷�")=="����")
	{
		message_vision(HIW"������������֮���$n����˲�䣬��ע�������ĵ�����Ȼ���̣�ֱ��$n�۲����˵������ն�����\n"NOR,me,target);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	}

	me->add_temp("apply/damage",-skill/5);
	me->add("jingli", -50);
	me->add("neili", -100);
    return 1;
}
int remove_diao(object target)
{
	int skill;
	if (!target) return 0;
	skill=target->query_temp("qxb/diao");
	target->add_temp("apply/attack",skill/5);
	target->add_temp("apply/parry",skill/5);
	target->add_temp("apply/dodge",skill/5);
	target->delete_temp("qxb/diao");
	message_vision(HIW "\n$N����һ�������������������ɵ������������ָ��ˣ�\n"NOR,target);

	return;	
}
string perform_name(){ return HIR"���ŵ���"NOR; }

int help(object me)
{
        write(HIG"\n����޷�֮�����ŵ�������"NOR"\n\n");
        write(@HELP
	����޷��Ǵ���ҳ�������Ĺ�����������ˮ����������Ϥ
	ˮ�ԣ����Խ�������ĵú;������뵽����޷��У����ñ޷�
	�Ķ������ƣ����˷���ʤ�����˺������ж������йء�

	set ����޷� ���� �⿪���������С���ܺ��ж����˺�

	ָ�perform whip.diao
		
Ҫ��  
	��ǰ�������� 600 ���ϣ�
	����������� 1500 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	��������� 1300 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	����޷��ȼ� 140 ���ϣ�
	�����޷��ȼ� 140 ����:
	�����޷�Ϊ����޷���
	�����м�Ϊ����޷���
	���ֱֳ����������

HELP
        );
        return 1;
}
