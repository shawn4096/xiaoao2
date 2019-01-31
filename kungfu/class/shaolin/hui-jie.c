// Npc: /kungfu/class/shaolin/hui-jie.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;


void create()
{
	set_name("慧洁尊者", ({
		"huijie zunzhe",
		"huijie",
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
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("max_qi", 450);
	set("max_jing", 300);
	set("neili", 600);
	set("max_neili", 600);
	set("jiali", 50);
	set("combat_exp", 150000);
	set("score", 100);

	set_skill("force", 100);
	set_skill("yijin-jing", 100);
	set_skill("dodge", 100);
	set_skill("shaolin-shenfa", 100);
	set_skill("leg", 100);
	set_skill("shaolin-tantui", 100);
        set_skill("club", 100);
	set_skill("zui-gun", 100);
	set_skill("parry", 100);
	set_skill("buddhism", 100);
	set_skill("literate", 100);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("leg", "shaolin-tantui");
        map_skill("club","zui-gun");
	//map_skill("club", "zui-gun");
	map_skill("parry", "zui-gun");

	prepare_skill("leg","shaolin-tantui");
         create_family("少林派", 38, "弟子");

	setup();

        carry_object("/d/shaolin/obj/qimeigun")->wield();
        carry_object("/d/shaolin/obj/hui-cloth")->wear();
}



#include "/kungfu/class/shaolin/hui.h"