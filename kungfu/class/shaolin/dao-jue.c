// Npc: /kungfu/class/shaolin/dao-jue.c
// Date: YZC 96/01/19

inherit NPC;

void create()
{
	set_name("道觉禅师", ({
		"daojue chanshi",
		"daojue",
		"chanshi",
	}));
	set("long",
		"他是一位身材高大的中年僧人，两臂粗壮，膀阔腰圆。他手持兵\n"
		"刃，身穿一袭灰布镶边袈裟，似乎有一身武艺。\n"
	);

	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 40);
	set("shen_type", 1);
	set("str", 30);
	set("int", 20);
	set("con", 21);
	set("dex", 22);
	set("max_qi", 400);
	set("max_jing", 300);
	set("neili", 450);
	set("max_neili", 450);
	set("jiali", 40);
	set("combat_exp",80000);
	set("score", 100);

	set_skill("force", 80);
	set_skill("yijin-jing", 80);
	set_skill("dodge", 80);
	set_skill("shaolin-shenfa", 80);
	set_skill("hand", 83);
	set_skill("fengyun-shou", 83);
	set_skill("leg", 85);
	set_skill("shaolin-tantui", 85);
        set_skill("club", 85);
	set_skill("weituo-gun", 85);
	set_skill("parry", 80);
	set_skill("buddhism", 80);
	set_skill("literate", 80);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("hand", "fengyun-shou");
	map_skill("leg", "shaolin-tantui");
	map_skill("parry", "weituo-gun");
        map_skill("club", "weituo-gun");

	prepare_skill("hand", "fengyun-shou");
        prepare_skill("leg", "shaolin-tantui");

	create_family("少林派", 39, "弟子");

	setup();

        carry_object("/d/shaolin/obj/dao-cloth")->wear();
        carry_object("/d/shaolin/obj/qimeigun")->wield();
}

#include "/kungfu/class/shaolin/dao.h"
