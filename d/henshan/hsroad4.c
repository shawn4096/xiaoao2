inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "黄土路");
        set("long", @LONG
你走在一条尘土飞扬的黄土路上，两旁满是阴森森的树林。东面
不远就是衡阳县城了。往西是另外一条大道。
LONG );
         set("outdoors", "衡山");

        set("exits", ([
                "east"  : __DIR__"hengyang11",
                "west"  : __DIR__"hsroad5",
        ]));

  //      set("coor/x", -30);
	//set("coor/y", -110);
	//set("coor/z", 0);
	setup();
      //  replace_program(ROOM);
}
