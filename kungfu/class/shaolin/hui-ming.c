// Npc: /kungfu/class/shaolin/hui-ming.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;


void create()
{
	set_name("慧名尊者", ({
		"huiming zunzhe",
		"huiming",
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
	set("int", 20);
	set("con", 27);
	set("dex", 22);
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
	set_skill("strike", 100);
	set_skill("weituo-zhang", 100);
	set_skill("blade", 100);
	set_skill("xiuluo-dao", 100);
	set_skill("parry", 100);
	set_skill("buddhism", 100);
	set_skill("literate", 100);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("strike", "weituo-zhang");
	map_skill("blade", "xiuluo-dao");
	map_skill("parry", "weituo-zhang");

	prepare_skill("strike", "weituo-zhang");

	create_family("少林派", 38, "弟子");

	setup();

        carry_object("/d/shaolin/obj/jiedao")->wield();
        carry_object("/d/shaolin/obj/hui-cloth")->wear();
}


#include "/kungfu/class/shaolin/hui.h"

