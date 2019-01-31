// Room:jpei隐居之地
// Date: Zhuifeng 2010

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",  HIW "迷雾山崖" NOR);
	set("long", @LONG
这里是一个数丈高的山崖，你抬头一看，忽然发现山崖上生长着一颗朱果树，
不由得心中狂喜！你不住的往上看，竟然没注意到这里没有任何出路。
LONG
	);

	set("no_clean_up", 0);
	set("exits", ([
		"down" : "d/city/dangpu",
	]));

	set("objects", ([ 
		//"zhang" : 1 
	]));

	set("no_death",1);
	setup();
}

void init()
{
	add_action("do_tiao", "walk");
	add_action("do_kao", "kao");
	add_action("do_cai", "cai");
}
int do_kao(string arg)
{
	object ob;
	object me = this_player();
	if (arg != "shanji" )
		return notify_fail("你要干什么？\n");
	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");
	/*
	if( me->query("id") !="jpei"|| me->query("id") !="zhuifeng" )
	return notify_fail("你想要干什么？\n");
	*/
	if ( (int)me->query("jingli")<400)
	{
		write("你现在太累了，休息一下吧！\n");
		return 1;
	} 

	if(random(10) > 5)
	{
		me->add("jingli",-random(300));
		return notify_fail("你四下找了半天，发现这里的山鸡都被你抓光拉！。\n"); 
	}

	message_vision("忽然草丛中一只五彩斑斓的"HIY"锦"HIG"鸡"NOR"被$N惊到，扑棱棱的想飞。\n"NOR, me);
	message_vision("$N眼疾手快，一把把"HIY"锦"HIG"鸡"NOR"抓在手里。\n"NOR, me);
	message_vision("$N不禁食指大动，准备生火，烧烤野味。\n"NOR, me);
	message_vision("$N生起一堆"HIY"火焰。\n"NOR, me);
	message_vision("不一会一只香喷喷的"HIY"叫花鸡"NOR"就烤好了。。\n"NOR, me);
	ob = new("/kungfu/class/gaibang/obj/jiaohuaji");
	ob->move(me);
	me->start_busy(10);
	//ob->move(environment(me));
	return 1;
}

int do_cai(string arg)
{
	object ob;
	object me = this_player();

	if (arg != "zhuguo")
		return notify_fail("你要采什么？\n");
	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");

	if( me->query("id") !="jpei" )
		return notify_fail("一个声音自空中响起，“这里是天神闪电培育奇花异草之苗圃，你一介凡人是如何进来的？！”\n");

	if ( (int)me->query("jingli")<400)
	{
		write("你现在太累了，休息一下吧！\n");
		return 1;
	}
	if(random(20) == 3)
	{
		me->add("jingli",-random(300));
		return notify_fail("你四下找了半天，什么也没找到。\n"); 
	}

	if (present("zhuguo", me))
	return notify_fail("你身上已经有一枚"HIR"万年朱果"NOR"了，莫要贪得无厌！\n");
	message_vision("$N艰难的攀缘到之上，伸手采下了一枚"HIR"万年朱果"NOR"。\n你忽然发现旁边还有长有一颗"HIG"草还丹"NOR"，赶紧采了下来。\n"NOR, me);
	ob = new("/u/jpei/zhuguo");
	ob->move(me);
	ob = new("/u/jpei/huandan");
	//ob->move(me)
	return 1;
}

int do_tiao(string arg)
{
	object me = this_player();
	if (arg != "down")
		return notify_fail("你要怎么蹦达？？\n");
	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");
	message_vision("$N整理了一下衣冠，施施然的走进了巫师会客室。\n", me);
	tell_object(me, "你整理了一下衣冠，施施然的走进了巫师会客室。\n");

	me->receive_damage("jing", 30);
	me->move("/d/wizard/guest_room");
	message_vision("$N的身影子突然出现在一阵云雾中。\n", me);

	me->start_busy(random(2));
	return 1;
}

