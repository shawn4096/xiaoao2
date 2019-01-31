// 农夫 By River@SJ 2002.6.5

inherit NPC;
#include <ansi.h>

void create()
{
	set_name("农夫", ({ "nong fu", "nong", "fu" }) );
	set("long", "只见他实无惊人之处，双手托着黄牛大石，却又显得并不如何吃力。\n");
	set("gender", "男性" );
	set("age", 45);
	set("str", 30);
	set("con", 30);
	set("dex", 25);
	set("int", 25);
	set("per", 22);
	set("unique", 1);
	set("attitude", "friendly");

	set("max_qi", 15000);
	set("max_jing", 3800);
	set("eff_jingli", 3600);
	set("neili", 8000);
	set("qi", 15000);
	set("jingli", 3600);
	set("max_neili", 8000);
	set("jiali", 150);

	set("combat_exp", 4500000);
	set("score", 5000);

	set_skill("parry", 350);
	set_skill("dodge", 350);
	set_skill("force", 350);
	set_skill("literate", 200);
	set_skill("qiantian-yiyang", 350);
	set_skill("tianlong-xiang", 350);
	//set_skill("axe", 350);
	//set_skill("pangen-fu", 350);
	set_skill("strike", 350);
	set_skill("qingyan-zhang", 350);
	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "qingyan-zhang");
	map_skill("force", "qiantian-yiyang");
	map_skill("strike", "qingyan-zhang");
	//map_skill("axe", "pangen-fu");
	prepare_skill("strike","qingyan-zhang");

	setup();
	carry_object(ARMOR_D("b_cloth"))->wear();
	carry_object(ARMOR_D("caoxie"))->wear();
}
