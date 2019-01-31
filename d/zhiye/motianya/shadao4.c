// Write By Yanyang@SJ 2001.10.13
// Room: /d/changan/northroad10.c

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", YEL"沙道"NOR);
        set("long", @LONG
这里已经接近西域戈壁沙漠了，日复一日的风沙已经将原有的官道几乎覆盖。
再往前走就是西域沙漠了，里面凶险无比，曾有无数商旅，侠客葬身其中。
LONG
	);
	        set("outdoors", "motianya");


	set("exits", ([
		"east" :__DIR__"shadao3",

            
		"west"  : __DIR__"shamo1",
	]));

	setup();
}
