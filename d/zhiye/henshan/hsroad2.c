inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "土路");
        set("long", @LONG
你走在一条尘土飞扬的黄土路上，两旁满是阴森森的树林。
LONG );

         set("outdoors", "衡山");

        set("exits", ([
                //"northwest" : __DIR__"hsroad1",  //这里变成去武当了，地图格局不对
                "southwest" : __DIR__"hsroad3",
                "southeast" : "/d/fuzhou/wroad4",
        ]));

       // set("coor/x", 30);
	//set("coor/y", -100);
	//set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}
