// nroad6.c
// Modified by Java Apr.27 1998

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","休息室");
        set("long",@LONG
几张大床依次排列在墙角，幽暗的灯光下，数位喇嘛正在休息
横七竖八不成正形，鼾声如雷。其中一张床上居然有一位赤身裸体
的女子正在娇笑着和一位喇嘛说着什么，神情甚是暧昧。
LONG );
        set("exits",([
                "east"   : __DIR__"cave",
                //"southup" : __DIR__"nroad5",
        ]));
        set("objects",([
             /*  "/clone/weapon/miandao" : 1,
				
				"/clone/weapon/xinyuedao" : 1,*/
				//"/clone/weapon/blade" : 1,

        ]));
        //	set("no_clean_up", 0);
        set("sleep_room", 1);
        set("no_fight", 1);
		setup();
        replace_program(ROOM);
}

