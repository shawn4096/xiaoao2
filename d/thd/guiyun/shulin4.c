// /u/jpei/guiyun/shulin4.c

inherit ROOM;

void create()
{
	set("short", "树林深处");
	set("long",@LONG
这是一片小树林。地面上绿草如荫，茂密地生长着。树叶的缝隙间偶尔会
有一只小鸟被惊起，四周十分静寂。
LONG
);
	set("exits",([
		"northwest" : __DIR__"shulin5",
		"east" : __DIR__"shulin6",
		"south" : __DIR__"shulin3",
	]) );
	set("no_clean_up",0);
	set("outdoors", "归云庄");
	setup();
}

