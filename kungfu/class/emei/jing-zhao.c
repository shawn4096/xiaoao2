// /kungfu/class/emei/jing-zhao.c
// Update by Lklv 2001.10.18

#include "nigu.h"
inherit F_MASTER;
inherit NPC;

void create()
{
	set_name("静照师太", ({"jingzhao shitai", "jingzhao", "shitai"}));
	set("long",
		"她是一位慈祥的中年师太，在福寿庵修行。\n"
		"她是灭绝师太的八大静字辈弟子之五，最擅长剑法与掌法。\n"
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
	set("max_qi", 11500);
	set("max_jing", 5500);
	set("neili", 11500);
	set("max_neili", 11500);
	set("jiali", 130);
	set("combat_exp", 4500000);
	set("score", 100);

	set_skill("dacheng-fofa", 320);
	set_skill("linji-zhuang", 320);
	set_skill("literate", 320);
	set_skill("huifeng-jian", 310);
	set_skill("sword", 310);
	set_skill("strike", 320);
	set_skill("sixiang-zhang", 320);
	set_skill("parry", 310);
	set_skill("dodge", 310);
	set_skill("force", 320);
	set_skill("anying-fuxiang", 320);
        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
        ]));

	map_skill("strike", "sixiang-zhang");
	map_skill("force", "linji-zhuang");
	map_skill("sword", "huifeng-jian");
	map_skill("parry", "huifeng-jian");
	map_skill("dodge", "anying-fuxiang");

	prepare_skill("strike", "sixiang-zhang");

	create_family("峨嵋派", 4, "弟子");

	setup();
	carry_object("/d/emei/obj/changjian")->wield();
	carry_object("/d/emei/obj/shoes")->wear();
	carry_object("/d/emei/obj/cloth")->wear();
}
