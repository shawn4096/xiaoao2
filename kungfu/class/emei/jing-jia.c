// /kungfu/class/emei/jing-jia.c
// Update by Lklv 2001.10.18

#include "nigu.h"
inherit F_MASTER;
inherit NPC;

void create()
{
	set_name("静迦师太", ({"jingjia shitai", "jingjia", "shitai"}));
	set("long",
		"她是一位慈祥的中年师太，睿智的面上带着和蔼的微笑。\n"
		"她是灭绝师太的八大静字辈弟子之六，最擅刀法与掌法。\n"
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
	set("dex", 30);
	set("max_qi", 11500);
	set("max_jing", 5500);
	set("neili",11500);
	set("max_neili", 11500);
	set("jiali", 130);
	set("combat_exp", 4500000);
	set("score", 100);

	set_skill("dacheng-fofa", 330);
	set_skill("linji-zhuang", 320);
	set_skill("yanxing-daofa", 330);
	set_skill("literate", 120);
	set_skill("blade", 330);
	set_skill("strike", 320);
	set_skill("sixiang-zhang", 330);
	set_skill("parry", 330);
	set_skill("dodge", 330);
	set_skill("force", 330);
	set_skill("anying-fuxiang", 130);
	set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
        ]));
	map_skill("strike", "sixiang-zhang");
	map_skill("force", "linji-zhuang");
	map_skill("blade", "yanxing-daofa");
	map_skill("parry", "yanxing-daofa");
	map_skill("dodge", "anying-fuxiang");
	prepare_skill("strike", "sixiang-zhang");

	create_family("峨嵋派", 4, "弟子");

	setup();
	carry_object("/d/emei/obj/blade")->wield();
	carry_object("/d/emei/obj/shoes")->wear();
	carry_object("/d/emei/obj/cloth")->wear();
}
