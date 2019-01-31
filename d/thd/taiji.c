// Room: /u/jpei/thd/taiji.c

inherit ROOM;

int do_quit();
int do_save();

void create()
{
	set("short", "太极");
	set("long", @LONG
这里是太极层，你一走下来，往上的铁梯就被撤掉了。往下有一道悬挂着
的铁梯，通向两仪层。太极是世界的统一体，阴阳流转不息，互相转化，成为
一个整体，这就是所谓的混沌状态。由太极的两个极端变化而生出阴阳，就是
太极生两仪。
LONG
	);
	set("exits", ([ 
		"down" : __DIR__"liangyi",
	]) );

	set("no_clean_up", 0);
	setup();
}

void init()
{
	object me = this_player();

	me->delete_temp("wuxing");
	me->delete_temp("liangyi");
	me->delete_temp("sixiang");
	me->delete_temp("wuxing_total");
	me->delete_temp("wuxing_step");
	me->delete_temp("wuxing_error");
	add_action("do_save", "save");
	add_action("do_quit", "quit");
}

int do_save()
{
	write("这里不准存盘！\n");
	return 1;
}

int do_quit()
{
	write("这里不准退出！\n");
	return 1;
}

