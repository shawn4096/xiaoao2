// tea1.c

#include <ansi.h>

inherit ITEM;

void init()
{
     add_action("do_drink", "drink");
}


void create()
{
	set_name(HIW "普洱茶" NOR, ({"puer cha", "cha", "tea"}));
	set_weight(700);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "这是源自大理所制的普洱茶。\n");
		set("unit", "杯");
		set("value", 10000);
	}
}

int do_drink(string arg)
{
	object me = this_player();
	if (!living(me)) return notify_fail("想当机吗？\n");
	if (!id(arg)) return 0;
	message_vision(YEL "$N品了一口"
	+this_object()->query("name")+
	YEL "，顿时觉得精神为之一振。\n"
	NOR,me);
        me->set("jing", me->query("max_jing"));
        me->set("water", me->max_water_capacity());
       	destruct(this_object());
	return 1;
}
