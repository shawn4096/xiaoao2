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
		"west" : __DIR__"caodi9",
		"north" : __DIR__"shulin12",
		"south" : __DIR__"shulin10",
	]));
	set("outdoors", "�Խ�ɽׯ");
	setup();
}

#include "sjsz_room.h";