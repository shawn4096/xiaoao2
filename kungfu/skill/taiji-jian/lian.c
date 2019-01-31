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
		return notify_fail("�������־�ֻ����ս���жԶ���ʹ�á�\n");

	if( !living(target) )
		return notify_fail("�������־�ֻ����ս���жԶ���ʹ�á�\n");

	if( !weapon || weapon->query("skill_type") != "sword" )
		return notify_fail("�������޽������ʹ�á������־���\n");

	if( me->query_skill_mapped("sword") != "taiji-jian" )
		return notify_fail("����������̫���������޷�ʹ�á������־���\n");

	if( me->query_skill_mapped("parry") != "taiji-jian" )
		return notify_fail("�������̫������Ϊ�мܲ���ʹ�á������־���\n");  
//��������⿪̫���񹦺������������
	if( me->query_temp("tjj/chan") && !me->query("quest/wd/yyzq/taiji/pass"))
		return notify_fail("������ʹ�á������־���\n");

	if( (int)me->query_temp("tjj/lian") )
		return notify_fail("����������ʹ�á������־���\n");

	if( (int)me->query_skill("taiji-jian", 1) <300 )
		return notify_fail("���̫��������Ϊ�в�����,�޷�ʹ�á������־���\n");             

	if( (int)me->query_skill("yinyun-ziqi",1) < 300 )
		return notify_fail("�����������Ϊ��ǳ������ʹ�á������־���\n");

	if( (int)me->query_skill("sword",1) < 300 )
		return notify_fail("�����������Ϊ�в�����,����ʹ�á������־���\n");  

	if( (int)me->query("max_neili") < 1500 )
		return notify_fail("���������Ϊ̫��������ʹ�á������־���\n");

	if( (int)me->query("neili") < 800 )
		return notify_fail("�������̫���ˣ�����ʹ�á������־���\n");  

	message_vision(CYN"\n$N΢΢һЦ��ʹ��̫������"+RED+"������"+CYN+"�־����������ӻ�����ת,���ֳֽ��������𣬽���������ǰ��\n"
			"����������ԣ��籧Բ������"+weapon->name()+CYN"δ������Ȼ�������\n"NOR,me,target);

	me->set_temp("tjj/lian",1);

	ap = me->query("combat_exp", 1) / 1000 * me->query_int(1);
	dp = target->query("combat_exp", 1) / 1000 * target->query_int(1);

	skill = me->query_skill("taiji-jian", 1);

	msg = CYN"\n$N����"+weapon->name()+CYN"������ǰ��������һ���Σ�һ��ɭɭ������ֱ����$n��ͻȻ֮�䣬$N�������֣�����һ������$n��ȥ��\n"NOR;

	if ( random( ap + dp) > dp
		||random(me->query_dex(1))>target->query_dex(1)/2) 
	{
		damage = me->query_skill("sword") * 2;
		damage = to_int( damage * skill/100.0);
		damage = damage/2 + random(damage);
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
	me->start_perform(2, "�������־�");
	me->start_busy(random(2));
	me->delete_temp("tjj/lian");
	if ( skill > 150 ) {
		me->set_temp("tjj/lian", 1);
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
		me->delete_temp("tjj/lian");
		return 1;
	}

	msg =YEL"\n$N�ֽ��������֣�����ǰ��������ԲȦ���������໤סȫ�������ް�ֿ�϶���������Ž�����\n"+
		"����"+weapon->name()+YEL"��ס�Ķ���������$n�����ߴ�ҪѨ�����⼱��������������δ���\n"NOR;     

	if ( random( ap + dp) > dp ) {
		damage = me->query_skill("sword",1) +me->query_skill("taiji-jian",1)+me->query_skill("yinyun-ziqi",1);
		damage = to_int( damage * skill/150.0);
		damage = damage + random(damage);
		if (damage > 3500 ) damage = 3500 + random(damage-3500)/50;
		if ( i ) damage -= random(damage/2);
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi",damage/4, me);
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
	message_vision( msg, me, target);
	me->start_perform(3, "�������־�");
	me->delete_temp("tjj/lian");
	if ( skill > 200 ) {
		me->set_temp("tjj/lian", 1);
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
		me->delete_temp("tjj/lian");
		return 1;
	}

	msg = HIC"\n$N�������õ�"+RED+"��Ȧ"+HIC+"Խ��Խ�࣬������ʱ��ȫ������������"+RED+"��Ȧ"+HIC+"֮�У�"+RED+"��Ȧ"+HIC+"��Ȧһ��δ������һ��������\n"
		"����"+weapon->name()+HIC"��ʹ�ü��죬ȴ˿����������������֮�����������֮�����Ѵ��ڻ�����\n"
		HIC"$n���ӽ�����������"+RED+"��Ȧ"+HIC+"�����Լ������޿��˱ܣ�ֻ��ð��һ���������ֱ�һ�죬��"+RED+"��Ȧ"+HIC+"�����Ļ���ֱ�롣\n"NOR;

	if ( random( ap + dp) > dp
		||random(me->query_str())>target->query_dex()/2) {
		damage = me->query_skill("sword",1) * 4;
		damage = to_int( damage * skill/100.0);
		damage = damage + random(damage);
		if (damage > 4500 ) damage = 4500 + random(damage-4500)/100;
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
		me->start_perform(3+random(2), "�������־�");
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		me->add("neili", -100);
		me->add("jingli", -50);
		me->start_perform(3, "�������־�");
	}

	msg += HIY"\n$N�������־�������ϣ��������֣��ս�������������ȫ�����µĴ�С��Ȧ�漴������Ӱ��\n\n"NOR;
	me->delete_temp("tjj/lian");
	message_vision( msg, me, target);
	return 1;
}

string perform_name(){ return CYN"������"NOR; }

int help(object me)
{
        write(CYN"\n̫������֮������������"NOR"\n\n");
        write(@HELP
	̫�������������������۷�֮���������˽���
	����˸յ��Ⱥӡ�������ת�����ϴ󽭴�ӣ�
	���ϲ����������������ǽ��˽����ںϵ�����
	֮�У�����������
	
	perform sword.lian

Ҫ��
	��ǰ����Ҫ�� 800 ����;
	�������Ҫ�� 1500 ���ϣ�
	̫�������ȼ� 300 ���ϣ�
	�������ȼ� 300 ���ϣ�
	���������ȼ� 300 ���ϣ�
	��������Ϊ̫��������
	�����м�Ϊ̫��������
	�����ڹ�Ϊ��������

HELP
        );
        return 1;
}