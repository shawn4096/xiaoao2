inherit ROOM;

void create()
{
	set("short", "��Ӫ����");
	set("long", @LONG
����վ�ڱ�Ӫ���ſڣ������һ�ż�ª��Ӫ�������Կ��������Ʒ��Ĺ�
�����ڲ�������ʱ�ش����ź������ϰ����ǲ������ڴ˹ۿ��ģ�����øϿ�
�߿���
LONG
	);

	set("exits", ([
		"south" : __DIR__"bingyin",
		"north" : __DIR__"xidajie1",
	]));

	set("objects", ([
        __DIR__"npc/bing" : 2,
	]));

	set("coor/x",100);
  set("coor/y",-220);
   set("coor/z",0);
   set("incity",1);
	setup();
}

int valid_leave(object me, string dir)
{
	if (!wizardp(me) && objectp(present("guan bing", environment(me))) && 
		dir == "south")
		return notify_fail("�ٱ���ס�����ȥ·��\n");
	return ::valid_leave(me, dir);
}
