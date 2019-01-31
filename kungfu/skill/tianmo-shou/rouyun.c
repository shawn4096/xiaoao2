// rouyun.c ����
//ǿ��Ů�Ե�����֮��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{

	int damage;
	

    
	if( !target ) target = offensive_target(me);

	if( !target ||!living(target)|| !target->is_character() || !me->is_fighting(target) )
		return notify_fail("�����ƾ�����ֻ����ս���жԶ���ʹ�á�\n");

	if( objectp( me->query_temp("weapon")) )
		return notify_fail("ֻ�п��ֲ���ʩչ�����ƾ�������\n");
    if( me->query_skill_mapped("dodge")!="huanmo-wubu" )
		return notify_fail("��Ҫ������ħ�貽����ʩչ�����ƾ�������\n");
	if( (int)me->query_skill("tianmo-shou", 1) < 250 )
		return notify_fail("�����ħ�Ʒ�������죬����ʹ�á����ƾ�������\n");

	if( (int)me->query_skill("tianmo-gong", 1) < 250 )
		if( (int)me->query_skill("xixing-dafa", 1) < 250 )
		return notify_fail("��������ڹ��ȼ�����������ʹ�á����ƾ�������\n");
	
	if( (int)me->query_dex() < 25 )
		return notify_fail("���������ǿ������ʹ�á����ƾ�������\n");



	if( (int)me->query("neili", 1) < 1200 )
		return notify_fail("����������̫��������ʹ�á����ƾ�������\n");

	if( (int)me->query("neili", 1) < 50 )
		return notify_fail("�����ڵ�����ʩչ������ô���С�\n");

	if( me->query_temp("tms/rouyun"))
		return notify_fail("�������ʩչ���ƾ�����\n");
	if(target->is_busy())
		return notify_fail("�Է��Ѿ�æ�ң��Ͻ������ɣ�\n");
    damage=me->query_skill("tianmo-shou",1)+me->query_skill("tianmo-gong",1)+me->query_skill("xixing-dafa",1);
	damage=damage*2+random(damage);
	me->set_temp("tms/rouyun",1);

	message_vision(HIG"$N��Ȼ˫��һ�䣬�����ƺ��������������ƻ�ʵ�죬�·�һ���޻�����һ��������ħ�֡����ƾ�������\n"NOR, me, target);
	message_vision(HIG"$N��˫��˲���ף�������ʯ�����赭д����$n��ǰ��Ѩ��ȥ��\n"NOR, me, target);
	if( random(me->query("combat_exp")) > target->query("combat_exp")/2
		||random(me->query_skill("hand",1))>target->query_skill("parry",1)/2)
	{
		message_vision(HIB"$nֻ��$N��������$n�����ḧ��һ�£�ԭ���������⣬��˲��һ�ɼ�Ϊ����ľ���������\n"NOR, me, target);
		target->add_condition("neishang",1+random(2));
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/5,me);
		if (userp(target)) target->add_busy(1);
		else target->add_busy(3+random(1));
		call_out("rouyun_attack",1+random(1),me,target);
	}    
	
	call_out("remove_effect",2,me);
    
	 return 1;
}
int rouyun_attack(object me,object target)
{
	if (!me) return;
	if (!me->is_fighting()||!target) 
	{
		message_vision(BLU"$N������ĺ�һ�´�գ�������й��\n"NOR,me,target);
		return 1;
	}
	message_vision(BLU"$N��ʩչ�����ƾ�����ʱ���ŷ�����$nֻ����ɾ������Լ��������Ҵܲ��ѣ�$N����������У�\n"NOR,me,target);
	target->set_temp("must_be_hit",1);
		me->add_temp("apply/damage",me->query_skill("tianmo-shou",1)/4);
		 COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
		  COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
		 me->add_temp("apply/damage",-me->query_skill("tianmo-shou",1)/4);
	target->delete_temp("must_be_hit");
	target->add_condition("neishang",2+random(2));
	return 1;
}
int remove_effect(object me)
{
	if (!me) return 0;
	me->delete_temp("tms/rouyun");
	message_vision(HIC"$Nһ�������³��������ƾ������չ���\n"NOR,me);
	return 1;
}
string perform_name(){ return HIY"���ƾ���"NOR; }

int help(object me)
{
	write(HIG"\n��ħ��֮�����ƾ�������\n"NOR);
	write(@HELP
	��ħ���������������Ů�Ը���������һ�ž�ѧ���������ྡྷ
	��������ַ���Ů�����͵��ص㣬��ս�������赭д֮�佫��
	��֮��ʽʩչ�ڶԷ����ϣ�����ɱ��������ַ���ʤ����
	���ƾ�����ͨ���������ĽӴ��������ᾢ������Է�Ѩ��֮
	�е��¶Է����е�������ʽ��

	ָ�perform hand.rouyun

Ҫ��	
	��ħ�ַ��ȼ� 250 ���ϣ�
	�����ַ��ȼ� 250 ���ϣ�
	��ħ���ȼ� 250 ���ϣ������Ǵ󷨣�
	������� 1200 ���ϣ� 
	��С������ 25��
HELP
      );
   return 1;
}
