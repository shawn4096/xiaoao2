// Room: /u/jpei/guiyun/jiugong1.c

#include <ansi.h>

inherit ROOM;

#define HERENO	1

int do_get(string arg);
int do_drop(string arg);
int do_look(string arg);
int do_inv(string arg);

void create()
{
	set("short", "�Ź��һ���");
	set("outdoors","����ׯ");

	set("exits", ([
		"east" : __DIR__"jiugong2",
		"south" : __DIR__"jiugong4",
	]));
	setup();
}

#include "jiugong.h"