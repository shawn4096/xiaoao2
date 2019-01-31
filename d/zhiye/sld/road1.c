// road1.c
// 路1
inherit ROOM;
void create()
{
	set("short","走廊");
	set("long",@long
这是一条很长的用青石板砌成的走廊，沿着走廊的两边放着数盆艳丽
的鲜花，走廊的左边有一个门。
long);
	set("exits",([
	    "east" : __DIR__"slj",
           "west"  : __DIR__"road2",
           "south" : __DIR__"womanws",
		"north" : __DIR__"manws",
]));
	//set("outdoors", "神龙岛");
        set("coor/x",510);
  set("coor/y",430);
   set("coor/z",90);
   setup();
}
	    	

int valid_leave(object me, string dir)
{
		if (me->query("killer"))
		{
			return notify_fail("通缉犯不许乱闯。\n");
		}
        if ((me->query("gender") == "女性") && dir == "north") 
           return notify_fail("女子人家还是不要到那去的好，否则就不好找婆家了。\n");
		if ((me->query("gender") == "男性") && dir == "south") 
           return notify_fail("那是女人的卧室！慎重！\n");
        return ::valid_leave(me, dir);
}
