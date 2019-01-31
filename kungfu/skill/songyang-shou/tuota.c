// Created by Numa 2000.1.25
// Modified by darken@SJ

#include <ansi.h>
#include <combat.h> 
#include "/kungfu/skill/eff_msg.h"
inherit F_SSERVER;

void remove_tuota(object me, int count);

string perform_name() {return HBYEL+HIW"������"NOR;}

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

		if( (int)me->query_skill("songyang-shou", 1) < 250 )
			return notify_fail("��Ĵ������ֻ�򲻹���\n");

		if( (int)me->query_skill("parry", 1) < 250 )
			return notify_fail("��Ļ����мܻ�򲻹���\n");

		if( (int)me->query_skill("hanbing-zhenqi", 1) < 250 )
			return notify_fail("��Ļ����ڹ���򲻹���\n");

		if( (int)me->query("max_neili") < 3500 )
			return notify_fail("���������Ϊ������\n");

		if( (int)me->query("neili") < 800 )
			return notify_fail("�������������\n");

		if( (int)me->query("jingli") < 500 )
			return notify_fail("��ľ���������\n");

		if (userp(me)&&!me->query("quest/ss/sys/tuota/pass"))
			return notify_fail("�㲻�������־�����\n");
		if (me->query_temp("sys/tuota"))
			return notify_fail("������ʩչ�����־�����\n");
		
		if (me->query_skill_mapped("force") != "hanbing-zhenqi")
			if (me->query_skill_mapped("force") != "lengquan-shengong")
			return notify_fail("���ڹ����Ժ������־���������?\n");

		if (me->query_skill_prepared("hand") != "songyang-shou"
		|| me->query_skill_mapped("parry") != "songyang-shou"
		|| me->query_skill_mapped("hand") != "songyang-shou")
			return notify_fail("�������޷�ʹ�������֡�\n");

		if (me->query_temp("weapon"))
			return notify_fail("�����־���ֻ�ܿ���ʹ�ã�\n");

		if( me->query_temp("sys/tuota"))
			return notify_fail("������ʹ�������־�����\n");

		me->add("neili", -200);
		me->add("jingli", -50);
		message_vision(HIY "\n$N˫��΢΢��������������Ȼ���һ����˫�����У���������ǧ��������������׳�����ϵľ�����Ȼ���Ӳ��٣�\n" NOR,me);

		me->add_temp("apply/attack", skill/3);
		me->add_temp("apply/damage", skill/6);
		me->add_temp("apply/hand", skill/5);

		me->set_temp("sys/tuota", skill);
		
		remove_tuota(me,skill/30);

        return 1;
}


void remove_tuota(object me, int count)
{
		int skill;
		if (!me) return;
		skill=me->query_temp("sys/tuota");
		if(!me->is_fighting()
		|| me->query_temp("weapon")
		|| me->query_skill_prepared("hand") != "songyang-shou"
		|| me->query_skill_mapped("hand") != "songyang-shou"
		|| count < 1 )
		{
			me->add_temp("apply/attack", -skill/3);
			me->add_temp("apply/damage", -skill/6);
			me->add_temp("apply/hand", -skill/5);

			message_vision(HIY "\n$N�����ͷ��������������������\n" NOR,me);
			me->delete_temp("sys/tuota");
			return;
		}
		call_out("remove_tuota", 1, me, count - 1);
}

int help(object me)
{
	write(HIW"\n��������֮"+HIY"�������֡���"NOR"\n\n");
        write(@HELP
	��������������ɽ���������似���������书���̺�
	���⾳ȥ����С����е��ص��������Լ�ǿ������
	��ע��˫�֣����������������ߣ����ô��У��ٸ���
	�Զ����ھ���������������������ɫ��
	����������ɽʮ��̫��֮�׵Ķ��������һ�ִ�����
	�ֳ����뻯���ھ�������

	ָ�perform hand.tuota

Ҫ��
	�������  3500 ���ϣ�
	��ǰ����  800  ���ϣ�
	��ǰ����  500  ���ϣ�
	��������  250  �����ϣ�
	��������  250  �����ϣ�
	�����ַ�Ϊ�����֣�
	�����м�Ϊ������
	�����ڹ�Ϊ���������������ڹ�;
	���ַ�Ϊ�����֣�
	���֣�
HELP
        );
        return 1;
}