#include <ansi.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "厨房");
        set("long", @LONG
这里是衡山派长廊东北侧的一间厨房，平常衡山的弟子们饿了便
可以到这里来要(serve)些食物吃。房中灶火正旺，一个厨师正忙的满
头大汗。屋角放着一个大水缸。  
LONG );
	set("exits", ([
  	       "southwest" : __DIR__"changlang",
	]));
	
        set("objects", ([
                __DIR__"npc/chushi" : 1,
        ]));

        set("ricewater", 5);

	//set("coor/x", -20);
//	set("coor/y", 110);
//	set("coor/z", 40);
	setup();
}

void init()
{
        add_action("do_serve", "serve");
}

int do_serve()
{
        object me;
        object food;
        object water;
        me = this_player();

        if (me->query("family/family_name") != "衡山派")
                return notify_fail(CYN "厨师大眼一瞪，说道：你又不是衡山派的，吃白食啊？\n" NOR);

        if (present("man tou", this_player())) 
                return notify_fail(CYN "厨师眉头一皱，说道：吃完了再拿，别浪费食物。\n" NOR);

        if (present("water", this_object())) 
                return notify_fail(CYN "厨师眉头一皱，说道：吃完了再拿，别浪费食物。\n" NOR);

        if (query("ricewater") > 0)
        {
                message_vision(CYN "厨师将一个馒头和一碗清水递到$N手中，笑"
                               "道：你慢用。\n" NOR, me);
                food = new(__DIR__"obj/mantou");
                water = new(__DIR__"obj/water");
                food->move(me);
                water->move(me);
                add("ricewater", -1);
        }
        else 
                message_vision(CYN "厨师对$N" CYN "歉声道：嗨，吃的喝的都"
                               "没了。\n" NOR,me);
        return 1; 
}
