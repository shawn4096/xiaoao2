inherit ROOM;
#include <ansi.h>
void create()
{
       set("short", "土路");	
        set("long", @LONG
你走在一条尘土飞扬的黄土路上，两旁满是阴森森的树林。这里
向北通往扬州，往南就进入湖南地界了。
LONG );
 
       set("outdoors", "衡山");
   
      set("exits", ([
		//"northdown" : "/d/wudang/wdroad4",	
                "southeast" : __DIR__"hsroad2",

	]));

	//set("coor/x", 20);
	//set("coor/y", -90);
	//set("coor/z", 0);
	setup();
	//replace_program(ROOM);
}
