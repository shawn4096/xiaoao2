// ����Ϊ����yihunӦ��100%�����Լ�����Ҫ�ж�pfm�Ƿ����С��� 
#include <ansi.h>
inherit F_SSERVER;

int exert(object me, object target)
{       
	int skill, ap, dp;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
        || !me->is_fighting(target)
        || !necessary(target) )
		return notify_fail("�ƻ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
    if ((int)me->query_skill("jiuyin-zhengong", 1) < 450)
		return notify_fail("��ľ����湦��Ϊ��������\n");
	if ((int)me->query_skill("force", 1) < 450)
		return notify_fail("��Ļ����ڹ���Ϊ��������\n");
    if (me->query_skill_mapped("force")!="jiuyin-zhengong")
		return notify_fail("�㼤�����ڹ����ԡ�\n");
	if( (int)me->query("int") < 40 )
                return notify_fail("����������Բ�����\n");

	if( (int)me->query("neili") < 2000 )
		return notify_fail("�������������\n");

	skill = me->query_skill("jiuyin-zhengong",1);

    ap = me->query_skill("force",1);
    dp = target->query_skill("force",1)/3;

	message_vision(HIW"$N����ͻȻ��ʼ����������ֵı��飬����ĺܣ��·���һ��ħ��������$n,$n����ʶ�࿴��һ�ۡ�\n"NOR, me, target);

    if (random(me->query_int()) > target->query("int")/2) 
    {
        int qi2 = target->query("qi");
        message_vision(HIW"$n��׼��ȡЦ$N��ãȻ������ʶ��ȴ��֪������ѧ��$N�ı��鶯����\n"NOR, me, target);
		message_vision(HIR"$N��Ȼ�������Լ������Ķ�����$n�������Լ������ƵĹ�������������Խ��Խ�أ�\n"NOR, me, target);
		target->add_temp("apply/attack",skill/3);
		target->add_temp("apply/damage",skill/3);
        target->set_temp("must_be_hit",1);

        COMBAT_D->do_attack(target, target, target->query_temp("weapon"), 3);
        if( me->is_fighting(target)&& random(2))
			COMBAT_D->do_attack(target, target, target->query_temp("weapon"),3);
        if( me->is_fighting(target)) 
			COMBAT_D->do_attack(target, target, target->query_temp("weapon"),3);
        if(objectp(target))
          {
			target->add_temp("apply/attack",-skill/3);
			target->add_temp("apply/damage",-skill/3);
            target->delete_temp("must_be_hit");

			if(qi2 > target->query("qi")) target->set_temp("last_damage_from", me);
           }
	        me->add("neili", - 350);
	        me->add("jingli", -100);
	}
	else {
		    message_vision(HIW"����$N��ô�仯���飬$n�������һ������Ϊ������\n"NOR, me, target); 
	        me->add("neili", - 150);
	        me->add("jingli", -50);
	}
    me->start_exert(3, "���ƻ�󷨡�");
	if ( !me->is_perform())
		me->start_perform(2, "���ƻ�󷨡�");
	return 1;
}

string exert_name(){ return HIG"�ƻ��"NOR; }

int help(object me)
{
        write(HIG"\n�����湦֮���ƻ�󷨡���"NOR"\n\n");
        write(@HELP
		�����澭�������������������������������أ���������
		�ⲿ�����澭����������ֶ�����ѧ�������ƻ��
		�ǽ��ڹ���ʹ��Ŀ�У�ʹ�öԷ�����ãȻ����֪�����˵�
		�����ն����ĺ��С�
		Ҫ��
			��ǰ���� 2000 ���ϣ�
			�������� 40 ���ϣ�
			�����湦�ȼ� 450 ���ϡ�
			�����ڹ��ȼ� 450 ���ϡ�

HELP
        );
        return 1;
}
