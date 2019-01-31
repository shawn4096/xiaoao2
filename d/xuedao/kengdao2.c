// hollow.c

inherit ROOM;

void create()
{
        set("short", "坑道");
        set("long", @LONG
这是血刀门内的过渡性坑道，为了连接各个重要山洞所用，洞壁
两侧是一排排的松木所制造，松香阵阵，远处间或传来幽香的气息。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "south"   : __DIR__"kengdao1",
			"west"   : __DIR__"kengdao3",
        ]));
        set("item_desc", ([
           // "dong"   : "一个深邃幽暗的洞穴。\n",
        ]));
        set("objects",([
             //   __DIR__"npc/zhizhu" : 1,
        ]));
        setup();
}
