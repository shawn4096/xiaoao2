// ci.c canhe-zhi perform ���־�
// by leontt 1/5/2000
// modified by darken to reduce busy time

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

void remove_effect(object me, int improve);

int perform(object me, object target)
{
	string msg;
	int improve, ap, dp, skill, i,c;

	if( !target ) target = offensive_target(me);

         if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
		return notify_fail("�����־���ֻ����ս���жԶ���ʹ�á�\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("��������ʹ�á����־�����\n");

	if( (int)me->query_skill("canhe-zhi",1) < 450 )
		return notify_fail("��Ĳκ�ָ������죬����ʹ�á����־�����\n");

	if( (int)me->query_skill("shenyuan-gong",1) < 450 )
		return notify_fail("�����Ԫ���ȼ�����������ʹ�á����־�����\n");

	if( (int)me->query_str(1) < 60 )
		return notify_fail("��ı�������ǿ������ʹ�á����־�����\n");

	if( (int)me->query("max_neili") < 3000 )
		return notify_fail("�������̫��������ʹ�á����־�����\n");	
	
	if( (int)me->query("neili") < 1000 )
		return notify_fail("�������̫���ˣ��޷�ʹ�ó������־�����\n");

	if (me->query_skill_prepared("finger") != "canhe-zhi"
	|| me->query_skill_mapped("finger") != "canhe-zhi")
		return notify_fail("�������޷�ʹ�á����־������й�����\n");

    if ( me->query_skill_mapped("force") != "shenyuan-gong")
        return notify_fail("û����Ԫ��֧�����ʹ�á����־�����\n");
	if ( me->query_skill_mapped("parry") != "canhe-zhi"
	&& me->query_skill_mapped("parry") != "douzhuan-xingyi")
		return notify_fail("�������޷�ʹ�á����־������й�����\n");
	
	
	if( target->query_temp("chz/ci"))
	       return notify_fail("�Է��Ѿ�������Ĵ��־�,������ʹ�òκ�ָ�����⹥�������־�����\n");
	
	msg = HIC"\n$NͻȻһ�������Լ��ĵ����ϼ���ȫ��������γ�һ�ɡ�"HIR"����"HIC"����������Ĵָ�������������$n�ļ粿��\n" NOR;
	message_vision(msg, me, target);

//	pfm ci �в��� aut pfm �ı�� by lane
//	me->set_temp("chz/ci", 1);


	ap = me->query_skill("finger",1);
	dp = me->query_skill("parry",1);

	if ( target->is_busy())
		dp -= dp/3;

	skill = me->query_skill("canhe-zhi", 1);

	i = skill/3+me->query_skill("shenyuan-gong",1)/3;
	if ( skill > 275 )
		i = to_int( skill/3 * skill/275);
	//��ζ��550������������
	
	
	
	if(	random(ap + dp) > dp 
		||random(me->query_str(1))>target->query_str(1)/2)
	{
		
		msg = HIR"$n�ļ�ؽ�һ�ᣬ˫����ʱʧȥ֪�����������á�\n"NOR;
		message_vision(msg, me, target);
		target->add_condition("no_perform", 1);
		target->add_condition("neishang", 2);
		target->add_busy(random(1)+1);   
		
		
		
		if (!userp(target)) c=i*2;
		else c=i;
        
		me->add_temp("apply/damage", c/6);
		
	
		if (present(target,environment(me)) && me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		
		me->add_temp("apply/damage",-c/6);
		
		if (objectp(target)&&!target->query_temp("chz/ci"))
		{
			improve = me->query_str(); //�������Ϊ���죬�����������				
			target->add_temp("apply/strength", -improve/2);
			target->set_temp("chz/ci", improve/2);

			call_out("remove_effect", 5, target ,improve/2,);//(int)me->query_skill("finger",1)/30  ����ʱ��̫�����׳�bug
		}

		if (random(me->query_str())>target->query_str()/2)
		{
			target->receive_damage("qi", 2000, me);
			target->receive_wound("qi", 1000, me);
			message_vision(HIR "ֻ�������͡�һ����ָ������$n��ǰ����һ��Ѫ��ģ���Ĵ󶴣�͸����롣\n" NOR,me,target);
		}		
		
		me->add("neili", -100);
		me->add("jingli", -50);
	}
	else {
		msg = CYN"$n����һԾ�����ݵض����$N����һ�У�\n"NOR;
		message_vision(msg, me, target);
		me->add_busy(1);
	}

	me->start_busy(random(1));
	me->add("neili", -500);
	me->add("jingli", -280);

	//me->start_perform(4, "�����־���");  //��Щ����ȥ������Ȼ�ͳɻ���ǹ��
	return 1;
}

void remove_effect(object target, int improve)
{
	if(!target) return;
	target->add_temp("apply/strength", improve);
	target->delete_temp("chz/ci");
	tell_object(target, HIR"\n������һ����ɫ������ֻ࣬����˫���Ѿ��ָ���ԭ״��\n"NOR);
}

string perform_name(){ return HIC"���־�"NOR; }

int help(object me)
{
        write(HIC"\n�κ�ָ֮�����־���"NOR"\n\n");
        write(@HELP
	�κ�ָ����Ľ���ϵľ�ѧ�������������ת���ƣ�����Ľ��
	�Ҵ��ľ����似���κ�ָ��ǿ�������������������������
	�Է���������ϰ�òκ�ָ�ľ����ؼ���������������������
	�ɵ�ָ��������
	���־������Զ�ת����֮����ϰ���ֽ��ָ��֮�⣬һ�д�
	��̴��Է�������Ҫ������һ�д��жԷ��۰������Է���

ָ�perform finger.ci

Ҫ��
	��ǰ���� 1000 ���ϣ�
	������� 3000 ���ϣ�
	�κ�ָ�ȼ� 450 ���ϣ�
	��Ԫ���ȼ� 450 ���ϣ�
	����ָ��Ϊ�κ�ָ��
	��ָ��Ϊ�κ�ָ��
	������С��60��
	�����ޱ���,

HELP
        );
        return 1;
}
                                
