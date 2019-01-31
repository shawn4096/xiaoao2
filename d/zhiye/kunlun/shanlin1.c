// shanlin1.c (kunlun)

#include <ansi.h>
#include <room.h>

inherit ROOM;
int do_jump(string arg);
void create()
{
	 set("short", "云杉林");
	 set("long",@long
这是一片蜿蜒无尽的翠绿的树林，密密的云杉(yunshan)像撑天的巨伞，重重
叠叠的枝丫，只漏下斑斑点点细碎的日影。林子十分幽静，连鸟雀也少飞来，只偶尔
能听到远处的几声鸟鸣。
long);
	 set("exits",([
                "west" : __DIR__"shanlin2",
                "northeast" : __DIR__"jiuqulang2",
                "southeast" : __DIR__"shanlin3",
         ]));

	 set("objects",([
		__DIR__"obj/da-shugan.c" :  1,
		__DIR__"obj/xiao-shuzhi.c" :  1,
	 ]));
     set("item_desc", ([
                "yunshan" : "密集丛林中的云杉树，笔直高耸。\n你身处其中，忍不住想跳（tiao/jump）上去看看风景。\n"]));

         set("outdoors", "昆仑");
         setup();
}

void init()
{
	add_action("do_jump","jump");
	add_action("do_jump","tiao");
}

int do_jump(string arg)
{
	object me=this_player();

	int level, jinglicost;

	level = me->query_skill("dodge", 1);
	if (!arg||arg!="yunshan")
		return notify_fail("你要击打什么？\n");
	
	jinglicost = level / 3 + random(level / 3);
	
	if (me->query("jingli") <= jinglicost)
	{
			write("你太累了，先歇歇吧！\n");
			return 1;
	}
		me->receive_damage("jingli", jinglicost);
	if (level < 30) {
			write("你耸身作势，向云杉树上跃去，可惜的基本轻功不足30，,脚尖还差一些才能够到。\n");
			return 1;
		}
	
		if (level < 120) 
		{
			message_vision("$N吸了口气，纵身向云杉树杈处跃去，状若云燕，甚是敏捷。\n", me);
			me->improve_skill("dodge", me->query_int() / 3);
		}
		else
			message_vision("$N微一运劲，双脚发力，轻飘飘跃上云杉树杈，你的基本轻功已经无法提高了。\n", me);
		return 1;
}