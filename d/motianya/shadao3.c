// Write By Yanyang@SJ 2001.10.13
// Room: /d/changan/northroad10.c

inherit ROOM;

void create()
{
        set("short", "ɳ��");
        set("long", @LONG
�����Ѿ��ӽ�������ɳĮ�ˣ��ո�һ�յķ�ɳ�Ѿ���ԭ�еĹٵ��������ǡ�
LONG
	);
	        set("outdoors", "motianya");


	set("exits", ([
		"east" :__DIR__"shadao2",

            
		"west"  : __DIR__"shadao4",
	]));

	setup();
}
