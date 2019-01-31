// Room: /d/jiaxing/yanyu.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIC"����¥"NOR);
	set("long", @LONG
����¥���ڼ��˵ķ羰ʥ���Ϻ������һ��С���ϣ��������겻�ϵ�ˮ��
�������ֵ��������ɵġ�����������ī�͵��������棬ƾ��Զ�������ͼ��˵�
����ɽɫ��
LONG
	);
	set("group", 1);
	set("exits", ([
		"north" :  "/d/jiaxing/nanhu1",
		"up" :  "/d/jiaxing/jxyanyu2",
	]));
	set("objects", ([ 
                "d/jiaxing/npc/xiaoer" : 1,
	 ]) );

	set("outdoors", "���˳�");
	setup();
}
int init()
{
	object me;
	me=this_player();
	
	if (me->query_temp("quest/���Ӣ�۴�/�����߹�/askjiaomu")
		&&me->query_temp("quest/���Ӣ�۴�/�����߹�/jugang"))
	{
		message_vision(HIY"$N�����е�ͭ��������һ�ţ���ʱ�ض�ɽҡ!\n$N�Ե�С���ȵ�����С��������ͭ�׵ĸ���װ���˾ƣ���Ҫ�д�����Ŀ��ˡ�\n"NOR,me);
		//��ʼ����¥��ս�Ľӿ���
		me->delete_temp("quest/���Ӣ�۴�/�����߹�/askjiaomu");
		me->set_temp("quest/���Ӣ�۴�/�����߹�/fanggang",1);
		
	}
}