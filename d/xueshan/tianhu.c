// Room: tianhu.c

inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
������һƬ�����ĵ�ˮ�������һ�����󣬺�ˮ�峺տ�������ֳ�һ������
�ĸ�ԭ��⡣
���ǣ�
    ����ŭ����ˣ������չ⺮��
    �޷�ˮ�����������������ƣ�΢������������ɳ���Ӱ��ɡ�
    һǧ�������£�ֻ��̲���ƾ�ʱ��
LONG
	);

	set("exits", ([
		"west" : __DIR__"shanlu1",
                "south" : __DIR__"xiaodian",
                "southwest" : __DIR__"xiaolu1",
"north" :__DIR__"tianxi",
	]));
        set("outdoors", "ѩɽ");
        set("objects", ([
  			       __DIR__"npc/zhimaya" : 1,
     			       __DIR__"npc/bantouyan" : 1
        ]));
	set("coor/x",-250);
  set("coor/y",140);
   set("coor/z",0);
   setup();
}
