//shufang.c 书房
#include <ansi.h>

inherit ROOM;
void create()
{
          set("short","书房");
          set("long",@LONG
这是一间书房，房内陈列着众多四书五经，还有一些基本武功书籍，以供
铁掌帮弟子阅读，
LONG
    );

           set("indoors","铁掌帮");
           set("exits",([
"south": __DIR__"zoulang-2",
]));

            set("objects",([
__DIR__"obj/brush_book": 1,
]));
            set("no_clean_up", 0);
            set("coor/x",-340);
  set("coor/y",-240);
   set("coor/z",10);
   setup();
}

int init()
{
	add_action("do_fan","search");

}
int do_fan(string arg)
{	
	object me=this_player();
	object book;
	if (me->query("family/family_name")!="铁掌帮"||!me->query("quest/tz/dichuan"))
	{
		return notify_fail("你并非铁掌嫡传弟子，到铁掌帮乱翻什么？\n");
	}
	if (!arg || arg!="书籍")
	{
		return notify_fail("你要翻看什么？\n");
	}
	if (random(me->query("kar"))>25)
	{
	
		message_vision(HIC"$N走到书架前面，从各种武功秘籍中翻看，随意的抽出一本书，正是一本铁掌心法。\n"NOR,me);
		book=new("d/tiezhang/obj/xinfa1");
		book->move(me);
		return 1;
	}else {

		message_vision(HIY"$N翻看半天，忽然觉得一股戾气从心间升起，有将这书架掀翻的冲动。\n"NOR,me);
		me->start_busy(2);

		return 0;
	}

}