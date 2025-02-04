// Npc: /kungfu/class/shaolin/xuan-cheng.c
// Date: YZC 96/01/19

inherit NPC;
string ask_me();
string ask_yzc();

void create()
{
	set_name("玄澄大师", ({
		"xuancheng dashi",
		"xuancheng",
		"dashi",
	}));
	set("long",
		"他是一位白须白眉的老僧，身穿一袭银丝棕黄袈裟。他身材高大，\n"
		"两手过膝。双目半睁半闭，却不时射出一缕精光。\n"
	);


	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 70);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 1500);
	set("max_jing", 1000);
	set("neili", 2000);
	set("max_neili", 2000);
	set("jiali", 150);
	set("combat_exp", 1000000);
	set("score", 500000);

	set_skill("buddhism", 160);
	set_skill("force", 450);
	set_skill("dodge", 450);
	set_skill("parry", 450);
	set_skill("strike", 450);
	set_skill("finger", 450);
	set_skill("leg", 450);
	set_skill("cuff", 450);

	set_skill("banruo-zhang", 450);
	set_skill("club", 450);
	set_skill("zui-gun", 450);
	set_skill("jingang-quan",450);
	set_skill("yizhi-chan",450);
	set_skill("yijin-jing", 450);
	set_skill("shaolin-shenfa", 450);
	set_skill("ruying-suixingtui",450);
	set_skill("buddhism", 180);
	set_skill("literate", 150);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("parry", "banrou-zhang");
	map_skill("strike", "banruo-zhang");
	map_skill("leg", "ruying-suixingtui");
	map_skill("cuff", "jingang-quan");
	map_skill("finger", "yizhi-chan");

	prepare_skill("strike", "yizhi-chan");
	prepare_skill("cuff", "jingang-quan");

	set("chat_chance",15);
        set("chat_msg",({
      "玄澄大师道：“贫僧只因贪图武学，佛法修为不足，强自多学上乘武功，结果筋脉尽断。”\n",
      "玄澄大师道：“本寺千年以来，历代高僧均以禅理上的领悟作为第一要务。”\n",
      "玄澄大师道：“贫僧虽已无法再练武功，但整日参悟天竺摩诃僧诋律，勤修佛法，由此开悟。”\n",                              
        }) );
        set("inquiry", ([
		"摩诃僧诋律" :    (: ask_me :),
		"一指禅" :    (: ask_yzc :),
		]));
        set("book_count",1);
	create_family("少林派", 36, "弟子");

	setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}
void heart_beat()
{
	::heart_beat();

	clear_conditions_by_type("poison");
	if( !is_fighting() && living(this_object()))
		reincarnate();
}

string ask_me()
{
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "少林派")
		return RANK_D->query_respect(this_player()) + 
		"与本派素无来往，不知此话从何谈起？";

	if (  present("moheseng diyu", this_player()) )
		return RANK_D->query_respect(this_player()) + 
		"你现在身上不是有这本书吗，怎麽又来要了？ 快去好好研读吧！";

	if (query("book_count") < 1) return "对不起，摩诃僧诋律已经被人要走了！";

	ob = new("/d/shaolin/npc/obj/fojing3");
	ob->move(this_player());

	add("book_count", -1);
	

	message_vision("玄澄大师从怀中取出一本书交给了$N。\n",this_player());
	return "好吧，记住，一定要认真研读此书，不可马虎。";

}

string ask_yzc()
{
	mapping fam; 
	object me=this_player();
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "少林派")
		return RANK_D->query_respect(this_player()) + 
		"与本派素无来往，不知此话从何谈起？";

	if (me->query_skill("yizhi-chan",1)<200)
	{
		command("say 你的一指禅绝技不足200，继续修炼去吧！");
		return "";
	}
	if (me->query_skill("buddhism",1)<160)
	{
		command("say 少林武技需要佛法来化解，你的禅宗佛法不足160，继续修炼去吧！");
		return "";
	}
	command("say 西来大意谁能穷\n");
	command("say 五乳峰头九载功\n");
	command("say 若道真诠尘内了\n");
	command("say 达摩洞内自圆通\n");
	command("buddhism ");
    me->set_temp("yzc/askxuancheng",1);
	
	message_vision("玄澄大师双掌合十，生态肃然。\n",this_player());
	return "好吧，一切皆凭机缘，去吧。";

}