#include <ansi.h>
inherit ROOM;
int do_fail();
void create()
{
        set("short", "灵堂");
        set("long", @LONG
此地是摆放全真教掌教王重阳灵枢的房间。房间很大，真人
的棺木(guan)摆放在正中央，四周整齐地铺着一排排的鲜花和挽
联，有弟子正在守灵，隐隐有啜泣之声传来。
LONG);
       // set("sleep_room",1);
        set("exits", ([
                "down" : __DIR__"laojundian",
        ]));
        set("item_desc", ([
                "guan": RED "这是一个硬木材所制造棺材，重阳真人的遗体正躺在里面，面容肃静，栩栩如生。\n" NOR
        ]));
        set("objects", ([
                "/d/quanzhen/obj/xianglu": 1,
				"/d/quanzhen/obj/guancai": 1,
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
		if (!this_player()->query_temp("quest/qz/xtg/dingyang/start")) return;
		
        add_action("do_ketou","ketou");
		add_action("do_jingxiang","jingxiang");
		add_action("do_jibai","jibai");
		add_action("do_zhengli","zhengli");

}
int do_jingxiang()
{
	object me=this_player();
	if (me->query("family/family_name")!="全真教")
	{
		return notify_fail("你无缘无故，非全真教弟子，来此作甚？！\n");
	}
	message_vision(MAG"$N走向按前，从香案上拿起三支檀香，点然后恭恭敬敬上香！\n"NOR,me);
	
	me->set_temp("marks/jingxiang",1);
	return 1;

}
int do_ketou(string arg)
{
	object me=this_player();
	if (!me->query_temp("marks/jingxiang"))
	{
		return notify_fail("你该先上香再磕头！\n");
	}
	if (!arg||arg!="重阳祖师")
	{
		return notify_fail("你要给谁磕头！\n");
	}
	message_vision(HIC"$N跪在重阳真人棺椁之前，恭恭敬敬磕了三个响头，棒棒作响！\n"NOR,me);
	me->set_temp("marks/ketou",1);
	message_vision(HIY"\n\n这时候司仪在旁边喊了声，“祭拜开始！”\n"
		HIW+"\n\n忽然间，$N隐约听到屋顶似乎有轻微的瓦片碎了的声音！\n"NOR,me);

	return 1;

}
int do_jibai(string arg)
{
	object me=this_player();
	if (!me->query_temp("marks/ketou"))
	{
		return notify_fail("你该先磕头再祭拜祖师！\n");
	}
	if (!arg||arg!="重阳祖师")
	{
		return notify_fail("你要祭拜谁！\n");
	}
	message_vision(HIC"$N跪在重阳真人棺椁之前，拿起案上的纸钱，点火后焚烧在铜盆之中！\n"NOR,me);
	message_vision(HIG"\n\n$N然后又重新跪下开始给祖师磕头！\n"NOR,me);

	message_vision(HIY"\n\n$N作为全真弟子，心中异常沉痛，按照习俗，孝子孝孙当为祖师整理仪表仪容！\n"NOR,me);
	
	me->set_temp("marks/jibai",1);
	//call_out("do_oyfcome",1,me);
	return 1;

}
int do_zhengli(string arg)
{
	object me=this_player();
	if (!me->query_temp("marks/jibai"))
	{
		return notify_fail("你该先祭拜完了再整理祖师遗容！\n");
	}
	if (!arg||arg!="祖师遗容")
	{
		return notify_fail("此地乃是祖师灵堂，你要做什么？！\n");
	}
	message_vision(HIC"$N跪在重阳真人棺椁之前，为祖师整理仪表仪容！\n"NOR,me);
	message_vision(HIR"\n\n$N想起祖师日常恩德然，不禁心中悲痛，忍不住想要嚎啕大哭一场！\n"NOR,me);

	add_action("do_cry","cry");
	
	me->set_temp("marks/zhengli",1);
	//call_out("do_oyfcome",1,me);
	return 1;
}
int do_cry(string arg)
{
	object me=this_player();
	if (!me->query_temp("marks/zhengli"))
	{
		return notify_fail("你该先整理祖师遗容！\n");
	}
	message_vision(HIC"$N跪在重阳真人棺椁之前，见祖师遗容栩栩如生，可惜生死相别，永无再见之日！\n"NOR,me);
	message_vision(HIR"\n\n$N想到从此生死两途，来生再见！不禁扶棺痛哭！泪如雨下！\n"NOR,me);

	message_vision(HIY"\n\n然而，生死无常，无论$N如何痛哭，重阳真人已然仙逝，一动不动！\n"NOR,me);
	message_vision(HIR"\n\n这时，忽听屋外一阵喋喋怪笑传来，“王重阳！你个死牛逼字，真的就这么死了”！\n"NOR,me);

	me->set_temp("marks/zhengli",1);
	call_out("do_oyfcome",4+random(4),me);
	return 1;
}

int do_oyfcome(object me)
{
		object feng;
		int i;

		i=me->query("max_pot")-100;
		i=i+50+random(20);

		if (me->query("family/family_name")!="全真教")
		{
			me->move("/d/quanzhen/laojundian");
			return notify_fail("你非全真教弟子，如何发现这儿？\n");
		}
        message_vision(HIR "忽然间，门外窜入一个黑衣壮汉！\n\n" NOR, me);
        if (!objectp(feng=present("ouyang feng",this_object())))
        {
			feng=new("/d/quanzhen/npc/feng");
			if (me->query("combat_ext")<18000000)
				feng->move("/d/quanzhen/lingshi");
			else{
				feng->set("combat_exp",me->query("combat_exp"));
				feng->set_skill("lingshe-zhangfa",i);
				feng->set_skill("lingshe-quan",i);
				feng->set_skill("hamagong",i);
				feng->set_skill("cuff",i);
				feng->set_skill("force",i);
				feng->set_skill("staff",i);
				feng->set_skill("dodge",i);
				feng->set_skill("hamabu",i);
				feng->move("/d/quanzhen/lingshi");
			}
        }
		feng->feng_say();

		//feng->kill_ob(me);
		//feng->check();
		
		message_vision(HIW"眼见这名黑衣人迈步走向重阳真人棺椁前，试图掀开棺椁，侵犯真人遗骸！\n"NOR,me);
		message_vision(HIW"$N心中大吃一惊！\n"NOR,me);
		add_action("do_zulan","zulan");
		
		if (objectp(feng=present("ouyang feng",this_object())))
	
		call_out("do_check",30,me,feng);

		me->query_temp("marks/times",time());		
        return 1;
}
//阻拦欧阳锋
int do_zulan(string arg)
{	
	object me,feng;
	me=this_player();
	//欧阳锋不再失败
	if (!arg||arg!="欧阳锋")
	{
		return notify_fail("此人即将掀翻棺椁，你要阻止谁？！\n");
	}
	if (objectp(feng=present("ouyang feng",this_object())))
	message_vision(HIR"$N大怒，立即闪身挡在$n面前，喝道，“你这恶贼，竟然如此猖狂，为何要动我祖师遗骸！”\n"NOR,me,feng);	
	feng->kill_ob(me);
	me->set_temp("marks/zulan",1);


}
int do_check(object me,object feng)
{
	if (!me) return 0;
	if (!feng) 
	{
		tell_object(me,"这个黑衣人已经被你杀死了!任务失败！\n");
		
		return do_fail();
	}
	if (time()-me->query_temp("marks/times")>35
		||!me->query_temp("marks/zulan"))
	{
		message_vision(HIC"$n一招蛤蟆功拍在重阳真人身上，抢夺棺椁内的那本九阴真经，哈哈大笑转瞬离去！\n"
		+"\n\n你没能阻挡住欧阳锋抢夺九阴真经，任务失败！\n"NOR,me,feng);
		if (objectp(feng))
			destruct(feng);
		return do_fail();
	}
	if (!me->is_fighting()
		||me->query("eff_qi")<me->query("max_qi")/2)
	{
		message_vision(HIC"$n一招蛤蟆功拍在重阳真人身上，抢夺棺椁内的那本九阴真经，哈哈大笑转瞬离去！\n"
		+"\n\n你没能阻挡住欧阳锋抢夺九阴真经，任务失败！\n"NOR,me,feng);
		return do_fail();
	}
	message_vision(HIY"\n\n这时，惊变突起！\n"
		+"\n\n就在$N和$n剧烈打斗的紧要关头，一直紧紧地躺在棺椁中重阳真人忽然跃起！\n"
		+"\n\n运起闻名天下的先天功，一指点向$n的额头！\n"
		+"\n\n$n一时不妨，为重阳真人破了$n的蛤蟆功！\n"
		"\n\n$n大叫一声，心中惊愕万分，一个倒翻身，向西逃窜而去！\n"NOR,me,feng);
	if (objectp(feng)) destruct(feng);

	call_out("wang_die",3+random(3),me);
}
int wang_die(object me)
{
	message_vision(HIC"$N眼见祖师重生，心中大喜，急忙磕头拜见祖师！\n"NOR,me);
	message_vision(HIM"\n\n但重阳真人一言不发，只是神情的看了$N一眼，含笑而立！\n"NOR,me);
	message_vision(HIY"\n\n半晌时光，重阳真人依然一动不动，$N这时才发现祖师已然气绝身亡！\n"NOR,me);
	message_vision(HIG"\n\n$N这时恍悟，“方才祖师原来是假死，目的就是欺骗欧阳锋来盗经，趁机破了他的蛤蟆功”！\n"NOR,me);
	message_vision(HIR"\n\n念及此，想通了其中关节，$N俯首叩头，不禁嚎啕大哭！\n"NOR,me);
	message_vision(HIR"\n在悲痛间，$N忽然见到重阳真人袖子中落下一张纸！\n"NOR,me);
	message_vision(HIR"\n\n你仔细一看，上面写道，“若有缘之人，赠后山另文”---重阳真人！\n"NOR,me);

 	message("channel:rumor", HIM"【谣言】某人："+me->query("name")+"机缘巧合，发现重阳真人五篇另文的线索！\n"NOR, users());
	me->set("quest/qz/xtg/dingyang/start",1);

	message("channel:chat", HIC"【聊天】"+me->query("name")+"：重阳真人不幸仙逝！全真教与白驼山庄誓不两立！\n"NOR, users());
	message("channel:chat", HIC"【聊天】"+me->query("name")+"：我大全真必将崛起江湖！\n"NOR, users());
	return 1;
}
int do_fail()
{
	object me,feng;

	if (!me) return 0;
	me=this_player();
	me->delete_temp("marks");
	me->delete_temp("quest/qz");
	me->set("quest/qz/xtg/dingyang/time",time());
	me->add("quest/qz/xtg/dingyang/fail",1);
	tell_object(me,HIW"\n\n任务失败，再接再厉！\n"NOR);
	if (objectp(feng=present("ouyang feng",this_object())))
		destruct(feng);
	return 1;
}