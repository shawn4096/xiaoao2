// /d/mr/kongfang.c
// by leontt 2000/10/18

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", HIW"空房间"NOR);
	set("long", @LONG
你无意间走到了一个空房间里，四周什么都没有，不时传来阵阵怪异的声
音，你不由的打了一个冷颤。
LONG);
	set("exits", ([             
		"west" : __DIR__"migong2",
		"out" : __DIR__"didao1",

	]));
	set("objects", ([
                __DIR__"obj/9dan" : 2,
		        __DIR__"obj/guiyuan-dan" : 2,		        
	            __DIR__"obj/qingxin-san" : 2,
                __DIR__"obj/jia" : 1,
		        __DIR__"obj/crown" : 1,
		        __DIR__"obj/hboot" : 1,
		        __DIR__"obj/gbelt" : 1,
		        __DIR__"obj/gfinger" : 1,
              ]));
	setup();
} 

