// Room: /d/taishan/.c

inherit ROOM;

void create()
{
	set("short", "月观峰");
	set("long", @LONG
这里是位于南天门西面的山岭，怪石攒簇，最高的地方一石卓立，名为君
子峰。往北走便是泰山的西天门。
LONG
	);

	set("exits", ([
		"east" : __DIR__"nantian",
		"northup" : __DIR__"xitian",
	]));

	set("outdoors", "泰山");
	setup();
}
