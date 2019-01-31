// slj.c
// 神龙教
inherit ROOM;
void create()
{
	set("short","走廊");
	set("long",@long
这是一条很长的走廊，沿着走廊的两边放着数盆艳丽的鲜花，走廊的
前边和左边各有一个门。右侧是近邻一片巨大的青草坪，甚是荒凉。向东
看去一条弯曲的碎石子通往后山。
long);
	set("exits",([
	    "north" : __DIR__"dt",
           "west"  : __DIR__"road1",	
		"east"  : __DIR__"caoping",	
          "out" : __DIR__"sfd",
]));
	set("coor/x",520);
  set("coor/y",430);
   set("coor/z",90);
   setup();
}
	    	
