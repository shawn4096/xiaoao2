//suishilu1


#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "碎石路");
	set("long", @LONG
一条幽静的青石板路，一头通向大厅，一头通向竹林，路旁放着几
盆花卉，开着菊花、蔷薇等，煞是艳丽。向东走属于后山区域，甚是荒
凉，杂草丛生，蛇群经常出没。
LONG
	);
	set("outdoors", "神龙岛");
	set("exits", ([
		"northup" : __DIR__"houshan",
		"west" : __DIR__"caoping",
		
	]));
	set("objects", ([
		//CLASS_D("shenlong")+"/zhong" : 1,
	]));
	setup();
	replace_program(ROOM);
}

