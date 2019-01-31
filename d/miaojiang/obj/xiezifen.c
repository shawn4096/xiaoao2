// sheyao.c

#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_tumo", "tumo");
}

void create()
{
        set_name(HIB "Ы�Ӷ���" NOR, ({"xiezi dufen","dufen","fen"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long",
                "����һ��Ы�Ӷ������Ƶ�ҩ�裬�����̱ǵ��ȳ�ζ����\n�ƺ�����ͿĨ(tumo)��ʲô����֮��!\n");
		set("unit", "��");
		set("medicine", "drug");
		//set("no_get", 1);
//                set("no_drop", 1);
	}
}

int do_tumo(string arg)
{
	object me = this_player();
    
	if (!living(me)) return notify_fail("�뵱����\n");
	//if (!id(arg)) return 0;
	if (arg=="����"||arg=="hand"||arg=="shouzhang")
	{
		message_vision(HIG "$N��һ��Ы�Ӷ���ͿĨ���Լ�������֮�ϣ���ʱһ�ɶ���˳�ž�������ǰ�С�\n "NOR,me);
		me->set_temp("hsz/Ы�Ӷ�",1);
		me->apply_condition("xiezi_poison",20+random(20));
		destruct(this_object());

	}
	else message_vision(HIC"$NҪ��Ϳ��Ĩʲô��\n"NOR,me);
	return 1;
}
