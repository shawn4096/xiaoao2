// sroad4.c
// Modified by Java Apr.27 1998

inherit ROOM;
void create()
{
        set("short","大雪山口");
        set("long",@LONG
这里已经到了藏边，大雪山的山口。大雪山又叫岷山，位于川
藏之间，由于山势高峻，山顶有终年不化的积雪，故而得名。四下
毫无人迹，只有几只秃鹰在高处盘旋，俯视着茫茫雪山。
LONG );
        set("exits",([
                "eastdown"  : __DIR__"sroad3",
                "westup"    : __DIR__"sroad5",
        ]));
        set("objects",([
                __DIR__"npc/eagle": 2,
        ]));
        set("outdoors", "xuedao");
        set("no_clean_up", 0);
        setup();
	replace_program(ROOM);
}
