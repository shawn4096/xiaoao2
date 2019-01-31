// Room: /u/jpei/thd/njwest.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "村口");
	set("long", @LONG
这是一座小村落的西村口。村子很小，笼罩在一片寂静中。南边隐约可以
看到一条大江。
LONG
	);
	set("no_clean_up", 0);
	set("outdoors","牛家村");

	set("exits", ([
		"northwest": __DIR__"road2.c",
		"east": __DIR__"njroad1.c",
	]) );

   set("coor/x",80);
   set("coor/y",-360);
   set("coor/z",0);
   setup();
}


int init()
{
	object me,bing;
	me=this_player();
	if (me->query_temp("quest/射雕英雄传/风雪惊变/yestongyin")) 
	{
		message_vision(YEL"这时，$N只见村中涌入一大群士兵，正在到处烧杀抢掠！\n"NOR,me);
		message_vision(YEL"$N眼见现场惨烈，意图劝阻(quanzu)！\n"NOR,me);

		if (!objectp(bing=present("song bing",this_object())))
		{
			bing=new("d/thd/niujia/npc/songbing");
			bing->move("d/thd/niujia/njwest");
		}
		me->set_temp("quest/射雕英雄传/风雪惊变/findsongbing",1);
		me->delete_temp("quest/射雕英雄传/风雪惊变/yestongyin");
		add_action("do_quanzu","quanzu");

	}
}
int do_quanzu()
{
	object me,bing;
	me=this_player();
	bing=present("song bing",this_object());
	if (!me->query_temp("quest/射雕英雄传/风雪惊变/findsongbing")) 
	{
		return notify_fail("你要劝阻什么？\n");
	}
	message_vision(HIW"$N狭义心肠陡起，试图劝阻这种残暴的行为！但是这些宋兵根本不理睬$N。\n"NOR,me);
	tell_object(me,HIG"\n\n你只感觉这金兵甲行事为何如此卑鄙，居然不分青红皂白杀人，不由火气暴涨，立刻对金兵发动攻击。\n"NOR); 
	bing->kill_ob(me);
	me->set_temp("quest/射雕英雄传/风雪惊变/quanzu",1);
	call_out("do_check",10,me);
	return 1;
}
int do_check(object me)
{
	object bing;
	if (!me) return notify_fail("被宋兵甲所杀，任务失败！\n");
	if (file_name(environment(me))!="/d/thd/niujia/njwest")
	{
		return notify_fail("你为宋兵所驱赶，实力不济，到处乱跑！\n");
	}
	if (!objectp(bing=present("song bing",this_object())))
	{
		message_vision(HIC"你刚把这个为非作歹的宋兵杀死，忽听得杨家小院传来杨铁心的怒吼声！\n"NOR,me);
		message_vision(HIC"你忽然意识道，“这一定是一场阴谋，需要赶紧过去救人要紧”！\n"NOR,me);
		message_vision(HIC"你心想，“多一个人就多一份力量，道长虽然不在了，需喊上郭大哥一起出手”！\n"NOR,me);
		me->set("quest/射雕英雄传/风雪惊变/killsongbing",1);
		me->set_temp("quest/射雕英雄传/风雪惊变/killsongbing",1);
		return 1;
	}
	
	call_out("do_check",1,me);
}

int valid_leave(object me, string dir)
{
       if (me->query_temp("quest/射雕英雄传/风雪惊变/quanzu"))
       {
		   if (me->is_fighting())
			   return notify_fail(RED"\n宋兵大声喝道：哪里走。一把拦住你，你竟然无法离开。\n"NOR);
		   if (present("song bing",this_object()))
			   return notify_fail(RED"\n宋兵大声喝道：哪里走。一把拦住你，你竟然无法离开。\n"NOR);
			if(me->query_condition("killer")) 
			   return notify_fail(RED"\n怎么进来的？？这里等wiz吧。\n"NOR);
			return ::valid_leave(me, dir);
		}
		return 1;
}

