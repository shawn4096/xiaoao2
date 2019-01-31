// d/wudang/npc/xiaocui.c
// modified by cck on 17/6/97 to puren.c


inherit NPC;
#include <ansi.h>

void create()
{
	set_name("郑家仆人", ({"pu ren", "puren", "pu"}) );
	set("gender", "男性" );
	set("age", 50);
	set("long",
	  "这是个老实巴交的老仆人，虽然衣服上打了很多补丁，却是十分的整洁。\n"
	  "因为长期待在厨房里，眼睛被烟熏成了一条缝。\n");
	set("attitude", "friendly");
	set("shen_type", 1);

        set("str", 27);
	set("int", 25);
	set("con", 24);
	set("dex", 24);
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
