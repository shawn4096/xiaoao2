// mtxiaowu.c 木屋
#include <ansi.h>

inherit ROOM;
#define XKX_QUEST1 "quest/侠客行/摩天崖/"

void create()
{
        set("short", "木屋");
        set("long", @TEXT
这里是一个很小的木屋，室中放着一些乱七八遭的家具，墙角边
还有一张破烂的小床，有一个英俊的少年在屋内走来走去，似乎有什
么心事，不时的发出几声长叹...... 
TEXT );

       set("exits", ([
           "west" : __DIR__"mtdating",
       ]));

       set("objects",([
           __DIR__"npc/shizhongyu" : 1,
       ]));

       setup();       
}

void init()
{

	add_action("do_jiejiu","jiejiu");
}

int do_jiejiu(string arg)
{
	object me,shi,min;
	me=this_player();

	if (!arg||arg!="石中玉")
	{
		return notify_fail("你要解救谁？");
	}
	if (!me->query_temp(XKX_QUEST1+"yihuo"))
	{
		return notify_fail("你和石中玉无缘无故，他根本就不听你瞎掰！\n");
	}
	message_vision(RED"就在$N给石中玉松绑的过程中，忽听屋外有人清喝一声，\n“原来我的孩子是让你这奸贼给抓走了，奸贼，休走！”\n"NOR,me);
	message_vision(RED"\n屋外闯入两个身影，一个身穿白衣，一个身穿黑衣，正是江湖人称黑白双剑的石清闵柔夫妇。”\n"NOR,me);
	if (!objectp(shi=present("shi qing",environment(me))))
	{
		shi=new("d/motianya/npc/shiqing");
		shi->move(environment(me));
	}
	if (!objectp(min=present("min rou",environment(me))))
	{
		min=new("d/motianya/npc/minrou");
		min->move(environment(me));
	}
	shi->kill_ob(me);
	min->kill_ob(me);
	if (objectp(shi)&&objectp(min)&&objectp(me))
		call_out("do_wuhui",6+random(6),me,shi,min);
	return 1;
}
int do_wuhui(object me,object shi,object min)
{
	if (!shi)
	{
		tell_object(me,"石清被你失手杀死，石中玉对你很不满，任务失败！下次在来。\n");
		me->delete_temp("quest/侠客行/摩天崖");
		return 1;

	}
	if (!min)
	{
		tell_object(me,"闵柔被你失手杀死，石中玉对你很不满，任务失败！下次在来。\n");
		me->delete_temp("quest/侠客行/摩天崖");

		return 1;

	}
	if (!me) 
	{	
		tell_object(me,"你自己壮烈了，任务失败！下次在来。\n");
		return 1;
	}
	message_vision(HIR"\n\n\n石中玉忽然大喊一声，“住手！自己人！爹娘，你们怎么来了？”\n"NOR,me);
	shi->remove_all_enemy();
	shi->start_busy(2);
	min->remove_all_enemy();
	min->start_busy(2);

	me->remove_all_enemy();
	me->start_busy(2);

	call_out("do_huangwu",3+random(4),me);
	return 1;
}
int do_huangwu(object me)
{
	object shi,min,yu;
	message_vision(HIY"$N听了石中玉的介绍方才知道原来这二位乃是石中玉的亲生爹娘！\n"NOR,me);
	message_vision(HIY"石中玉原本是玄素庄主石清的亲生儿子，一直追寻线索找到此地，\n方才以为"+me->query("name")+"要对自己儿子不利方才出手，原来是一场误会！\n"NOR,me);
	message_vision(HIR"\n\n$N看石中玉跟随自己爹娘一起离开，心中五味杂陈。\n"NOR,me);

	message_vision(HIR"\n\n$N感慨人生无常，竟然有如此的曲折，这任务算是完成了还是没完成呢？\n"NOR,me);
	message_vision(YEL"\n\n看来还是先回去跟贝先生告知一下再说。\n"NOR,me);
	me->set(XKX_QUEST1+"over",1);
	me->set("quest/侠客行/time",time());
	me->set("quest/侠客行/exp",me->query("combat_exp"));

	me->delete_temp("quest/侠客行/摩天崖");
	if (objectp(shi=present("shi qing",environment(me))))
	{
		destruct(shi);
	}
	if (objectp(min=present("min rou",environment(me))))
	{
		destruct(min);
	}
	if (objectp(yu=present("shi zhongyu",environment(me))))
	{
		destruct(yu);
	}

	message_vision(HBYEL+HIW"\n\n恭喜$N完成了《侠客行》故事系列一之《摩天崖篇》\n"NOR,me);
	message_vision(HIC"\n\n已经远去的石清夫妇在远处喊道，“如果有空，请来素玄庄做客！”\n"NOR,me);

	return 1;
}