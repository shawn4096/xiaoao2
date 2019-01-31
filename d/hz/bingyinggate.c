// Room: /d/suzhou/bingyinggate.c
// Last Modified by winder on May. 15 2001
#include <ansi.h>

inherit ROOM;
string look_mugan();

void create()
{
	set("short", "兵营大门");
	set("long", @LONG
你正站在兵营的门口，面对着一排简陋的营房，可以看到穿着制服
的官兵正在操练，不时地传来呐喊声。老百姓是不允许在此观看的，你
最好赶快走开。兵营大门竖立一个木杆(mugan)，上面挂满了反贼的首级
下面占满了守卫士兵，戒备森严。
LONG
	);
	set("outdoors","杭州");
	set("exits", ([
		"south" : __DIR__"bingying",
		"north" : __DIR__"qsddao3",
	]));
	set("objects", ([
		"/d/city/npc/bing" : 4,
	]));
	set("item_desc",([
		"mugan" : (:look_mugan:),
	]));
	//set("no_clean_up",0);
	set("shouji",10);
	setup();
	replace_program(ROOM);
}
int init()
{
	object me;
	me=this_player();
	add_action("do_han","han");
	add_action("do_han","ma");
	add_action("do_han","jiaozhen");
}

int valid_leave(object me, string dir)
{
	if (!wizardp(me) && objectp(present("guan bing", environment(me))) && 
		dir == "south")
		return notify_fail("官兵拦住了你的去路。\n");
	if (dir == "south"
		&&me->query_temp("quest/射雕英雄传/江南七怪/getshouji"))
	{
		return notify_fail("你刚偷了首级并安葬，难道想自投罗网？\n");
	}
	return ::valid_leave(me, dir);
}

string look_mugan()
{
	object me;
	me=this_player();
	if (!me->query("quest/射雕英雄传/风雪惊变/over"))
		message_vision(HIR"$N抬头看去，却发现木杆上挂满了一个个血淋淋的反贼首级!\n"NOR,me);
	else if (me->query_temp("quest/射雕英雄传/江南七怪/hzdatan")&&query("shouji"))
	{
		message_vision(HIY"$N抬头看去，赫然发现木杆上正挂着郭啸天的首级！\n数日前一起喝酒的景象历历在目，但此刻却人鬼殊途，你不觉悲从中来!\n"NOR,me);
		message_vision(HIC"$N恨不能马上爬到木杆上去抢了"HIY"郭啸天的首级"HIC"，但此地乃是军机大营之地，白天戒备森严，无法下手!\n"NOR,me);
		me->set_temp("quest/射雕英雄传/江南七怪/lookgan",1);
		me->delete_temp("quest/射雕英雄传/江南七怪/hzdatan");
		add_action("do_pa","pa");
		add_action("do_pa","climb");
	}
	return "木杆上挂了很多首级，但此地戒备森严,只有到了晚上才有所松懈！\n";
}
//晚上取首级
int do_pa(string arg)
{
	object me,ob,bing;
	
	mixed *local;
	local = localtime(time() * 60);

	me=this_player();
	if (!arg||arg!="mugan")
	{
		return notify_fail("你没事到处乱爬，学乌龟么？\n");
	}
	if(local[2] >6 && local[2] < 18)
	{
		write(WHT"天气高远，空中白云悠悠，木杆下士兵戒备森严，根本无从下手！\n"
			"看来你只有等夜间夜深人静的时候才有机会下手。\n"NOR);
		return 1;
	}
	if (!me->query_temp("quest/射雕英雄传/江南七怪/lookgan"))
	{
		return notify_fail("你无缘无故来此地瞎转悠什么？\n");
	}
	if (me->query_skill("dodge",1)<300)
	{
		return notify_fail("你的轻功太差，不足300级，根本爬不上这个木杆！\n");
	}
	//if (query("shouji")<1)
	//{
		//return notify_fail("木杆上的首级已经给被人取走了！\n");
	//}

	tell_object(me,HIW"你顺着这个木杆爬上去，小心取下郭啸天的首级收好,并爬了下来！\n"NOR);
	tell_object(me,HIR"忽听有人喊道，“谁，抓叛党！”\n"NOR);
	ob=new("d/hz/obj/shouji");
	ob->move(me);
	//add("shouji",-1);

	if (!objectp(bing=present("jinguo gaoshou",this_object())))
	{
		//write("1");
		bing=new("d/thd/niujia/npc/jinguogaoshou");
		//write("2");
		bing->move(this_object());

	}
	bing->kill_ob(me);
	me->delete_temp("quest/射雕英雄传/江南七怪/lookgan");
	me->set_temp("quest/射雕英雄传/江南七怪/getshouji",1);
	return 1;
}
//埋骨后回来杀段天德
int do_han(string arg)
{
	object me;
	me=this_player();
	if (!arg||arg!="段天德")
	{
		return notify_fail("你要对谁喊？");
	}
	if (!me->query_temp("quest/射雕英雄传/江南七怪/maihead"))
	{
		return notify_fail("你看着旗杆上的首级，心中极度愤恨,似乎觉得有些事没做，虽不断咒骂，但心总有些遗憾！\n");
	}
	
	message_vision(HIC"你心中一片坦荡，唯一剩下报仇一事，运起丹田气喝道，“段天德，你这狗贼，给我出来”!\n"NOR,me);
	message_vision(HIC"喊了半天，段天德也没出来，你心中愤恨，决定硬闯!\n"NOR,me);
	me->apply_condition("killer",10);
	me->set_temp("quest/射雕英雄传/江南七怪/hanhua",1);
	
	me->delete_temp("quest/射雕英雄传/江南七怪/getshouji");
	return 1;
}