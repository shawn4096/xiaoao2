// xuegu.c 
// sohu 
inherit ROOM;
#include "sxuegu.h"

void create()
{
	set("short",  WHT"浅雪层"NOR);
	set("long", @LONG
这是一层很浅的雪中，四周全是白雪，极为耀眼，四周听不见
任何声音，也看不见任何人，因雪层较薄，虽然空气不流通，但待
在这里也不觉得气闷。
LONG);
	set("xueceng", 1);


	set("outdoors", "血刀门");

   setup();
}


