// sheyao.c

#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_tumo", "tumo");
}

void create()
{
        set_name(HIB "蟾蜍毒粉" NOR, ({"chanchu dufen","dufen","fen"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long",
                "这是一颗蟾蜍毒炼制的药丸，发出刺鼻的腥臭味道。\n似乎可以涂抹(tumo)到什么物体之上!\n");
		set("unit", "颗");
		set("medicine", "drug");
		//set("no_get", 1);
//                set("no_drop", 1);
	}
}

int do_tumo(string arg)
{
	object me = this_player();
    
	if (!living(me)) return notify_fail("想当机吗？\n");
	//if (!id(arg)) return 0;
	if (arg=="手掌"||arg=="hand"||arg=="shouzhang")
	{
		message_vision(HIG "$N将一颗蟾蜍毒粉涂抹在自己的手掌之上，顿时一股毒气顺着经脉蜿蜒前行。\n "NOR,me);
		me->set_temp("hsz/chanchudu",1);
		me->apply_condition("hama_poison",20+random(20));
		destruct(this_object());

	}
	else message_vision(HIC"$N要乱涂乱抹什么？\n"NOR,me);
	return 1;
}
