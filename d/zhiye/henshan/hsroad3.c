inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "土路");
        set("long", @LONG
你走在一条尘土飞扬的黄土路上，两旁满是阴森森的树林。西面
不远就是衡阳县城了。
LONG );
         set("outdoors", "衡山");

        set("exits", ([
                "northeast": __DIR__"hsroad2",
                "west"     : __DIR__"hengyang2",
        ]));

  //      set("coor/x", 20);
	//set("coor/y", -110);
	//set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}
