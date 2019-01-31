// Room: /d/city/chmiao.c
//Update By Jpei for Change_body 2011

#include <ansi.h>

inherit ROOM;
void create()
{
        set("short", "紧闭室");
        set("long", @LONG
这是大智岛的紧闭室，失败者就会被关进这里等待回去。
LONG    );
        set("exits", ([
              
        ]));
        set("no_fight", 1);
        set("no_sleep_room", 1);        
        setup();        
}

void init()
{
        
}