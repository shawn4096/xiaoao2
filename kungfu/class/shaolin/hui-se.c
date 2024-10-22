// Npc: /kungfu/class/shaolin/hui-se.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;


void create()
{
	set_name("慧色尊者", ({
		"huise zunzhe",
		"huise",
		"zunzhe",
	}));
	set("long",
		"他是一位两鬓斑白的老僧，身穿一袭青布镶边袈裟。他身材略高，\n"
		"太阳穴微凸，双目炯炯有神。\n"
	);


	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 50);
	set("shen_type", 1);
	set("str", 30);
	set("int", 18);
	set("con", 28);
	set("dex", 25);
	set("max_qi", 450);
	set("max_jing", 300);
	set("neili", 600);
	set("max_neili", 600);
	set("jiali", 70);
	set("combat_exp", 150000);
	set("score", 100);

	set_skill("force", 100);
	set_skill("yijin-jing", 100);
	set_skill("dodge", 100);
	set_skill("shaolin-shenfa", 100);
	set_skill("claw", 100);
	set_skill("jimie-zhua", 100);
//	set_skill("strike", 70);
//	set_skill("sanhua-zhang", 70);
	set_skill("parry", 100);
	set_skill("buddhism", 100);
	set_skill("literate", 100);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("claw", "jimie-zhua");
//	map_skill("strike", "sanhua-zhang");
	map_skill("parry", "jimie-zhua");

	prepare_skill("claw", "jimie-zhua");

	create_family("少林派", 38, "弟子");

	setup();

        carry_object("/d/shaolin/obj/hui-cloth")->wear();
}


#include "/kungfu/class/shaolin/hui.h"

