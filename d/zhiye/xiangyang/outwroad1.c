// /d/xiangyang/outwroad1.c 青石大道
// Lklv Modify 2001.9.22

inherit ROOM;
void create()
{
	set("short", "西门外");
	set("long", @LONG
这是一条笔直的青石大道，路上人来人往非常繁忙，不时有人骑着马匆匆
而过。路南有条小路通向一个山丘。从此往西是云贵川的方向，东面远远的可
以望见一座城楼，那里就是襄阳城了。
LONG
	);
	set("outdoors", "襄阳");
	set("xyjob", "1"); 
	set("exits", ([
		"east" : __DIR__"baihumen",
		"west" : __DIR__"tanxi",
		"south" : __DIR__"shanlu1",
		"north" : "/d/gumu/jqg/shanlu3",
	]));
	setup();
}
int valid_leave(object me, string dir)
 {
     mapping exits = query("exits");
    /* if (!load_object(exits[dir])->query("xyjob") 
     && me->query_temp("xyjob"))
             return notify_fail("你想临阵脱逃么？\n");*/
     return ::valid_leave(me, dir);
 }      
