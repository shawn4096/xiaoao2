// Room: /d/shaolin/zhushe.c
// Date: YZC 96/01/19
// Dat:  Cleansword 96/02/20

inherit ROOM;
#include <ansi.h>

string look_stone();
string look_pig();

/* (move stone) 猪舍石块下埋着奄奄一息的乔三槐。告诉你
金刚伏魔圈前半段的走法(western)，说完头一歪，死了。如玩家
学过内功，可用所学内功中(life heal)之法延续乔三槐一口气，
令其说出后半段走法(news)，并且告知出迷宫走法藏在厨房莫处，
未及说完何处就死了。玩家自己找出何处（灶头里，可以钻进去，
里面有一块砖，上刻出迷宫走法）。*/


void create()
{
	set("short", "猪舍");
	set("long", @LONG
这是间破烂的农家猪舍。圈里养着几头瘦猪(pig)，泔槽已经干涸了，草料
也开始发霉腐烂。由于好多天没人清理牲口的粪便，满屋子弥漫着一股恶臭。屋
角堆了一大堆石块(stone)，足有半人高。
LONG
	);

	set("exits", ([
		"southeast" : __DIR__"houshan",
	]));

	set("item_desc",([
		"stone"		:	(: look_stone :),
		"pig"		:	(: look_pig :),
	]));

	set_temp("available",1);

	setup();
}

void init()
{
	add_action("do_move", "move");
	add_action("do_weizhu", "wei");
	add_action("do_weizhu", "weishi");
}

int do_move(string arg)
{
//	string dir;
	object me,ob;

	if( !arg || arg=="" || !query_temp("available") ) return 0;

	if( arg=="stone" && query_temp("available")) {
		write("你试著把石块一块块地搬开，突然发现下面埋着个奄奄一息的老人 !\n\n");
	        delete_temp("available");
	}


	me = new(__DIR__"npc/lao-qiao",1);
	me->move(__DIR__"zhushe");

	ob = this_player();	

	message_vision("老人断断续续地说道: 我是乔三槐，快...，快往北山上走...，
进了松林...，往西...，往东...，往南，往东...，再往北......\n\n", ob);

	message_vision("乔三槐嘴唇动了动，似乎还想说些什麽，却因伤重难支，昏死了过去。\n", ob);

	me->unconcious();

	remove_call_out("fainting");
	call_out("fainting", 20, me, ob);

	return 1;
}

void fainting(object me, object ob)
{

	if ( (int)me->query("qi") <= 50 ) 
	{
		message_vision("乔三槐缓缓苏醒了过来，说道: 谢...谢......。\n",ob);
		me->die();
	}
	else
	{
		message_vision("\n乔三槐醒了过来，说道: 再往北，往东，往西，南......出路在砖......\n\n",ob);
		message_vision("说罢脑袋便软软地垂了下去......",ob);
		me->die();
	}

	return;
}

string look_stone()
{
	return "这是一大堆石块，堆在墙脚边，不知是派什麽用场。\n";
}
string look_pig()
{
	return "一头瘦骨嶙峋的猪，很久没饲养了，真冲你哼哼地叫，你如有猪食，可以(weishi)它们。\n";
}

int do_weizhu(string arg)
{
	object me,shi;
	me=this_player();

	if (!arg||arg!="猪")
		return notify_fail("你要喂食什么动物？\n");
	if (me->is_busy()||me->is_fighting())
		return notify_fail("你正在忙碌中？\n");
	if (!me->query_temp("sljob/weizhu/askqiao"))
		return notify_fail("这头猪是有主人的，你随便喂食不怕猪咬你？\n");
	if (me->query_temp("sljob/weizhu/over"))
		return notify_fail("这头猪已经喂饱了，可以回去跟乔大妈交差了？\n");
	if (!objectp(shi=present("zhu shi",me)))
		return notify_fail("你身上没有猪食，无法喂养它们？\n");
	if (random(2))
	{
		message_vision(HIC"$N拿起猪食，弯腰用勺子要了一勺，慢慢倒入猪槽之中，嘴里喊道，“猪宝宝们，吃吧！”\n"NOR,me);

	}else {
				message_vision(YEL"$N拿起猪食，嘴里喊道，“啰`````````````！”\n"NOR,me);

	}
	shi->add("food_remaining",-1);
	me->add_busy(1);
	me->add_temp("sljob/weizhu/times",1);
	me->add("jingli",-1-random(10));
	if (!shi->query("food_remaining"))
	{
		message_vision(HIY"$N将最后一勺猪食倒入猪槽，看猪吃起来非常开心，仿佛这头猪长了不少！”\n"NOR,me);
		write("这头猪看样子已经喂饱了，可以回去交差了！\n");
		if (shi)
		{
			destruct(shi);
		}
		me->set_temp("sljob/weizhu/over",1);
	}
	return 1;
}