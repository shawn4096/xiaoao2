// by dubei
// Modify By River@sj 99.5.24
#include <room.h>
#include <ansi.h>
inherit ROOM;
#include "/d/gumu/xuantie/linhai.h";

void create()
{
	set("short", CYN"����"NOR);
	set("long", @LONG
������һƬһ�������ֺ���ÿ����ľ����ʮ���ɸߣ���Χ��İ������ʮ
�ɸߵĴ�������һ�飬��ʵ��֦Ҷ��һ�����ɡ��������գ��������ڵ�˿��
Ҳ�ޡ����ƺ���ʧ�˷�����ûͷ��Ӭ�㵽���Ҵ���
LONG
	);
	set("exits", ([
		"south" :  __DIR__"linhai"+(random(10)+1),
		"north" : __DIR__"linhai1",
		"west" :  __DIR__"linhai"+(random(10)+1),
		"east" : __DIR__"linhai"+(random(10)+1),
	]));

        set("outdoors", "����");
        setup();
}

void reset()
{
	set("exits", ([
		"north" : __DIR__"linhai1",
		"south" :  __DIR__"linhai"+(random(10)+1),
		"west" :  __DIR__"linhai"+(random(10)+1),
		"east" : __DIR__"linhai"+(random(10)+1),
	]));
}
/*
void init()
{
	object me=this_player();
	object fox;
	if (me->query_temp("anran/askheal")&& !me->query_temp("anran/findfox")&& random(10)>5)
	{
		fox=new("clone/npc/fox");
		fox->move(this_object());
		me->set_temp("anran/findfox",1);
	}
	return;
}*/