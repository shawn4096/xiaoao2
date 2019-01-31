// king.c 段正明
// added by tangfeng@sj 2004

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龙八部/天龙营救篇/"
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"

string enter();
string qinwang(object ob);
string askduanyu();
string tianlonghelp();
string asksave();
string askxiaofeng();
string askjiumozhi();
string ask_zhijian();
string ask_sandie();
string ask_yyz();
void create()
{
	set_name("段正明", ({ "duan zhengming", "duan", "master" }) );
	set("nickname", HIW"保定帝"NOR);
	set("title","大理皇帝");
	set("gender", "男性" );

	set("age", 48);
	set("str", 28);
	set("con", 28);
	set("dex", 28);
	set("int", 28);
	set("per", 26);

	set("max_qi", 34000);
	set("max_jing", 6000);
	set("eff_jingli", 6000);
	set("neili", 34000);
	set("qi", 34000);
	set("jingli", 6000);
	set("max_neili", 34000);
	set("jiali", 200);
	set("liumai-shenjian/guanchong",1);
    set("env/liumai","guanchong");

	set("rank_info/respect", "陛下");
	create_family("天龙寺", 13, "俗家弟子");
	set("long", "他看上去平易近人又颇有风度，气宇轩昂，眉目之间透着一股逼人的英气。\n");
	set("combat_exp", 9600000);
	set("score", 20000);
//set liumai 关冲
	set_skill("parry", 450);
	set_skill("dodge", 450);
	set_skill("qingyan-zhang", 450);
	set_skill("strike", 450);
	set_skill("buddhism",200);
	set_skill("force", 450);
	set_skill("literate", 150);
	set_skill("sword", 450);
	set_skill("duanjia-jianfa", 450);
	//set_skill("cuff", 450);
	set_skill("duanjia-quan", 450);
	set_skill("yiyang-zhi", 450);
	set_skill("finger", 450);
	set_skill("qiantian-yiyang", 450);
	set_skill("tianlong-xiang", 450);

	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "duanjia-jianfa");
	map_skill("sword", "duanjia-jianfa");
	map_skill("force", "qiantian-yiyang");
	map_skill("cuff", "duanjia-quan");
	map_skill("strike", "qingyan-zhang");
	map_skill("finger","yiyang-zhi");
	prepare_skill("finger","yiyang-zhi");
    set("chat_chance_combat",70);
    set("chat_msg_combat",({ 
		   (: exert_function, "yiyang" :),
           (: perform_action, "finger.sandie" :),
		   (: perform_action, "finger.yizhisanmai" :),
		  // (: perform_action, "finger.ciqu" :),
        }));
	set("inquiry", ([
		"入后宫" : (: enter :),
		"亲王" : (: qinwang :),
		"指剑绝技" : (: ask_zhijian :),
		"一阳指神功" : (: ask_yyz:),
		"name": "朕就是保定帝段正明。",
		"here": "这里便是大理皇宫。",
		"段誉" : (: askduanyu :),
		"大理" : "这里便是大理。",
		"天龙寺" : "天龙寺是我段家武学的最高之地，不过，想拜天龙寺可不是那么容易的.",
		"天龙有难" : (: tianlonghelp :),
		"营救" : (: asksave :),
		//"搭救" : (: asksave :),
		"萧峰" : "江湖人称南慕容、北萧峰，端得一条好汉。",
		"营救段誉" : (: asksave :),
		"营救萧峰" : (: askxiaofeng :),
		"慕容复" : "江湖人称南慕容、北萧峰，听说慕容公子年级轻轻，却无所不精。",
		"慕容博" : "姑苏慕容不出的杰才，可惜英年早逝。",
		"鸠摩智" : (: askjiumozhi :),
		"阳关三叠" : (: ask_sandie :),
		"六脉神剑" : "传说的我天龙寺最高绝学，朕也未能得见。",
	]));

	setup();
	carry_object("/d/dali/npc/obj/huangpao")->wear();
	carry_object("/clone/weapon/gangjian")->wield();
}

void init()
{
	object ob,me;
	me=this_object();
	ob = this_player();
	::init();
	if (interactive(ob = this_player()) 
	 && living(this_object())
	 && (int)ob->query_temp("killqueen")) {
		command ("say 你竟敢杀我的皇后，纳命来！\n");
		me->set_leader(ob);
		remove_call_out("kill_ob");
		call_out("kill_ob", 0, ob);
	}
}
string askjiumozhi()
{
	object me;
	me = this_player();
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "听说，大轮寺第一高僧鸠摩智将来我天龙寺佛法交流，真是我大理之幸啊。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
  	  command("? "+me->query("id"));
		  return "这魔僧竟然如此欺负我大理无人，妄为吐蕃国第一佛法高僧，所谓口生莲花，全是一派胡言。";
  }
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "鸠摩智妄为西域第一佛法高僧，所谓口生莲花，全是一派胡言。";
  }
  command("nod");
	return "大轮明王鸠摩智是吐蕃国的护国法王，但听说他具大智慧，精通佛法，想来武功也是惊人。";
}
string askxiaofeng()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR3+"start"))
  {
  	  command("hoho");
  		return "江湖人称南慕容、北萧峰，端得一条好汉，何来援救之说。";
  }
	if (me->query(QUESTDIR3+"start") && !me->query(QUESTDIR3+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是涉及到大辽与大宋之争，实在不好插手。";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
	  return "萧峰，难不是你所迫出中原，今日所谓搭救不知何意。";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是涉及到大辽与大宋之争，实在不好插手。";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "萧峰乃小侄之义兄，自然要救。这位"+RANK_D->query_respect(me) +"可先行一步，大理段家弟子随后援到。";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "这一战真是痛快，"+me->query("name")+"更是威震武林，端得厉害啊。";
  }
  command("hoho");
	return "江湖人称南慕容、北萧峰，端得一条好汉，何来援救之说。";
}
string asksave()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start") &&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "段誉素来不喜武学，只爱佛法易经，平易近人，何来援救之说？";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说，前段时间和镇南王又是吵架一番，至今未有回家，不知"+RANK_D->query_respect(me) +"可否帮助打听一下。";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "刚有探报，小侄被万劫谷所盘留，此事还请"+RANK_D->query_respect(me) +"速速前往万劫谷一趟。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "多谢"+RANK_D->query_respect(me) +"搭救小侄，只是自从万劫谷回来，小侄精神恍惚，不知所中何毒还是受何种内伤。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "段誉自万劫谷回来，总是气血不定，内力怪异，才被送往天龙求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "竟然惹出鸠摩智这等高手，但愿段誉吉人天相啊。";
  }
  command("hoho");
	return "段誉素来不喜武学，只爱佛法易经，平易近人，何来援救之说？";
}
string askduanyu()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start" )&&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "段誉正是朕之小侄，素来不喜武学，只爱佛法易经。";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说，前段时间和镇南王又是吵架一番，至今未有回家。";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "刚有探报，小侄被万劫谷所盘留，不得已只怕要走一次了。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "多谢"+RANK_D->query_respect(me) +"搭救小侄。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "段誉自万劫谷回来，总是气血不定，内力怪异，才被送往天龙求救去了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "竟然惹出鸠摩智这等高手，但愿段誉吉人天相啊。";
  }
  command("hoho");
	return "段誉正是朕之小侄、镇南王之子。";
}
string tianlonghelp()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"over"))
  {
  	  command("haha");
  		return "天龙寺是我段家武学的最高之地，高手众云，请不要危言耸听。";
  }
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "听说，大轮寺高僧鸠摩智不日将来我天龙寺，不知是喜是祸。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
		  return "这魔僧竟然如此欺负我大理无人，妄为吐蕃国第一佛法高僧。";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("thank "+me->query("id"));
		  return "多谢"+RANK_D->query_respect(me) +"化解这场天龙危机，还将我侄子得以解救。";
  }
  command("hoho");
	return "天龙寺是我段家武学的最高之地，高手众云，请不要危言耸听。";
}
string enter()
{
	object ob;
	string target;
	ob = this_player();
	if ( ob->query("combat_exp") < 100000)
		return "你想进后宫干吗？";
	if ( ob->query_temp("fan")){
		string book;
		book=ob->query_temp("book_target");
		return("让你去找"+book+CYN"，还不快去。"NOR);
	}
	switch  (random(8)){
		case 0: target = HIW"天神篇"NOR; break;
		case 1: target = HIW"龙神篇"NOR; break;
		case 2: target = HIW"夜叉篇"NOR; break;
		case 3: target = HIW"乾达婆篇"NOR; break;
		case 4: target = HIW"阿修罗篇"NOR; break;
		case 5: target = HIW"迦楼罗篇"NOR; break;
		case 6: target = HIW"紧那罗篇"NOR; break;
		case 7: target = HIW"摩呼罗迦篇"NOR; break;
	}
	ob->set_temp("fan",1);
	ob->set_temp("book_target",target);
	return "想入后宫，先帮我把天龙八部的"+target+CYN"找来。"NOR;
}

string qinwang(object ob)
{
	string new_title,title,*title1,*title2;
	mapping fam;
	ob=this_player();
	fam = ob->query("family");
	title1 =({ "承","平","定","乾","滇" });
	title2 =({ "东","南","西","北" });
	if ((!fam)||(fam["family_name"] != "天龙寺"))
		return RANK_D->query_respect(ob)+"与本国素无来往，不知此话从何谈起？";
	if (ob->query("tls") || ob->query("class")=="bone")
		return RANK_D->query_respect(ob) + "已经贵为天龙寺高僧，这个亲王显然是不适合你的。";
	if (ob->query("job_time/大理") < 3000 && ob->query_skill("qiantian-yiyang",1) < 160)
		return RANK_D->query_respect(ob) + "为大理做的还不够，就想成为王爷了？";
	if (stringp(ob->query("qinwang")))
		return RANK_D->query_respect(ob) + "已经是我朝亲王了，怎么还来打听？";
	title= title1[random(sizeof(title1))]+title2[random(sizeof(title2))]+"王";
	new_title= "大理国"+title;
	ob->set("title",HIW + new_title + NOR);
	ob->set("qinwang", title);
	command("chat 哈哈哈，即日起朕封" + ob->query("name")+"为我"+new_title+"。");
	return "好吧，看你劳苦功高，朕就封你为"+ new_title +"。";
}

void attempt_apprentice(object ob)
{
	string name, new_name, *prename;
	prename = ({ "段", "段" });
	if (ob->query("tls")&&ob->query("class")=="bone") {
		command ("say 你已经是天龙寺出家弟子了，我不能再收你了！");
		return;
	}
	if( (int)ob->query_skill("qiantian-yiyang",1) < 350 ){
		command ("hmm");
		command ("say 你乾天一阳功如此之差，我可不收你！");
		return;
	}
	if(ob->query_int() < 50){
		command("say 武学之道必须悟性高，依我看" + RANK_D->query_respect(ob) + "的悟性不足50，似乎不够？");
		return;
	}
	if(ob->query("shen") < 2000000){
		command("say 大理乃堂堂皇室，而这位" + RANK_D->query_respect(ob) + "不足2m正神，我看不适合在我大理呆下去了。");
		return;
	}
	if ((int)ob->query("shen") < 1000000){
		command ("say  我大理段氏乃堂堂正派，依我看" + RANK_D->query_respect(ob) +"正神不足1m，不适合入我大理段氏。");
		return;
	}
	command("smile");
	command("say 很好，" + RANK_D->query_respect(ob) + "多加努力，他日必定有成。");
	name = ob->query("name");
	new_name = prename[random(sizeof(prename))] + name[<4..<1];
	command("say 入我大理段家，从今以后你的名字就叫做" + new_name + "。");
	ob->set("name", new_name);
	command("recruit " + ob->query("id") );
	if (!ob->query("qinwang")) ob->set("title","大理国御前侍卫");
}

void recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
	ob->set("class", "officer");
}

int accept_object(object who, object ob)
{
	string bookname;
	bookname=ob->query("name");
	if ((bookname!=HIW"天神篇"NOR)
	 &&(bookname!=HIW"龙神篇"NOR)
	 &&(bookname!=HIW"夜叉篇"NOR)
	 &&(bookname!=HIW"乾达婆篇"NOR)
	 &&(bookname!=HIW"阿修罗篇"NOR)
	 &&(bookname!=HIW"迦楼罗篇"NOR)
	 &&(bookname!=HIW"紧那罗篇"NOR)
	 &&(bookname!=HIW"摩呼罗迦篇"NOR))
		return notify_fail("段正明对你摇头道：我要这东西没用啊。\n");
	if ( bookname==this_player()->query_temp("book_target")){
		if ( ob->query_temp("find") == who->query("id")){
			command("smile");
			command("say 很好，你可以进后宫了。");
			who->set_temp("enter",1);
			who->delete_temp("book");
			call_out("destroying", 1, ob);
			return 1;
		}
		command("hmm");
		command("say 这好象不是你找到的吧。");
		call_out("destroying", 1, ob);
		return 1;
	}
	else {
		command("hmm");
		command("say 这不是我要的书，你再去找。");
		call_out("destroying", 1, ob);
		return 1;
	}
}

void destroying(object ob)
{
	destruct(ob);
	return;
}

int prevent_learn(object ob, string skill)
{
	if (skill == "yiyang-zhi"){
		command("一阳指乃是我大理国镇国之宝，非做出巨大贡献者不得而传。\n");
		return 1;
	}
	return 0;
}

string ask_zhijian()
{
	object me, ob;
	int i,j,x;
	
	ob = this_object();
	me = this_player();       
	if (!me->query("family")
		|| me->query("family/family_name")!="天龙寺")
		return "你非我派弟子，来问此问题作甚？";

	
    if( me->query_skill("yiyang-zhi", 1) < 300 )
		return "你的一阳指造诣不够300，还无法领悟我派一阳指以劲气化为指剑绝技精要所在！";
	
	if( me->query("quest/tls/zhijian/pass") )
		return "你已经解密了这个指剑绝技，又何故开此玩笑呢？";

	if ((int)me->query("int")<30)
		return "这一阳指很看悟性，你先天悟性30，别来找我！\n";
	
	
	if( time()- me->query("quest/tls/zhijian/time")<86400)
		return "嗯？你不是刚来请教过我这门绝技的奥秘吗？还是再努力段时间吧！";

   
	message_vision(HIC"$N严肃的看着$n，慢慢说道：“我派的一阳指绝技讲究的千变万化，以劲气化为实质剑气，力争一招伤敌，\n"
						"你看好了，我给你演示一遍，看你自己的悟性了。\n"+
						HIR"\n\n\n$N纵身而已，劲气汹涌，本来往复，疾驰如电，迅捷无比。看的$n眼花缭乱\n"NOR,this_object(),me);
	
 
    i=random(10);
	j=random(me->query("kar"));
	x=random(me->query("int"));
	command("say 本门一阳指乃当世绝技，这一点你千万要记住。\n");
	command("pat "+me->query("id"));
	if( i>=6 
		&& me->query("kar")<31
		&& x >= 20
		&& j >= 26 ) 
	{
		tell_object(me,HIY"\n你听了段正明的指点，对一阳指以气为剑的奥妙颇有心得。\n"NOR);
		tell_object(me,HIG"\n你试图将内息冲到商阳穴中，突然只觉手三阳经上一股热气直通双手，手上经脉不禁豁然一轻。\n"
			             +"你下意识地顺手一挥，一阵破空声传来，波的一声，劲力脱指而出，瞬间将前方的墙上点了个洞。\n"
						 +"你终于领悟了这门以气化剑绝技的运用法门。心中大喜。\n"NOR);
		me->set("quest/tls/zhijian/pass",1);
		log_file("quest/yyzzhijian", sprintf("%8s(%8s) 失败%d次后，学到一阳指剑绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/tls/zhijian/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "恭喜解密一阳指指剑绝技绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/yyzzhijian", sprintf("%8s(%8s) 解密一阳指指剑绝技绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/tls/zhijian/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了段正明的指点，可是对一阳指指剑绝技的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/tls/zhijian/fail",1);
		me->set("quest/tls/zhijian/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密一阳指指剑绝技失败"+me->query("quest/tls/zhijian/fail")+"次。\n";
	}

}


string ask_sandie()
{
	object me, ob;
	int i,j,x;
	
	ob = this_object();
	me = this_player();       
	if (!me->query("family")
		|| me->query("family/family_name")!="天龙寺")
		return "你非我派弟子，来问此问题作甚？";

	
    if( me->query_skill("yiyang-zhi", 1) < 250 )
		return "你的一阳指造诣不够250，还无法领悟我派一阳指以劲气化为阳关三叠绝技精要所在！";
	
	if( me->query("quest/tls/yyz/sandie/pass") )
		return "你已经解密了这个阳关三叠绝技绝技，又何故开此玩笑呢？";

	if ((int)me->query("int")<30)
		return "这一阳指很看悟性，你先天悟性30，别来找我！\n";
	
	
	if( time()- me->query("quest/tls/yyz/sandie/time")<86400)
		return "嗯？你不是刚来请教过我这门绝技的奥秘吗？还是再努力段时间吧！";

   
	message_vision(HIY"$N一脸平和地对$n慢慢说道：“阳关三叠乃是我大理一阳指的绝技之一，其中破煞、惊神、截天三招，\n"
						"各自功效不同，破煞能提高命中且伤害对方的最大气。惊神可以让对方封招闭气功效而截天的功能\n"+
							"却更为不同，会有效牵制对方的行动。你看好了，我给你演示一遍，看你自己的悟性了。\n"+
						HIC"\n\n\n$N纵身而已，劲气汹涌，本来往复，疾驰如电，迅捷无比。看的$n眼花缭乱\n"NOR,this_object(),me);
	
 
    i=random(10);
	j=random(me->query("kar"));
	x=random(me->query("int"));
	command("say 本门一阳指乃当世绝技，这一点你千万要记住。\n");
	command("say 解开后要仔细查看本门武技的特点，方不枉我这一番教诲。\n");
	command("pat "+me->query("id"));
	if( i>=5 
		&& me->query("kar")<31
		&& x >= 20
		&& j >= 22 ) 
	{
		tell_object(me,HIC"\n你听了段正明的指点，对一阳指阳关三叠的奥妙颇有心得。\n"NOR);
		tell_object(me,HIG"\n你试图将内息冲到关冲穴中，突然只觉手三阳经上一股热气直通双手，手上经脉不禁豁然一轻。\n"
			             +"你下意识地顺手连点三招，一阵破空声传来，惊天、截天、惊神三招连发，电闪雷鸣，迅捷无比。\n"
						 +"你终于领悟了这门阳关三叠绝技的运用法门。心中大喜。\n"NOR);
		me->set("quest/tls/yyz/sandie/pass",1);
		log_file("quest/yyzsandie", sprintf("%8s(%8s) 失败%d次后，学到一阳指阳关三叠绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/tls/yyz/sandie/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "恭喜解密一阳指阳关三叠绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/yyzsandie", sprintf("%8s(%8s) 解密一阳指阳关三叠绝技绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/tls/yyz/sandie/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了段正明的指点，可是对一阳指阳关三叠绝技的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/tls/yyz/sandie/fail",1);
		me->set("quest/tls/yyz/sandie/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密一阳指阳关三叠绝技失败"+me->query("quest/tls/yyz/sandie/fail")+"次。\n";
	}

}


string ask_yyz()
{
	object me, ob;
	int i,j,x;
	
	ob = this_object();
	me = this_player();       
	
	if (!me->query("family")
		|| me->query("family/family_name")!="天龙寺")
		return "你非我派弟子，来问此问题作甚？";
	if (!me->query("quest/tls/yyz/start/helpnhsover"))
	{
		return "你虽是我派弟子，但大理一阳指只传段氏子弟！\n";
	}
	
    if( me->query_skill("qiantian-yiyang", 1) < 450 )
		return "你的乾天一阳造诣不够450，还无法领悟我派一阳指绝技精要所在！";
	
	if( me->query("quest/tls/yyz/pass") )
		return "你已经解密了这个一阳指神功绝技，又何故开此玩笑呢？";

	if ((int)me->query("int")<30)
		return "这一阳指很看悟性，你先天悟性不足30，别来找我！\n";
	if ((int)me->query("str")<30)
		return "这一阳指很看臂力，你先天臂力不足30，别来找我！\n";
	
	if( time()- me->query("quest/tls/yyz/time")<86400)
		return "嗯？你不是刚来请教过我这门绝技的奥秘吗？还是再努力段时间吧！";

   
	message_vision(HIC"$N一脸平和地对$n慢慢说道：“一阳指乃是我大理绝技之一，也是我天南大理不传之秘。本非我族弟子不得外传\n"
						"但你既然帮我大理打败了四大恶人，化解了我大理的危机，功劳的确很大，我和二弟商量了下，唯有将这门武功\n"+
							"传授于你，你看好了，我给你演示一遍，能否领悟就看你自己的悟性了。\n"+
						HIR"\n\n\n$N纵身而起，“嗤”的一声射出一股若有若无的劲气，瞬间数招，看的$n眼花缭乱\n"NOR,this_object(),me);
	
 
	j=random(me->query("kar"));
	command("say 本门一阳指乃当世绝技，这一点你千万要记住。\n");
	command("say 要仔细查看本门武技的特点，方不枉我这一番教诲。\n");
	command("pat "+me->query("id"));
	if( me->query("kar")<31
		&& j >= 25 ) 
	{
		tell_object(me,HIC"\n你听了段正明的指点，对一阳指的奥妙颇有心得。\n"NOR);
		tell_object(me,HIG"\n你试图将内息冲到关冲穴中，突然只觉手三阳经上一股热气直通双手，手上经脉不禁豁然一轻。\n"
			             +"你下意识地顺手连点三招，一阵破空声传来，惊天、截天、惊神三招连发，电闪雷鸣，迅捷无比。\n"
						 +"你终于领悟了这门一阳指神功绝技的运用法门。心中大喜。\n"NOR);
		me->set("quest/tls/yyz/pass",1);
		log_file("quest/yyzpass", sprintf("%8s(%8s) 失败%d次后，学到一阳指绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/tls/yyz/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "恭喜解密一阳指绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/yyzpass", sprintf("%8s(%8s) 解密一阳指绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/tls/yyz/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了段正明的指点，可是对一阳指阳关三叠绝技的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/tls/yyz/fail",1);
		me->set("quest/tls/yyz/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密一阳指绝技失败"+me->query("quest/tls/yyz/fail")+"次。\n";
	}

}