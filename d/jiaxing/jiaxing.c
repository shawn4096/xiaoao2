// Room: /d/jiaxing/jiaxing.c

inherit ROOM;

void create()
{
	set("short", "�м�");
	set("long", @LONG
���ǽ������Ǽ��˵������м��������������������������֡���ɫ������
�����ؽ�������������Ÿ��ֻ�Ʒ������ķ����������һ�����š�������ֱ
���Ƕ����Ƿ羰�续���Ϻ����������Ľֵ�ͨ�����ݡ�
LONG
	);

	set("exits", ([
                "north" : __DIR__"beimen",
                "east" : __DIR__"dbianmen",
		"south" : __DIR__"jxnanmen",
	]));
	set("objects", ([ 
		  __DIR__"npc/quanjinfa.c" : 1,
		 // __DIR__"npc/tuolei.c":1,
	]));

        set("outdoors", "����");
	setup();
}
