inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "林间道");
        set("long", @LONG
这里是一条林间小道，在树丛中蜿蜒。西北方连着一条黄土路，
南面的道路要宽一些。
LONG );
       set("outdoors", "衡山");

        set("exits", ([
                //"northwest" :"/d/wudang/wdroad9",
                "south"     : __DIR__"hsroad7",
        ]));

   //     set("coor/x", -40);
//	set("coor/y", -80);
	//set("coor/z", 0);
	setup();
      //  replace_program(ROOM);
}
