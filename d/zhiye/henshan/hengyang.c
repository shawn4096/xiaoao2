inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "衡阳城");
        set("long", @LONG
这里就是衡阳县城。衡阳地处偏远，显见远不如中原繁华了。
LONG );
               set("outdoors", "衡山");

	set("exits", ([
	       "east"   : __DIR__"hengyang2",
	       "west"   : __DIR__"hengyang1",
	       "south"  : __DIR__"chaguan",
	       "north"  : __DIR__"lingxingmen",
	]));

       /* set("objects", ([
                "/d/henshan/npc/lu" : 1,
        ]));*/
	//set("coor/x", 0);
	//set("coor/y", -110);
	//set("coor/z", 0);
	setup();
	//replace_program(ROOM);
}

