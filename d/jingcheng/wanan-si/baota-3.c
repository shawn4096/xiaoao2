#define FLOOR 3
#define SAVE_NPC "常敬之"
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "宝塔三层");
        set("long","这里是万安寺内宝塔的第三层，戒备森严，一看就知道关押着重要人物。\n");
        set("exits", ([
                "down" : __DIR__"baota-2",
                "up" : __DIR__"baota-4"
        ]));
        setup();
}

#include "baota.h"