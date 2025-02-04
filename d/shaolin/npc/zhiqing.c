// Npc: /d/shaolin/npc/seng-bing1.c
// Date: YZC 96/01/19

inherit NPC;


void create()
{
	set_name("止清小和尚", ({
		"zhi qing",
		"zhiqing",
		"seng",
	}));
	set("long",
		"他是一位身材清秀的小僧人。身穿一袭白布镶边袈裟。\n"
	);

	set("gender", "男性");
	set("attitude", "heroism");
	set("class", "bonze");

	set("age", 15);
	set("shen_type", 1);
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("max_qi", 500);
	set("max_jing", 300);
	set("neili", 500);
	set("max_neili", 500);
	set("pursuer", 1);
	set("combat_exp", 2000);
	set("score", 1);

	set_skill("force", 30);
	set_skill("hunyuan-yiqi", 30);
	set_skill("dodge", 30);
	set_skill("shaolin-shenfa", 30);
	set_skill("unarmed", 30);
	set_skill("banruo-zhang", 30);
	set_skill("parry", 30);
	set_skill("blade", 30);
	set_skill("cibei-dao", 30);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("unarmed", "banruo-zhang");
	map_skill("parry", "cibei-dao");
	map_skill("blade", "cibei-dao");

	setup();

	carry_object(__DIR__"obj/jiedao")->wield();
	carry_object(__DIR__"obj/cloth")->wield();
}




