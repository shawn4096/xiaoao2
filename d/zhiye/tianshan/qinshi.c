// Room: /d/tianshan/qinshi.c
// By Linux
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
������һ�侫�µ�С�ᣬһ���ű��ŵ�һ��Ũ�ҵĻ��㣬���������廨��
�棬�ƺ�����ɽͯ�ѵ����ҡ�
LONG);
	 set("exits", ([
		"north" : __DIR__"zoulang5",
        ]));     
		set("book",1);
        set("objects", ([
                __DIR__"npc/shinvtong" : 1,
        ]));    
	setup();
}
void init()
{
	object me=this_player();
	add_action("do_search","search");
	add_action("do_search","find");

}

int do_search(string arg)
{
	object book;
	object me=this_player();
	if (!arg||arg!="��")
	{
		return notify_fail("��Ҫ����ʲô��\n");
	}
	if (!me->query_temp("askyangyanshu"))
	{
		return notify_fail("����Ե�޹�����������ҷ�������ͯ�������鷳��\n");
	}
	if (this_object()->query("book")<1)
	{
		return notify_fail("�㱾���Ѿ�����ȡ���ˣ�\n");

	}
	book=new("d/tianshan/obj/yangyanshu2");
	book->move(me);
	this_object()->add("book",-1);
	message_vision(HIY"$N��ͯ�Ѵ��׸������Ұ��죬����һ����ɫ������鼮���漴�����Լ����\n"NOR,me);
	return 1;
}