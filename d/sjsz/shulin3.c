//shulin.c ����

#include <ansi.h>
#include <room.h>

inherit ROOM;
void create()
{
	set("short",HIG"����"NOR);
	set("long", @LONG
����һƬ���֡���ʮ�ɸߵĴ�������һ�飬��ʵ��֦Ҷ��һ�����ɡ����
����գ��������ڵ�˿��Ҳ�ޡ������������У������µ���Ҷ�ȵ�ɳɳ�졣
LONG
	);

	set("exits", ([
		"southeast" : __DIR__"caodi5",
		"northeast" : __DIR__"caodi6",
		"north" : __DIR__"shulin4",
		"south" : __DIR__"shulin2",
	]));
	set("outdoors", "�Խ�ɽׯ");
	setup();
}

#include "sjsz_room.h";