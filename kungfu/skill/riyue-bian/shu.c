// shu.c ���±޷�����������
// 
#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;
	object weapon = me->query_temp("weapon");
	int busy,skill;
	skill=me->query_skill("riyue-bian",1);
	if( !target ) target = offensive_target(me);

        if( !objectp(target)
	  ||!target->is_character()
	  ||!me->is_fighting(target) )
		return notify_fail("ǣ�ƹ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( (int)me->query_skill("yijin-jing", 1) < 250 )
		return notify_fail("����׽�ڹ��ȼ�����������ʹ�á�������������\n");

	if( (int)me->query_skill("riyue-bian", 1) < 250 )
		return notify_fail("������±޷�������죬����ʹ�á�������������\n");

	if (!weapon
	 || weapon->query("skill_type") != "whip"
	 || me->query_skill_mapped("whip") != "riyue-bian"
	 || me->query_skill_mapped("parry") != "riyue-bian")
		return notify_fail("�������޷�ʹ��ǣ�ƹ�����\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("����������̫��������ʹ�á�������������\n");

	if( target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

	//me->start_perform(4, "����������"); 

	message_vision(HIY"$Nʹ�����±޷��������������������ޣ�ɢ�������������ͼ��$n��ȫ�����������\n"NOR,me,target);
	message_vision(HIY "$N����"+weapon->query("name")+"�ƻ�ʵ����ȴ���ް�������������ȣ�˵�����Ĺ��졣\n"NOR,me,target);

	me->add("neili", -350);
	me->add("jingli", -250);

	if(random(me->query("combat_exp")) >  target->query("combat_exp")/2
		||random(me->query_int(1))>target->query_int(1)/2)
	{
		message_vision(YEL"���$n��$N���˸����ֲ�����\n" NOR,me,target);
		target->receive_damage("qi",2000+random(1000),me);
		target->add_busy(skill/100);
		me->set_temp("ryb/shu",1);
		//call_out("check_fight", 1, me, target, weapon, 7); 
	}else {
		message_vision(CYN"����$n������$N����ͼ����û���ϵ���\n" NOR,me,target);
		me->start_busy(1);
	}
	//���ܺ�������������������
	if (objectp(me)
		&&objectp(target)
		&&me->is_fighting()
		&&me->query("quest/sl/ryb/shu/pass"))
	{
		call_out("check_fight",1,me,target,skill/20);
	}
	return 1;
}

void check_fight(object me,object target,int count)
{
	object weapon;
	if (!me||!target) return;
	if (!objectp(weapon=me->query_temp("weapon"))||weapon->query("skill_type")!="whip") return;
	if (me->query_skill("whip")!="riyue-bian"||count<0) return;
	
	
	if (random(me->query_skill("whip",1))>target->query_skill("parry",1)/2)
	{
		message_vision(YEL"$n�����һ���������Ժ�������Ϣ��Ȧ������ס��$n�����䣬$N˲��һ������$n����������\n" NOR,me,target);
		target->receive_damage("qi",3000,me);
		target->receive_wound("qi",1000,me);
		target->apply_condition("no_exert",1);
		target->add_busy(1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	}else if (random(me->query_skill("force",1))>target->query_skill("force",1)/2)
	{
		message_vision(RED"$n����һ������ͼץס���ص����������������������˦ȥ��ͻ����������һ����һ����ɽ�������ھ����ؿ�ײ����\n"
						+"���ھ�ֻҪ�е�ʵ�ˣ���������߹Ƕ��ۣ��������飡\n" NOR,me,target);
		target->receive_damage("qi",3000,me);
		target->receive_wound("qi",1000,me);
		target->apply_condition("neishang",2);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	}else if (random(me->query_skill("riyue-bian",1))>target->query_skill("dodge",1)/2)
	{
		message_vision(YEL"$nͻ����������������״����һ��Ϯ�����Ⱦ��ް�����ף�һ��֮�£������ŵع�����ֻ��һ����������Ϻ��Ӷ�����\n"
						+"��಻���ߣ�ȥ���漱��ȴ�Ǿ��޾��磬\n" NOR,me,target);
		message_vision(HIR"$n�����о��Լ���$N�ĳ�����������Խ��Խ���������ڲ������ţ�\n"NOR,me,target);
		target->receive_damage("jingli",1000+random(2000),me);
		//target->receive_wound("jingli",1000,me);
		target->apply_condition("no_perform",2);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	}
    call_out("check_fight", 1, me,target,count -1);/**/
}
string perform_name(){ return HIY"������"NOR; }
int help(object me)
{
	write(HIC"\n���±ޡ�����������"NOR"\n");
	write(@HELP
	���±���������������֮һ��������������������֮�����ɸջ�����书
	��ʱ�����ڹ��Դ��������տ�����������������¶��ǵľ��硣Խ��Խ����
	����Խ�̹���Խǿ�����������������շ����ġ����޼ɾ�лѷ�������գ�
	��һ�ֿ�������ɮ����һս��Ȼ�ɾ������޼ɵ���������ͬʱ���������ϵ�
	���±�Ҳ�������¡�
	���������ǽ����±�����֮�����������£����ñ��Ӷ���֮�ʣ����Է�����
	�̴�������������Ч����ʹ�öԷ��ڶ�ʱ�����޷������ұ�ѹ�ơ�
	
	ָ�perform whip.shu

Ҫ��	
	��ǰ���� 500 ���ϣ� 
	��ǰ���� 500 ���ϣ� 
	�׽�ȼ� 250 ���ϣ�
	���±޷��ȼ� 250 ���ϣ�
	�����ķ��ȼ� 250 ���ϣ�
	�������±޷�Ϊ�мܣ�
	�����׽Ϊ�ڹ���
	װ�������������     
HELP
	);
	return 1;
}


