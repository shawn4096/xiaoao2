// liuxu.c ��������

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	string msg, dodge_skill;
	object weapon;
	int ap, dp,i,skill;
    
	if( !target ) target = offensive_target(me);

	//if( !me->query("quest/mr/mrjf/liuxu/pass") )
		//return notify_fail("��δ�ô��ڡ�������������\n");

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target)
	|| !living(target) )
		return notify_fail("������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");


	if( (int)me->query_skill("murong-jianfa", 1) < 200 )
		return notify_fail("���Ľ�ݽ�������̫ǳ�ˡ�\n");

	if( (int)me->query_skill("sword", 1) < 200 )
		return notify_fail("��Ļ�����������̫ǳ�ˡ�\n");

	if( (int)me->query_skill("shenyuan-gong", 1) < 200 )
		return notify_fail("����ڹ�����̫ǳ�ˡ�\n");

	if( (int)me->query("max_neili") < 3000 )
		return notify_fail("�������̫ǳ�ˡ�\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("�������������\n");

	if( me->query_skill_mapped("force") != "shenyuan-gong" )
		return notify_fail("Ľ�ݽ�����Ľ�ݼҴ��书����Ҫ��Ԫ��֧�֡�������������\n");
	if( me->query_temp("mrjf/liuxu") )
		return notify_fail("������ʹ�á�����������\n");
	if( target->query_temp("mrjf/liuxu") )
		return notify_fail("�Է��Ѿ�������ġ�����������\n");

	if( !objectp(weapon = me->query_temp("weapon"))
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "murong-jianfa")
	 
		return notify_fail("�㼤������ʹ���ˡ�����������ô?\n");
	
	//if( target->is_busy() )
		//return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");
	//For npc Chan+liuxu ��å����
      
	ap = me->query("combat_exp")/100000;
	dp = target->query("combat_exp")/100000;
	//550������������
	if( me->query_skill("murong-jianfa", 1) > 549 )
	{
		ap += random(ap/2);
       // me->set_temp("apply/armor",me->query("shenyuan-gong",1)/3);
	}	      

	message_vision(HIW"\n$Nʩչ��Ľ�ݽ����е���������������"+weapon->query("name")+HIW"�������������Ϣ��������������,������ȴ����������\n"NOR,me,target);
	
	skill=(int)me->query_skill("murong-jianfa",1);
	
	if (me->query("quest/mr/syg/pass"))
	{
		skill=skill+me->query_skill("shenyuan-gong",1)/2;
	}
	
	if ( random( ap + dp ) > dp 
		||random(me->query_int())>target->query_int()/2) 
	{
		message_vision(HIC"\n$n����$N���ƹ��죬����ͻأ���ƣ�����ʤ������ʱ���У�\n"NOR,me,target);		
		
		if (userp(target)) target->add_busy(2);
		else target->add_busy(4);
		
		if( target->query_temp("lost_attack") < 1 )
			target->add_temp("lost_attack", 2+random(3));
		me->add("neili", -300);
		me->add("jingli", -100);
		//���ͶԷ�����
		me->set_temp("mrjf/liuxu",skill);
		if (!target->query_temp("mrjf/liuxu"))
		{
			target->add_temp("apply/dodge",-skill/6);
			target->add_temp("apply/attack",-skill/6);
			target->add_temp("apply/parry",-skill/6);
			
			target->set_temp("mrjf/liuxu",skill);
	//����target
			call_out("target_liuxu",(int)skill/50,target);

		}
		//�����Լ��ж�
		call_out("liuxu_effect",1,me,(int)skill/20);		
		
	}
	else {
		
		message_vision(HIY"$n����һ�����㿪��$N���й�����\n"NOR, me, target);

		me->add("neili", -100);
		me->add("jingli", -50);
		me->start_busy(1);
		me->start_perform(1+random(2), "������������");
	}	
	return 1;
}

int liuxu_effect(object me,int count)
{

        object weapon;
		int skill;
		if (!me) return 0;
		
		weapon=me->query_temp("weapon");

		if (!me->is_fighting()
			|| me->query_skill_mapped("sword")!="murong-jianfa"
			|| !weapon
			|| !me->query_temp("mrjf/liuxu")
			|| count < 0
			|| weapon->query("skill_type")!="sword")
		{				
			
			me->delete_temp("mrjf/liuxu");			
			message_vision(HIB"$N�����еĽ���������������������չ���\n"NOR,me);			
			return 1;
		}
		call_out("liuxu_effect",1,me,count--);
		
	  
}
int target_liuxu(object target)
{
	int skill;
	if (!target) return 0;
	if (!target->query_temp("mrjf/liuxu")) return 0;

	skill=target->query_temp("mrjf/liuxu");
	
	tell_object(target, HIW"���𽥻ָ������С�������������������˥��״̬��\n"NOR);
	target->add_temp("apply/attack", skill/6);
	target->add_temp("apply/dodge", skill/6);
	target->add_temp("apply/parry", skill/6);
	target->delete_temp("mrjf/liuxu");
	return 1;
	
	
}

string perform_name(){ return HIC"��������"NOR; }

int help(object me)
{
        write(MAG"\nĽ�ݽ���֮��������������"NOR"\n\n");
        write(@HELP
	������������Ľ�ݼҴ�Ľ�ݽ����ľ����似��
	ƾ���������ڹ���Ϊ����������ע�뽣��
	֮�У�������Ϣ�����ٳ��У��ڶ�ʱ���ڶ�
	�����γ�Ǳ�ڵ���в��ΪĽ���ϳ����似
	
	ָ�perform sword.liuxu

Ҫ��  
	��ǰ����Ҫ�� 1000 ����;
	�������Ҫ�� 3000 ���ϣ�
	Ľ�ݽ����ȼ� 200 ���ϣ�
	��Ԫ�����ȼ� 200 ���ϣ�
	���������ȼ� 200 ���ϣ�
	��������ΪĽ�ݽ�����
	�����ڹ�Ϊ��Ԫ����

HELP
        );
        return 1;
}
