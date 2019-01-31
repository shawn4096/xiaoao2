// miaodi.c 妙谛和尚
// by sohu

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_for_join();
int do_kneel();
string ask_job();
string ask_finish();
string ask_fail();
string ask_jobshu();
string ask_miji();

void create()
{
	set_name("妙谛", ({"miao di","miao"}));
	set("long",@LONG
				"他是血刀门宝象的小弟子，皮肤白皙，神态雍容，甚是安详\n"
                "乃是佛法修为高深之辈，偶尔抬头远看，似乎神色有些忧虑。\n"
				"受师傅委托在此看守山洞并广招门徒。\n"

LONG
	);

    set("title",  "血刀门第六代弟子");
	set("gender", "男性");
	set("attitude", "peaceful");
	set("class", "huanxi");
	
	set("nick",HIC"花开"HIG"并蒂"NOR);
	
	set("inquiry",([
		"入世修行"	: (: ask_for_join :),
		"打猎"	: (: ask_job :),
		"工作次数"	: (: ask_jobshu :),
		"放弃"	: (: ask_fail :),
		"秘籍"	: (: ask_miji :),

	]));

	set("age", 30);
	set("shen_type", -1);
	set("str", 25);
	set("int", 15);
	set("con", 25);
	set("dex", 20);
	set("max_qi", 5450);
	set("eff_jing", 4200);
	set("max_jing", 4200);
	set("neili", 4500);
	set("max_neili", 4500);
	set("jiali", 100);
	set("combat_exp", 3500000);
	set("score", 1000);
	set("unique", 1);
	set_skill("force", 220);
	set_skill("xuedao-jing", 220);
	set_skill("dodge", 220);
	set_skill("xueying-dunxing", 220);
	set_skill("xuedao-daofa", 220);
	set_skill("blade", 220);
	//set_skill("hand", 220);
	set_skill("jingang-liantishu", 220);

	set_skill("strike", 220);
	set_skill("hongsha-zhang", 220);
	set_skill("parry", 220);
	set_skill("huanxi-chan", 100);
	set_skill("literate", 130);
	map_skill("blade", "xuedao-daofa");

	map_skill("force", "xuedao-jing");
	map_skill("dodge", "xueying-dunxing");
	map_skill("strike", "hongsha-zhang");
	map_skill("parry", "xuedao-daofa");

	prepare_skill("strike", "hongsha-zhang");

	create_family("血刀门", 6, "弟子");
	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
		(: exert_function, "yuxue" :),
		(: perform_action, "blade.jixue" :),
		(: perform_action, "blade.shendao" :),
		(: perform_action, "blade.chilian" :),
		(: perform_action, "blade.wuying" :),
	}));

	setup();
    carry_object("clone/weapon/blade")->wield();

    carry_object("d/xuedao/obj/qinxiu-jiasha")->wear();
}

void init()
{
	add_action("do_kneel", "kneel");
}
//采五肉的工作
string ask_job()
{
	object me,ob;
	me=this_player();
	
	if (!me->query("quest/xuedao/shoujie"))
	{
		command("say 你尚未受戒，不能入世修行，怕你心神有失！\n");
		command("say 你需要有入世修行的大恒心方可！\n");
		return "唉，滚滚红尘啊！\n";
	}
	command("say 既然你已经受戒将入世修行，须得多去世间体验下这世间的残酷！\n");
	command("say 我这里有一个小礼物先送给你!");
	ob=new("d/xuedao/obj/xiao_peidao");
	
	ob->set("owner",me->query("id"));
	if (me->query_conditon("job_busy"))
	{
		return "你现在正在忙于工作，稍后片刻！\n";
	}
	if (me->query("combat_exp")<100000)
	{
		command("say 你拿此刀到忘忧谷一侧的灌木林中巡视一番，如果发现猎物就顺手用这把配刀采集些新鲜血液，\n"
					+"这把刀是特制的，刀内中空，未必非要杀死猎物，只要按我说的心法和手法去操作，采集些野兽\n"
					+"的新鲜血液还是不难的。切记，你只需要从这些野兽身上采集些鲜血，无需杀了他们。\n"
					+"这既对你的考验。也替门派打些猎物采点鲜血回来，为我派制作药丸之用！\n");
		me->set_temp("xuedao/askcaixue",1);
		ob->set("job","采血");
	}else if (me->query("combat_exp")> 300000 && me->query("quest/xuedao/baishi/pass"))
	{
		command("say 你的经验值已经超过300k，并且已经拜师了就不要跟你师弟们抢这任务了！\n");
		return "爱弥陀佛，善哉善哉！\n";
	}
	else{
		command("say 你拿此刀到忘忧谷一侧的灌木林中巡视一番，如果发现野物顺手就杀了\n"
			+"这既对你的考验。也替门派打些猎物采点鲜肉回来，为我派制作药丸之用！\n");
		me->set_temp("xuedao/askdalie",1);
		ob->set("job","采肉");
	}
	ob->move(me);
	me->apply_condition("job_busy",15);
	me->apply_condition("xddl_job",15);

	command("say 快去快回，小心危险，千万记住佛不度无缘之人！");
	return "滚滚红尘，皆为劫数！\n福祸相依，又有谁知？\n";
}
string ask_jobshu()
{
	object me,ob;
	me=this_player();
	
	command("say 你现在打猎工作总任务次数为"+me->query("job_time/血刀打猎")+"次！\n");

	command("say 不要懈怠，只要你运气好，做到一定程度我就收你为徒，好好干！");
	return "唉，现在的年轻人，太容易偷懒了!\n";
}
//打猎工作交付

int accept_object(object who, object obj)
{
	object sil;
	int exp,pot,gold;
	
	if (obj->query("xuedao/caixue/ok"))
	{
		exp=250+random(100);
		pot=100+random(10);
		gold=50+random(10);
	}else if (obj->query("xuedao/cairou/ok"))
	{
		exp=300+random(100);
		pot=100+random(10);
		gold=50+random(10);

	}
	
	if (obj->query("id")=="xiao peidao" 
		&&obj->query("owner")==who->query("id")
		&&(obj->query("xuedao/cairou/ok")&&who->query_temp("xuedao/cairou/ok")||obj->query("xuedao/caixue/ok")&&who->query_temp("xuedao/caixue/ok")))
	{
		command("say 没想到你这小喇嘛居然如此勤奋，我血刀门将大兴旺啊！\n");
		command("laugh ");
		command("say 老祖回来看到如此多的肉食，必定开心的很！\n");
		who->delete_temp("xuedao/cairou");
		who->delete_temp("xuedao/askdalie");
		who->delete_temp("xuedao");
		
		destruct(obj);
		//奖励开始 who->query("job_time/血刀打猎")&&
		if (who->query("combat_exp")<300000) 
		{
			sil=new("clone/money/silver");
			sil->set("set_amount",gold);
			sil->move(who);
			who->add("combat_exp",exp);
			who->add("potential",pot);
			//command("give  to "+who->query("id"));
			message_vision(HIY"\n$N获得了"+exp+"点经验和"+pot+"点潜能,和"+chinese_number(gold)+"两白银的奖励！\n"NOR,who);
			
			if (who->query_condition("db_exp"))
			{
				who->add("combat_exp",exp);

				message_vision(HBYEL+HIW"$N因双倍经验获取又获得了"+exp+"点经验奖励！\n"NOR,who);
			}

			
		}else message_vision(YEL"$N经验超过300k都没能拜师，妙谛有些恼火，没有奖励！\n"NOR,who);

		who->apply_condition("job_busy",5);
		who->set("job_name","血刀打猎");
		who->add("job_time/血刀打猎",1);
		
		if (random(who->query("job_time/血刀打猎"))>300 &&!who->query("quest/xuedao/baishi/pass"))
		{
			command("say 我看"+who->query("name")+"一直辛苦工作，很是满意，经过考验，我可以收你为徒！\n");
			command("say 我血刀门乃是青海第一大派，你入我门来当光大我大血刀！");
			command("say 如果你愿意，可以拜我为师！\n");

			who->set("quest/xuedao/baishi/pass",1);
		}
		return 1;
	}
	
}
//打猎失败job
string ask_fail()
{
	object me,ob;
	me=this_player();
	if (me->query_temp("xuedao/askdalie"))
	{
		command("say 既然你完不成采肉任务就暂时下去歇息去了,哼！\n");
		me->delete_temp("xuedao/askdalie");

	}
	else if (me->query_temp("xuedao/caixue"))
	{
		command("say 既然你完不成采血就暂时下去歇息去了,哼！\n");

		me->delete_temp("xuedao/askcaixue");

		
	}else command("say 你什么都没做，瞎放弃什么？\n");


	if (objectp(ob=present("xiao peidao",me)))
	{
		destruct(ob);
	}
	me->delete_temp("xuedao");
	me->apply_condtion("job_busy",15);
	return "你放弃了从妙谛这儿接到的任务";
}

string ask_for_join()
{
	object me;

	me = this_player();
	if (me->query("family")&&me->query("family/family_name")!="血刀门")
		return RANK_D->query_respect(me) + "不是在开玩笑吧。\n";
	
	if (me->query("combat_exp")>10000)
		return RANK_D->query_respect(me) + "你居然超过10k的高手了，难道是其他门派的卧底？。\n";

	if( (string)me->query("class")=="huanxi" )
		return "我已经给你开坛受戒过了，你想比别人多一次？这可不行。\n";

	if( (string)me->query("gender") == "无性" )
		return "施主身体残缺，虽说佛祖普渡众生，可是我血刀门有时候完全靠那玩意，.……\n";

   	if( (string)me->query("gender") != "男性" ) {
		command("say"+ RANK_D->query_respect(me)+ "我派只收男性弟子，女施主可否愿意随我修炼欢喜禅？\n");
		return "嘿嘿``\n";
	}
  
	me->set_temp("pending/join_huanxi", 1);
	return "你若真心献身侍奉欢喜佛，请跪下(kneel)受戒。\n";
}

int do_kneel()
{
	object me = this_player();

	if( !me->query_temp("pending/join_huanxi") )
		return 0;

	message_vision("$N弯腰低头，恭恭敬敬地跪了下来。\n\n",me);
    message_vision("$n掏出几件法器，低眉垂目，围着你绕了几圈，口中念念有词。\n\n",me);
    message_vision("$n弹些清水撒在$N头上，山风一吹，$N不由得打了几个寒战。\n\n",me);
    message_vision("$n声音越来越高，额头渗出密密的汗水，似乎用了很大的力气。\n\n",me);
    message_vision("$n长吁了一口气，把法器放回怀中，用衣袖擦了擦脸上的汗水。\n\n",me);
	command("smile ");
	command("say 好啦，受戒法事做完了，从今以后欢喜佛祖会保佑你的。\n");
	me->delete_temp("pending/join_huanxi");
	me->set("class", "huanxi");
	me->set("quest/xuedao/shoujie",1);
	me->set("family/family_name","血刀门");
	me->set("family/generation",7);
	me->set("title","血刀门受戒小喇嘛");
    return 1;
}



void attempt_apprentice(object ob)
{
	
	//预留门派job考验任务接口

	if (ob->query("family") && (string)ob->query("family/family_name") != "血刀门") {
		command("say"+ RANK_D->query_respect(ob) + "不是本寺弟子，在这里捣什么乱？！");
		return;
	}
//如果血刀经不足60就不收徒
	if (ob->query("class")!="huanxi")
	{
		command("say 你不是我的密宗欢喜宗的弟子，没事就不要来骚扰我。\n");
		return;
	}
	if (!ob->query("quest/xuedao/shoujie"))
	{
		command("say 你没有受戒，一旦修行，我怕你控制不住自己的情欲。\n");
		return;
	}
    if (!ob->query("quest/xuedao/baishi/pass"))
    {
		command("say 你没有通过入门考验，一旦修行，我怕你是正派派来的奸细！。\n");
		return;

    }

	if( (string)ob->query("gender") == "无性" ) {
		command("say"+ RANK_D->query_respect(ob)+ "身体残缺不全，如何随我修炼？\n");
		return;
	}
	if( (string)ob->query("gender") != "男性" ) {
		command("say"+ RANK_D->query_respect(ob)+ "我派只收男性弟子，女施主可否愿意随我修炼欢喜禅？\n");
		return;
	}
//	if( ob->query("combat_exp")>200000 ) {
		//command("say"+ RANK_D->query_respect(ob)+ "我我不接受功力高深之辈，血刀经需从头修炼方可大乘？\n");
	//	return;
	//}

	if ((int)ob->query("shen") > -10000) {
		command("hmm");
		command("say 我血刀门老祖声名远扬，那些所谓的江湖大侠哪个不是望风而逃？");
		command("say 你现在戾气大于-10000，如果收你为徒，恐怕会被人耻笑。");
		return;
	}
	command("say 我就喜欢你这样的年轻小男人。好，就收你为我弟子吧。");
	command("recruit " + ob->query("id"));
	return;
	
}

string ask_miji()
{
	object me,ob;
	me=this_player();
	
	if (me->query("class")!="huanxi")
	{
		command("say 你尚未受戒，不能入世修行，怕你心神有失！\n");
		command("say 你需要有入世修行的大恒心方可！\n");
		return "唉，滚滚红尘啊！\n";
	}
	command("say 既然你已经受戒将入世修行，那很好！\n");
	command("say 我这里有一本血刀经入门秘籍送给你，老祖说了要东西要送给有缘人!");
	ob=new("d/xuedao/obj/xdj_book1");
	
	//ob->set("owner",me->query("id"));

	ob->move(me);

	command("say 好好修炼，《血刀经》博大精深,武林第一！");
	return "血刀经天下第一！\n";
}