// ban.c �򹷰���--���־�
// Creat by Looklove@SJ 3/16/2001
// modified by Looklove 2001.5.10
// Modified by Lane@SJ 2005.7.29

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HBBLU"���־�"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int ap ,dp ,p, n;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("�����־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	if (!userp(me)) return 1;
	
	weapon = me->query_temp("weapon");

	if( !weapon
	 || weapon->query("skill_type") != "stick"
	 || me->query_skill_mapped("stick") != "dagou-bang" 
	 || me->query_skill_mapped("parry") != "dagou-bang" )
		return notify_fail("�������޷�ʹ�á����־�����\n");

	ap = me->query("combat_exp");
	dp = target->query("combat_exp");

	tweapon = target->query_temp("weapon");

	if( me->query_skill("dagou-bang", 1) < 400 )
		return notify_fail("��Ĵ򹷰�����������죬����ʹ�á����־�����\n");

	if( me->query_skill("bangjue",1) < 200 )
		return notify_fail("��Ĵ򹷰���������죬�޷�ʹ�������־�����\n");

	if( (int)me->query_skill("huntian-qigong",1) < 400 )
		return notify_fail("��Ļ��������������㣬�޷�ʹ�������־�����\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("��������������޷�ʹ�������־�����\n");

	if( (int)me->query("jingli") < 1000 )
		return notify_fail("��ľ�������������ʹ�������־�����\n");

	if( (int)me->query("max_neili") < 5000 )
		return notify_fail("��������Ϊ���ڲ����������á����־�����\n");

	if( target->query_temp("dgb/ban") )
		return notify_fail("�Է��Ѿ��������ˣ����ֹ����ɡ�\n");

	n = me->query_skill("bangjue", 1);

	if( me->query_skill("dagou-bang", 1) > 450 )
		n += random(me->query_skill("bangjue", 1)/2);

	ap = COMBAT_D->skill_power(me, "stick", SKILL_USAGE_ATTACK);
	dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE);

	ap += ap /100000 * me->query_skill("stick") * me->query_int(1)/3;
	dp += dp /100000 * target->query_skill("dodge") * target->query_int(1)/3;

	msg=HBBLU"$N"+weapon->name()+HBBLU"�ӳ����ԡ����־����ŵ�ɨȥ��һ���У������������������̣���Ӱ��ɽ���糤����������������\n"NOR;

	if( ( ap = random(ap+dp) ) > dp/2 )
	{
		msg+=HBBLU"$N�����ݵ�����˿����Ϣʱ����$n����������ת�������ˣ���֪�мƣ���"+weapon->name()+HBBLU"��������һ����������һ�����˵ص��ˡ�\n"NOR;
		target->add_busy(2+random(3));
		target->recieve_damage("qi", n*3, me);
		target->recieve_wound("qi", n*3, me);
		if (random(2))
		{
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		target->set_temp("dgb/ban", n*2);
		target->add_temp("apply/dodge",-n*2);
		target->apply_condition("dgb_ban_wound", n/30);
		me->add("neili", -400);
		me->add("jingli", -200);
		me->start_busy(random(2));
		me->set_temp("dgb/ban",1);
		call_out("check_perform", 1,me, target,weapon, n);
	}
	else if( ap > dp ) {
		msg+=HBBLU"$n���»��ң�̧����ȥ̤ס"+weapon->name()+HBBLU"��ȴ��"+weapon->name()+HBBLU"�ڽ�����һ����ͨ���ء�\n"NOR;
		target->add_busy(1+random(2));
		target->recieve_damage("qi", n*2, me);
		target->recieve_wound("qi", n*2, me);
		if( random(2) ) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		target->set_temp("dgb/ban", n);
		target->add_temp("apply/dodge",-n);
		target->apply_condition("dgb_ban_wound",n/40);
		me->add("neili", -300);
		me->add("jingli", -100);
		me->start_busy(random(2));
		me->set_temp("dgb/ban",1);
		call_out("check_perform", 1, me,target,weapon, n/2);
	}
	else {
		msg += HIG"$n���̹���ʮ����ʵ����չ��Ų��㿪"+weapon->name()+HIG"�İ��ƣ�˳��һ������$N��ƨ�ɡ�\n"NOR;
		me->start_busy(1+random(2));
		me->add("neili", -150);
		me->add("jingli", -50);
	}
	if( wizardp(me) ) tell_object(me, HIY"�򹷰��������־��������ʶԱ� "+ap+" ��"+dp+"��\n"NOR);
	if (!me->query("quest/gb/dgb/bangjue/pass") || me->query_skill("dagou-bang",1)<450)
		me->start_perform(2,"���־�");
	message_vision(msg, me, target);
	return 1;
}

void check_perform(object me,object target, object weapon,int bonus)
{
	
	if (!me) return;
	
	
	if (!me->is_fighting()
		||!target
		||!me->query_temp("dgb/ban")
		|| bonus<1) 
	{
		me->delete_temp("dgb/ban");
		message_vision(HBBLU"$N�ۼ��Է��Ѿ����䣬�����е�"+weapon->query("name")+HBBLU"һ�գ�����һ������ֹͣ�����־�����\n"NOR,me);
		return;
	}
	if (random(10)>5)
	{	
		switch (random(3))
		{
			case 0:
				message_vision(CYN"$Nһ���У������������������̣���ֻһ�������־����м�ȴ�̲���ǧ���򻯣�����ʤ����\n"+
							"$nԽԾԽ�죬��������һƬ��Ӱ���ɵı̹��������衣������ʮ�߰��£�$n������������\n"+
							weapon->query("name")+CYN"��������һ����������һ�����˵��ڵأ�\n"NOR,me,target);
				target->receive_damage("qi",1000+random(2000),me);
				target->receive_damage("qi",500+random(1000),me);
				target->add_busy(2);
				break;
			case 1:
				message_vision(YEL"$n������Ծ�����ǡ����־�����������һ������һ������һ�����ܱܹ�����ʱ�㿪�������跨\n"+
								"���ܵڶ���������һ��������������������Ҫ�����ڶ���������̸�����ף������ý�������\n"+
								"���������ӣ����Ʋ���������֦֮�У�һ��ˤ��������������һ��ˤ����\n"NOR,me,target);
				target->add_busy(2+random(2));
				target->receive_damage("jing",random(800),me);
				target->recieve_wound("jing",random(500),me);
				break;
			case 2:
				message_vision(WHT"$nת�������ˣ���֪�мƣ�΢�о���Ϯ�����̣���æӿ��Ծ����������һ�У����ǡ����־���\n"+
								"���糤����ӣ���������������ݵ�����˿����Ϣʱ����һ���У������������������̣���ֻһ��\n"+  
								"��ʽ����ȴ�仯��ǧ�������޾���\n"NOR,me,target);
				target->add_busy(2+random(2));
				target->receive_damage("jingli",random(1000),me);
			//target->recieve_wound("jingli",random(1000),me);

				break;
		}
	 }
	call_out("check_perform", 1, me,target,weapon,bonus-3);
	return;
}

int help(object me)
{
        write(HBBLU"\n�򹷰������־�����"NOR"\n");
        write(@HELP
	�򹷰����ᡢ�ɡ�����ƣ��轫�������Ĵ�ֻ����Ӱ������Ӱ��
	�⡸���־�����ȴ��ר���������̵��������������̲��ȵĶ���
	������Ч��һ�����У��������α������ش������ơ�
	ע�⣺�⿪�����־������ܺ󣬡����־�����ɡ�
	
	ָ�perform stick.ban
	
Ҫ��
	����������� 2000 ���ϣ�
	��ǰ�������� 600 ���ϣ�
	�򹷰����ȼ� 400 ���ϣ�
	���������ȼ� 400 ���ϣ�
	�򹷰����ȼ� 200 ���ϣ�
	�����м�Ϊ�򹷰���
HELP
        );
        return 1;
}
