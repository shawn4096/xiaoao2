// hezudao.c (kunlun)

inherit NPC;
#include <ansi.h>
string ask_qin();
string ask_xunlei();
string ask_qinjian();
string ask_book4();
string ask_liangyi();
string ask_zfliangyi();
string ask_hundun();
string ask_diezhang();

void create()
{
	object ob;
	set_name("何足道", ({ "he zudao", "he" }));
	set("title", "昆仑派开山祖师");
	set("nickname", HIW"昆仑三圣"NOR);
	set("long",
		"他就是昆仑派开山祖师，号称琴剑棋三绝的“昆仑三圣”。\n"
		"长脸深目，瘦骨棱棱，约莫三十岁左右年纪。\n");
	set("gender", "男性");
	set("age", 35);
	set("attitude", "friendly");
	set("shen_type", 0);
	set("per", 27);
	set("str", 35);
	set("int", 40);
	set("con", 30);
	set("dex", 28);

	set("max_qi", 35000);
	set("max_jing", 8500);
	set("neili", 38000);
	set("eff_jingli", 7000);
	set("max_neili", 38000);
	set("jiali", 250);
	set("combat_exp", 15500000);
	set("unique", 1);
	set("score", 40000);
	set("quest/kl/xtwj/qinjian/pass",1);
	set("quest/kl/lyj/xunlei/pass",1);
	set("quest/kl/lyj/hundun/pass",1);
	set("quest/kl/lyj/liangyi/pass",1);

	set("qinji-book",1);
	set("chat_chance_combat", 85);
	set("chat_msg_combat", ({
  		(: perform_action, "sword.feihua" :),
		(: perform_action, "sword.jinzhen" :),

  		(: perform_action, "sword.hundun" :),
		(: perform_action, "sword.xunlei" :),
  		(: perform_action, "sword.liangyi" :),
		(: exert_function, "wuji" :),			
		(: exert_function, "qinjian" :),
  		(: perform_action, "sword.feipu" :),
	}));

	set("inquiry", ([
		"琴" : (: ask_qin :),
		"迅雷剑意" : (: ask_xunlei :),
		"琴剑双绝绝技" : (: ask_qinjian :),
		"焦尾琴" : (: ask_qin :),
		"琴技高级篇" : (: ask_book4 :),
		"反两仪决" : (: ask_liangyi :),
		"正反两仪诀" : (: ask_zfliangyi :),
		"混沌剑网" : (: ask_hundun :),
		//"昆仑掌蓄劲绝技" : (: ask_xu :),
		"昆仑掌叠掌" : (: ask_diezhang :),

	]));

	set_skill("art", 200);
	set_skill("literate", 200);

	set_skill("force", 500);
	set_skill("xuantian-wuji", 500);
	set_skill("dodge", 500);
	set_skill("taxue-wuhen", 500);
	//set_skill("xunlei-jian", 500);
	set_skill("strike", 500);
	set_skill("kunlun-zhang", 500);
	set_skill("parry", 500);
	set_skill("sword", 520);
	set_skill("cuff", 500);
	set_skill("zhentian-quan", 500);
	set_skill("liangyi-jue", 220);
	set_skill("leg", 500);
	set_skill("chuanyun-tui", 500);
	set_skill("liangyi-jian", 520);


	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("strike", "kunlun-zhang");
	map_skill("cuff", "zhentian-quan");
	map_skill("leg", "chuanyun-tui");
	map_skill("parry", "liangyi-jian");
	map_skill("sword", "liangyi-jian");
	prepare_skill("strike", "kunlun-zhang");

	add_temp("apply/sword", 150);
	add_temp("apply/parry", 100);
	add_temp("apply/force", 100);
	add_temp("apply/dodge", 100);
	add_temp("apply/strike", 100);
	add_temp("apply/damage", 75);

	create_family("昆仑派", 1, "开山祖师");
	setup();
	if (clonep()) {
		ob = unew(BINGQI_D("sword/jwqin"));
		if (!ob) ob = new(BINGQI_D("guzheng"));
		ob->move(this_object());
		ob->wield();
		carry_object("/d/kunlun/obj/pao1")->wear();
	}
}

void attempt_apprentice(object ob)
{
	object letter;
	if(ob->query_int() < 50 ) {
		command("say 弹琴下棋需要灵性极高的人才(50悟性)可以领悟其真谛，不致与武功背道而驰。");
		command("say "+RANK_D->query_respect(ob)+"还是先回去多读点书吧。");
		return;
	}
	if ((int)ob->query_skill("xuantian-wuji", 1) < 350) {
		command("say 玄天无极为本派根本。");
		command("say " + RANK_D->query_respect(ob)+"是否还应该先在玄天无极功（350）上多下点功夫？");
		return;
	}
	if ((int)ob->query_skill("liangyi-jian", 1) < 350) {
		command("say 两仪剑为本派根本。");
		command("say " + RANK_D->query_respect(ob)+"是否还应该先在两仪剑（350）上多下点功夫？");
		return;
	}
	if ((int)ob->query_skill("taxue-wuhen", 1) < 350) {
		command("say 踏雪无痕为本派根本。");
		command("say " + RANK_D->query_respect(ob)+"是否还应该先在踏雪无痕（350）上多下点功夫？");
		return;
	}
	if ((int)ob->query_skill("art", 1) < 150) {
		command("say 我昆仑三圣以琴棋剑著称，剑法倒也罢了。");
		command("say " + RANK_D->query_respect(ob)+
			"是否琴棋书画的修为浅了些呢（200）？");
		return;
	}
	if ((int)ob->query("max_neili", 1) < 6000) {
		command("say 内力不够（6000），一心二用则极容易走火入魔。");
		command("say " + RANK_D->query_respect(ob) +
			"是否还应该先好好修炼内力？");
		return;
	}
	if ( ob->query("gender") == "男性" && ob->query_skill("zhentian-quan", 1) < 350 ){
		command("say "+ RANK_D->query_respect(ob) +"是否还应该先在震天拳（350）上多下点功夫？");
		return;
	}
	if ( ob->query("gender") == "女性" && ob->query_skill("chuanyun-tui", 1) < 350 ){
		command("say "+ RANK_D->query_respect(ob) +"是否还应该先在穿云腿上（350）多下点功夫？");
		return;
	}
	if (!ob->query_temp("kl/baihe/fangxin"))
	{
		command("想要拜我为师？好，我这儿有一封信，需要送到少林寺，你把这事替我办了，我就收下你。\n");
		if (present("bai tie",ob))
		{
			command("say 哼，我已经派你去少林一趟，你怎么还不快去？");
			return;
		}
		if (ob->query_temp("klbs/askhe"))
		{
			command("say 哼，我已经派你去少林一趟，你为何如此懒啊？");
			return;
		}
		letter=new("d/kunlun/obj/baitie");
		letter->move(ob);
		
		ob->set_temp("klbs/askhe",1);
		
		command("say 好吧，我这儿有一封信，是写给少林掌门的，你就替我跑一趟，替我捎个口信。\n");
		return;

	}
	command("say 看来你也是性情中人，我就教你一些琴剑棋的知识吧。");
	command("recruit "+ob->query("id"));
	ob->set("appren_hezudao", 1);
	//预留判断下一个环节参数
	ob->delete_temp("klbs/askhe");
	ob->delete_temp("kl");
	ob->set("title",HIC"昆仑三圣亲传弟子"NOR);
}
void reset()
{
	object ob;

	if (clonep() && (ob = unew(BINGQI_D("sword/jwqin")))) {
		ob->move(this_object());
		command("wield jiaowei qin");
	}
}

string ask_qin()
{
	object me = this_player();

	if (me->query("family/master_name") != "何足道")
		return "这焦尾琴是我昆仑派的宝物，你并非我的传人，不能给你！";

	if (present("jiaowei qin",this_object())) {
		command("unwield jiaowei qin");
		command("give jiaowei qin to " + me->query("id"));
		return "这焦尾琴就给你了，你可要妥善保管好！";
	}
	return "你来晚了，焦尾琴我已经送与他人了。";
}
//琴剑quest入口。。

string ask_qinjian()
{
	object me = this_player();

	if (me->query("family/master_name") != "何足道"
		||me->query("family/master_id") != "he zudao")
		return "这琴剑双绝乃是我昆仑三圣的不传之谜，你并非我的传人，不能传授给你！";
	if (!me->query("family")
		|| me->query("family/family_name")!="昆仑派")
		return "你非我派弟子，来问此问题作甚？";
	if (!me->query("quest/kl/dichuan"))
	{
		return "你竟然不是昆仑嫡传弟子？！\n";
	}

	
    if( me->query_skill("xuantian-wuji", 1) < 350 )
		return "你的玄天无极造诣不够350，还无法领悟我派两仪剑法的精要所在！";
	
	if( me->query("quest/kl/xtwj/qinjian/pass") )
		return "你已经解密了这个秘密，又何故开此玩笑呢？";

	if ((int)me->query("int")<35)
		return "这琴剑双绝很看悟性，你先天悟性35，别来找我！\n";
	
	
	if( time()- me->query("quest/kl/xtwj/qinjian/time")<86400)
		return "嗯？你不是刚来请教过我这门绝技的奥秘吗？还是再努力段时间吧！";
	
	command("say 数十年前我曾受人之托，到少林寺去送一封信，当时遇到一位西域少林的高手。\n");
	command("say 另外还遇到一位少女，她之说她叫郭襄，父亲是郭靖，母亲是黄蓉。\n");
	command("say 当时我刚弹奏一首琴曲，乐颠颠的想让她品鉴，谁知道在少林山下的迎客亭遇到几个高手。\n");
	command("say 我把他们打发走了，用的就是玄天无极功的一心二用之术。\n");
	command("say 你如感兴趣，就再去哪儿看看，说不定有什么收获。\n");
    me->set_temp("qinjian/askhe",1);

	return "这琴剑绝技很是看悟性，乖徒儿能否领悟看你的造化了！";
	

	
}
//ask xunlei 剑意
string ask_xunlei()
{
	object me, ob;
	int i,j,x;
	
	ob = this_object();
	me = this_player();       

	if (!me->query("family")
		|| me->query("family/family_name")!="昆仑派")
		return "你非我派弟子，来问此问题作甚？";

	if (!me->query("quest/kl/dichuan"))
	{
		return "你竟然不是昆仑嫡传弟子？！\n";
	}

    if( me->query_skill("xuantian-wuji", 1) < 300 )
		return "你的玄天无极造诣不够300，还无法领悟我派两仪剑法的精要所在！";
	
	if( me->query("quest/kl/lyj/xunlei/pass") )
		return "你已经解密了这个迅雷剑诀，又何故开此玩笑呢？";

	if ((int)me->query("int")<30)
		return "这迅雷剑诀很看悟性，你先天悟性30，别来找我！\n";
	
	
	if( time()- me->query("quest/kl/lyj/xunlei/time")<86400)
		return "嗯？你不是刚来请教过我这门绝技的奥秘吗？还是再努力段时间吧！";

   
	message_vision(HIC"$N严肃的看着$n，慢慢说道：“我派的迅雷剑诀讲究的以迅雷不及掩耳之势连出数招，我本来已经创立了一门迅雷剑法，\n"
						"供初期弟子使用，但你既然到达如此程度，我就传给你这迅雷剑意，我给你演示一遍，看你自己的悟性了。\n"+
				   HIR"\n\n\n$N缓缓抽出一柄长剑，一招既出，后招连绵不绝，疾驰如电，迅捷无比。看的$n眼花缭乱\n"NOR,this_object(),me);
	
 
    i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	j=random(me->query("kar"));
	x=random(me->query("int"));
	command("say 本门迅雷诀讲究的动若闪电，迅捷无比，是这门剑法的精要所在。\n");
	command("pat "+me->query("id"));
	if( i<4
		&& me->query("kar")<31
	//	&& x >= 32
		&& j >= 26 ) 
	{
		tell_object(me,HIY"\n你听了何足道的亲自指点，联想起早期自己所用迅雷剑的种种心得，两下印照。\n"NOR);
		tell_object(me,HIG"\n你剑招连连，宛如长江大河，滔滔不绝，一出手剑招即为连环招式，下意识的出招。\n"
			             +"招式看似繁复，但大多数招式你已经了然若胸，信手拈来，连绵不绝。\n"
						 +"你终于领悟了这门迅雷绝技的运用法门。心中大喜。\n"NOR);
		me->set("quest/kl/lyj/xunlei/pass",1);
		log_file("quest/lyjxunlei", sprintf("%8s(%8s) 失败%d次后，学到迅雷剑诀绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/xunlei/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "恭喜解密迅雷剑诀绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/lyjxunlei", sprintf("%8s(%8s) 解密迅雷剑诀绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/xunlei/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了何足道的指点，可是对两仪剑决迅雷剑诀的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/lyj/xunlei/fail",1);
		me->set("quest/kl/lyj/xunlei/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密两仪剑之迅雷剑意失败"+me->query("quest/kl/lyj/xunlei/fail")+"次。\n";
	}


}

string ask_book4()
{
	mapping fam;
	object ob;

	if (!(fam = this_player()->query("family"))
		 || fam["generation"] >4
		 || fam["family_name"] != "昆仑派")
	   return RANK_D->query_respect(this_player())+ "与本派素无来往，不知此话从何谈起？";  
		
		if (this_object()->query("qinji-book")<1)
		{
			 return "你来晚了，本派心经已被你师兄拿走了。";
		}
		this_object()->add("qinji-book",-1);
		ob = unew("/d/kunlun/obj/string-book4.c");     
		ob->move(this_player());

		return "我这里有本「琴技高级技巧篇」，你拿回去好好钻研，有空多来找我哦";
}
//两仪quest
string ask_liangyi()
{
	mapping fam;
	object ob;
	object me=this_player();

	if (!(fam = this_player()->query("family"))
	 || fam["master_name"] != "何足道"
	 || fam["family_name"] != "昆仑派")
	   return RANK_D->query_respect(this_player())+ "与本派素无来往，不知此话从何谈起？";  
	if( me->query_skill("xuantian-wuji", 1) < 350 )
		return "你的玄天无极造诣不够350，还无法领悟我派两仪剑法的精要所在！";
	if( me->query_skill("liangyi-jue", 1) < 200 )
		return "你的正两仪决造诣不够200，还无法领悟我派正两仪剑法的精要所在！";
	if (!me->query("quest/kl/dichuan"))
	{
		return "你竟然不是昆仑嫡传弟子？！\n";
	}
	if( me->query("quest/kl/lyj/liangyi/pass") )
		return "你已经解密了这个两仪剑诀，又何故开此玩笑呢？";
	
	
	if ((int)me->query("int")<30)
		return "这两仪剑诀很看悟性，你先天悟性30，别来找我！\n";
	
	
	if( time()- me->query("quest/kl/lyj/liangyi/time")<86400)
		return "嗯？你不是刚来请教过我这门绝技的奥秘吗？还是再努力段时间吧！";

   
	message_vision(HIC"$N拍了拍$n的头，说道：“我派的两仪剑决博大精深，正两仪剑讲究的是堂堂正正，奇正结合。\n"+
						"若能领悟也可以纵横江湖，与群雄争一长短，但这不过只是其一。你若是能和华山派的反两仪决。\n"+
						"想融合，那么这门神技将发生质的变化，威力无穷，你若是感兴趣，就去一趟华山后山，去跟。\n"+
						"华山二老请教，我昆仑派和他们曾有过交情，若能习得反两仪的奥妙，则正两仪剑将彻底大成。\n"+
				   HIY"\n\n\n$N仿佛陷入了沉思，但$n分明感觉到$N似乎眼中剑气纵横，心中不由地对这门剑法极为神往！\n"NOR,this_object(),me);
	me->set_temp("liangyi/askhe",1);
	return "去吧，这两仪决关系重大，也许这就是你的富源！\n";

}
//正反两仪解密入口
string ask_zfliangyi()
{
	mapping fam;
	object ob;
	int i,j,k,total;
	object me=this_player();

	if (!(fam = this_player()->query("family"))
	 || fam["master_name"] != "何足道"
	 || fam["family_name"] != "昆仑派")
	   return RANK_D->query_respect(this_player())+ "与本派素无来往，不知此话从何谈起？";  
	if( me->query_skill("xuantian-wuji", 1) < 350 )
		return "你的玄天无极造诣不够350，还无法领悟我派两仪剑法的精要所在！";
	if( me->query_skill("liangyi-jue", 1) < 200 )
		return "你的正两仪决造诣不够200，还无法领悟我派正两仪剑法的精要所在！";
	if( me->query_skill("fanliangyi-jue", 1) < 200 )
		return "你的反两仪决造诣不够200，还无法领悟我派正两仪剑法的精要所在！";
	if (!me->query("quest/kl/lyj/liangyi/jue"))
		return "让你向高矮两长老请教，你总是偷懒，现在还无法领悟我派正两仪剑法的精要所在！";
	if (!me->query("quest/kl/dichuan"))
	{
		return "你竟然不是昆仑嫡传弟子？！\n";
	}

	if( me->query("quest/kl/lyj/liangyi/pass") )
		return "你已经解密了这个两仪剑诀，又何故开此玩笑呢？";
	
	if (time()-me->query("quest/kl/lyj/liangyi/time")<86400)
		return "武功贪多不烂，你来的太勤快了？\n";

	if ((int)me->query("int")<40)
		return "这两仪剑诀很看悟性，你先天悟性40，别来找我！\n";
	 i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	k=random(me->query("kar"));
	//total=me->query("int")+me->query("str")+me->query("dex")+me->query("con");
	j=random(me->query("int"));
	if (i<3
		&& me->query("kar")<31
		&& j>40
		&& k>27)
	{
	
		command("laugh "+me->query("id"));
		command("chat* pat "+me->query("id"));
		command("chat 从今后"+me->query("name")+"就是我昆仑三圣的真传弟子，还望武林同道多加照付！");
		command("chat* smile ");
		command("chat 我大昆仑从此崛起于西域！唯我独尊！");
		command("say 至此后，你对于我两仪剑的领悟已经是融会贯通了，还望你今后多家努力，为我大昆仑增光添彩。");
		command("say 我昆仑正两仪剑至此大成，你好自为之。");
		me->set("quest/kl/lyj/liangyi/pass",1);
		me->set("title",HIG"两仪剑真传"NOR);
		log_file("quest/zfliangyi", sprintf("%8s(%8s) 失败%d次后，学到正反两仪彻底融会贯通。随机数j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/liangyi/fail"),j,me->query("kar"),me->query("combat_exp")) );

	}
	else {
		log_file("quest/zfliangyi", sprintf("%8s(%8s) 解密正反两仪诀失败%d次！。随机数j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/liangyi/fail"),j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIG"你听了何足道的指点，可是对正反两仪诀的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		command("angry "+me->query("id"));
		me->add("quest/kl/lyj/liangyi/fail",1);
		me->set("quest/kl/lyj/liangyi/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密正反两仪诀失败"+me->query("quest/kl/lyj/liangyi/fail")+"次。\n";
	


	}
	return "哈哈！";
}
//混沌剑网解密
//进入朝露台领悟混沌剑网

string ask_hundun()
{
	mapping fam;
	object ob;
	object me=this_player();
	if (me->query("killer"))
	{
		return "你一个pker，来此作甚？\n";
	}
	if (!(fam = this_player()->query("family"))
	 || fam["master_name"] != "何足道"
	 || fam["family_name"] != "昆仑派")
	   return RANK_D->query_respect(this_player())+ "与本派素无来往，不知此话从何谈起？";  
	if( me->query_skill("xuantian-wuji", 1) < 500 )
		return "你的玄天无极造诣不够500，还无法领悟我派两仪剑法的精要所在！";
	if( me->query_skill("liangyi-jian", 1) < 500 )
		return "你的正两仪剑造诣不够500，还无法领悟我派正两仪剑法的精要所在！";
	if( me->query("quest/kl/lyj/hundun/pass") )
		return "你已经解密了这个两仪剑诀，又何故开此玩笑呢？";
	if( time()- me->query("quest/kl/lyj/hundun/time")<86400)
		return "嗯？你不是刚来请教过我这门绝技的奥秘吗？还是再努力段时间吧！";

	if ((int)me->query("int")<40)
		return "这两仪剑诀很看悟性，你先天悟性40，别来找我！\n";
	
	command("say 这混沌剑网乃是我当初在朝露台一处异地所悟，寻常地点根本无法修得。");
	command("say 既然你想修炼，那我就指点你些诀窍，然后你要自己去领悟。");
	command("say 至于你是否能领悟，就看你的悟性了。");
	message_vision(YEL"$N只觉一股大力传来，宛如腾云驾雾般飞起。\n"NOR,me);
	me->set_temp("hundun/askhe",1);
	me->move("d/kunlun/zhaolutai");
	return "你仰面朝天，只觉得眼前碧空如洗，远处云卷云舒，身下万丈深渊！\n";
}

//昆仑叠掌

string ask_diezhang()
{
	object me;
	int i,j;
	me=this_player();

	if (me->query("family/family_name")!="昆仑派")
	{
		return "你的不是昆仑派，难道不怕死么？！\n";
	}
	if (me->query_skill("kunlun-zhang",1)< 400)
	{
		return "你的昆仑掌等级不足500，告诉你也没用！\n";
	}
	if (me->query("quest/kl/klz/diezhang/pass"))
	{
		return "你的蓄劲技巧已经解开了”！\n";
	}
	if (time()-me->query("quest/kl/klz/diezhang/time")<86400)
	{
		return "你来的太频繁了，明天再来！\n";
	}

	message_vision(HIC"$N严肃的看着$n，慢慢说道：“我派的昆仑掌讲究的臂力和功力深厚，和其他门派都不太相同。\n"
						"你既然到达如此程度，我就传给你这招叠掌的奥秘，我给你演示一遍，看你自己的悟性了。\n"+
				   HIR"\n\n\n$N纵身跃起，双掌运功发力，看的$n心旌神摇！\n"NOR,this_object(),me);
	
 
    i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	j=random(me->query("kar"));
	command("say 你看懂了么。\n");
	command("pat "+me->query("id"));
	if( i<5
		&& me->query("kar")<31
		&& j >= 25 ) 
	{
		tell_object(me,HIY"\n你听了的何足道师傅的亲自指点，联想起早期自己所用昆仑掌的种种心得，两下印照。\n"NOR);
		tell_object(me,HIG"\n你终于领悟了这门昆仑掌叠掌的运用法门。心中大喜。\n"NOR);
		me->set("quest/kl/klz/diezhang/pass",1);
		log_file("quest/klzdiezhang", sprintf("%8s(%8s) 失败%d次后，学到昆仑掌叠掌,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/klz/diezhang/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "恭喜解密昆仑掌叠掌绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/klzdiezhang", sprintf("%8s(%8s) 解密昆仑掌叠掌绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/klz/diezhang/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了何足道师傅的指点，可是对昆仑掌叠掌的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/klz/diezhang/fail",1);
		me->set("quest/kl/klz/diezhang/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密昆仑掌叠掌失败"+me->query("quest/kl/klz/diezhang/fail")+"次。\n";
	}


}