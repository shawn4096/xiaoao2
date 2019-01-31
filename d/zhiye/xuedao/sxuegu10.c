// xuegu.c 
// sohu 
#include <ansi.h>

inherit ROOM;
#include "sxuegu.h"

void create()
{
	set("short", WHT"浅雪层"NOR);
	set("long", @LONG
这是一层很浅的雪中，四周全是白雪，极为耀眼，四周听不见
任何声音，也看不见任何人，因雪层较薄，透气性好，虽然空气不
流通，但是待在这里并不气闷。你仔细一看发现此地似乎有人钻过。
LONG);
	set("exits", ([
		//"up" : __DIR__"xuegu1",
		//"down" : __DIR__"sxuegu20",
	]));
	set("xueceng", 1);
	set("zuan", 1);

	set("outdoors", "血刀门");

   setup();
}


