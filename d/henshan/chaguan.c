inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "衡阳茶馆");
        set("long", @LONG
你一进来，就闻到一股茶香沁入心脾，精神为之一爽。几张八仙
桌一字排开，四周坐满了客人，或高声谈笑，或交头接耳。你要想打
听江湖掌故和谣言，这里是个好所在。
LONG );
	set("resource/water", 1);

	set("exits", ([
	       "north" : __DIR__"hengyang",
	]));

	set("objects", ([
		__DIR__"npc/chaboshi" : 1,
	]));

	//set("coor/x", 0);
	//set("coor/y", -120);
	//set("coor/z", 0);
	setup();
	//replace_program(ROOM);
}

