// midao1.c
// by sohu

inherit ROOM;

void create()
{
	set("short", "����ͨ��");
	set("long", @LONG
����һ���ֳ��ֺڵ�����ͨ������Լ���Ըо��������Ǳ������Ӳ��ʯ
�ڣ���ʲô�˿��������ֻ���Կ�������ǰ����
LONG );
	set("exits", ([
		"south" : __FILE__,
		"east" : __FILE__,
		"west" : __FILE__,
		"north" : __DIR__"midao2",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}

void init()
{
       set("exits/east", __DIR__"midao"+(1+random(4)));
       set("exits/south", __DIR__"midao"+(1+random(4)));
       set("exits/north",  __DIR__"midao"+(1+random(4)));
       set("exits/west",  __DIR__"midao"+(1+random(4)));
}

