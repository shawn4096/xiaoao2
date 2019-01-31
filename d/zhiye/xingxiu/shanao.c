//shanao.c 山坳，为捉冰蚕和洗温泉做准备

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "山坳");
        set("long", @LONG
这里位于天山后山，已经是峡谷深处，四周一片冰雪覆盖，左侧为一个
小型的温泉，雾气腾腾，宛如仙境，右侧靠近山壁一侧有一个阴森森的小型
冰洞(cave)，阴森恐怖。
LONG
        );
        set("exits", ([
          "southeast" : __DIR__"tsroad3",
          //"northwest" : __DIR__"tsroad2",
			"west" : __DIR__"wenquan",
        ]));

        set("outdoors", "tianshan");

        set("coor/x",-10);
		set("coor/y",50);
		set("coor/z",0);
		setup();
}
void init()
{
	object me=this_player();
	add_action("do_enter","enter");
	me->receive_damage("qi",300,"寒气冻死");
	me->receive_wound("qi",100,"寒气冻死");
}
int do_enter(string arg)
{
	object me=this_player();
	if (!arg||(arg!="cave"&&arg!="冰洞"))
	{
		return notify_fail("你到处乱钻，以为自己是土拨鼠么？\n");
	}
	message_vision(HIC"$N一弯腰钻进了小冰洞中去，一股寒气吹来，忍不住打了个寒噤。\n"NOR,me);
	me->receive_damage("qi",50,"寒气冻死");
	me->receive_wound("qi",300,"寒气冻死");
	me->move("/d/xingxiu/bingdong");
	return 1;
}