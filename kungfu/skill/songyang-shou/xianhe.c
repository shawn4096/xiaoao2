// Created by Numa 2000.1.25
// Modified by darken@SJ

#include <ansi.h>
#include <combat.h> 
#include "/kungfu/skill/eff_msg.h"
inherit F_SSERVER;

string perform_name() {return HIG"�ɺ���"NOR;}

int perform(object me, object target)
{
		int i, j, damage, num, p, win=0;
		int tmp,focus,skill;
		string msg;
		focus = me->query_temp("ss/focus");
		skill = me->query_skill("songyang-shou", 1);
		if( !target ) target = offensive_target(me);
		
		if( !target
		|| !target->is_character()
		|| !me->is_fighting(target) 
		|| !living(target))
			return notify_fail("�����־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

		if( (int)me->query_skill("songyang-shou", 1) < 220 )
			return notify_fail("��Ĵ������ֻ�򲻹���\n");

		if( (int)me->query_skill("parry", 1) < 220 )
			return notify_fail("��Ļ����мܻ�򲻹���\n");

		if( (int)me->query_skill("hanbing-zhenqi", 1) < 220 )
			return notify_fail("��Ļ����ڹ���򲻹���\n");

		if( (int)me->query("max_neili") < 2500 )
			return notify_fail("���������Ϊ������\n");

		if( (int)me->query("neili") < 500 )
			return notify_fail("�������������\n");

		if( (int)me->query("jingli") < 500 )
			return notify_fail("��ľ���������\n");

		if (userp(me)&&!me->query("quest/ss/sys/xianhe/pass"))
			return notify_fail("�㲻�������־�����\n");

		if (me->query_skill_mapped("force") != "hanbing-zhenqi")
			if (me->query_skill_mapped("force") != "lengquan-shengong")
			return notify_fail("����ʲôΪ������ʹ�����־���?\n");

		if (me->query_skill_prepared("hand") != "songyang-shou"
		|| me->query_skill_mapped("hand") != "songyang-shou")
			return notify_fail("�������޷�ʹ�������֡�\n");

		if (me->query_temp("weapon"))
			return notify_fail("�����־���ֻ�ܿ���ʹ�ã�\n");

		if( me->query_temp("ss/xianhe"))
			return notify_fail("������ʹ�������־�����\n");

		me->add("neili", -200);
		me->add("jingli", -50);
		message_vision(HIY "\n$N����Ծ�𣬰���������ɺ�չ�ᣬʩչ�������־������ɺ��֡���˫���������裬����$n�����ƾ���\n" NOR,me, target);

		me->add_temp("apply/attack", skill/3);
		me->add_temp("apply/damage", skill/5);
		me->set_temp("ss/xianhe", skill);
		
		if (me->query("quest/ss/sys/xianhe/pass"))
		{		
			msg = HIB "\n$N˫����������,������裬�����ۻ�ľ���һǰһ��ѹ��$n��$n��ʱ�о���Ϣ��˳��\n" NOR;

			if (random(me->query("combat_exp")) > target->query("combat_exp")/3
				|| random(me->query_skill("hand",1))>target->query_skill("parry",1)/3)
			{
				msg += HIW"$n�������������ɺ��־޴���ѹ�ƣ�һ����Ѫ��ʱ�����ؿڣ���Ϊ���ܣ��۵�һ���³�һ����Ѫ��\n"NOR;
				damage = (int)me->query_skill("hanbing-zhenqi") + (int)me->query_skill("songyang-shou")*2;
				damage = (random(damage) + damage) * (random(2)+2);
				if(userp(target)&&damage > 4000) damage = 4000 + (damage - 4000)/100;
				if (damage>5000) damage = 5000 + (damage - 5000)/10;
				if (me->query_skill_mapped("force") == "hanbing-zhenqi")
					target->add_condition("cold_poison",1);
				target->receive_damage("qi", damage,me);
				target->receive_wound("qi", damage/3,me);
				target->add_busy(2);
				target->apply_condition("no_exert",2);

				me->add("neili", -200);
				me->add("jingli", -50);
				if (wizardp(me)) tell_object(me,HIW"damage��"+damage + "��\n"NOR);
				p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
				msg += damage_msg(damage, "����");
				msg += "( $n" + eff_status_msg(p) + " )\n";
			}
			message_vision(msg, me, target);

		}	

		me->add_temp("apply/attack",me->query_skill("songyang-shou",1)/3);
		//me->add_temp("apply/damage",me->query_skill("songyang-shou",1)/6);
		COMBAT_D->do_attack(me, target, 0, random(2)?3:1);
		COMBAT_D->do_attack(me, target, 0, random(2)?3:1);
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);

		me->add_temp("apply/attack",-me->query_skill("songyang-shou",1)/3);
		//me->add_temp("apply/damage",-me->query_skill("songyang-shou",1)/6);

		message_vision(HIY "\n$N������أ�����һ��������\n" NOR,me, target);

		me->delete_temp("sys/xianhe");
		me->add_temp("apply/attack", -skill/3);
		me->add_temp("apply/damage", -skill/5);
		me->start_perform(5,"�ɺ���");
		me->start_busy(1);

        return 1;
}

int help(object me)
{
	write(HIW"\n��������֮"+HIY"���ɺ��֡���"NOR"\n\n");
        write(@HELP
	��������������ɽ���������似���������书���̺�
	���⾳ȥ����С����е��ص��������Լ�ǿ������
	��ע��˫�֣����������������ߣ����ô��У��ٸ���
	�Զ����ھ���������������������ɫ��
	�ɺ�������ɽʮ��̫���е�½�ؾ�����һ�ִ�������
	��ʹ�����ɺ׵ĵ�����ʽ��Ҳ��������ѹ���˵���ʽ
	
	ָ�perform hand.xianhe

Ҫ��
	�������  2500 ���ϣ�
	��ǰ����  500  ���ϣ�
	��ǰ����  500  ���ϣ�
	��������  220  �����ϣ�
	��������  220  �����ϣ�
	�����ַ�Ϊ�����֣�
	�����м�Ϊ������
	�����ڹ�Ϊ���������������ڹ�;
	���ַ�Ϊ�����֣�
	���֣�
HELP
        );
        return 1;
}