// wugu.c
// by sohu

inherit NPC;
#include <ansi.h>

void create()
{
	set_name("五姑", ({"wu gu", "gu", "wugu"}) );
	set("gender", "女性" );
	set("title","掌门小妾");
	set("age", 50);
	set("long",
	  "她是昆仑掌门铁琴先生的小妾五姑，平时长得如花似玉，很得何太冲的喜欢。\n"
	  "不知何故近日脸上浮肿一片，浑身宛如充气般的肿胀如球。\n");
	set("attitude", "friendly");
	set("shen_type", 1);

        set("str", 27);
	set("int", 25);
	set("con", 24);
	set("dex", 24);
		set("per", 26);

	set("no_quest", 1);

	set("max_qi", 650);
	set("max_jing", 400);
	set("neili", 150);
	set("max_neili", 150);

        set("combat_exp", 1000+random(800));
	set("score", 1000);

	set_skill("force", 40);
	set_skill("dodge", 30);
	set_skill("unarmed", 25+random(20));
	set_skill("parry", 30);
	set_temp("apply/attack", 10);
	set_temp("apply/defense", 15);
	set_temp("apply/damage", 4);

        setup();
	carry_object(ARMOR_D("cloth"))->wear();
}
