// nroad6.c
// Modified by Java Apr.27 1998
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","兵器库");
        set("long",@LONG
这是一间血刀门的私有兵器库，旁边一行行的货架上
摆放了很多兵器，但其中主要是以刀为主。
LONG );
        set("exits",([
                "west"   : __DIR__"shandong3",
                //"southup" : __DIR__"nroad5",
        ]));
        set("objects",([
                "/clone/weapon/miandao" : 2,
				"/clone/weapon/mudao" : 1,
				"/clone/weapon/xinyuedao" : 2,

        ]));
        //	set("no_clean_up", 0);
       // set("outdoors", "xuedao");
        setup();
       //        replace_program(ROOM);
}

