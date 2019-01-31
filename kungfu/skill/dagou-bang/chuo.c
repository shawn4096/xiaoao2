// chuo.c �򹷰���--���־�
// Creat by Looklove@SJ 2001.4.9
// Modified by Looklove@SJ 2001.5.19
// update for condition limit by Lklv 2002.1.16

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int dgb_chuo(object me,object target,object weapon);

string perform_name(){ return HBWHT"���־�"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int mexp, texp, mlvl, tlvl, i, j, b, n;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("�����־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	weapon = me->query_temp("weapon");

	if( !weapon
	 || weapon->query("skill_type") != "stick"
	 || me->query_skill_mapped("stick") != "dagou-bang" )
		return notify_fail("�������޷�ʹ�á����־�����\n");

	mexp = me->query("combat_exp");
	texp = target->query("combat_exp");

	mlvl = me->query_skill("dagou-bang",1);
	tlvl = target->query_skill("dodge",1);

	i = me->query_int(1);
	j = target->query_int(1);
	b = me->query_skill("bangjue",1);

	tweapon = target->query_temp("weapon");

	if( mlvl < 200 )
		return notify_fail("��Ĵ򹷰�����������죬����ʹ�á����־�����\n");

	if( b < 120 )
		return notify_fail("��Ĵ򹷰���������죬�޷�ʹ�������־�����\n");

	if( (int)me->query_skill("huntian-qigong", 1) < 200 )
		return notify_fail("��Ļ��������������㣬�޷�ʹ�������־�����\n");

	if( (int)me->query("neili") < 600 )
		return notify_fail("�������������\n");
	if( me->query_skill_mapped("force")!="huntian-qigong" )
		return notify_fail("�㼤�����ڹ����ԡ�\n");
	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("��������Ϊ���ڲ���, �����á����־�����\n");

	if ( target->query_condition("no_exert") || target->query_condition("no_force"))
		return notify_fail("�Է��Ѿ�����Ĵ��־����У��󵨽����ɣ�\n");

	i = mexp/1000000*(mlvl+i);
	j = texp/1000000*(tlvl+j*2);
	i += COMBAT_D->skill_power(me, "stick", SKILL_USAGE_ATTACK);
	j += COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE);

	n = b /100 + random(b/100) + mlvl/50;
	if( mlvl > 450 ) n += (mlvl-450)/50;
	if( n > 8 ) n = 8; // ����Ŀ�����busy ��condition��

	msg = HBWHT"$Nʹ���򹷰������־�����"+weapon->query("name")+HBWHT"�������ϣ��������ֱ��$n�����к���\n"NOR;

	if( random(i+j) > j*5/4 ) {
		msg += HBWHT"$n�������˼�����������һ�����ֲ�������"+weapon->query("name")+HBWHT"�͵Ĵ���ҪѨ��\n"NOR;
		msg += HBCYN+HIW"���$n��ʱ��ɫ�԰ף��о�������Ϣ���ң�ͷ�ؽ��ᡣ\n"NOR;
		target->add_busy(1+random(2));
		target->set_temp("dgb/chuo", n);
		target->apply_condition("no_force",n);
		target->add_busy(1);
		target->add("neili",-2000-random(1000));		
		//����Է���������
		if (target->query("neili")<0)
			target->set("neili",0);
		//���жԷ���
		target->receive_damage("qi",2000+random(1000),me);
		target->receive_wound("qi",500+random(500),me);
		message("wizard", HIG"���־���ʱЧ"+n*20+"�룬ʹ����EXP"+mexp+"������EXP"+texp+"��\n"NOR, environment(me), me);
	}
	else {
		if (tweapon) msg += HBWHT"$n���һ������æ������"+tweapon->query("name")+HBWHT"��"+weapon->query("name")+HBWHT"��һ����\n"NOR;
		else msg += HBWHT "$n���а��в��ã������������������������ܹ���"+weapon->query("name")+HBWHT"�����ơ�\n" NOR;
		
		if ( random(mexp) > texp/2 ){
			msg += WHT "����$N�����ϵ�$n�д�һ�У�����"+weapon->query("name")+WHT"һת���Ĵ�$n�Ľ��ס�\n" NOR;
			msg += WHT ""+weapon->query("name")+WHT"����������$n�Ѿ����޿ɱܣ���ͨһ��Ӧ��������\n" NOR;
			target->apply_condition("no_exert",(int)n/2);
			target->add_busy(3+random(2));
			message("wizard", HIG"���־���ʱЧ"+n*20/3+"�룬ʹ����EXP"+mexp+"������EXP"+texp+"��\n"NOR, environment(me), me);
		}
		
	}
	if (objectp(target))
		call_out("dgb_chuo",1,me,target,weapon);
	message_vision(msg, me, target);
	
	me->start_perform(3, "���־�");

	me->start_busy(1+random(2));
	me->add("neili",-500);
	me->add("jingli",-200);
	return 1;
}

int dgb_chuo(object me,object target,object weapon)
{
	
	if (!me || !target) return 0;
	
	message_vision(HIC"$N��$n��ע�⣬��Ȼת��$n�������"+weapon->query("name")+HIC"���ͣ�ʹ���򹷰����е����С������־���������$n���ϴ�ȥ��\n"NOR,me,target);

	if (random(me->query_int())>target->query_int()/3)
	{
			message_vision(HIY"\n��$n���书��Ϊ����������ͻʩ���㣬���в�֪֮�����Ǵ򹷰����˵�������$n�侪��������֮���վ����ǲ�����ô���磬\n"+
					"�۵�һ�£������β�������$n�ڹ�����β����Ƕ���֮����������һ��ȴҲ������ʹ����֮���䲻�⣬��ֻ�����ɱܹ���ƫƫ���ִ��У�\n"+
					"���ɵá�������һ�����˳�����\n"NOR,me,target);
			target->receive_damage("qi",2000+random(1000),me);
			target->receive_wound("qi",500+random(500),me);
			target->receive_damage("jingli",100+random(500),me);

	}else {
		message_vision(HIC"$nʶ����$N����ͼ����ǰһ������˿�ȥ��\n"NOR,me,target);

	}
	target->set_temp("must_be_hit",1);
	me->add_temp("apply/damage",(int)me->query_skill("dagou-bang",1)/4);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/damage",-(int)me->query_skill("dagou-bang",1)/4);
	target->delete_temp("must_be_hit");
	return 1;

}
int help(object me)
{
	write(HBWHT"\n�򹷰������־�����"NOR"\n");
	write(@HELP
	�򹷰���ʽ�쳣���ɺ�ɨ���򣬴ˡ����־�����������
	���������в��������Ϣ���֮ҪѨ��һ�����У�����ס��
	��֮��Ϣ��·��һ��ʱ����ʹ������Ϣ���Ҷ��������е�����
	�����뾭��ֵ���似�ȼ��й�
	
	ָ�perform stick.chuo

Ҫ��
	����������� 2000 ���ϣ�
	��ǰ�������� 600 ���ϣ�
	�򹷰����ȼ� 200 ���ϣ�
	���������ȼ� 200 ���ϣ�
	�򹷰����ȼ� 120 ���ϣ�
	��������Ϊ�򹷰�
	�����м�Ϊ�򹷰���
	�����ڹ�Ϊ��������
	�ְֳ�������
HELP
	);
	return 1;
}
