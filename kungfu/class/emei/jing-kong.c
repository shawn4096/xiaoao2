// /kungfu/class/emei/jing-kong.c
// Update by Lklv 2001.10.18

#include "nigu.h"
inherit F_MASTER;
inherit NPC;

void create()
{
	set_name("静空师太", ({"jingkong shitai", "jingkong", "shitai"}));
	set("long",
		"她是一位慈祥的中年师太，在万年庵修行。\n"
		"她是灭绝师太的八大静字辈弟子之四，最擅长掌法。\n"
	);

	set("gender", "女性");
	set("attitude", "friendly");
	set("unique", 1);
	set("class", "bonze");

	set("age", 35);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 32);
	set("max_qi", 6500);
	set("max_jing", 4500);
	set("neili", 8500);
	set("max_neili", 8500);
	set("jiali", 130);
	set("combat_exp", 3500000);
	set("score", 100);

	set_skill("dacheng-fofa", 330);
	set_skill("linji-zhuang", 330);
	set_skill("sixiang-zhang", 330);
	set_skill("strike", 330);
	set_skill("literate", 330);
	set_skill("parry", 330);
	set_skill("dodge", 330);
	set_skill("force", 330);
	set_skill("anying-fuxiang", 330);
	set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
        ]));
	map_skill("force", "linji-zhuang");
	map_skill("strike", "sixiang-zhang");
	map_skill("parry", "sixiang-zhang");
	map_skill("dodge", "anying-fuxiang");

	prepare_skill("strike", "sixiang-zhang");

	create_family("峨嵋派", 4, "弟子");

	setup();
	carry_object("/d/emei/obj/shoes")->wear();
	carry_object("/d/emei/obj/cloth")->wear();
}
