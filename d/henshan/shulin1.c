#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","树林");
        set("long", @LONG
这里是衡山半山腰的一片树林，据说这里经常有野兽出没。
LONG );

	set("objects",([
	   //   __DIR__"npc/hunter" : 1,	
		  __DIR__"npc/jian-ke" : 1,	
	]));

	set("exits", ([
		"east"  :  __DIR__"shanlu6",
	]));

	set("outdoors","衡山");
	//set("coor/x", -70);
	//set("coor/y", 50);
	//set("coor/z", 20);
	setup();
      //  replace_program(ROOM);
}
