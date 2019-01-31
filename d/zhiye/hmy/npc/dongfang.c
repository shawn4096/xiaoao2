// dongfang.c 东方不败
// By River@SJ For kuihua-baodian Quest 2003.1.11

inherit NPC;

//inherit F_MASTER;

#include <ansi.h>

string ask_me();
string ask_rwx();
void create()
{
	object ob;
	set_name("东方不败", ({ "dongfang bubai", "dongfang", "bubai"}));
	set("long", "他就是武林之中一位惊天动地，威震当世的怪杰。\n"+
		"此刻他剃光了胡须，脸上竟然施了脂粉，身上那件衣衫式样男不男，女不女，\n"+
		"颜色之妖，便穿在少女身上，也显得太娇艳、太刺眼了些。\n");

	set("title",HIY"日月神教教主"NOR);         
	set("nickname", HIR"日出东方 唯我不败"NOR);
	set("gender", "无性");
	set("age", 54);
	set("attitude", "friendly");
	set("str", 20);
	set("int", 35);
	set("con", 30);
	set("dex", 30);
	set("per", 28);
	set("class", "eunuch");
	set("unique", 1);

	set("max_qi", 55000);
	set("max_jing", 10500);
	set("eff_jingli", 8000);
	set("max_neili", 86000);
	set("neili", 86000);
	set("jiali", 200);
	set("combat_exp", 12500000);
	set("shen", -50000);

	set_skill("sword", 550); 
	set_skill("parry", 500);
	set_skill("dodge", 500);
	set_skill("claw", 500);
	set_skill("force", 550);
	set_skill("pixie-jian", 550);        
	set_skill("youming-zhao", 500);
	set_skill("literate", 280);
	set_skill("kuihua-shengong", 550);

	map_skill("sword", "pixie-jian");
	map_skill("parry", "pixie-jian");
	map_skill("dodge", "pixie-jian");
	map_skill("claw", "youming-zhao");
	map_skill("force", "kuihua-shengong");
	prepare_skill("claw", "youming-zhao");

	set("chat_chance_combat", 150);
	set("chat_msg_combat", ({
		(: exert_function, "guimei" :),
		(: perform_action, "sword.cimu" :),
		(: perform_action, "sword.jue" :),
		(: perform_action, "sword.feiying" :),
		(: perform_action, "sword.pixie" :),
	}));
/* 消减阿姨威力
	set_temp("apply/damage", 50);
	set_temp("apply/dodge", 120);
	set_temp("apply/attack", 80);
	set_temp("apply/armor", 170);
	*/
	set_temp("幽冥", 1);

	set("inquiry", ([
		"葵花宝典": (: ask_me :),
		"任我行": (: ask_rwx :),
	]));

	setup();

	if (clonep()) {
		ob = unew(BOOK_D("kuihua"));
		if (!ob) ob = new("/clone/money/gold");
		ob->move(this_object());
		carry_object(BINGQI_D("xiuhua"))->wield();
		carry_object(ARMOR_D("xiupao2"))->wear();
	}
}
void init()
{
        object me=this_player();
		if (me->query_temp("xinxing/askren"))
        {
			command("heng "+me->query("id"));
			command("say 是任我行派你来的？");
			command("say 关了他这么多年了，本是为了他好，想不到今日终究还是要这教主之位，他若想来就让他亲自来。\n");
			
        }
} 

void reset()
{
	object ob;

	if (clonep() && (ob = unew(BOOK_D("kuihua"))))
		ob->move(this_object());
}

string ask_me()
{
	object ob, me = this_player();
	mapping quest;
	int i, time;

	if ( is_busy() || is_fighting())
	 	return "你没看到我正忙着么？";

	if ( me->query("gender") == "女性")
		return "倘若我和你一样，生为女儿身，那就好了。";

	if ( me->query("int") < 20 )
		return "你的灵性不够，「葵花宝典」不适合你练习。";

	if ( me->query("dex") < 15 )
		return "「葵花宝典」讲究的是腾挪之法，你的身法实在太低了。";

	if ( me->query("combat_exp", 1) < 5000000)
		return "你的实战经验还不够，「葵花宝典」还不适合你修炼。";

	if ( present("kuihua baodian", me))
		return "咦？「葵花宝典」不是在你身上么？还问我作甚？";

	ob = present("kuihua baodian", this_object());

	if ( ! ob)
		return "耶？「葵花宝典」给我放到那里去了？";

	time = time() - me->query("quest/pixie/pxj_time");
	if ( me->query("quest/pixie/pxj_time") && time < 86400 && !wizardp(me))
	 	return "我现在很忙，没兴趣和你多罗嗦。";

	quest = me->query("quest/pixie");

	if ( ! quest || ! quest["pxj_passwd"])
	{
		command("grin");	
        ::kill_ob(me);
		return "你从哪里听说到「葵花宝典」的？";
	}

	if ( quest["pass"] ) {
		if ( ob ) {
			ob->set("owner", me);
			ob->move(me);
			return "好吧，这本「葵花宝典」你拿回去好好研究研究。";
		}
		else
			return "你要的「葵花宝典」已经给别人拿走了。";
	}

	i = me->query("combat_exp", 1) - 4500000;
	i /= 500000;

        if ( me->query("registered")< 3 && quest["fail"] >= i)
	 	return "我现在很忙，没兴趣和你多罗嗦！";
        if ( quest["fail"] >= i && !me->query("cw_exp") )
	 	return "我现在很忙，没兴趣和你多罗嗦！";
	me->set_temp("pxj_quest", 1);
	kill_ob(me);
	me->kill_ob(this_object());
	return "就凭你这"+RANK_D->query_rude(me)+"也敢来窥视我的「葵花宝典」！";
}

string ask_rwx()
{
	object obj,me;
	me = this_player();
	obj=this_object();
	if ( is_busy() || is_fighting())
	 	return "你没看到我正忙着么？";

	if (me->query_temp("xixing/askren"))
	 {  
	    kill_ob(me);
	    me->kill_ob(this_object());
	   }
       me->delete_temp("xixing/askren");
	   me->set_temp("xixing/kdf",1);
	  return "就凭你这"+RANK_D->query_rude(me)+"也敢来替任我行生事，看招！";
}


void kill_ob(object me)
{	
	command("grin");	
    ::kill_ob(me);
   return;
}


void die()
{
	int total,i,j;
	object me = query_temp("last_damage_from");
	object ob = present("kuihua baodian", this_object());
	
	if (objectp(me)) {

     if (me->query_temp("xixing/kdf")) 
	{
		me->set_temp("xixing/killeddf",1);
		me->delete_temp("xixing/kdf");
		destruct(ob);
	}
	else if (me->query_temp("pxj_quest"))
    {
		if (QUEST_D->questing(me,10,190,0,"kuihua/book"))
			  
                {
			     message_vision("\n", me);
			     command("say 哈哈，你我也算是有缘之人，这本「葵花宝典」就交给你吧。");		         
			me->delete_temp("pxj_quest");
			QUEST_D->setmytitle(me,"kuihuatitle",HBMAG+HIG"欲练神功·引刀自宫"NOR);			
			ob->set("owner", me);
			ob->move(me);
		}
		else {
			message_vision(CYN"\n$N怒叫道：「即使我死了，你等也休想得到「葵花宝典」，哈哈哈哈……」\n"NOR, this_object());
			message_vision("$N将那「葵花宝典」放在双掌中一搓，功力到处，一本原已十分陈旧的册页登时化作碎片。\n\n", this_object());			
			ob->set("name", HIW"葵花宝典的碎片"NOR);
			ob->move(environment(this_object()));
		}
          
	}
	else destruct(ob);
	}	
	else
	{
		
		destruct(ob);
	}	
	::die();
}

void unconcious()
{
	die();
}
                                                                                              
