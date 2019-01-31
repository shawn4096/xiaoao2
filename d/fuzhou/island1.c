// island1.c 小岛
// Modify by Looklove 2k/5/18
// 2001.9.27 update

#include <ansi.h>
inherit ROOM;
int do_fail(object me);
int do_baohu(string arg);
void create()
{
        set("short",YEL"小岛"NOR);
        set("long", @LONG
这是一个离大陆不远的小岛。隔着中间浅浅的海峡，可以望见对面大陆上
的渔港。脚下软软的沙滩上布满了美丽的贝壳，一些小鱼小虾，在岸边的海水
里自由自在地游来游去。海水一遍一遍涌过来，打湿了你的鞋子。
LONG
        );
        set("outdoors","福州");
        set("exits",([
		"west"  : __DIR__"island"+(1+random(3)),
		"east"  : __DIR__"island"+(1+random(3)),
		"north" : __DIR__"island3",
		"south" : __DIR__"island"+(1+random(3)),
        ]));
	set("objects", ([
		MISC_D("beike") : 1,
		"/d/kunlun/npc/keshuang" : 1,
		"/d/kunlun/npc/klbaobiao" : 1,
		"/d/kunlun/npc/jiapu" : 1,

	]));
        setup();
}

void init()
{
        add_action("do_swim","swim");
        add_action("do_swim","youyong");
		add_action("do_kill","kill");
		add_action("do_baohu","baohu");

}

int do_swim()
{
        object me = this_player();

        if (me->is_busy())
		return notify_fail("你现在正忙着呢！");

        message_vision("$N一个俯冲，跳进海里，往浪里一钻就不见了。\n", me);
        tell_object(me,"你游了一会，转眼到了岸边，往岩石上一按，跃了上去。\n");
        me->move(__DIR__"haigang");
        tell_room(environment(me), me->name() +
	"抓着岸边岩石，噔噔噔地爬了上来。\n", me);
        return 1;
}

int do_kill(string arg)
{
	object me,ob1,ob2;
	me=this_player();
	ob1=present("zheng keshuang",this_object());
	ob2=present("huyuan dizi",this_object());

	if (!arg)
	{
		return notify_fail("你要杀谁？\n");
	}
	if (arg=="zheng keshuang"||arg=="zheng"||arg=="keshuang")
	{
		message_vision(HIR"郑克爽身边的保镖一看$N要杀自己的主人，顿时大怒，立下杀手！\n"NOR,me);
		ob2->kill_ob(me);

	}
	
}


int do_baohu(string arg)
{
	object me;
	me=this_player();
	if (!arg||arg!="郑克爽")
	{
		return notify_fail("你要保护谁？\n");
	}
	if (!me->query_temp("quest/kl/baifxf/askzheng"))
	{
		return notify_fail("你跟郑公子非亲非故，不需要你没事献殷勤！\n");

	}
	if (!present("zheng keshuang",environment(me)))
	{
		return notify_fail("郑克爽不再此地，你要保护谁？\n");
	}
	if (time()-me->query("quest/kl/baifxf/time")<86400)
	{
		return notify_fail("你来的太频繁了，明天再来？\n");

	}
	if (me->query_temp("quest/kl/baifxf/askzheng")&&arg=="郑克爽")
	{
		message_vision(HIY"$N对郑克爽鞠了一躬，说道，“请小王爷放心！有我在，任何来犯之敌都伤不了你！”\n"NOR,me);
		
		call_out("do_guard",10+random(10),me);
		me->start_busy(10);
	}
	return 1;
}

int do_guard(object me)
{
	object obj,ob;
	//me=this_player();
	ob=present("zheng keshuang",environment(me));
	if (!ob)
	{
		return notify_fail("郑克爽已经为人所杀，你要保护谁？\n");

	}
	tell_object(me,HIC"$N正在四处打量之际，心中着实紧张，不知刺客何时能到，担心有违冯长老的指示。\n" 
                       "这时，忽听一阵嘻嘻索索的声音传来，显然有高手在飞速朝此处奔来！\n"NOR+
                    RED"\n“敌袭！敌袭！”"NOR+HIC"你飞身挡在郑克爽面前，猛觉背后风声劲急，一股刚猛无比的掌力直扑自己背心！\n"NOR); 
     message_vision(HIY"\n$N飘然落地，只见前厅里站着四个黑衣人，听到一个黑衣人喊道：并肩一起上。\n"NOR, me);
     obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
	 obj->kill_ob(me);
	 obj->kill_ob(ob);
     
	 obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
	 obj->kill_ob(me);
	 obj->kill_ob(ob);

     obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));    
     obj->kill_ob(me);
	 obj->kill_ob(ob);

     obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));    
     obj->kill_ob(me);
	 obj->kill_ob(ob);

	 call_out("check_fight",50,me,ob);

	return 1;
}
int check_fight(object me,object ob)
{
	
	if (!me) return 1;
	if (environment(ob)!=environment(me))
	{
		write("你已经离开这个区域，保护郑克爽任务失败！\n");
		do_fail(me);
		return notify_fail("你已经离开这个区域，保护郑克爽任务失败！\n");
	}
	
	if (!present("zheng keshuang",environment(me)))
	{
		write("郑克爽被刺客所杀，任务失败！\n");

		do_fail(me);
		return notify_fail("郑克爽被刺客所杀，任务失败！\n");
	}
	if (present("heiyi ren",environment(me)))
	{
		message_vision(HIR"黑衣人眼见被众人围住，忽然大喊一声，浑然不顾自己伤势，拼尽全身力气刺向郑克爽!\n"NOR,me);
		if (ob)
		{
			message_vision(HIY"郑克爽大叫一声，为刺客一刀刺死!\n"NOR,me);
			ob->die();
		}
		write("郑克爽被刺客临终反击所杀，任务失败！\n");

		do_fail(me);
		return notify_fail("郑克爽被刺客所杀，任务失败！\n");

	}
	me->set("quest/kl/baifxf/baohu",1);
	me->set("quest/kl/baifxf/time",time());
	me->set("quest/kl/baifxf/combat",me->query("conbat_exp"));
	me->delete_temp("quest/kl");
	message_vision(HBBLU+HIW"$N已经完成冯锡范长老的任务，保护郑克爽成功，可以回去复命了！\n",me);	
	return 1;


}

int do_fail(object me)
{
	if (!me) return;
	
	me->add("quest/kl/baifxf/fail",1);
	me->set("quest/kl/baifxf/time",time());
	me->set("quest/kl/baifxf/combat",me->query("conbat_exp"));
	me->delete_temp("quest/kl");
	message_vision(HIC"在规定时间内郑克爽被人所刺杀，任务失败！\n"NOR,me);
	return 1;
}
