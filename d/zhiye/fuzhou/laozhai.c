// room: laozhai.c
// modify by Lklv 2001.9.6

#include <room.h>
#include <ansi.h>

inherit ROOM;
int check_fight(object me);

void create()
{
    set("short", "向阳老宅");
    set("long", @LONG
这里是一间破败的老宅院，平常没有什么人会来这里。地上横七竖八地堆
着几件家具。西边的墙角结着一张蜘蛛网，屋里到处是尘土，显然是已经很久
没有人住了。房间的尽头有一扇门(men)，但已被坍塌的砖瓦挡住了。
LONG
    );

    	set("exits", ([
        	"west" : __DIR__"xyxiang2",
    	]));

    	set("item_desc", ([
        	"men" : "这扇门已被挡住无法通行，除非你打破(break)它。\n",
    	]) );
	setup();
}

void init()
{
	object book, me,yue;
	me = this_player();
	add_action("do_break", "break");	
	
	if (objectp(book=present("zijin jiasha",me))) {
		//remove_call_out("buqun_rob");
		//call_out("buqun_rob", 0, me, book);
		if (!objectp(yue=present("yue buqun",environment(me))))
		{
			yue=new("/d/fuzhou/npc/yuebuqun");
			yue->move(this_object());
		}
		message_vision(HIR "忽然，一个蒙面人从黑影里闪了出来，一招「有凤来仪」，"
        "手中长剑闪烁\n不定，刺向$N的咽喉！\n" NOR,  me);
		yue->kill_ob(me);
		me->start_busy(1);
		call_out("check_fight",1,me);	
	}
}

int do_break(string arg)
{
	int n;
	n = this_player()->query("neili");
	if( !arg || arg!="men" ) {
		write("不要随随便便就乱砸别人的东西！\n"); // by pishou
		return 1;
	}
	message_vision("$N走到后门前，拜出骑马蹲裆式，深吸一口气，双掌同时拍出。\n", this_player());

	if (n>=500 && this_player()->query("quest/pixie/pxj_passwd")) {
		message_vision("$N只听一声轰响，$N把门震开了！\n", this_player());
		set("exits/south", __DIR__"houyuan");
		this_player()->set("neili",n-500);
		remove_call_out("close");
		call_out("close", 5, this_object());
	}
	else {
		message_vision("$N大吼一声“开！”，结果什么也没发生。看来$N的内力不够强。\n", this_player());
		this_player()->set("neili",0);
	}
	return 1;
}

void close(object room)
{
	message("vision","门上的砖头瓦块稀里哗拉坍塌下来，又挡住了后门。\n", room);
	room->delete("exits/south");
}

int check_fight(object me)
{
	object book,yue;
	if (!me) return 1;
	yue=present("yue buqun",this_object());
	if (!objectp(book=present("zijin jiasha",me)))
	{
		tell_object(me,HIY"你的紫金袈裟已经为蒙面人抢走了！\n"NOR);
		return 1;
	}	
	if (!living(me))
	{
		message_vision(HIR"$N一愣之间，已被蒙面人刺中咽喉！顿时鲜血如注！\n"NOR, me);
		book->move(this_object());
		destruct(book);
		me->unconcious();
		return 1;
	}
	if (!yue || yue->query("qi")<yue->query("max_qi")/2)
	{	
		message_vision(HIC"$N经过艰苦奋战，终于将这蒙面人打跑。\n"NOR, me);	
		write(HIR"蒙面人双足点地，越墙而走。\n你感觉蒙面人的身法好像是华山派的。\n"NOR);
		destruct(yue);
		return 1;
	}
	call_out("check_fight",1,me);
	return 1;

}
