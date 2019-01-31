// /u/jpei/guiyun/zoulang3.c
#include <ansi.h>
inherit ROOM;
int do_jump(string arg);
int story1(object me);
int story2(object me);
void create()
{
	set("short","走廊");
	set("long",@LONG
这是连接中厅与后厅的走廊。走廊曲曲折折，两旁种满了花树。
LONG
);
	/*  set("object",([
	__DIR__"obj/luchenfen.c" :     1,
	]));  */
	set("exits",([
		"east" : __DIR__"zoulang2",
		"south" : __DIR__"houting",
        "north" : __DIR__"wofang1",
	]) );
	set("no_clean_up",0);
	set("outdoors", "归云庄");
	setup();
}
void init()
{
	//增加判断
	
	add_action("do_jump","jump");
	add_action("do_jump","tiao");
	//add_action("do_pull","move");
	//add_action("do_pull","yi");
}

int do_jump(string arg)
{
	object me = this_player();

	if (me->is_busy() || me->is_fighting())	return notify_fail("你正忙着呢！\n");
	if (arg == "liang"||arg == "梁") {
		if (me->query_skill("dodge",1)<350)
		{
		   message_vision("$N想跃起，怎奈轻功身法不够，跃起半空之际，又飘然落地。\n", me);
		   return 1;
		}
		else {
		   message_vision(HIC"$N运起轻功，轻轻跃起，跃上正北房间的外廊，以脚挂在外廊梁上，向里屋看去。\n"NOR, me);
           message_vision(HIC"只见房中共有七人，都是女子，一个十八九岁的美貌女子正在灯下看书，想必就是那位程大小姐了。\n"
		   +" 其余六人都是丫鬟打扮，手中却各执兵刃，劲装结束，精神奕奕，看来都会武艺。\n"
		   +"$N原本要来救人，却见人家早已有备，料得中间另有别情，两人精神一振，悄悄翻上屋顶，坐下等候，只待瞧一场热闹。\n"NOR, me);
           me->move("/d/thd/guiyun/menliang");
		   me->set_temp("slbw/tiaoliang",1);
		   return 1;
		}
	}

}
