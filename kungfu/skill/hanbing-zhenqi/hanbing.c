// by darken@SJ
// Lklv add help at 2001.10.06

#include <ansi.h>
inherit F_SSERVER;
string exert_name(){ return HIW"������"NOR; }

int exert(object me)
{
	string msg;
	int lv;
	lv = me->query_skill("hanbing-zhenqi",1);

	if (!me->is_fighting())
		return notify_fail("��ֻ����ս����ʹ�á�����������\n");
	
	if (me->query_temp("ss/hb"))
		return notify_fail("������ʹ�á�����������\n");

	if ((int)me->query_skill("hanbing-zhenqi",1) < 100)
		return notify_fail("����Ŀǰ���ڹ���Ϊ���޷�ʹ�á�����������\n");

	if ((int)me->query("max_neili") < 1000)
		return notify_fail("����Ŀǰ��������Ϊ���޷�ʹ�á�����������\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("�������������\n");

	msg = HIW"$N����������ת����������֮�䣬һ���������ֵĺ����㿪ʼ��$N��������ת��\n"NOR;
	if (me->query_skill("hanbing-zhenqi",1)>550 && me->query("quest/ss/hbzq/pass"))
	{
		msg+=HIB"$N����������Ȼ��ɣ���ת֮�ʣ�����������Ϯ�ˣ�����ʵ��,������������������\n"NOR;
		me->set_temp("hbzq/hanbing",1);
		me->add_temp("apply/strength",lv/20);
		me->add_temp("apply/attack",lv/5);
		me->add_temp("apply/damage",lv/6);
		me->add_temp("apply/sword",lv/6);
	}
	
	me->set_temp("ss/hb", lv);
	me->add("neili", -250);
	message_vision(msg, me);
	me->add_temp("apply/attack",lv/4);
    me->add_temp("apply/damage",lv/6);
	if ((int)me->query_skill("hanbing-zhenqi",1) < 350)
	{
		me->start_busy(random(2));
		//me->start_exert(1, "����������");
	}
	if ((int)me->query_skill("hanbing-zhenqi",1) < 450)
	{
		//me->start_busy(random(2));
		me->start_exert(1, "����������");
	}

	call_out("remove_effect", lv/5 + random(10), me);
	return 1;
}

void remove_effect(object me)
{
	int lv;
	if (!me || !me->query_temp("ss/hb")) return;

	lv = me->query_temp("ss/hb");
	me->add_temp("apply/attack",-lv/4);
    me->add_temp("apply/damage",-lv/6);
	if (me->query_temp("hbzq/hanbing")&&me->query("quest/ss/hbzq/pass"))
	{
		me->delete_temp("hbzq/hanbing");
		me->add_temp("apply/strength",-lv/20);
		me->add_temp("apply/attack",-lv/5);
		me->add_temp("apply/damage",-lv/6);
		me->add_temp("apply/sword",-lv/6);

	}
	message_vision(HIW"$N����һ���������������������������ϵĺ���������ɢȥ�ˡ�\n"NOR,me);

	me->delete_temp("ss/hb");
	return;
}

int help(object me)
{
	write("\n��������֮������������\n\n");
        write(@HELP
	������������������ɽ���ɵ������似���뵱����������������
	��������̽���������һս���Ժ������������������еĽ�����
	��ɧһʱ������������ɽ�ɵ��似��Ч�����ѡ�350��С�ɡ�450
	�ٷɣ�550��⿪�����������أ��������������ͷš�
	
	ָ�yun hanbing

Ҫ��
	�������  1000 ���ϣ�
	��ǰ����  500  ���ϣ�
	��������  100  �����ϣ�
	�����ڹ�Ϊ����������
HELP
        );
        return 1;
}