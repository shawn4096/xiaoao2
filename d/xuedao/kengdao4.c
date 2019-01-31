// hollow.c
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "大坑道");
        set("long", @LONG
这是血刀门内的一个比较大的坑道，为了连接各个重要山洞所用，
洞壁两侧是一排排的松木所制造，松香阵阵，远处间或传来幽香的气息。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "east"   : __DIR__"midong",
			"south"   : __DIR__"kengdao3",
				"north"   : __DIR__"huanxidong1",
        ]));
        set("item_desc", ([
           // "dong"   : "一个深邃幽暗的洞穴。\n",
        ]));
        set("objects",([
             //   __DIR__"npc/zhizhu" : 1,
        ]));
		create_door("north", "小门", "south", DOOR_CLOSED);

        setup();
}
