// Created by Numa 2000.1.25
// Modified by darken@SJ

#include <ansi.h>
#include <combat.h> 
#include "/kungfu/skill/eff_msg.h"
inherit F_SSERVER;

string perform_name() {return HIY"��������"NOR;}

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
			return notify_fail("�������־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

		if( (int)me->query_skill("songyang-shou", 1) < 300 )
			return notify_fail("��������ֻ�򲻹���\n");

		if( (int)me->query_skill("parry", 1) < 300 )
			return notify_fail("��Ļ����мܻ�򲻹���\n");

		if( (int)me->query_skill("hanbing-zhenqi", 1) < 300 )
			return notify_fail("��Ļ����ڹ���򲻹���\n");

		if( (int)me->query("max_neili") < 1500 )
			return notify_fail("���������Ϊ������\n");

		if( (int)me->query("neili") < 1000 )
			return notify_fail("�������������\n");

		if( (int)me->query("jingli") < 600 )
			return notify_fail("��ľ���������\n");

		if (userp(me)&&!me->query("quest/ss/sys/yinyang/pass"))
			return notify_fail("�㲻��������־�����\n");

		if (me->query_skill_mapped("force") != "hanbing-zhenqi")
			return notify_fail("����ʲôΪ������ʹ�������־���?\n");

		if (me->query_skill_prepared("hand") != "songyang-shou"
		|| me->query_skill_mapped("hand") != "songyang-shou")
			return notify_fail("�������޷�ʹ�������֡�\n");

		if (me->query_temp("weapon"))
			return notify_fail("�������־���ֻ�ܿ���ʹ�ã�\n");

		if( me->query_temp("sys/yinyang"))
			return notify_fail("������ʹ�ô������־�����\n");

		me->add("neili", -200);
		me->add("jingli", -50);
		message_vision(HIY "\n$N���ں�$n��ս֮�ʣ�ͻȻ��󵹴ܣ���˫��ȴ�Ⱥ�����$n����ң����\n" NOR,me, target);

		me->add_temp("apply/attack", skill/3);
		me->add_temp("apply/damage", skill/5);
		me->set_temp("sys/yinyang", skill);

		msg = HIB "\n$N˫��һ��һ���������ȳ�������ȴ�������壬һ�ɺ���ֱ��$n��ȥ��\n" NOR;

		if (random(me->query("combat_exp")) > target->query("combat_exp")/3
		|| random(me->query_skill("hand",1))>target->query_skill("parry",1)/3) {
			msg += HIW"$n��Ҫ���ܣ�ֻ��һ�ɺ���Ϯ����������ʱ��������˸���ս��\n"NOR;
			damage = (int)me->query_skill("hanbing-zhenqi") + (int)me->query_skill("songyang-shou")*2;
			damage = (random(damage) + damage) * (random(2)+2);
			if(userp(target)&&damage > 4000) damage = 4000 + (damage - 4000)/100;
			if (damage>5000) damage = 5000 + (damage - 5000)/10;
			if (me->query_skill_mapped("force") == "hanbing-zhenqi")
				target->add_condition("cold_poison",1);
			target->receive_damage("qi", damage,me);
			target->receive_wound("qi", damage/3,me);
			me->add("neili", -200);
			me->add("jingli", -50);
			if (wizardp(me)) tell_object(me,HIW"damage��"+damage + "��\n"NOR);
			p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
			msg += damage_msg(damage, "����");
			msg += "( $n" + eff_status_msg(p) + " )\n";
		}
		else{ 
			msg += HIC"$n�������������������ϣ���ʱ��ȫ�����˵���������ܡ�\n"NOR;
			win = 1;
		}
		message_vision(msg, me, target);
		me->add_temp("apply/attack",me->query_skill("songyang-shou",1)/3);
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
		me->add_temp("apply/attack",-me->query_skill("songyang-shou",1)/3);

		//�ڶ��ƣ�����
		if (win == 1){
			me->start_busy(1+random(1));
			call_out("remove_effect", 1, me, target, 2, skill); //���У��ӳ�3��
			return 1;
		}
		else {
			msg = HIR"$nֻһ����һ�����ȵ��Ʒ�����˵���\n"NOR;
			if (random(me->query("combat_exp")) > target->query("combat_exp")/2
			||random(me->query_int())>target->query_int()/2) {
				msg += RED"$n�������ܣ����ǲ��ܣ��������ƻ��ջ��ǰ�ʹ����\n"NOR;
				damage = (int)me->query_skill("hanbing-zhenqi") + (int)me->query_skill("songyang-shou")*2;
				damage = (random(damage) + damage) * (focus+1);
				if(damage > 2000) damage = 2000 + (damage - 2000)/100;
				me->add("neili", -200);
				me->add("jingli", -50);
				target->receive_damage("qi", damage,me);
				target->receive_wound("qi", damage/3,me);
				if (wizardp(me)) tell_object(me,HIW"damage��"+damage + "��\n"NOR);
				p = (int)target->query("qi") * 100 / (int)target->query("max_qi"); 
				msg += damage_msg(damage, "����");
				msg += "( $n" + eff_status_msg(p) + " )\n";
			}
			else {
				msg += "$n�������������������ϣ���ʱ��ȫ�����˵���������ܡ�\n";
			}
			message_vision(msg, me, target);
			me->add_temp("apply/hand",skill/4);
			COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
			COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);

			me->add_temp("apply/hand",-skill/4);
		}

		me->delete_temp("sys/yinyang");
		me->add_temp("apply/attack", -skill/3);
		me->add_temp("apply/damage", -skill/5);
		me->start_perform(3,"��������");
		me->start_busy(1);

        return 1;
}


void remove_effect(object me, object target, int count, int skill)
{
		if (!me) return;
		if(!target
		|| !me->is_fighting(target)
		|| me->query_temp("weapon")
		|| me->query_skill_prepared("hand") != "songyang-shou"
		|| count < 1 ){
			me->add_temp("apply/attack", -skill/3);
			me->add_temp("apply/damage", -skill/5);
			me->delete_temp("sys/yinyang");
			return;
		}
		call_out("remove_effect", 1, me, target, count - 1, skill);
}

int help(object me)
{
	write(HIW"\n��������֮"+HIY"���������֡���"NOR"\n\n");
        write(@HELP
	��������������ɽ���������似����������ȡ��ɽ��
	����֮�⣬�������书���̺����⾳ȥ����С���
	�е��ص��������Լ�ǿ�������Լ������ͶԷ����ƶ�
	�ƿ��⣬���������������ߣ����ô��У��ٸ����Զ�
	���ھ��������������ʹ�öԷ�����ʤ������Ȼ����
	�ȶԷ������ͣ����Ϊ�Է�����������ɽ�������
	��ʹ�á�ע�⣬160������к��б仯��
	ע�⣺������Ҫ���ֺ���̡�
	
	ָ�perform hand.yinyang

Ҫ��
	�������  1500 ���ϣ�
	��ǰ����  1000  ���ϣ�
	��ǰ����  600  ���ϣ�
	��������  300  �����ϣ�
	��l������  300  �����ϣ�
	�����ַ�Ϊ�����֣�
	�����м�Ϊ������
	�����ڹ�Ϊ���������������ڹ�;
	���ַ�Ϊ�����֣�
	���֣�
HELP
        );
        return 1;
}