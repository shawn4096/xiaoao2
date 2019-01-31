// sanhua.c �����۶���
// sohu@xojh

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage,skill,wap,wdp;
	string *limb, type, result, str,msg;

	type = "����";

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("�����۶�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( me->query_temp("sanhua") )
		return notify_fail("������ʹ�������۶��ˣ�\n");

	if( me->query_temp("kongming") )
		return notify_fail("������ʹ����̨�����ˣ�\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("���ֲ���ʩչ�����۶���\n");

	if( me->query_skill_mapped("strike") != "haotian-zhang" )
		return notify_fail("�����õĲ����������ƣ�����ʩչ�����۶���\n");

	if( me->query_skill_prepared("strike") != "haotian-zhang" )
                return notify_fail("�������Ĳ����������ƣ�����ʩչ�����۶���\n");

	if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("�����õĲ������칦��ʩչ���������۶���\n");

	if( me->query_skill("force") < 150 )
		return notify_fail("������칦���δ�����޷�ʩչ�����۶���\n");

	if( me->query_skill("strike") < 150 )
		return notify_fail("�����۶���Ҫ��տ���������Ʒ�����Чʩչ��\n");

	if( me->query("neili") <= 300 )
		return notify_fail("�����������ʹ�������۶���\n");

	if( me->query("jing") <= 200 )
		return notify_fail("��ľ�����ʹ�������۶���\n");


	msg = HIM"$N�����������칦�������鲼ȫ��ͷ��ð��˿˿��������Ȼ����������������������һ�ƣ�һ���������˳�һ����$nϮ����\n\n"NOR;
	message_vision(msg, me, target);

	me->set_temp("sanhua", 1);

	skill =  ( me->query_skill("strike")
		+ me->query_skill("force") ) / 3;

	me->add_temp("apply/attack", skill/2);
	me->add_temp("apply/damage",  skill/6);
	me->add_temp("apply/dodge",  skill/2);
	me->add_temp("apply/parry",  skill/2);
	me->add_temp("apply/defense",  skill/2);
//����Է�������
	weapon = target->query_temp("weapon");

    if( objectp(weapon) )
	{
		wap =   me->query("force")/5
		+ (int)me->query("haotian-zhang")/5
		+ (int)me->query_str()
		+ (int)me->query("jiali");

		wdp = (int)weapon->weight() / 500
		+ (int)target->query_str()
		+ (int)target->query("jiali")
		+ (int)target->query_skill("parry")/3;

		wap = wap/2 + random(wap/2);

		if( wap > 3 * wdp ) {
			message_vision(HIY"ֻ��$N���ϵ�$n"+HIY+"�ѱ�һ����ϡ�\n"NOR, target, weapon);
			weapon->unequip();
			weapon->move(environment(target));
			weapon->set("name", "�ϵ���" + weapon->query("name"));
			weapon->set("value", 0);
			weapon->set("weapon_prop", 0);
			target->reset_action();
			me->add("neili", -150); // to break weapon takes more neili
		} else if( wap > 2 * wdp ) {
			message_vision(HIW"$Nֻ��������" + weapon->name() + "��һ����ðѳֲ��������ַɳ���\n" NOR, target);
			weapon->unequip();
			weapon->move(environment(target));
			target->reset_action();
			me->add("neili", -120); // to break weapon takes more neili
		} else if( wap > wdp ) {
			message_vision("$Nֻ��������" + weapon->name() + "һ����Щ���֣�\n", target);
			me->add("neili", -100); // to break weapon takes more neili
		}
	}
	else{
		me->add_temp("apply/attack", skill/2);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
		me->add_temp("apply/attack", -skill/2);
	}
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

	me->add("neili", -skill/2);
	me->add("jingli", -100);
	me->add("jing", -100);
	me->start_busy(random(2));

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/2 :), skill/15);

	return 1;
}

void remove_effect(object me, int amount)
{
	me->add_temp("apply/attack", -amount);
	me->add_temp("apply/damage", -amount/3);
	me->add_temp("apply/parry", -amount);
	me->add_temp("apply/dodge", -amount);
	me->add_temp("apply/defense", -amount);
	me->delete_temp("sanhua");
	message_vision(
	HIY "\n$N����һ�������������ջص��\n\n" NOR, me);

	return;
}

int help(object me)
{
        write(HIW"\n�����֮�������۶�����"NOR"\n");
        write(@HELP
	�������ȫ���ǰ���书֮һ���������к��ĵ��������书
	ȫƾһ���������ڣ����಻������ʹ���������Է���������
	����ȫ��߼��书�Ļ�����ȫ�����������������
	�����۶�����ȫ����������Ƶĸ����Ʒ��������칦������
	�����Ʒ��У���ʱ���������Ʒ�������ͬʱ˲���������У�
	�����޴�������������õõ����Խ��Է�������ϡ�
	
	ע�⣺set ����� �� �书ЧΪ��϶Է�����
		
	ָ�perform strike.sanhua

Ҫ��
	���칦���ĵȼ� 200  ���ϣ�
	ԧ�������ȵȼ� 200  ���ϣ�
	�����ȷ��ĵȼ� 200  ���ϣ�
	��������Ҫ�� 1500 ���ϣ�
	��ǰ������Ҫ�� 800  ���ϣ�
	�����ұ��Ʒ�Ϊ����ƣ�
	�������칦��
	�����ұ��Ʒ�Ϊ����ơ�
HELP
        );
        return 1;
}

