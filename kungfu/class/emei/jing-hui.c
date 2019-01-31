// /kungfu/class/emei/jing-hui.c
// Update by Lklv 2001.10.18

#include "nigu.h"
#include "xue_dacheng.h"
int ask_force();
int ask_fofa();
int ask_linji();
inherit F_MASTER;
inherit NPC;

void create()
{
	set_name("静慧师太", ({"jinghui shitai", "jinghui", "shitai"}));
	set("long",
		"她是一位慈祥的中年师太，睿智的面上带着和蔼的微笑。\n"
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
	set("dex", 35);
	set("max_qi", 12000);
	set("max_jing", 6000);
	set("neili", 11500);
	set("max_neili", 11500);
	set("jiali", 150);
	set("combat_exp", 4500000);
	set("score", 100);

	set("inquiry",([
          "修炼" : (: ask_force :),
          "大乘佛法" : (: ask_fofa :),
          "临济十二庄" : (: ask_linji :),
          "剃度"  : (: ask_for_join :),
          "出家"  : (: ask_for_join :),
         ]) );

	set_skill("dacheng-fofa", 320);
	set_skill("linji-zhuang", 320);
	set_skill("yanxing-daofa", 320);
	set_skill("literate", 120);
	set_skill("blade", 320);
	set_skill("parry", 320);
	set_skill("dodge", 320);
	set_skill("force", 320);
	set_skill("anying-fuxiang", 320);

	map_skill("force", "linji-zhuang");
	map_skill("blade", "yanxing-daofa");
	map_skill("parry", "yanxing-daofa");
	map_skill("dodge", "anying-fuxiang");


	create_family("峨嵋派", 4, "弟子");

	setup();
	carry_object("/d/emei/obj/blade")->wield();
	carry_object("/d/emei/obj/shoes")->wear();
	carry_object("/d/emei/obj/cloth")->wear();
}
