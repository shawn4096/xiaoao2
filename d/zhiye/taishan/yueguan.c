// Room: /d/taishan/.c

inherit ROOM;

void create()
{
	set("short", "�¹۷�");
	set("long", @LONG
������λ�������������ɽ�룬��ʯ�ܴأ���ߵĵط�һʯ׿������Ϊ��
�ӷ塣�����߱���̩ɽ�������š�
LONG
	);

	set("exits", ([
		"east" : __DIR__"nantian",
		"northup" : __DIR__"xitian",
	]));

	set("outdoors", "̩ɽ");
	setup();
}