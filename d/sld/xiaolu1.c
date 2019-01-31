#include <wanted.h>
inherit ROOM;

void create()
{
	set("short", "小草路");
	set("long", @LONG
这是神龙岛西面的一条小路，弯弯曲曲的沿向西方蜿蜒。路
不宽，仅容二人并行，路边长着些花草，甚是茂盛，几只蝴
蝶在花丛中飞来飞去。一阵海风吹来，夹杂阵阵腥气。
LONG
	);

	set("exits", ([
		"west" : __DIR__"sanpo6",
		"east" : __DIR__"xiaolu2",
	]));
	set("outdoors", "神龙岛");

	setup();
}
