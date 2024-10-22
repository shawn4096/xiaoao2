// Npc: /kungfu/class/shaolin/qing-guan.c
// Date: YZC 96/01/19

inherit NPC;


void create()
{
	set_name("清观比丘", ({
		"qingguan biqiu",
		"qingguan",
		"biqiu",
	}));
	set("long",
		"他是一位体格强健的壮年僧人，他身得虎背熊腰，全身似乎蕴含\n"
		"着无穷劲力。他身穿一袭白布黑边袈裟，似乎身怀武艺。\n"
	);


	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 30);
	set("shen_type", 1);
	set("str", 25);
	set("int", 15);
	set("con", 25);
	set("dex", 25);
	set("max_qi", 350);
	set("max_jing", 200);
	set("neili", 350);
	set("max_neili", 350);
	set("jiali", 30);
	set("combat_exp", 50000);
	set("score", 100);

	set_skill("force", 60);
	set_skill("yijin-jing", 60);
	set_skill("dodge", 60);
	set_skill("shaolin-shenfa", 60);
	set_skill("finger", 60);
	set_skill("mohe-zhi", 60);
        set_skill("claw", 60);
	set_skill("jimie-zhua", 60);
	set_skill("parry", 60);
	set_skill("buddhism", 60);
	set_skill("literate", 60);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("finger", "mohe-zhi");
        map_skill("claw", "jimie-zhua");
	map_skill("parry", "jimie-zhua");

	prepare_skill("claw", "jimie-zhua");
        prepare_skill("finger", "mohe-zhi");

	create_family("少林派", 40, "弟子");

	setup();

        carry_object("/d/shaolin/obj/qing-cloth")->wear();
}



