// mtroad.c  山路

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIG"绿洲山路"NOR);
        set("long", @LONG
这是一条山路，两旁是依靠绿洲滋养的树木，有一个女孩在这眼望南边发
呆，南边就是摩天崖了，一股阴森恐怖的气氛随之而来，你不禁告诉
自己，还是快走吧。
LONG );
        set("outdoors", "motianya");
        set("exits", ([
            "south" : __DIR__"mtyadi",
            "east"  : __DIR__"mtroad1",
        ]));
        set("objects",([
            __DIR__"npc/dingdang" : 1,
        ]));
        setup();       
}
