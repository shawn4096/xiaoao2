// guofu.c 郭芙
// Lklv modify 这个贱人 at 2001.10.21

inherit NPC;
string ask_me();

void create()
{
        set_name("郭芙", ({"guo fu", "guo", "fu"}));
        set("long","她就是郭靖、黄蓉的女儿郭芙。\n");

        set("gender", "女性");
        set("attitude", "peaceful");
        set("unique", 1);

        set("age", 25);
        set("shen_type", 1);
        set("str", 32);
        set("int", 32);
        set("con", 32);
        set("dex", 32);
        set("max_qi", 5500);
        set("max_jing", 5500);
        set("neili", 5500);
        set("max_neili", 5500);
        set("max_jingli", 5500);
        set("eff_jingli", 5500);
        set("jiali", 50);
        set("combat_exp", 1200000);
        set("chat_chance_combat", 40);

        set_skill("bihai-chaosheng", 165);
        set_skill("jieshou-jiushi", 165);
        set_skill("yuxiao-jian", 165);
        set_skill("luoying-zhang", 165);
        set_skill("anying-fuxiang", 165);
        set_skill("lanhua-shou",180);

        set_skill("hand", 165);
        set_skill("literate", 5);
        set_skill("strike", 165);
        set_skill("sword", 165);
        set_skill("parry", 165);
        set_skill("dodge", 165);
        set_skill("force", 165);

        map_skill("force", "bihai-chaosheng");
        map_skill("sword", "yuxiao-jian");
        map_skill("parry", "huifeng-jian");
        map_skill("dodge", "anying-fuxiang");
        map_skill("strike", "luoying-zhang");
        map_skill("hand", "lanhua-shou");
        prepare_skill("hand", "lanhua-shou");
        set("inquiry", ([
                "郭靖" : "呀！你也知道我爹爹的名字？\n",
                "黄蓉" : "她是我娘，最疼我了。\n",
               // "耶律齐" : "他……不就是……\n",
               //"杨过" : "唉，我一直不知道，其实我应该是喜欢他的。\n",
                //"小龙女" : "她是杨过的师父。\n",
                "打狗棒诀" : (:ask_me:),
                "郭襄" : "她是我妹妹，最近又不知道跑哪里去了。\n",
        ]));

        setup();
        carry_object(BINGQI_D("changjian"))->wield();
        carry_object(ARMOR_D("changqun"))->wear();
        carry_object(ARMOR_D("xiupao"))->wear();
}
string ask_me()
{
	object me=this_player();
	if (me->query("family/family_name")!="丐帮")
	{
		command("say 我妈妈乃是丐帮帮主，你乱打听什么！");
		return "哼！";
	}
	if (!me->query_temp("bangjue/asklu"))
	{
		command("say 你虽然身为丐帮弟子，自当奋不顾身杀敌去，没事来此作甚！");
		return "哼！";
	}
	command("say 既然你是鲁长老派你来助守襄阳的，就是自己人了。\n");
	command("giggle "+me->query("id"));
	command("smile "+me->query("id"));
	command("say 妈妈和爸爸助守襄阳，都居住在城西柳宗镇中。\n");
	command("say 妈妈待会要给鲁长老传授打狗棒诀，要不我们一起去看看？\n");
	me->set_temp("bangjue/askfu",1);
	return "你先过去，我一会就到，咱们一起偷偷看，一定很有趣!";
}