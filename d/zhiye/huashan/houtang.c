// Room: /d/huashan/houtang.c
// Date: Look 99/03/25

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
   ���ǻ�ɽ�ɵĺ��ã��������˲��Ǻֻܶ࣬����������������æµ�š�
������ֱ�����Ů������Ϣ�ĵط��������ǻ�ɽ����������Ⱥ�����ҡ�
LONG
        );

        set("valid_startroom", 1);
        set("no_sleep_room",1);

	set("objects",([
		__DIR__"npc/ludayou" : 1,
	]));
        set("exits",([
        	"north" : __DIR__"zhengqi",
        	"south" : __DIR__"qinshi",
        	"west" : __DIR__"celang3",
        	"east" : __DIR__"celang4",
	]));
	set("indoors", "��ɽ" );
	set("coor/x",80);
  set("coor/y",-30);
   set("coor/z",80);
   setup();

}
/*
int valid_leave(object me, string dir)
{

	if ((dir == "south") && ( �������� )
	{
		return notify_fail("�������ŵ����ң���ͨ���Ӳ��ܽ�ȥ!\n");
	}

	return ::valid_leave(me, dir);
}
*/