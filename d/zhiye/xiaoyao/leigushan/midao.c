// midao.c
// by sohu

inherit ROOM;

void create()
{
	set("short", "����ͨ��");
	set("long", @LONG
����һ���ֳ��ֺڵ�����ͨ������Լ���Ըо��������Ǳ������Ӳ��ʯ
�ڣ���Ȼǰ�涫�߳���һ˿�����⣬�����д�ϲ����æ������ǰ����
LONG );
	set("exits", ([
		"south" : __DIR__"midao3",
		"east" : __DIR__"shandong",
		"west" : __DIR__"midao2",
		"north" : __DIR__"midao1",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
