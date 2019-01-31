// mtroad1.c  树林

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIG"戈壁绿洲"NOR);
        set("long", @LONG
这里是摩天崖附近的戈壁绿洲，风沙已经停息了，绿洲附近的微风吹来还有丝丝凉意。
你发现原来绿洲附近有条商旅经常行走的沙石小径，从这边走似乎有回去的捷径。
LONG );
        set("outdoors", "motianya");
        set("exits", ([
            "east"  : "/d/changan/northroad10", //连接长安
            "west"  : __DIR__"mtroad",
            
        ]));
        setup();       
}
