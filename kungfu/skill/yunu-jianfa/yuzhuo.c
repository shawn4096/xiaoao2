// yuzhuo.c �������
//Created by sohu@xojh 2014/9

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HIW"�������"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int ap, dp,damage;

	me->clean_up_enemy();
	target = me->select_opponent();

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("���������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	weapon = me->query_temp("weapon");
	tweapon = target->query_temp("weapon");
	damage=me->query_skill("yunu-jianfa",1)+me->query_skill("yunu-xinjing",1)+me->query_skill("suxin-jue",1);
	damage=damage*me->query_dex(1)/20+random(damage);

	if( !weapon
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("parry") != "yunu-jianfa" 
	 || me->query_skill_mapped("sword") != "yunu-jianfa" )
		return notify_fail("�������޷�ʹ�á����������\n");

	if( !tweapon )
		return notify_fail("�Է�û��ʹ���κα��������޷�ʹ�á����������\n");

	if((int)me->query_skill("yunu-jianfa", 1) < 200 )
		return notify_fail("�����Ů������������죬����ʹ�á����������\n");
	if((int)me->query_skill("yunu-xinjing", 1) < 200 )
		return notify_fail("�����Ů�ķ���������죬����ʹ�á����������\n");
	if((int)me->query("neili") < 2000 )
		return notify_fail("�������������\n");

	if( (int)me->query_dex() < 50 )
		return notify_fail("��ĺ��������㣬�޷�ʹ�á����������\n");

	if( me->query_skill_mapped("sword") != "yunu-jianfa"
		|| me->query_skill_mapped("parry") != "yunu-jianfa" )
                return notify_fail("����Ҫ�����м�Ϊ��Ů����������ʹ�á����������\n");
	if( me->query_skill_mapped("force") != "yunu-xinjing")
                return notify_fail("����Ҫ�����ڹ�Ϊ��Ů�ľ�������ʹ�á����������\n");
	message_vision(HIY"$N�����󽣾�бָ��������ס"+weapon->query("name")+NOR+HIY"�ڿ��л���һ��Բ��һ����ȴͻȻ����$n������\n"NOR,me,target);

	//me->start_perform(3, "�������");

	ap = me->query("combat_exp")/100000;
	dp = target->query("combat_exp")/200000;

	if( random(ap)>dp
		||random(me->query_int(1))>target->query_int(1)/2
		|| random(me->query_dex(1))>target->query_dex(1)/2) 
	{				
		message_vision(HIR"$nֻ������һʹ��Ϊ$N���С����Ѩ����һ�����ղ�ס�����б���������ϡ�\n"NOR,me,target);
		target->add_busy(2+random(2));
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/4,me);
		if (tweapon)
		{
			tweapon->unequip();
			tweapon->move(environment(target));
		}
		
	}
	else {
		if (!objectp(tweapon) && objectp(target)) message_vision(CYN"$n��æ���֣������˹���������"+weapon->query("name")+CYN"������������$N�ġ���������������Σ�\n"NOR,me,target);
		if (objectp(weapon) && objectp(tweapon))
			 message_vision(CYN"$n��æ���֣������˹���"+tweapon->query("name")+CYN"��"+weapon->query("name")+CYN"����һ���⻷����$N�ġ���������������Σ�\n"NOR,me,target);
		me->add_busy(1);

	}
	if (me->query_skill("yunu-jianfa",1)<350)
	{
		me->start_perform(1,"�������");
	}
	me->add("neili",-300);
	me->add("jingli",-100);
	
	return 1;
}

int help(object me)
{
	write(WHT"\n��Ů����֮�����������"NOR"\n");
	write(@HELP
	��Ů�������ؾ��У����Ĺ��ΪŮ�ӣ�������Ů����
	������ʤ�����ǿ����о�����������ʽ�����鶯��ʤ
	������������,��̬ƮƮ����,��������Ʈ�ݷ��ˣ��
	����ӣ��Ծ���д��жԷ�������Ѩ��

	perform sword.yuzhuo
	
Ҫ��
	��ǰ����Ҫ�� 2000 ���ϣ�
	��Ů�����ȼ� 200 ���ϣ�
	��Ů�ľ��ȼ� 200 ���ϣ�
	��Ч���ȼ� 50  ���ϣ�
	��������Ϊ��Ů������
	�����м�Ϊ��Ů������
	���������ޱ���������Ч����
HELP
	);
	return 1;
}