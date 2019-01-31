// midao1.c
// by sohu

inherit ROOM;

void create()
{
	set("short", "秘密通道");
	set("long", @LONG
这是一段又长又黑的秘密通道，隐约可以感觉到四周是冰冷而坚硬的石
壁，你什么了看不清楚，只可以靠摸索着前进。
LONG );
	set("exits", ([
		"south" : __FILE__,
		"east" : __FILE__,
		"west" : __FILE__,
		"north" : __DIR__"midao2",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

void init()
{
       set("exits/east", __DIR__"midao"+(1+random(4)));
       set("exits/south", __DIR__"midao"+(1+random(4)));
       set("exits/north",  __DIR__"midao"+(1+random(4)));
       set("exits/west",  __DIR__"midao"+(1+random(4)));
}

