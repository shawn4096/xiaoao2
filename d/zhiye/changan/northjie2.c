// Write By Yanyang@SJ 2001.9.30
// Room: /d/changan/northjie2.c

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
����һ����������ʯ�ֵ������ϱ���ͷ���졣�����Ǳ�����ͨ����⡣��
�����ǳ����ĵ���¥��������һ��֯���������治ʱ����֯����֯����������
������һ�Ҳ÷��̣��˿��н��г������ⲻ��
LONG
	);
	set("outdoors", "����");
	
	set("objects",([
		"/clone/zhiye/npc/yangcan-popo" : 1,
	]));

	set("exits", ([
		"east"   : __DIR__"zhibufang",
		"west"   : __DIR__"caifengpu",
		"south"  : __DIR__"northjie1",
		"north"  : __DIR__"northjie3",
	]));

	set("incity",1);
	setup();
}
