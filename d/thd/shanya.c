// Room: /u/numa/thd/shanya.c
// Modified by Numa 19980903

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "断崖");
        set("long",@LONG
你向前奔了一阵，发现了这个断崖，已无路可走。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "westdown" : __DIR__"shanyao",
        ]) );
        set("no_clean_up", 0);
        set("outdoors","桃花岛");

        setup();
}

void init()
{
	add_action("do_jump","jump");
	add_action("do_jump","yue");
}

int do_jump(string arg)
{
	object me = this_player();
	
	if (me->is_fighting() || me->is_busy())
		return notify_fail("你正忙着呢！\n");
	if (arg!="ya") return 0;
	
	if (!me->query_temp("quest/thd/biguan/askhuang"))
	{
		return notify_fail("那是桃花岛秘密所在，没有征得岛主同意不能非法闯入！\n");

	}
	if (me->query_condition("killer"))
	{
		return notify_fail("你正在被通缉，无法进入此地！\n");

	}

	if(me->query_encumbrance() * 100 / me->query_max_encumbrance() > 20)
	        return notify_fail("你负重过多，恐怕难以跃过去。\n");
        if (me->query_skill("dodge",1) < 100)
                return notify_fail("你基本轻功太低，不足100，尝试跃过断崖，但却发现自己无法跃过去！\n");
        tell_room(environment(me), HIC+me->name()+"紧了紧随身物品，随即一招「随波逐流」跃过断崖，稳稳的落在对面。\n" NOR, ({me}));
        write("你内息一提，纵身跃过断崖。\n");
        me->add("neili",-200);
        me->start_busy(random(3));
        me->move(__DIR__"shanding");
        return 1;
}

	
