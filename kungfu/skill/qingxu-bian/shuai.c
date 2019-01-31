//shuai.c ˦��
//by sohu
//������ʽ

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int skill,damage;
	object weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);
	skill=me->query_skill("qingxu-bian",1);
	damage=skill*me->query_dex()+random(skill);
	if (damage>2000) damage=2000+random(1000);
	
	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("ɨ�־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if(me->query_skill("qingxu-bian",1) < 100)
		return notify_fail("��ġ�����޷�����������죬����ʹ�á�˦�־�����\n");

	if(me->query_skill("whip",1) < 100)
		return notify_fail("��ġ������޷�����������죬����ʹ�á�˦�־�����\n");
	if(me->query_skill("force",1) < 100)
		return notify_fail("��ġ������ڹ�����������죬����ʹ�á�˦�־�����\n");
	
	if( !weapon 
	|| weapon->query("skill_type") != "whip"
	|| me->query_skill_mapped("whip") != "qingxu-bian" 
	|| me->query_skill_mapped("parry") != "qingxu-bian" ) 
		return notify_fail("�������޷�ʹ�á�˦�־�����\n");

	if( me->query("neili") < 500 )
		return notify_fail("�����������500��\n");
	if( me->query("jingli") < 500 )
		return notify_fail("��ľ�������500��\n");

	if( me->query("max_neili") < 1500 )
		return notify_fail("��������������1500��\n");
	if((int)me->query("max_jingli") <1300)
	{
		write("max_jingli="+me->query("max_jingli"));
		return notify_fail("������������1300!\n");
	}
//	if( target->is_busy() )
//		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");
	
	message_vision(HIG "\n$N��ʹ����޷���˦�־����������е�"+weapon->query("name")+HIG"��$n���沿˳��˦����\n"NOR,me,target);
	
	
	if(random(me->query("combat_exp") )> target->query("combat_exp")/2
		||random(me->query_dex(1)) > target->query_dex(1)/2)
	{
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/3,me);
		message_vision(HIY "\n���$p��$P�����沿��һ�ɴ�����������ʱ$p��ð���ǣ�\n" NOR,me,target);

	    if(userp(me) && me->query("env/damage"))
        	tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage*4/3+ WHT"�㹥���˺���\n"NOR);
		
		if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage*4/3+ WHT"���˺���\n"NOR);

	}
	else {
		message_vision(HIW "����$p������$P��ɨ�־�������һԾ��㿪�ˡ�\n" NOR,me,target);
	}
	//message_vision(msg, me, target);
	me->add_temp("apply/attack",skill/3);
	me->add_temp("apply/damage",skill/4);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	me->add_temp("apply/attack",-skill/3);
	me->add_temp("apply/damage",-skill/4);

	me->add("jingli", -100);
	me->add("neili", -60);
	me->start_perform(4,"˦�־�");
    return 1;
}

string perform_name(){ return HIG"˦�־�"NOR; }

int help(object me)
{
        write(HIG"\n����޷�֮��˦�־�����"NOR"\n\n");
        write(@HELP
	����޷��Ǵ���ҳ�������Ĺ�����������ˮ����������Ϥ
	ˮ�ԣ����Խ�������ĵú;������뵽����޷��У����ñ޷�
	�Ķ������ƣ����˷���ʤ�����˺������ж������йء�
    
	ָ�perform whip.shuai
		
Ҫ��  
	��ǰ�������� 500 ���ϣ�
	����������� 1500 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	��������� 1300 ���ϣ�
	����޷��ȼ� 100 ���ϣ�
	�����޷��ȼ� 100 ����:
	�����ڹ��ȼ� 100 ����;
	�����޷�Ϊ����޷���
	�����м�Ϊ����޷���
	���ֱֳ����������

HELP
        );
        return 1;
}
