///u/qingyun/lsd/shanfeng.c
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", YEL"山峰"NOR);
	set("long", @LONG
沿着山坡而行，向北而上是一座山峰，山峰座落在灵蛇岛的北部，在山峰
之东，可以看见一间孤零零的茅屋。
LONG);
	set("exits", ([
	  	"southdown" : __DIR__"sfjiao",
	]));
	/*
	set("objects",([
                CLASS_D("mingjiao") + "/huiyue" : 1,
                CLASS_D("mingjiao") + "/liuyun" : 1,
                CLASS_D("mingjiao") + "/miaofeng" : 1,
	]));
	*/
	set("outdoors","灵蛇岛");
	setup();
}
int init()
{
	object me=this_player();
	
	if (me->query_temp("quest/mj/shlf/zhang") )
	{
		message_vision(HIC"$N放眼望去，忽然听到山峰处传来一片吆喝的声音。\n看样子似乎有人正在打斗！\n"NOR,me);
		call_out("weigong_xie",3+random(3),me);	
		add_action("do_jiejiu","help");
	}
}
//设计情节。。
int weigong_xie(object me)
{
	object xie,huiyue,liuyun,miaofeng;
	
	if (!objectp(xie=present("xie xun",environment(me))))
	{
		xie=new("kungfu/class/mingjiao/xie2");
		xie->move(this_object());
	}
	if (!present("huiyue shi",environment(me)))
	{
		huiyue=new("kungfu/class/mingjiao/huiyue");
		huiyue->move(this_object());
	}
	if (!present("liuyun shi",environment(me)))
	{
		liuyun=new("kungfu/class/mingjiao/liuyun");
		liuyun->move(this_object());
	}
	if (!present("miaofeng shi",environment(me)))
	{
		miaofeng=new("kungfu/class/mingjiao/miaofeng");
		miaofeng->move(this_object());
	}
	huiyue->kill_ob(xie);
	miaofeng->kill_ob(xie);
	liuyun->kill_ob(xie);
	return 1;

}
int check_fight(object me)
{
	object xie,huiyue,miaofeng,liuyun;
	if (!me) return 0;
	if (present("huiyue shi",environment(me)))
	{
		huiyue=present("huiyue shi",environment(me));
	}

	if (present("liuyun shi",environment(me)))
	{
		liuyun=present("huiyue shi",environment(me));
		
	}
	if (present("miaofeng shi",environment(me)))
	{
		miaofeng=present("huiyue shi",environment(me));
		
	}
	if (present("xie xun",environment(me)))
	{
		xie=present("xie xun",environment(me));
	}
	if (!objectp(xie))
	{
		return notify_fail("明教金毛狮王谢逊已经被波斯三使所杀,任务失败！\n");
	}
	if (!me->is_fighting() && objectp(xie)&&!objectp(huiyue)&&!objectp(miaofeng)&&!objectp(liuyun))
	{
		message_vision(HIC"$N经过艰苦的搏斗，终于将波斯三使杀死，并谢逊解救出来。\n"
							+"现在可以回去跟教主复命了。\n"NOR,me);
		me->set("quest/mj/shlf/helpxie",1);
		me->delete_temp("quest/mj/shlf/zhang");
		
		destruct(xie);
		return 1;
	}
	call_out("check_fight",2,me);
	

}

int do_jiejiu(string arg)
{
	object me=this_player();
	object xie,huiyue,liuyun,miaofeng;

	if (!arg||arg !="谢逊")
	{
		return notify_fail("你要帮谁？\n");
	}
	if (!objectp(xie=present("xie xun",environment(me))))
	{
		return notify_fail("明教金毛狮王谢逊已经被波斯三使所杀,任务失败！\n");
	}
	message_vision(HIC"$N见谢逊正在为波斯三使围困，局势异常危险，当即出手，喝道，“谢大侠别慌，我来帮你了。”\n"NOR,me);
	message_vision(HIY"\n\n谢逊对$N喝道“这是哪位少侠？谢逊不胜感激!””\n"NOR,me);
	message_vision(HIG"\n\n$N回答道“谢法王请放心，我乃大光明教张教主座下"+me->query("name")+HIG"是也!奉张教主之命来此协助法王!”\n"NOR,me);
	
	
	if (objectp(huiyue=present("huiyue shi",environment(me))))
	{
		huiyue->kill_ob(me);
		me->kill_ob(huiyue);
	}
	if (objectp(liuyun=present("liuyun shi",environment(me))))
	{
		liuyun->kill_ob(me);
		me->kill_ob(liuyun);
	}
	if (objectp(miaofeng=present("miaofeng shi",environment(me))))
	{
		miaofeng->kill_ob(me);
		me->kill_ob(miaofeng);
	}
	
	call_out("check_fight",1,me);
	return 1;

}