// Room: /d/huashan/v-road-1.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ROOM;
int do_han(string arg);
int do_bo(string arg);
void create()
{
        set("short", "山涧");
        set("long", @LONG
这里周围都是灌木(guanmu)，东南的方向和东北面的方向似乎能走过去。
LONG);
	set("item_desc",([
	"guanmu" : "灌木丛后面隐约有什么东西。\n",
]));
        set("exits", ([ 
                "northeast"     : __DIR__"v-road-2",
	              "southeast"     : __DIR__"v-road-5",
                "southwest"     : __DIR__"shentan",
        ]));
        set("objects",([
                //__DIR__"npc/sword/chengbuyu" : 1,
                //__DIR__"npc/sword/chongbuqi" : 1,
               // __DIR__"npc/sword/fengbuping" : 1,
        ]));

        set("outdoors", "华山");
        set("coor/x",40);
        set("coor/y",80);
        set("coor/z",-10);
        setup();
}
void init()
{
	add_action("do_bo", "bo");
	//add_action("do_han","han");
//	add_action("do_han","yell");
	
}

int do_bo(string arg)
{
	
	object me;
	me = this_player();
	if(!living(me) ) return 0;

        if (me->is_busy() || me->is_fighting())
	return notify_fail("你正忙着哪！\n");

	if ( arg=="" || arg!="guanmu"|| !arg) 
	return notify_fail("你要干什么？\n");

	if ( arg == "guanmu") {
	write("你拨开一片片灌木丛，突然眼前一亮。\n", me);
	me->move(__DIR__"maowu");
	return 1;
	}
}

