#define FLOOR 6
#define SAVE_NPC "俞莲舟"
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "宝塔六层");
        set("long","这里是万安寺内宝塔的第六层，戒备森严，一看就知道关押着重要人物。\n");
        set("exits", ([
                "down" : __DIR__"baota-5",
                "up" : __DIR__"baota-7"
        ]));
        setup();
}

#include "baota.h"