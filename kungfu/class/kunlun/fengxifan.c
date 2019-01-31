// fengxifan.c (kunlun) 鹿鼎记，一剑无血冯锡范
// by sohu
// 新增红砂掌和一剑无血绝技

inherit NPC;
#include <ansi.h>
string ask_wei();
string ask_tiandi();
string ask_chen();
string ask_hongsha();
string ask_wuxue();
void create()
{
	object ob;
	set_name("冯锡范", ({ "feng xifan", "feng" }));
	set("title", "昆仑派长老");
	set("nickname", HIR"一剑无血"NOR);
	set("long",
		"他就是昆仑派高手，兼任昆仑派长老，号称“一剑无血”。\n"
		"专以剑尖点人死穴，由于气功练到了“由利返钝”的高深境界\n"
		"被点之人决不出血，因此得名\n他长脸深目，瘦骨棱棱，约莫五十岁左右年纪。\n");
	set("gender", "男性");
	set("age", 55);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("per", 27);
	set("str", 30);
	set("int", 25);
	set("con", 30);
	set("dex", 28);

	set("max_qi", 35000);
	set("max_jing", 6500);
	set("neili", 28000);
	set("eff_jingli", 7000);
	set("max_neili", 28000);
	set("jiali", 250);
	set("combat_exp", 13500000);
	set("unique", 1);
	set("score", 40000);
//	set("quest/kl/xtwj/qinjian/pass",1);
	set("quest/kl/xlj/wuxue/pass",1);
	set("quest/kl/klz/hongsha/pass",1);

	set("chat_chance_combat", 85);
	set("chat_msg_combat", ({
  		(: perform_action, "sword.podi" :),
  		(: perform_action, "sword.sanqiu" :),
		(: perform_action, "sword.benlei" :),
  		(: perform_action, "sword.dianxue" :),
		(: exert_function, "wuji" :),			
  		(: perform_action, "dodge.taxue" :),
	}));

	set("inquiry", ([
		"韦小宝" : (: ask_wei :),
		"天地会" : (: ask_tiandi :),
		"陈近南" : (: ask_chen :),
		"一剑无血绝技" : (: ask_wuxue :),
		"红砂掌绝技" : (: ask_hongsha :),

	]));

	set_skill("art", 200);
	set_skill("literate", 200);

	set_skill("force", 500);
	set_skill("xuantian-wuji", 500);
	set_skill("dodge", 500);
	set_skill("taxue-wuhen", 500);
	set_skill("xunlei-jian", 520);
	set_skill("strike", 500);
	set_skill("kunlun-zhang", 500);
	set_skill("parry", 500);
	set_skill("sword", 520);
	set_skill("cuff", 500);
	set_skill("zhentian-quan", 500);
	set_skill("liangyi-jue", 220);
	set_skill("leg", 500);
	set_skill("chuanyun-tui", 500);


	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("strike", "kunlun-zhang");
	map_skill("cuff", "zhentian-quan");
	map_skill("leg", "chuanyun-tui");
	map_skill("parry", "xunlei-jian");
	map_skill("sword", "xunlei-jian");
	prepare_skill("strike", "kunlun-zhang");

	add_temp("apply/sword", 150);
	add_temp("apply/parry", 100);
	add_temp("apply/force", 100);
	add_temp("apply/dodge", 100);
	add_temp("apply/strike", 100);
	add_temp("apply/damage", 75);

	create_family("昆仑派", 1, "门中长老");
	setup();
	if (clonep()) {
		ob = unew(BINGQI_D("sword/gangjian"));
		if (!ob) ob = new(BINGQI_D("changjian"));
		ob->move(this_object());
		ob->wield();
		carry_object("/d/kunlun/obj/pao1")->wear();
	}
}
void init()
{
	object me=this_player();
	if (me->query_temp("quest/kl/klz/hongsha/lugive")
		&&me->query_temp("quest/kl/klz/hongsha/kegive")
		&&me->query_temp("quest/kl/klz/hongsha/yingive")
		&&me->query_temp("quest/kl/klz/hongsha/langive")
		&&me->query_temp("hsz/shedu")
		&&me->query_temp("hsz/chanchudu")
		&&me->query_temp("hsz/蜘蛛毒")
		&&me->query_temp("hsz/蝎子毒"))
	{
		command("laugh "+me->query("id"));
		command("pat "+me->query("id"));
		command("thumb "+me->query("id"));
		command("say 既然你已经搜集了这五种毒素，我就替你完成这红砂掌的修炼。\n");
		message_vision(HIR"$N运起玄天无极功，劲气涌动，双手贴在$N的后背，将这四股毒气瞬间融合在一起！\n"NOR,me);
		me->delete_temp("hsz/shedu");
		me->delete_temp("hsz/chanchudu");
		me->delete_temp("hsz/蜘蛛毒");
		me->delete_temp("hsz/蝎子毒");
		me->set("quest/kl/klz/hongsha/du",1);
		return;
	}
}

void attempt_apprentice(object ob)
{
	object letter;
	if(ob->query_con() < 50 ) {
		command("say 我的功夫全凭精湛的内功(50根骨)可以领悟其真谛。");
		command("say "+RANK_D->query_respect(ob)+"还是先回去多读点书吧。");
		return;
	}
	if ((int)ob->query_skill("xuantian-wuji", 1) < 300) {
		command("say 我的功夫全凭精湛的内功。");
		command("say " + RANK_D->query_respect(ob)+"是否还应该先在玄天无极功（300）上多下点功夫？");
		return;
	}
	if ((int)ob->query_skill("art", 1) < 150) {
		command("say 我昆仑三圣以琴棋剑著称，剑法倒也罢了。");
		command("say " + RANK_D->query_respect(ob)+
			"是否琴棋书画的修为浅了些呢（150）？");
		return;
	}
	if ((int)ob->query("max_neili", 1) < 4000) {
		command("say 内力不够（4000），一心二用则极容易走火入魔。");
		command("say " + RANK_D->query_respect(ob) +
			"是否还应该先好好修炼内力？");
		return;
	}
	if ( ob->query("gender") == "男性" && ob->query_skill("zhentian-quan", 1) < 250 ){
		command("say "+ RANK_D->query_respect(ob) +"是否还应该先在震天拳（250）上多下点功夫？");
		return;
	}
	if ( ob->query("gender") == "女性" && ob->query_skill("chuanyun-tui", 1) < 250 ){
		command("say "+ RANK_D->query_respect(ob) +"是否还应该先在穿云腿上（250）多下点功夫？");
		return;
	}
	/*if (ob->query_skill("kunlun-zhang", 1) < 250 ){
		command("say "+ RANK_D->query_respect(ob) +"是否还应该先在昆仑掌上（250）多下点功夫？");
		return;
	}*/

	if (!ob->query("quest/kl/baifxf/baohu"))
	{
		if (ob->query("quest/kl/baifxf/time")&&time()-ob->query("quest/kl/baifxf/time")<86400)
		{
			command("say 你来的太频繁了！\n");
			return;

		}
		command("say 既然你有此心，就替我去福州小岛跑一趟！\n");
		command("say 我听说最近有大批刺客对郑可爽公子意图不轨，你去替我保护好郑公子！\n");
		command("say 郑公子身份金贵，前途不可限量，你切不偷懒！\n");
		command("say 据我所知，这批刺客数量极多，功力高深，你须得在1个时辰内速战速决！\n");
		command("say 如果郑公子有所闪失，以后休要再来面见我！\n");
		ob->set_temp("quest/kl/baifxf/start",1);
		return;
	}
	
	command("say 看你替我完成任务的基础上，你就随我修炼一段时间吧。");
	command("recruit "+ob->query("id"));
	ob->set("appren_fengxifan", 1);
	ob->set("title", HIC"冯锡范真传弟子"NOR);
	return;
}

string ask_wei()
{
	object me = this_player();

	command("say 数年前，韦小宝冒充神龙教的使者，到处招摇撞骗。\n");
	command("say 后来他跟我作对，一直跟我捣乱，后来听说他加入了天地会。\n");
	me->set_temp("quest/kl/xjl/wuxue/askfeng",1);

	me->start_busy(1);

	return "居然加入天地会，跟官府斗能有好下场？！\n";
}

string ask_tiandi()
{
	object me = this_player();
	if (!me->query_temp("quest/kl/xjl/wuxue/askfeng"))
	{
		command("say 没事别来骚扰我，滚，老子烦得很！\n");
	}

	command("say 天地会是民间的一个反动组织，聚集了一帮江湖匪徒。\n");
	command("say 天地会的前身是台湾郑成功的黑社会组织，后来为陈近南所控制。\n ");

	command("heng ");

	me->set_temp("quest/kl/xjl/wuxue/asktiandi",1);
	me->add_busy(1);
	return "我真不服气，凭我大昆仑的迅雷剑，谁是我对手！\n";
}

string ask_chen()
{
	object me = this_player();
	if (!me->query_temp("quest/kl/xjl/wuxue/asktiandi"))
	{
		command("say 没事别来骚扰我，滚，老子烦得很！\n");
	}
	command("say 虽然我没跟他交过手，据说武功天下第一。\n");
	command("heng ");
	command("say 英雄不识陈近南，便左英雄也枉然？\n");
	command("say 总有一日，陈老狗要死在我一剑无血之手！\n");
	me->set_temp("quest/kl/xjl/wuxue/askchen",1);
	me->add_busy(1);
	return "嘿嘿，一剑无血的外号岂是轻易叫的！\n";
}


int accept_object(object who, object obj)
{
	object obb;
	obb=obj->query("kill_by");
	if (obj->query("id")=="shouji" 
		&&obj->query("name")=="胡逸之的首级" 
		&& obb->query("id")==who->query("id"))
	{
		command("say 好大的一颗头颅！你为我杀了百胜刀王胡逸之这狗贼，终于了却我的一番心事？\n");
		command("laugh ");
		command("chat 哈哈！我大昆仑横扫天下，何愁江湖人物不再归顺与我？\n");
		who->set("quest/kl/xlj/killhu",1);
		destruct(obj);
		return 1;
	}
	
	if (obj->query("id")=="shouji" 
		&&obj->query("name")=="陈近南的首级" 
		&& obb->query("id")==who->query("id"))
	{
		command("say 好大的一颗头颅！你为我杀了陈近南这狗贼，终于了却我的一番心事？\n");
		command("laugh ");
		command("chat 哈哈！我大昆仑横扫天地会这群匪徒，何愁江湖人物不再归顺与我？\n");
		who->set("quest/kl/xlj/killchen",1);
		destruct(obj);
		return 1;
	}
}
//ask 红砂掌


string ask_hongsha()
{
	object me, ob;
	int i,j;
	
	ob = this_object();
	me = this_player();       

	if (!me->query("family")
		|| me->query("family/family_name")!="昆仑派")
		return "你非我派弟子，来问此问题作甚？";

	if (!me->query("appren_fengxifan"))
		return "你非我亲传弟子，来问此问题作甚？";
	if (!me->query("quest/kl/dichuan"))
	{
		return "你竟然不是昆仑嫡传弟子？！\n";
	}

    if( me->query_skill("kunlun-zhang", 1) < 300 )
		return "你的昆仑掌造诣不够300，还无法领悟我派红砂掌的精要所在！\n";
	
	if( me->query("quest/kl/klz/hongsha/pass") )
		return "你已经解密了这个红砂掌绝技，又何故开此玩笑呢？\n";
	
	if (!me->query("quest/kl/klz/hongsha/du"))
	{
		if (!me->query_temp("hsz/shedu"))
		{
			command("say 练习红砂掌需要将蛇毒炼入手掌，劲气催使之下，方可修习。\n");
			me->set_temp("quest/kl/klz/hongsha/asklu",1);
			return "神龙岛陆高轩曾与我有一面之缘，你到神龙岛走一趟问问他是否可以帮忙？\n";
		}
		if (!me->query_temp("hsz/chanchudu"))
		{
			command("say 练习红砂掌需要将蟾蜍之毒炼入手掌，劲气催使之下，方可修习。\n");
			me->set_temp("quest/kl/klz/hongsha/askke",1);
			return "白驼山庄少庄主欧阳克曾与我有一面之缘，你到白驼山庄附近走一趟问问他是否可以帮忙？\n";
		}
		if (!me->query_temp("hsz/蜘蛛毒"))
		{
			command("say 练习红砂掌需要将蜘蛛之毒炼入手掌，劲气催使之下，方可修习。\n");
			me->set_temp("quest/kl/klz/hongsha/askyin",1);
			return "明教的殷离曾与我有一面之缘，你到明教替我走一趟，问问她是否可以帮忙？\n";
		}
		if (!me->query_temp("hsz/蝎子毒"))
		{
			command("say 练习红砂掌需要将蝎子毒炼入手掌，劲气催使之下，方可修习。\n");
			me->set_temp("quest/kl/klz/hongsha/asklan",1);
			return "五毒教的蓝凤凰曾与我有一面之缘，你到明教替我走一趟，问问她是否可以帮忙？\n";
		}

	}
	if ((int)me->query("str")<30)
		return "这红砂掌最是看臂力，你先天臂力不足30，别来找我！\n";
	
	
	if( time()- me->query("quest/kl/klz/hongsha/time")<86400)
		return "嗯？你不是刚来请教过我红砂掌绝技的奥秘吗？还是再努力段时间吧！";

   
	message_vision(HIR"$N看着$n，慢慢说道：“我派的红砂掌乃是昆仑叠掌绝技，纯粹由内而外的功法，\n"
					"一旦施展，对手往往会中红砂掌毒，威力深大，你如此辛苦，我给你演示一遍，看你自己的悟性了。\n"+
				   HIC"\n\n\n$N缓缓运气于双掌之中，双掌顿时变成赤红一片。\n"NOR,this_object(),me);
	
 
    i = 20;
    if(me->query("m-card-vip")) i =  18;
    if(me->query("y-card-vip")) i =  15;
    if(me->query("buyvip"))     i =  10;
    i=random(i);
	j=random(me->query("kar"));
	command("say 本门红砂掌讲究的是劲气由后背运气于掌，经胸肋处直达劳宫穴，是这门掌法的精要所在。\n");
	command("pat "+me->query("id"));
	if( i<6
		&& me->query("kar")<31
		&& j >= 24 ) 
	{
		tell_object(me,HIY"\n你听了冯锡范的亲自指点，联想起早期自己所用昆仑掌的种种心得，两下印照。\n"NOR);
		tell_object(me,HIG"\n你丹田气劲盘旋游走，忽然间顺夹脊而上，汇聚于劳宫穴,双掌立即炙热无比。\n"
							"忽然间一股劲气震荡，如长江大河，滔滔不绝，顿时突破劳宫穴而达手掌。\n"
						 +"你终于领悟了这门迅红砂掌绝技的运用法门。心中大喜。\n"NOR);
		me->set("quest/kl/klz/hongsha/pass",1);
		log_file("quest/klzhongsha", sprintf("%8s(%8s) 失败%d次后，学到红砂掌绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/klz/hongsha/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		command("haha"+me->query("id"));		
		
		return "恭喜解密昆仑红砂掌绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/klzhongsha", sprintf("%8s(%8s) 解密红砂掌绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/klz/hongsha/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了冯锡范的指点，可是对昆仑掌红砂掌的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/klz/hongsha/fail",1);
		me->set("quest/kl/klz/hongsha/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密昆仑红砂掌失败"+me->query("quest/kl/klz/hongsha/fail")+"次。\n";
	}


}
//ask 一剑无血

string ask_wuxue()
{
	mapping fam;
	object ob;
	int i,j;
	object me=this_player();

	if (!(fam = this_player()->query("family"))
	 || fam["family_name"] != "昆仑派")
	   return RANK_D->query_respect(this_player())+ "与本派素无来往，也不是我亲传弟子，不知此话从何谈起？\n";  
	
	if (!me->query("appren_fengxifan"))
		return "你非我亲传弟子，来问此问题作甚？";
	if (!me->query("quest/kl/dichuan"))
	{
		return "你竟然不是昆仑嫡传弟子？！\n";
	}

	if(me->query_skill("xunlei-jian", 1) < 300 )
		return "你的迅雷剑造诣不够300，还无法领悟我派一剑无血的精要所在！\n";
	if(me->query_skill("force", 1) < 300 )
		return "你的基本内功造诣不够300，还无法领悟我派一剑无血的精要所在！\n";

	if( me->query("quest/kl/xlj/wuxue/pass") )
	{
		me->set("title",HIR"一剑"HIW"无血"NOR);
		me->set("mytitle/quest/yjwxtitle",HIR"一剑"HIW"无血"NOR);
		return "你已经解密了这个一剑无血的绝技，又何故开此玩笑呢？\n";
	}
	
	if (time()-me->query("quest/kl/xlj/wuxue/time")<86400)
		return "武功贪多不烂，你来的太勤快了？\n";
	
	if ((int)me->query("int")<30)
		return "这一剑无血很看悟性，你先天悟性不足30，别来找我！\n";
	/*
	if (!me->query_temp("quest/kl/xlj/wuxue/askchen"))
	{
		command("heng "+me->query("id"));
		return "真是聒噪！\n";
	}*/
	if (!me->query("quest/kl/xlj/killhu"))
	{
		command("say 数年前我跟百胜刀王胡逸之有些江湖恩怨，对我羞辱甚大，至今想起来我都很气愤！\n");
		command("say 你既然有如此诚心，那就替我把那百胜刀王胡逸之的人头给我拿来！\n");
		return "他据说最近贪恋美色，居然在大理茶花园中厮混，你去找找看，提头来见！\n";
	}

	if (!me->query("quest/kl/xlj/killchen"))
	{
		command("say 你既然有如此诚心，那就替我把陈近南那狗贼的人头给我拿来！\n");
		return "你一定要亲手杀了这个狗贼我才教你！\n";
	}
	message_vision(HIM"$N那眼神瞟了眼$n，缓缓地说道：“我这一剑无血绝技你可知其由来？\n"+
					"冯锡范看你摇了摇头，长叹一口气道，“我这一剑无血”的称号全凭为师打出来的。\n"+
					"这门功夫的核心心法在于以气御剑，将深厚的内力融合到剑尖，然后以剑尖颤动点穴。\n"+
					"功力深厚可能将对方直接点死，真正做到伤人于无形之中，正因为其极为厉害，中者。\n"+
				    "在外表往往看不出任何伤来，所以江湖中人舞步闻名丧胆。\n"NOR,this_object(),me);
	message_vision(HIM"$N长吁了口气，说道，这门功夫威力奇大，和昆仑其他寻常武功有些不同。\n"+
					"加之使用起来伤人无形，很多人都以为为师心狠手辣，其实不过是对于未知的恐惧罢了。\n"+
					"你若感兴趣，我就传授于你，能否领悟就看你的造化了！看好了....。\n"NOR,this_object(),me);
	message_vision(HIY"\n\n冯锡范拔剑而起，$n忽然感觉$N劲气运转之际，周身衣袍顿时鼓胀，忍不住向后。\n"+
				    "倒退两步。随着$N的劲气涌动，剑尖忽然闪烁，一下点在桌子上的一朵荷花图案上。\n"+
					"冯锡范对$n说道，“你过去看看那个图案！\n”\n"NOR,this_object(),me);
	message_vision(HIY"\n\n$n伸手一摸那个荷花瓣，顿时满手的木屑！\n"+
				    "$n吃惊之际，心中骇然，这一击之力外表看起来没什么变化，但威力竟然若斯！\n"+
					"$N喝道，“这当中的奥妙你可看清出来？”\n"NOR,this_object(),me);

	i = 20;
    if(me->query("m-card-vip")) i =  18;
    if(me->query("y-card-vip")) i =  15;
    if(me->query("buyvip"))     i =  10;
    j=random(i);
	
	if (j<3
		&& me->query("kar")<31
		&&random(me->query("kar"))>27)
	{
	
		command("laugh "+me->query("id"));
		command("chat* pat "+me->query("id"));
		command("chat 从今后"+me->query("name")+"就是我一剑无血冯锡范的关门弟子，还望武林同道多加照付！\n");
		command("chat* smile ");
		command("chat 我一剑无血冯锡范的弟子从此纵横江湖！\n");
		command("say 至此后，你对于我的以剑点穴的绝技已经是融会贯通了，还望你今后多加努力，为我大昆仑增光添彩。\n");
		command("say 我昆仑迅雷剑终将在武林中大放异彩，你要好自为之。\n");
		me->set("quest/kl/xlj/wuxue/pass",1);
		me->delete_temp("quest/kl/xlj");

	    me->set("title",HIR"一剑"HIW"无血"NOR);
		me->set("mytitle/quest/yjwxtitle",HIR"一剑"HIW"无血"NOR);
		log_file("quest/xljwuxue", sprintf("%8s(%8s) 失败%d次后，将迅雷剑一剑无血绝技彻底融会贯通。随机数j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/xlj/wuxue/fail"),j,me->query("kar"),me->query("combat_exp")) );

	}
	else {
		log_file("quest/xljwuxue", sprintf("%8s(%8s) 解密迅雷剑一剑无血绝技失败%d次！。随机数j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/xlj/wuxue/fail"),j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIG"你听了冯锡范的指点，可是对迅雷剑一剑无血绝技的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		command("angry "+me->query("id"));
		me->add("quest/kl/xlj/wuxue/fail",1);
		me->set("quest/kl/xlj/wuxue/time",time());
		me->delete_temp("quest/kl/xlj");
		me->start_busy(1+random(3));		
		return "非常遗憾解密迅雷剑一剑无血绝技失败"+me->query("quest/kl/xlj/wuxue/fail")+"次。\n";
	
	}
	return "哈哈！";
}
