// lgf.c
// 练功房
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short","练功房");
	set("long",@long
此处是总坛教众平时练功习武的地方。房中靠墙有个兵器架，上面插
着不少兵器，旁边放着几个石锁(suo)，屋子中间是一个梅花桩(zhuang)，
房子的大粱上则吊着几个沙袋(dai)。
long);
	set("exits",([
	    "south" : __DIR__"road2",
	]));
	set("item_desc",([
	    "dai" : "一个吊着的沙袋，是门中弟子练习掌法的道具，你可以打(da)试试。\n",
		"zhuang" : "梅花桩，是门中弟子练习轻功的地方，你可以跳(tiao)试试。\n",
	]));
	set("objects",([
	
	
		//__DIR__"obj/yaoli3" : 1,
	]));	
	set("coor/x",500);
	set("coor/y",440);
	set("coor/z",90);
	setup();
}
int init()
{
	add_action("do_da","da");
	add_action("do_tiao","tiao");
}
	   	
int do_da(string arg)
{
		object me=this_player();

		if (!arg || arg!="dai")
			return notify_fail("你要拍什么？。\n");
		
        if (me->is_busy())
			 return notify_fail("你正在忙碌中。\n");
		if (me->query_skill("strike",1)>100)
			return notify_fail("一掌下去，将沙袋打飞！\n");
		
		message_vision(YEL"$N运内力与掌，扬手一掌打向沙袋！\n"NOR,me);
		me->add_busy(1+random(1));
		
		if (random(me->query("jingli"))<30) return notify_fail("你精力不足\n");
		
		
		me->add("jingli",-20-random(10));
		
		
		if (me->query_skill("strike",1)<100)
		{			
			me->improve_skill("strike",(int)me->query_skill("strike",1));
		}
		return 1;
}

int do_tiao(string arg)
{
		object me=this_player();

		if (!arg || arg!="zhuang")
			return notify_fail("你要跳什么？。\n");
		
        if (me->is_busy())
			 return notify_fail("你正在忙碌中。\n");
		if (me->query_skill("dodge",1)>100)
			return notify_fail("在梅花桩上纵跳如飞，轻松自如！\n");
		
		message_vision(HIG"$N跃上梅花桩，辗转腾挪，轻功身法甚是受益不浅！\n"NOR,me);
		me->add_busy(1+random(1));
		
		if (random(me->query("jingli"))<30) return notify_fail("你精力不足\n");
		
		
		me->add("jingli",-20-random(10));
		
		
		if (me->query_skill("dodge",1)<100)
		{			
			me->improve_skill("dodge",(int)me->query_skill("dodge",1));
		}
		return 1;
}