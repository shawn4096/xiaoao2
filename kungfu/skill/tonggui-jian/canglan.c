#include <ansi.h>
inherit F_SSERVER;

int perform1(object me, object target, object weapon, int ap, int dp, int skill, int i);
int perform2(object me, object target, object weapon, int ap, int dp, int skill, int i);

int perform(object me, object target)
{
	string msg, dodge_skill;
	object weapon = me->query_temp("weapon");
	int ap, dp, damage, p, skill, i = 0;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("��������ʽ���־�ֻ����ս���жԶ���ʹ�á�\n");

	if( !living(target) )
		return notify_fail("��������ʽ���־�ֻ����ս���жԶ���ʹ�á�\n");

	if( !weapon || weapon->query("skill_type") != "sword" )
		return notify_fail("�������޽������ʹ�á�������ʽ���־���\n");

	if( me->query_skill_mapped("sword") != "tonggui-jian" )
		return notify_fail("����������ͬ�齣�����޷�ʹ�á�������ʽ���־���\n");

	if( me->query_skill_mapped("parry") != "tonggui-jian" )
		return notify_fail("�������ͬ�齣��Ϊ�мܲ���ʹ�á�������ʽ���־���\n");  
//��������⿪̫���񹦺�����Բ�����ʽ����
	if( me->query_temp("tgj/canglan") && !me->query("quest/wd/yyzq/taiji/pass"))
		return notify_fail("������ʹ�á�������ʽ���־���\n");

	//if( (int)me->query_temp("tgj/canglan") )
		//return notify_fail("����������ʹ�á�������ʽ���־���\n");

	if( (int)me->query_skill("tonggui-jian", 1) <120 )
		return notify_fail("���ͬ�齣����Ϊ�в�����,�޷�ʹ�á�������ʽ���־���\n");             

	if( (int)me->query_skill("force",1) < 120 )
		return notify_fail("��Ļ����ڹ���Ϊ��ǳ������ʹ�á�������ʽ���־���\n");

	if( (int)me->query_skill("sword",1) < 120 )
		return notify_fail("�����������Ϊ�в�����,����ʹ�á�������ʽ���־���\n");  

	if( (int)me->query("max_neili") < 1500 )
		return notify_fail("���������Ϊ̫��������ʹ�á�������ʽ���־���\n");

	if( (int)me->query("neili") < 300 )
		return notify_fail("�������̫���ˣ�����ʹ�á�������ʽ���־���\n");  

	message_vision(CYN"\n$Nʹ��ȫ��̵�ͬ�齣���е�"+RED+"��������ʽ��"+CYN+"�����׽���ȡͬ���ھ�֮�⣬���й���Ҫ���������Լӷ��أ�������Ƥ������ͷȺŹͬ��һ��\n"NOR,me,target);

	me->set_temp("tgj/canglan",1);

	ap = me->query("combat_exp", 1) / 1000 * me->query_int(1);
	dp = target->query("combat_exp", 1) / 1000 * target->query_int(1);

	skill = me->query_skill("tonggui-jian", 1);


	msg = YEL"\n$NȫȻ���˷�������Ȼ���һ��������$n��ǰ��˫���ս�"+weapon->name()+YEL"����ֱ����ȥ��\n"NOR;
	me->add_temp("apply/parry",-(int)skill/2);
	me->add_temp("apply/sword",(int)skill/2);

	if ( random( ap + dp) > dp
		||random(me->query_dex(1))>target->query_dex(1)/2) 
	{
		damage = me->query_skill("sword",1)+me->query_skill("force",1)+me->query_skill("tonggui-jian",1);
		damage = to_int( damage * skill/100);
		damage = damage + random(damage);
		if (damage > 4000 ) damage = 4000 + random(damage-4000)/50;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		me->add("neili", -200);
		me->add("jingli", -150);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
		i = 1;
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		me->add("neili", -100);
		me->add("jingli", -50);
	}
	message_vision( msg, me, target);
	me->add_temp("apply/parry",(int)skill/2);
	me->add_temp("apply/sword",-(int)skill/2);

	me->start_perform(2, "��������ʽ���־�");
	me->start_busy(random(2));
	me->delete_temp("tgj/canglan");
	if ( skill > 120 ) {
		me->set_temp("tgj/canglan", 1);
		perform1(me, target, weapon, ap, dp, skill, i);
	}
	return 1;
}

int perform1(object me, object target, object weapon, int ap, int dp, int skill,int i)
{
	string msg, dodge_skill;
	int damage, p;

	if ( !me) return 1;
	if( !weapon || !objectp(target)) {
		me->delete_temp("tgj/canglan");
		return 1;
	}

	msg =RED"\n$N��������������ϣ�"+weapon->name()+RED"��ס�Ķ���������$n�����ߴ�ҪѨ������б�·�ȫ���������У����д���$n��Ҫ����\n"NOR;     
	
	me->add_temp("apply/parry",-(int)skill/2);
	me->add_temp("apply/sword",(int)skill/2);

	if ( random( ap + dp) > dp ) {
		damage = me->query_skill("sword",1) +me->query_skill("tonggui-jian",1)+me->query_skill("force",1);
		damage = to_int( damage * skill/50.0);
		damage = damage + random(damage);
		if (damage > 5000 ) damage = 5000 + random(damage-5000)/50;
		if ( i ) damage -= random(damage/2);
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi",damage/2, me);
		me->add("neili", -250);
		me->add("jingli", -150);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		i = 0;
		me->add("neili", -100);
		me->add("jingli", -50);
	}
	me->add_temp("apply/parry",(int)skill/2);
	me->add_temp("apply/sword",-(int)skill/2);

	message_vision( msg, me, target);
	me->start_perform(3, "��������ʽ���־�");
	me->delete_temp("tgj/canglan");
	if ( skill > 160 ) {
		me->set_temp("tgj/canglan", 1);
		perform2(me, target, weapon, ap, dp, skill, i);
	}
	return 1;
}

int perform2(object me, object target,object weapon, int ap, int dp, int skill, int i)
{
	string msg, dodge_skill;
	int damage, p;

	if ( !me) return 1;
	if( !weapon || !objectp(target)) {
		me->delete_temp("tgj/canglan");
		return 1;
	}

	msg = MAG"\n$N����"+weapon->name()+MAG"�����������ལ�⣬��ʽ���ң�ȫȻ��Ҫ���Ĵ򷨣��󿪴�ϣ�����ֱ�롣\n"NOR;
	me->add_temp("apply/parry",-(int)skill/2);
	me->add_temp("apply/sword",(int)skill/2);

	if ( random( ap + dp) > dp
		||random(me->query_str())>target->query_dex()/2) {
		damage = me->query_skill("sword",1) * 4;
		damage = to_int( damage * skill/100.0);
		damage = damage + random(damage);
		if (damage > 6000 ) damage = 6000 + random(damage-6000)/100;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/2+random(damage/2), me);
		me->add("neili", -300);
		me->add("jingli", -150);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "����");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", "�ֱ�");
		me->start_perform(3+random(2), "��������ʽ���־�");
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
	}

	msg += WHT"\n$N��������ʽ��������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n\n"NOR;
	me->add_temp("apply/parry",(int)skill/2);
	me->add_temp("apply/sword",-(int)skill/2);

	me->delete_temp("tgj/canglan");
	message_vision( msg, me, target);
	me->add("neili", -100);
	me->add("jingli", -50);
	me->start_perform(3, "��������ʽ���־�");

	return 1;
}

string perform_name(){ return WHT"������ʽ"NOR; }

int help(object me)
{
        write(CYN"\nͬ�齣��֮��������ʽ����"NOR"\n\n");
        write(@HELP
	ͬ�齣��Ϊȫ������������ȫ�׽���ֻ�����أ������͹�����Ҫ��
	�������ͬ���ھ����ʵô�����ȫ�����Ӽɵ�ŷ�����书��ǿ����
	ŷ�����ػ���ԭʱȫ����и���֮�ݣ�Ϊ���������䵥ʱ��������
	������������������һ�˶���ȫͬ�š��𴦻��뽭���߹ּ���ľ��
	ʦ����ʱ�״�ʹ����
	������ʽ��ͬ�齣���������������ȫ�������ĵ��ʹ򷨣���ʽ�
	����������У����в�Ҫ������Ϊ��������ȱ��������������
	���½���������Ϊ�Է��������мǡ�

	ָ�perform sword.canglan

Ҫ��
	��ǰ����Ҫ�� 800 ����;
	�������Ҫ�� 1500 ���ϣ�
	ͬ�齣���ȼ� 120 ���ϣ�
	�����ڹ��ȼ� 120 ���ϣ�
	���������ȼ� 120 ���ϣ�
	��������Ϊͬ�齣����
	�����м�Ϊͬ�齣����
	�����ڹ����ޡ�

HELP
        );
        return 1;
}
