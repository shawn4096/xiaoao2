//fushedan.c
//蝮蛇胆
//增加精力

#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name("五步蛇胆", ({"wubu shedan", "shedan","dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "颗");
		set("long", "这是一颗暗黑色的五步蛇胆。\n");
		set("value", 15000);
	}
	setup();
}

int do_eat(string arg)
{	
// int max;
	object me = this_player();

	if (!id(arg))
		return notify_fail("你要吃什么？\n");
	if( !random(2) ) 
	{
		message_vision(HIM "$N张口轻轻一咬，蛇胆外皮便即破裂，登觉满口苦汁，腥极苦极，结果$N把自己吃的东西都吐了出来。\n" NOR, me);
		this_player()->set("food",10);
		destruct(this_object());
		return 1;
	}
	if (me->query("max_neili")>(me->query_skill("force")-me->query_temp("apply/force")) * 8 + me->query("combat_exp") / 1000)
	{
		return notify_fail("你的最大内力已经超过上限了，无法使用！\n");
	}
	 me->add("max_neili", 1);
//   me->set("jingli", max);
	message_vision(HIM "$N张口轻轻一咬，蛇胆外皮便即破裂，登觉满口苦汁，腥极苦极，几乎要呕将出来。\n" NOR, me);
	message_vision(HIM "可稍过片刻，$N内力充沛，最大内力得到提升。\n" NOR, me);
	destruct(this_object());
	return 1;
}

