// Room: /d/jiaxing/yanyu.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", YEL"�����"NOR);
	set("long", @LONG
վ�ڶ�¥���Ǹ�Զ�����������겻�ϵ�ˮ���������ֵ��������ɵġ�
����������ī�͵��������棬ƾ��Զ�������ͼ��˵ĺ���ɽɫ����С����
��æµ�š�¥���в������ͣ��˴˼������̸��ʲô�£�������Щ���š�
LONG
	);
	//set("group", 1);
	set("exits", ([
		"west" :  "/d/jiaxing/jxyanyu2",
	]));
	set("objects", ([ 
                "d/thd/niujia/npc/wanyan" : 1,
	 ]) );

	set("outdoors", "���˳�");
	setup();
}
