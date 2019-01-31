// Write By Yanyang@SJ 2001.10.13
// Room: /d/changan/northroad10.c

inherit ROOM;

void create()
{
        set("short", "沙道");
        set("long", @LONG
这里已经接近西域戈壁沙漠了，日复一日的风沙已经将原有的官道几乎覆盖。
LONG
	);
	        set("outdoors", "motianya");


	set("exits", ([
		"east" :__DIR__"shadao2",

            
		"west"  : __DIR__"shadao4",
	]));

	setup();
}
