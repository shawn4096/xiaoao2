// xuegu.c 
// sohu 
inherit ROOM;
#include "sxuegu.h"

void create()
{
	set("short", CYN"厚雪层"NOR);
	set("long", @LONG
这是一层较厚的雪中，四周全是白雪，光线有些晦暗，四周听
不见任何声音，也看不见任何人，因空气不流通，待在这里感觉有
些气闷。
LONG);
	set("exits", ([
		//"up" : __DIR__"xuegu1",
		//"down" : __DIR__"sxuegu20",
	]));
	set("xueceng", 3);

	set("outdoors", "血刀门");

   setup();

}

