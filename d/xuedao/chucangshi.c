// nroad6.c
// Modified by Java Apr.27 1998

#include <ansi.h>
inherit ROOM;
int do_yandu(string arg);
void create()
{
        set("short","储藏室");
        set("long",@LONG
血刀门的存放杂物之地，墙角堆满了数个大缸，不知道存放什么
东西，一旁的木架子上摆放了不少的杂物，布满了灰尘。
LONG );
        set("exits",([
                "west"   : __DIR__"lingwushi",
                //"north" : __DIR__"shufang",
        ]));
       set("objects",([            
				"d/xuedao/obj/qingkejiudai"   : 1,
				"d/xuedao/obj/pinang"   : 1,
				"clone/weapon/tiejili"   : 5,
		   		"d/xuedao/obj/dusha"   : 1,

        ]));
	
        setup();
        replace_program(ROOM);
}
