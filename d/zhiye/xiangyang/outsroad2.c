// /d/xiangyang/outsroad2.c

inherit ROOM;

void create()
{
	set("short", "青石大道");
	set("long", @LONG
你走在一条青石大道上，人来人往非常繁忙，不时有人骑着马匆匆而过。
大道往南进入湖南境内。北边通向襄阳城。
LONG
	);
        set("outdoors", "襄阳");
	set("xyjob", "1"); 
	set("exits", ([
		"south" : __DIR__"outsroad3",
		"north" : __DIR__"outsroad1",
	]));

	setup();
}
int valid_leave(object me, string dir)
 {
     mapping exits = query("exits");
	 /*
     if (!load_object(exits[dir])->query("xyjob") 
     && me->query_temp("xyjob"))
              return notify_fail("你想临阵脱逃么？\n");*/
     return ::valid_leave(me, dir);
 }
