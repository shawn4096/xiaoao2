// Write By actiong@SJ 2009.1.6
// Room: /d/changan/zhulin2.c
inherit ROOM;

void create()
{
	set("short", "绿竹林");
	set("long", @LONG
这里是洛阳东城郊外，好大的一片绿竹丛，迎风摇曳，雅致天然。你
刚来到这里，便听得琴韵丁冬，却是有人正在抚琴，绿竹林中一片清凉宁
静，和外面的洛阳城宛然是两个世界。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"northwest" : __DIR__"zhulin1",
  		"east" : __DIR__"zhulin3",
	]));
	
		set("objects", ([
		//"d/hmy/npc/xiang" : 1,
		//"d/hmy/npc/qu" : 1,
	]));

	set("coor/x", -140);
	set("coor/y", -10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
