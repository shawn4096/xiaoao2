// xuegu.c 
// sohu 
inherit ROOM;
#include "sxuegu.h"

void create()
{
	set("short", HIW"浅雪层"NOR);
	set("long", @LONG
这是一层较浅的雪中，四周全是白雪，极为耀眼，四周听不见
任何声音，也看不见任何人，因空气不流通，待在这里略微感觉有
些气闷，但并不大碍。
LONG);
	set("xueceng", 2);


	set("outdoors", "血刀门");

   setup();
}


