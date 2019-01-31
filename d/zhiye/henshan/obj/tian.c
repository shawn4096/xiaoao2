#include <ansi.h>
inherit NPC;
void greeting(object ob);
int accept_fight(object ob);
int ask_kuaidao();
string ask_yilin();
string ask_linghuchong();


void create()
{
	seteuid(getuid());
	set_name("田伯光", ({ "tian boguang", "tian","boguang" }));
	set("long", "他一身飘逸的白色长衫，风流儒雅。\n");
	set("nickname", HIM "万里独行" NOR);
	set("gender", "男性");
	set("age", 37);
	set("attitude", "peaceful");
	set("shen_type", -1);

       set("per", 23);
	set("str", 25);
	set("int", 24);
	set("con", 25);
	set("dex", 35);

	set("qi", 25000);
	set("max_qi", 25000);	
	set("combat_exp", 12500000);
	set("score", 40000);

	set("jing", 3800);
	set("max_jing", 3800);

	set("jingli", 4800);
	set("max_jingli", 4800);
	set("eff_jingli",4800);

	set("neili", 20000);
	set("max_neili", 20000);
	
	set("jiali", 200);
	set("quest/hmy/tmd/kuaidao/pass",1);

	set_skill("blade",500);
	set_skill("parry", 450);
	set_skill("force", 450);
	set_skill("strike", 500);
	set_skill("dodge", 450);

	set_skill("lingxu-bu", 450);
	set_skill("tianmo-jue", 200);

	set_skill("tianmo-zhang", 450);
	set_skill("tianmo-gong", 450);
	set_skill("tianmo-dao", 500);

	map_skill("dodge", "lingxu-bu");
	map_skill("parry", "tianmo-dao");
	map_skill("blade", "tianmo-dao");
    map_skill("strike","tianmo-zhang");
	map_skill("force","tianmo-gong");
	prepare_skill("strike","tianmo-zhang");
    set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
                (: perform_action, "blade.pi" :),
				(: perform_action, "blade.jingshen" :),
				(: perform_action, "blade.huashen" :),
				(: perform_action, "blade.kuaidao" :),
				(: exert_function, "tianmo" :),
				(: exert_function, "jieti" :),
        }) );
		
	set("chat_chance", 10);
	set("chat_msg", ({
		CYN "田伯光笑道：尼姑也没关系嘛，蓄起头发，两个月就是小美人了。\n" NOR,
		CYN "我有一项绝技就是闻香识女人，只要我闻过一遍，方圆十丈之内我就能找到她。\n" NOR,
		CYN "万里独行，岂是随便称呼的？。\n" NOR,
		CYN "令狐冲是条汉子？。\n" NOR,

	}) );
	set("inquiry",([
		"狂风快刀绝技" : (: ask_kuaidao :),
		"仪琳" : (: ask_yilin :),
		"令狐冲" : (: ask_linghuchong :),
		//"光大我派" : (: ask_dragon :),
        ]) );

	setup();
	carry_object(BINGQI_D("blade"))->wield();
	carry_object(ARMOR_D("cloth"))->wear();
	add_money("gold",10);
}

void init()
{
	object ob;

	::init();

	if( interactive(ob = this_player()) && !is_fighting() ) 
       {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}
void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	if ((string)ob->query("gender")=="女性")
	{
	if (ob->query("age")<26) 
		say(CYN "田伯光笑道：小娘子，你有沉鱼……沉鱼落雁之容。这家回雁楼就是为你开的。咱们喝个大醉，大家快活快活罢。\n" NOR);     
	else 
		say(CYN "田伯光笑道：妙极，妙极，可惜太老了点，我可没胃口。\n" NOR);     
	}
	else 
		say(CYN "田伯光笑着招招手：这位"+RANK_D->query_respect(ob) + "来喝"
                    "两杯，这个小尼姑嘛，反正也没什么事，就让她坐着就是。\n" NOR);									
					
	return;
}

int accept_fight(object ob)
{
	if ((string)ob->query("gender") == "女性")
	{
		write(CYN "田伯光笑道：花姑娘？杀了太可惜了的。\n" NOR);
		return 0;
        }
	return 1;
}
string ask_yilin()
{
	object me=this_player();
	if (me->query("family/family_name")!="日月神教")
	{
		command("say 你不是我大日月神教弟子，来此作甚？\n");
		command("blade "+me->query("id"));
		return "哼！";
	}
	if (me->query("quest/hmy/tmd/kuaidao/pass"))
	{
		command("say 你已经解开了这刀法绝技，来此消遣本大爷我么？\n");
		command("blade "+me->query("id"));
		return "哼！";
	}
	if (me->query_skill("tianmo-dao",1)<450)
	{
		command("say 你的天魔刀不足450，来此也理解不了？\n");
		command("blade "+me->query("id"));
		return "哼！";
	}
	if (me->query("str")<35)
	{
		command("say 你的先天臂力不足35，来此也理解不了？\n");
		command("blade "+me->query("id"));
		return "哼！";
	}

	command("say 当初我在路上遇到仪琳小师傅，一见倾心。\n");
	if (present("yi lin",environment(me)))
	{
		command("say 喏，这位小美女师太不正坐在我身边么？\n");
		command("18mo ");
	}
	//command("say 不过后来遇到了华山首徒令狐冲，他虽然功夫不如我，但我到很敬重他！\n");
	command("say 就在我和仪琳师妹在一起畅谈人生和理想的时候，来几个青城派的苍蝇！\n");
	me->set_temp("kuaidao/askyilin",1);
	command("say 你愿意替我抵挡住这一阵么？"+HIY"annswer yes |answer no\n");

	return "这些苍蝇居然在武林中号称“青城四秀”，我看是“青城四兽”还差不多！\n";
}


string ask_linghuchong()
{
	object me=this_player();
	
	if (!me->query_temp("kuaidao/answeryes"))
	{
		command("say 上次我让你办理的一点小事你都不搭理我，滚！！\n");

		command("say 我正在和仪琳师太聊天，谈理想，谈人生，别来骚扰我！\n");
		return "一呀摸，摸到仪琳妹妹的头发边.......!\n";
	}
	if (present("hou renying",environment(me)))
	{
		command("say 侯人英这四兽之一还在哪儿旁边，我心烦！\n");
		return "一呀摸，摸到仪琳妹妹的头发边.......!\n";
	}
	if (present("hong renxiong",environment(me)))
	{
		command("say 洪人雄这四兽之一还在哪儿旁边，我心烦！\n");
		return "一呀摸，摸到仪琳妹妹的头发边.......!\n";
	}
	if (present("yu renhao",environment(me)))
	{
		command("say 于人豪这四兽之一还在哪儿旁边，我心烦！\n");
		return "一呀摸，摸到仪琳妹妹的头发边.......!\n";
	}
	if (present("yu renjie",environment(me)))
	{
		command("say 于人杰这四兽之一还在哪儿旁边，我心烦！\n");
		return "一呀摸，摸到仪琳妹妹的头发边.......!\n";
	}
	if (present("yuling zi",environment(me)))
	{
		command("say 泰山老道玉灵子这臭道士还在哪儿旁边，我心烦！\n");
		return "一呀摸，摸到仪琳妹妹的头发边.......!\n";
	}

	command("say 令狐冲乃是华山首徒，我和他当时仅仅见过数面！\n");
	command("say 当时令狐冲和我一番激斗，最后他用计将我僵住！\n");
	command("say 你愿意替我来和令狐冲较量一番么？你可以通过"HIY"answer yes | no来回答！\n");
	me->delete_temp("kuaidao/askyilin");
	if (!present("yi lin",environment(me)))
	{
		command("say 喏，这位小美女师太不正坐在我身边么？\n");
		command("18mo ");
	}
	command("say 令狐冲当时说他坐着打天下第二，我不服气，就让他当场对战！\n");
	//command("say ");
	me->set_temp("kuaidao/asklhc",1);
//	call_out("qingcheng_dizi",3,me);
	return "令狐冲说他这门剑法叫“茅厕剑法”，可以和我的快刀绝技一战！\n";

}


int ask_kuaidao()
{
	int i,j,k;
	object me=this_player();
	if (!me->query_temp("kuaidao/answerlhcyes"))
	{
		command("say 你我非亲非故，我凭什么传授你[快刀绝技]？！\n");
		return 1;
	
	}
	if (!me->query("quest/hmy/tmd/pass"))
	{
		command("say 你天魔刀的基础没打好，连化身万千绝招都不会，来此也白搭。\n");
		return 1;
	}
	if (present("hou renying",environment(me)))
	{
		command("say 侯人英这四兽之一还在哪儿旁边，我心烦！\n");
		return 1;
	}
	if (present("hong renxiong",environment(me)))
	{
		command("say 洪人雄这四兽之一还在哪儿旁边，我心烦！\n");
		return 1;
	}
	if (present("yu renhao",environment(me)))
	{
		command("say 于人豪这四兽之一还在哪儿旁边，我心烦！\n");
		return 1;
	}
	if (present("yu renjie",environment(me)))
	{
		command("say 于人杰这四兽之一还在哪儿旁边，我心烦！\n");
		return 1;
	}
    
	if (present("linghu chong",environment(me)))
	{
		command("say 令狐冲在哪儿旁边，我心烦！\n");
		return 1;
	}
	if (me->query("family/family_name")!="日月神教")
	{
		command("say 你不是我大日月神教弟子，来此作甚？\n");
		command("blade "+me->query("id"));
		return 1;
	}
	if (me->query("quest/hmy/tmd/kuaidao/pass"))
	{
		command("say 你已经解开了这刀法绝技，来此消遣本大爷我么？\n");
		command("blade "+me->query("id"));
		return 1;
	}
	if (me->query_skill("tianmo-dao",1)<450)
	{
		command("say 你的天魔刀不足450，来此也理解不了？\n");
		command("blade "+me->query("id"));
		return 1;
	}
	if (time()-me->query("quest/hmy/tmd/kuaidao/time")<86400)
	{
		command("say 你来得太频繁了？\n");
		command("blade "+me->query("id"));
		return 1;
	}
	
	message_vision(HIY"田伯光？”\n"NOR,me);
	 j = 20;
     if(me->query("m-card-vip")) j =  18;
     if(me->query("y-card-vip")) j =  15;
     if(me->query("buyvip"))     j =  10;
	i=random(j);
	
	k=random(me->query("kar"));
	if (me->query("kar")<31
		&&k>26
		&&i<4)
	{
       message_vision(HIC"\n\n$N恍然大悟，欢然道：“那要全力以赴，刀法奇快，使对方来不及抵挡。”\n"
	   +"田伯光点头说道，“这一招全凭一口真气流转，快速出招，能有多快要多快，否则，对方趁势反击，你就危险了。”\n"NOR,me);
	    message_vision(HIR"\n\n恭喜你！你终于领悟了降龙十八掌的精髓武技，习得亢龙有悔绝技。\n"NOR,me);
		command("chat* haha"+me->query("id"));
	   command("chat "+me->query("name")+"用了这么长时间终于领悟了快刀绝技。");
	   command("chat "+"我万里独行田伯光的快刀绝技终于有传人了！。\n");
	   command("chat* congra"+me->query("id"));
	  
	   log_file("quest/tmdkuaidao",sprintf("%s(%s) 在衡阳回雁楼，得到田伯光的亲自指点快刀绝技。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),k,i,me->query("quest/hmy/tmd/kuaidao/fail"),me->query("combat_exp"),me));
	   
	   me->set("quest/hmy/tmd/kuaidao/pass",1);
	   me->set("title",HIW"快刀刀法传人"NOR);
	   me->start_busy(1);

	   return 1;
	}
	else
	{
		message_vision(HIC"\n\n$N虽然听田伯光说了快刀绝技的精要，但对于如何使用的劲力法门一时之间却是难以理解。\n"
		+"天魔刀威力并没有发挥出来，看来你还是有待于重新跟田伯光学习了。\n"NOR,me);
		message_vision(HBWHT HIB"解密天魔刀快刀绝技失败！"NOR,me);
		log_file("quest/tmdkuaidao",sprintf("%8s%-10s得到田伯光的亲自指点快刀绝技，但并没有成功，尚须努力。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),k,i,me->query("quest/hmy/tmd/kuaidao/fail"),me->query("combat_exp"),me));
		me->add("quest/hmy/tmd/kuaidao/fail",1);
		me->set("quest/hmy/tmd/kuaidao/time",time());
		me->start_busy(1);
		return 1;
	}     
	return 1;
}
