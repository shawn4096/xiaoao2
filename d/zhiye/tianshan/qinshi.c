// Room: /d/tianshan/qinshi.c
// By Linux
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "寝室");
	set("long", @LONG
这里是一间精致的小舍，一进门便闻到一阵浓烈的花香，椅上铺了绣花锦
垫，似乎是天山童姥的寝室。
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
	if (!arg||arg!="床")
	{
		return notify_fail("你要乱搜什么？\n");
	}
	if (!me->query_temp("askyangyanshu"))
	{
		return notify_fail("你无缘无故在这个屋内乱翻，不怕童姥找你麻烦？\n");
	}
	if (this_object()->query("book")<1)
	{
		return notify_fail("你本书已经被人取走了？\n");

	}
	book=new("d/tianshan/obj/yangyanshu2");
	book->move(me);
	this_object()->add("book",-1);
	message_vision(HIY"$N在童姥床底附近翻找半天，发现一本古色古香的书籍，随即揣在自己怀里！\n"NOR,me);
	return 1;
}