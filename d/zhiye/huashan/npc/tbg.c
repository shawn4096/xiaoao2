// NPC: /d/huashan/npc/tbq.c
// Date: Look 99/03/25

inherit NPC;

void create()
{
	set_name("田伯光", ({
		"tian boguang",
		"tian",
		"boguang",
	}));
	set("long",
		"他就是败坏无数良家妇女名节的大淫贼，\n"
		"他轻功绝佳，一手狂风快刀更是名震江湖。\n"
	);

	set("nickname", "万里独行");
	set("gender", "男性");
	set("attitude", "friendly");

	set("age", 30);
	set("shen_type", -1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);

	set("qi", 3500);
	set("max_qi", 3500);
	set("jing", 1500);
	set("max_jing", 1500);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 150);
	set("combat_exp", 1000000);
	set("score", 10000);
	set("chat_chance_combat",60);
	set("chat_msg_combat", ({
		(: perform_action, "blade.huashen" :),
		(: perform_action, "blade.jingshen" :),
		(: perform_action, "blade.kuaidao" :),
		(: exert_function, "tianmo" :),
		(: exert_function, "jieti" :),
	}));
	setup();
	carry_object(BINGQI_D("blade"))->wield();
	carry_object(ARMOR_D("cloth"))->wear();
}
