// xuegu.c 
// sohu 
inherit ROOM;
#include "sxuegu.h"

void create()
{
	set("short", HIW"浅雪层"NOR);
	set("long", @LONG
这是一层较浅的雪中，四周全是白雪，极为耀眼，四周听不见
任何声音，也看不见任何人，因空气不流通，待在这里略微有些气
闷。你用手扒了扒发现上下甚是松软，此地似乎有人上下爬过。
LONG);
	set("exits", ([
		//"up" : __DIR__"xuegu1",
		//"down" : __DIR__"sxuegu20",
	]));
	set("xueceng", 2);
	set("zuan", 1);

	set("outdoors", "血刀门");

   setup();
}


