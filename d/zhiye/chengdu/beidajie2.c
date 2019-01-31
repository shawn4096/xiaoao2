// Room: /d/chengdu/beidajie2.c
// By Jpei

inherit ROOM;

void create()
{
	set("short", "北大街");
	set("long", @LONG
这是成都的北大街。北边通向北城门，南边显得很繁忙。
LONG
	);
        set("outdoors", "成都");

	set("exits", ([
		"north" : __DIR__"beidajie3",
		"south" : __DIR__"beidajie1",
		"west"	: __DIR__"yaodian",
		"east"	: __DIR__"yaochang",
	]));
	
	set("objects",([
		"/clone/zhiye/npc/caiyao-ren" : 1,
	]));
	
	set("incity",1);
	setup();
}

