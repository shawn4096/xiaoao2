#define FLOOR 1
#define SAVE_NPC "班淑娴"
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "宝塔一层");
        set("long","这里是万安寺内宝塔的第一层，戒备森严，一看就知道关押着重要人物。\n");
        set("exits", ([
                "out" : __DIR__"wanan-siyuan",
                "up" : __DIR__"baota-2"
        ]));
        setup();
}

#include "baota.h"