inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "半山亭");
        set("long", @LONG
终于到了半山亭。这里离到祝融峰无论高程还是行程，均恰好是
一半之径，路边小亭显然已极古久，但仍为过往客旅遮风避雨。
LONG );

        set("exits", ([
               "southdown"  : __DIR__"shanlu4",
               "northwest"    : __DIR__"shanlu002",
        ]));

        //set("no_clean_up", 0);
        set("outdoors", "衡山");

       // set("coor/x", -20);
	//set("coor/y", 40);
	//set("coor/z", 20);
	setup();
       // replace_program(ROOM);
}

