inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "林间大道");
        set("long", @LONG
这里是一条林间大道，在树丛中蜿蜒。这里已是湖南境内。北边
是湖北。路边有可供路人休息的小茶亭。
LONG );
        set("outdoors", "衡山");

        set("exits", ([
                "east"   : __DIR__"chating",
                "north"  : __DIR__"hsroad7",
                "south"  : __DIR__"hsroad5",
        ]));

   //     set("coor/x", -40);
//	set("coor/y", -100);
//	set("coor/z", 0);
	setup();
  //      replace_program(ROOM);
}
