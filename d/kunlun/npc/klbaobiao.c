// kunlun-dizi1.c (kunlun)

inherit NPC;

void create()
{
	set_name("护院弟子", ({"huyuan dizi", "dizi"}));
	set("long",
		"他是郑克爽的保镖，看起来膀阔腰圆，是昆仑派的高手。\n");
	set("gender", "男性");
	set("age", 30);
	set("attitude", "heroism");
	set("shen_type", 1);
	set("str", 25);
	set("int", 20);
	set("con", 20);
	set("dex", 23);

	set("max_qi", 14000);
	set("max_jing", 5300);
	set("neili", 15000);
	set("max_neili", 15000);
	set("jiali", 150);
	set("combat_exp", 1300000);
	set("score", 4000);

	set_skill("force", 450);
	set_skill("xuantian-wuji", 450);
	set_skill("dodge", 450);
	set_skill("taxue-wuhen", 450);
	set_skill("xunlei-jian", 450);
	set_skill("kunlun-zhang", 450);

	set_skill("parry", 450);
	set_skill("sword", 450);
	set_skill("strike", 450);

	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("sword", "xunlei-jian");
	map_skill("parry", "xunlei-jian");
	map_skill("strike", "kunlun-zhang");
	prepare_skill("strike", "kunlun-zhang");
	set("chat_msg_combat", ({
  		(: perform_action, "sword.xunlei" :),
  		(: perform_action, "sword.podi" :),
		(: perform_action, "sword.benlei" :),
		(: exert_function, "wuji" :),			
	}));
	create_family("昆仑派", 4, "弟子");
	setup();
	carry_object("/d/kunlun/obj/sword")->wield();
	carry_object("/d/kunlun/obj/pao4")->wear();
}


