// Room: donglang2.c  东厢走廊
// by shang 97/6

#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "东厢走廊");
    set("long", @LONG
你走在一条木制结构的走廊上，南北是两间大屋，门口都挂有一标记，
南边的门牌(menpai1)是蓝的，北边的(menpai2)是白的。
LONG
    );
        set("exits", ([
            "south":__DIR__"xiuxishimen",
            "west" : __DIR__"xiaolu1",
    ]));
        setup();
}
