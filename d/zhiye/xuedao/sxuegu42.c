// xuegu.c 
// sohu 
inherit ROOM;
#include "sxuegu.h"

void create()
{
	set("short", HIC"深雪层"NOR);
	set("long", @LONG
这是一层很深的雪层中，四周全是白雪，光线模糊，四周听不见
任何声音，也看不见任何人，因空气一点都不流通，待在这里感觉非
常气闷。
LONG);
	set("exits", ([
		//"up" : __DIR__"xuegu1",
		//"down" : __DIR__"sxuegu20",
	]));
	set("xueceng", 4);

	set("outdoors", "血刀门");

   setup();
}


