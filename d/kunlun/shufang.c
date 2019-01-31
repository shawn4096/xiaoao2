inherit ROOM;
#include <ansi.h>

void create()
{
	set("short", "书房");
	set("long", @LONG
这里是书房，靠墙一排大书架，摆放着很多的书籍，昆仑三圣何足道以琴
棋而号称以“圣”，故昆仑派一直引以为荣，鼓励弟子学琴棋艺。一眼望过去，
似乎有关于不少琴棋方面的书。
LONG
	);
	set("exits", ([
		"south" : __DIR__"lang",
		"west"  : __DIR__"shilu1",
	]));
	set("objects",([
              "d/kunlun/obj/string-book1" : 1,
	
				"d/kunlun/obj/string-book2" : 1,
				"kungfu/class/kunlun/kubai" : 1,

		]));
	set("qls_miji",10);//只有一本可能不够，以后长期不重启，这个无法解
	setup();
}
int init()
{
	add_action("do_find","find");
	add_action("do_find","search");

}
int do_find(string arg)
{
	object me,obj;
	me=this_player();
	if (!arg||arg!="书架")
	{
		return notify_fail("你要搜寻什么？\n");
	}
	if (me->is_busy())
	{
		return notify_fail("你手忙脚乱，此乃昆仑重地，心浮气躁的作甚？\n");
	}
	if (me->query_temp("qlsmiji"))
	{
		return notify_fail("你已经拿到秘籍。\n");
	}
	if (this_object()->query("qls_miji")<1)
	{
		return notify_fail("秘籍已经为别人所拿，待会再来？\n");

	}
	if (me->query("quest/kl/qls/pass"))
	{
		message_vision(HIY"$N按照朱子柳的嘱咐开始在书架上不断搜寻，尝试寻找那本《清凉扇绝技》的秘籍！\n"NOR,me);
		if (random(me->query("kar"))>26)
		{
			obj=new("d/kunlun/obj/qls_miji.c");
			obj->set("owner",me->query("id"));
			obj->move(me);
			me->set_temp("qlsmiji",1);
			this_object()->add("qls_miji",-1);
			message_vision(HIY"$N在书架上突然翻到一本《清凉扇绝技》的秘籍！\n"NOR,me);
		}
		me->add_busy(1+random(3));

	}
	return 1;

}