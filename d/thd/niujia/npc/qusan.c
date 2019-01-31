// shagu.c

inherit NPC;

void create()
{
        set_name("曲三", ({"qu san","qusan","qu"}) );
        set("gender", "男性" );
        set("age", 21);
        set("long", "这是一个瘸子，身子柱着一条拐杖，是这家小酒店老板。\n");

        set("combat_exp", 4500000);
	set("shen", 0);
	set("shen_type", 0);
        set("str", 32);
        set("dex", 18);
        set("con", 18);
        set("int", 10);
	set("max_qi", 4900);
	set("max_jing", 4720);
	set("neili", 15000);
	set("max_neili", 15000);
	set("jiali", 120);

	set_skill("force", 360);
	set_skill("bihai-chaosheng", 360);
	set_skill("dodge", 360);
	set_skill("suibo-zhuliu", 365);
	set_skill("parry", 360);
	set_skill("strike", 380);
	set_skill("luoying-zhang", 380);
	set_skill("qimen-bagua", 130);

	map_skill("force", "bihai-chaosheng");
	map_skill("dodge", "suibo-zhuliu");
	map_skill("strike", "luoying-zhang");
	map_skill("parry", "luoying-zhang");
	prepare_skill("strike", "luoying-zhang");

	//set("rank_info/respect", "小姑娘");
/*
	set("inquiry", ([
		"name": "他们都叫我做傻姑。",
		"rumors": "杨兄弟打了姑姑一掌，杨兄弟就死了。",
		"here": "这里是牛家村。",
		"姑姑": "那个傻小子叫她做蓉儿。",
		"师公": "师公教我打拳玩。",
	]) );
	*/
        set("chat_chance", 4);
        set("chat_msg", ({
		"做人不能忘本\n",
		"师傅对我有大恩\n",
		"谁有好的字画，我会重金收购\n",
        }) );
	setup();

        carry_object(ARMOR_D("cloth"))->wear();
      //  carry_object(ARMOR_D("shoes"))->wear();
}

