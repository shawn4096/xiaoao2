// shuangjue.c It's a "pfm" .
// by Looklove@SJ 2001/2/14 ...���˽�
// Modify by looklove 2001.4.4
// Mofify by looklove 2001.4.8
// Modify by looklove 2001.5.2

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HIM"����˫��"NOR; }
int perform(object me, object target)
{
	int b, z, j;
	object weapon;
	b = me->query_skill("dagou-bang", 1);
	b += me->query_skill("xianglong-zhang", 1);
	weapon = me->query_temp("weapon");

	//if (!target ) target = offensive_target(me);
	//|| !necessary(target)

	if (!objectp(target) || !me->is_fighting(target))
		return notify_fail("������˫����ֻ����ս���жԶ���ʹ�á�\n");

	if(!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "stick")
		return notify_fail("������û�а����޷�ʹ�ð���˫����\n");
	if( !me->query("quest/gb/dgb/shuangjue/pass"))
		return notify_fail("����δ�ܵ����߹���ָ�㣬�޷�ʹ�ð���˫����\n");

	if( (int)me->query_int(1) < 50)
		return notify_fail("��������Բ��㣬�޷�ʹ�ð���˫����\n");

	if( (int)me->query_skill("dagou-bang", 1) < 450 )
		return notify_fail("��Ĵ򹷰�����������죬ʹ����������˫����������\n");

	if( (int)me->query_skill("xianglong-zhang", 1) < 450 )
		return notify_fail("��Ľ���ʮ���ƻ�δ���ɣ�����ʹ�ð���˫����\n");

	if( me->query_skill_mapped("force") != "huntian-qigong"
	|| (int)me->query_skill("huntian-qigong", 1) < 450 )
		return notify_fail("��Ļ���������û��ѧ�ɣ��޷�ʹ�ð���˫����\n");

	if( me->query_skill_mapped("parry") != "dagou-bang")
		return notify_fail("����мܹ����Ǵ򹷰����޷�ʹ�ð���˫����\n");

	if( me->query_skill_mapped("strike") != "xianglong-zhang"
	|| me->query_skill_prepared("strike") != "xianglong-zhang")
		return notify_fail("��û���ý���ʮ���ƣ��޷�ʹ�ð���˫����\n");

	if( (int)me->query("max_neili") < 5000 )
		return notify_fail("�����������̫����ʹ����������˫������\n");

	if( (int)me->query("neili") < 2500 )
		return notify_fail("����������̫����ʹ����������˫������\n");

	if((int)me->query("jingli") < 1200 )
		return notify_fail("��ľ�������������ʹ���˾�����\n");

	z = b/2;
	//z=b;		
	j = to_int( z / 4.5);

	if( z >= 450 )
		j = to_int( z/3 * z/250.0 );
	else j = to_int( z/5 * z/250.0 );
/*	if( z < 350 )
		j = to_int( z/5 * z/250.0 );	
	else if( z > 450 )
		j = to_int( z/3 * z/450.0 );*/
	//write("j="+j);
	message_vision(HBGRN+HIW"\n$N���һ��������˫����������"+weapon->name()+HBGRN+HIW+"��$n������ֻ�����в��ƣ��Ʋ��ɵ����������ҡ�\n"NOR, me, target);

	me->add_temp("apply/attack", j);
	me->add_temp("apply/damage", j/2);

	me->set_temp("shuangjue/dgb", 3);

	me->add_temp("apply/stick", j);
	me->add_temp("apply/damage", j /3);
	if( me->is_fighting(target)) {

		message_vision(HIG"\n$N���ִ򹷰��ܼ��Եĵ�أ�����һƬ��Ӱ,"+weapon->name()+HIG+"��$n������\n"NOR, me, target);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	}
	me->add_temp("apply/stick", -j);
	me->add_temp("apply/damage", -j/3);
//������
	//message_vision(HIY"\n$n������Ƭ��Ӱ֮�ʣ�$N����̧��������ɽ�����ǽ����Ƶ���ʽ��\n"NOR, me, target);

	me->set_temp("shuangjue/xlz", 2);

	weapon->unequip();
	me->add_temp("apply/strike", j);
	if( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/strike", -j);
	weapon->wield();
	//�򹷰���ʽ
	//message_vision(HIG"\n$N����һ������$n���б�У�ת��һ�д򹷰��������ֶ�����\n"NOR, me, target);

	me->add_temp("apply/stick", j);
	me->add_temp("apply/damage", j /2);
	if( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/stick", -j);
	me->add_temp("apply/damage", -j/2);
	//������
	//message_vision(HIY"\n$N��"+weapon->query("name")+HIY"�������֣����ֳʿ����л�֮�ƣ�����$n�����ߡ�\n"NOR, me, target);

	weapon->unequip();
	me->add_temp("apply/strike", j);
	if(me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/strike", -j);
	weapon->wield();
	//�򹷰�
	//message_vision(HIG"\n$N˫��ִ"+weapon->query("name")+HIG"�ȵ����������Ƥ��������������ɽ֮�ƣ���$n���˹�ȥ��\n"NOR, me, target);

	me->add_temp("apply/stick", j);
	me->add_temp("apply/damage", j /2);
	if( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/stick", -j);
	me->add_temp("apply/damage", -j/2);


	me->add_temp("apply/attack", -j);
	me->add_temp("apply/damage", -j/2);

	me->add("neili", -500-random(1000) );
	me->add("jingli", -300-random(200));
	me->delete_temp("shuangjue");
    me->start_perform(4+ random(2),"������˫����");
	me->start_busy(random(2));
	return 1;
}

int help(object me)
{
	write(WHT"\n�򹷰���֮������˫������"NOR"\n");
	write(@HELP
	�򹷰���һ�ž��������ϰ�����򹷰�������ûȫ��
	���ӳ���֮ǰ������ʩչ�򹷰��������Բ��㣬����
	�ͽ�����ʮ���Ƶ���ʽ���뵽�����У���Ȼ��Щ�Ӳ�
	�����򹷰��뽵��ʮ���ƾ�����һ�����в��ƣ���
	��Ҳ�Բ�ͬ���죬�����е���������Ҫ�����似��

	ָ�peform stick.shuangjue

Ҫ��
	������������ 50 ���ϣ�
	����������� 5000 ���ϣ�
	��ǰ�������� 2500 ���ϣ�
	�򹷰����ȼ� 450 ���ϣ�
	���������ȼ� 450 ���ϣ�
	�����Ʒ��ȼ� 450 ���ϣ�
	�����м�Ϊ�򹷰���
	�����书Ϊ����ʮ���ơ�
HELP
	);
	return 1;
}
