#define FLOOR 8
#define SAVE_NPC "矮老者"
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "宝塔八层");
        set("long","这里是万安寺内宝塔的第八层，戒备森严，一看就知道关押着重要人物。\n");
        set("exits", ([
                "down" : __DIR__"baota-7",
                "up" : __DIR__"baota-9"
        ]));
        setup();
}

#include "baota.h"