// Write By Yanyang@SJ 2001.10.13
// Room: /d/changan/northroad10.c

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", YEL"ɳ��"NOR);
        set("long", @LONG
�����Ѿ��ӽ�������ɳĮ�ˣ��ո�һ�յķ�ɳ�Ѿ���ԭ�еĹٵ��������ǡ�
����ǰ�߾�������ɳĮ�ˣ����������ޱȣ������������ã������������С�
LONG
	);
	        set("outdoors", "motianya");


	set("exits", ([
		"east" :__DIR__"shadao3",

            
		"west"  : __DIR__"shamo1",
	]));

	setup();
}
