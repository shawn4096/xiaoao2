// Write By Yanyang@SJ 2001.10.2
// Room: /d/changan/dayanta2.c

inherit ROOM;

void create()
{
        set("short", "����������");
        set("long", @LONG
�������ڽṹ������������ڲ��þ������������徲����֮�С����ܿ���
�贰��������¥��ֱͨ���¡������ƺ��Ƿ�ͬѰ���ĳ�����
LONG
        );
        set("exits", ([
                   "up"  : __DIR__"dayanta3",
                 "down"  : __DIR__"dayanta1",
        ]));

        set("incity",1);
	setup();
}