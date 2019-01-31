// midao.c
// by sohu

inherit ROOM;

void create()
{
	set("short", "秘密通道");
	set("long", @LONG
这是一段又长又黑的秘密通道，隐约可以感觉到四周是冰冷而坚硬的石
壁，忽然前面东边出现一丝的亮光，你心中大喜，急忙摸索着前进。
LONG );
	set("exits", ([
		"south" : __DIR__"midao3",
		"east" : __DIR__"shandong",
		"west" : __DIR__"midao2",
		"north" : __DIR__"midao1",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
