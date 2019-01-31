// bashuxian.c (kunlun)

inherit NPC;
inherit F_MASTER;
string ask_me();
string ask_zliangyi();
string ask_anjin();

#include <ansi.h>

void create()
{
	set_name("班淑娴", ({ "ban shuxian", "ban" }));
	set("title", "昆仑派掌门夫人");
	set("long",
		"她就是昆仑派掌门、名扬江湖的铁琴先生何太冲的夫人。\n"
		"她是一个身材高大的半老女子，头发花白，双目含威，眉心间聚有煞气。\n");
	set("gender", "女性");
	set("age", 44);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 26);
	set("int", 24);
	set("con", 28);
	set("dex", 28);

	set("max_qi", 23500);
	set("max_jing", 5000);
	set("neili", 23200);
	set("max_neili", 23200);
	set("jiali", 200);
	set("eff_jingli",5000);
	set("combat_exp", 9400000);
	set("score", 40000);
	set("liangyi", 1);

	set_skill("art", 150);

    set_skill("literate", 200);
	set_skill("force", 450);
	set_skill("dodge", 450);
	set_skill("parry", 450);
	set_skill("sword", 450);
	set_skill("leg", 450);
	set_skill("hand", 300);
	set_skill("throwing", 300);
	set_skill("sanyin-shou", 300);

	set_skill("liangyi-jue", 200);

	set_skill("xuantian-wuji",450);
	set_skill("taxue-wuhen", 450);
	set_skill("chuanyun-tui", 450);
    set_skill("liangyi-jian",450);	

	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("leg", "chuanyun-tui");
	map_skill("parry", "liangyi-jian");
	map_skill("sword", "liangyi-jian");
	map_skill("hand", "sanyin-shou");

	prepare_skill("hand", "sanyin-shou");
	prepare_skill("leg", "chuanyun-tui");
	
	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
  		(: perform_action, "sword.feipu" :),
		(: perform_action, "sword.jinzhen" :),
  		(: perform_action, "sword.feihua" :),
		(: perform_action, "sword.duanyun" :),
		(: exert_function, "wuji" :),			
  		(: perform_action, "dodge.taxue" :),
	}));
    create_family("昆仑派", 3, "掌门夫人");
	set("class", "taoist");
	set("inquiry",([
		"秘籍" : (: ask_me :),
		"正两仪诀" : (: ask_zliangyi:),
		"三阴手暗劲" : (: ask_anjin:),
	]));

	setup();
	carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/kunlun/obj/pao2.c")->wear();
}
void attempt_apprentice(object ob)
{
	if(ob->query("gender")=="男性"){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你们这些臭男人我见了就烦，快给我走开！");
		return;
	}
	if(ob->query("appren_hezudao", 1) == 1) {
		command("say "+RANK_D->query_respect(ob)+"怎敢开这等玩笑，真是折杀我了。");
		return;
	}  
	if(ob->query_skill("xuantian-wuji",1) < 300){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你的玄天无极功不足300,我可不想收你。");
		return;
	}
		if(ob->query_skill("chuanyun-tui",1) < 300){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你的穿云腿太差,不足300级别，我可不想收你。");
		return;
	}
	if(ob->query_skill("taxue-wuhen",1) < 300){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你的踏雪无痕太差,不足300级别，我可不想收你。");
		return;
	}

	command("say 好吧，以后你就跟我学武功吧，你须得安心学艺，不可乱来。");
	command("recruit " + ob->query("id"));
	ob->set("title","昆仑派第四代弟子");
}
string ask_me()
{
	mapping fam;
	object ob;

	if (!(fam = this_player()->query("family"))
	 || fam["family_name"] != "昆仑派")
		return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";

	if( this_player()->query("gender") == "男性")
		return "给我走开，我看见你们这些臭男人就烦。";

	ob = unew("/d/kunlun/obj/lyj-book.c");

	if(!clonep(ob)) return "你来晚了，本派真经已被你师兄拿走了。";

	if(clonep(ob) && ob->violate_unique()){
		destruct(ob);
		return "你来晚了，本派真经已被你师兄拿走了。";
	} 
	ob->move(this_player());
	return "先师曾传下来这本「两仪剑心得」，你拿回去好好钻研。";
}

string ask_zliangyi()
{
	mapping fam;
	object ob;

	if (!(fam = this_player()->query("family"))
	 || fam["family_name"] != "昆仑派")
		return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";

	

	ob = unew("/d/kunlun/obj/liangyi-jue.c");
	//ob->move(this_object());
	if(!clonep(ob)) return "你来晚了，本派真经已被你师兄拿走了。";
	
	if (this_object()->query("liangyi")<1&&clonep(ob) && ob->violate_unique())
	{
		destruct(ob);
		return "你来晚了，本派两仪决真经已被你师兄拿走了。";
	}else {
		//ob->move(this_player());

		ob->move(this_player());
		this_object()->add("liangyi",-1);
		return "先师曾传下来这本「两仪诀」秘籍，你拿回去好好钻研。";
		
	}


}


string ask_anjin()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="昆仑派")
	{
		return "你的不是昆仑派，难道不怕死么？！\n";
	}
	if (me->query_skill("sanyin-shou",1)<200)
	{
		return "你的三阴手等级不足200，告诉你也没用！\n";
	}
	if (me->query("quest/kl/sys/anjin/pass"))
	{
		return "你的三阴手“三阴暗劲”已经解开了！\n";
	}
	if (time()-me->query("quest/kl/sys/anjin/time")<86400)
	{
		return "你来的太频繁了，明天再来！\n";
	}

	message_vision(HIC"$N严肃的看着$n，慢慢说道：“我派的三阴手讲究的轻灵路线，和其他门派的硬功都不太相同。\n"
				   HIR"\n\n\n$N将三阴手的诀窍演示给$n看。\n"NOR,this_object(),me);
	
 
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
		tell_object(me,HIY"\n你听了的师傅的亲自指点，联想起早期自己所用三阴手的种种心得，两下印照。\n"NOR);
		tell_object(me,HIG"\n你运气冲关，忽然寸关穴一痛，一股劲气若隐若现，如臂使指，灵活无比。\n"			    
						 +"你终于领悟了这门三阴手暗劲的运用法门。心中大喜。\n"NOR);
		me->set("quest/kl/sys/anjin/pass",1);
		log_file("quest/klanjin", sprintf("%8s(%8s) 失败%d次后，学到三阴手暗劲绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/sys/anjin/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "恭喜解密三阴手绝技绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/klanjin", sprintf("%8s(%8s) 解密三阴手暗劲绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/sys/anjin/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了灵清居士的指点，可是对三阴手暗劲绝技的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/sys/anjin/fail",1);
		me->set("quest/kl/sys/anjin/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密三阴手暗劲绝技失败"+me->query("quest/kl/sys/anjin/fail")+"次。\n";
	}


}