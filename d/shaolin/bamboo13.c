// Room: /d/shaolin/bamboo13.c
// Date: YZC 96/01/19

inherit ROOM;




void create()
{
	set("short", "����");
	set("long", @LONG
����һƬ���ܵ����֡������˼�������Ω�����ߵ��·�棬��ɮ��ľ��
����΢�紵����Ҷ�������������������˳���Ϊ֮һ�ӣ����Ǿ��ѵ�������
�ڡ�
LONG
	);

	set("exits", ([
		"northeast" : __DIR__"bamboo"+(random(13)+1),
		"northwest" : __DIR__"bamboo14",
		"southeast" : __DIR__"bamboo"+(random(13)+1),
		"southwest" : __DIR__"bamboo"+(random(13)+1),
	]));

	set("outdoors", "shaolin");
	set("coor/x",50);
  set("coor/y",500);
   set("coor/z",150);
   setup();
}
/*
int valid_leave(object me, string dir)
{

	if (dir == "northwest" ) me->add_temp("bamboo/count", 1);
	else 			 me->add_temp("bamboo/count", -1);

	return ::valid_leave(me, dir);
}
*/
