inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "衡阳东街");
        set("long", @LONG
这里是衡阳东街，再往东走便出衡阳城了，北面是一家杂货铺，
南边是一条偏僻的小巷。
LONG );
              set("outdoors", "衡山");

	set("exits", ([
	       "east"   : __DIR__"hsroad3",
	       "west"   : __DIR__"hengyang",
	       "south"  : __DIR__"xiaoxiang1",
	       //"north"  : __DIR__"zahuopu",
	]));

        //set("no_clean_up", 0);

//	set("coor/x", 10);
//	set("coor/y", -110);
//	set("coor/z", 0);
	setup();
	//replace_program(ROOM);
}

