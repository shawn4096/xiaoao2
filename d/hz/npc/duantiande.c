// wujiang.c 武将

#include <ansi.h>
inherit NPC;
string ask_name();
string ask_liping();

void create()
{
	set_name(HIC"副指挥史"NOR, ({ "fu zhihuishi", "zhihuishi", "jiangjun"}));
	set("gender", "男性");
	set("age", random(10) + 30);
	set("str", 25);
	set("dex", 16);
	set("con", 25);
	set("int", 16);

	set("long", "他是杭州第六指挥所副指挥史，站在那里，麻醉脏话，正在的确有说不出的威风。\n");
	set("combat_exp", 75000);
	set("shen_type", 1);
	set("attitude", "peaceful");

	set_skill("cuff", 160);
	set_skill("force", 160);
	set_skill("sword", 160);
	set_skill("dodge", 160);
	set_skill("parry", 160);
	set_skill("taizu-quan", 160);
	set_skill("baduan-jin", 160);
	set_skill("caoshang-fei", 160);
	map_skill("force","baduan-jin");
	map_skill("dodge","caoshang-fei");
	map_skill("cuff","taizu-quan");
	map_skill("parry","taizu-quan");
	prepare_skill("cuff","taizu-quan");

	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 30);

	set("neili", 4000); 
	set("max_neili", 4000);
	set("jiali", 100);
    set("inquiry", ([
                //"全真教" :  "我全真教是天下道家玄门正宗,你若入我门来，不好好修炼，看我如何收拾你！\n",			      
                "段天德" : (: ask_name :),
			   // "李萍" : (: ask_liping :),
               //	"教中功绩" : (: ask_gongji :),
                 
        ]) );
	setup();
	carry_object(BINGQI_D("gangjian"))->wield();
	carry_object(ARMOR_D("armor"))->wear();
}


string ask_name()
{
	object me,bing,duan;
	me=this_player();
	if (!me->query_temp("quest/射雕英雄传/江南七怪/hanhua"))
	{
		command("say 兄弟们，给我上，剁了这孙子！\n");
		if (present("bing",environment(this_object())))
		{
			kill_ob(me);
		}
		kill_ob(me);
		me->apply_condition("killer",10);

		return "竟然敢闯军营，不想活了？\n";
	}
	command("say 啊，痛死了，别那么用力好不好？\n");
	command("say 方才我看到段大人从后面出去了！\n");
	message_vision(HIY"$N看了眼这个副指挥史，见他一副猥琐的样子，似乎不像是说谎，心中恨恨不已，骂道，“段天德这个狗贼”\n"NOR,me);
	command("say 段天德这个狗贼确实不是东西！\n");
	message_vision(HIY"$N心中惦记丘处机所言之事，刚想继续追问！这时忽然从这个副指挥史旁边窜出一道黑影，向你袭来\n"NOR,me);
	message_vision(HIR"$N和那个高手几下交手间你甚是差异，这显然不是中原武功，何时军中竟然隐藏如此高手？\n"NOR,me);
	if (!objectp(bing=present("jinguo gaoshou",environment(this_object()))))
	{
		bing=new("d/thd/niujia/npc/jinguogaoshou");
		bing->set("jiali",250);
		bing->move(environment(this_object()));
	}
	bing->kill_ob(me);
	this_object()->set_name(HIY"段天德"NOR, ({ "duan tiande", "duan", "tiande" }));
	message_vision(HIG"\n此时此人却在狂喊，“抓住反贼，重重有赏”，一边喊着，一边抓起身边的一个士兵就往外跑去？\n"NOR,me);
	message_vision(HIC"\n$N忽听那个士兵竟然发出女声，依稀有李萍的容貌，顿时心中雪亮，哪里还不知道这副指挥史就是段天德这狗贼？\n"NOR,me);
	message_vision(HIC"\n$N知道，只有抓住这个狗贼才能知道李萍的安危？\n"NOR,me);

	me->set_temp("quest/射雕英雄传/江南七怪/findduan",1);
	me->add_condition("killer",6);
	return "杀人啦！\n";
}
