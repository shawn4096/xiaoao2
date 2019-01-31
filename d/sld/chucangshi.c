#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "储藏室");
        set("long", @LONG
神龙岛的储藏室，几个大货架拜访在四周，放满了神龙教
弟子平时日常搜集的物品和重要东西。
LONG);
        set("exits", ([
                "east" : __DIR__"th",
        ]));
        set("objects", ([
                __DIR__"npc/obj/jieyao" : 1+random(3),
                __DIR__"npc/obj/jiudai" : 1+random(2),
                __DIR__"npc/obj/shefen" : 1+random(2),
				__DIR__"npc/obj/sheyao" : 1+random(2),
				__DIR__"npc/obj/shengzi" : 1+random(2),
				"kungfu/class/sld/pangtoutuo" : 1,
        ]));

        setup();
        replace_program(ROOM);
}
