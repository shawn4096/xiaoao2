// nroad6.c
// Modified by Java Apr.27 1998

#include <ansi.h>
inherit ROOM;
int do_dringk(string arg);
void create()
{
        set("short","食堂");
        set("long",@LONG
此处是血刀门山洞后厨区域，此处摆放了锅碗瓢盆，东面是一个
大灶台，有一个配胖的红衣喇嘛正在奋力搅拌锅中的炒菜，香气四溢
南面摆放了一排排的桌椅板凳。
LONG );
        set("exits",([
                "south"   : __DIR__"cave",
                "north" : __DIR__"kengdao1",
        ]));
        set("objects",([
                __DIR__"obj/maoniurou" : 1,
				__DIR__"obj/niurou" : 1,
				__DIR__"obj/suyoucha" : 1,
				"d/xuedao/npc/food_lama" : 1,
        ]));
        setup();
        replace_program(ROOM);
}


void init()
{
	add_action("do_drink", "drink");
}
int do_drink(string arg)
{
	int current_water, max_water;
	object me;

	me = this_player();
        current_water = me->query("water");
	max_water = me->query("str")*10 + 100;

        if (current_water<max_water) {
		me->set("water", current_water+30);
		message("vision", me->name()+"用茶勺从茶桶中舀了一口茶水来喝。\n", environment(me), ({me}) );
		write("你舀了一口桶中的茶水来喝。\n");
        }
	else
	write("你再也喝不下了。\n");
        return 1;
}
