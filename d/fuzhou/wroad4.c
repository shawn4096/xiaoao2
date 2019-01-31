// Room: /d/fuzhou/wroad4.c
// Lklv 2001.9.10

inherit ROOM;

void create()
{
	set("short", "山路");
	set("long", @LONG
这是武夷山脉的一条山路。时值春日，路旁的山坡上到处开满了金黄色的
油菜花。一阵阵山风吹来，空气里弥漫着油菜花的香味。由此向西南方向可进
入两广，往东北可到福州。
LONG
	);

	set("exits", ([
		"west" : "/d/group/entry/fzwroad5",
		"northeast" : __DIR__"wroad3",
		"northwest" : "/d/henshan/hsroad2",
	]));

	set("outdoors", "福州");
	setup();
}
