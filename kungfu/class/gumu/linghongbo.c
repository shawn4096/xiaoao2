// linghongbo.c 凌洪波
// By sohu@xojh 2015.1

#include <ansi.h>
inherit NPC;
string ask_job();
int ask_hexiu();
void create()
{
	set_name("凌洪波", ({ "ling hongbo", "ling", "hongbo" }));
	set("long","这是一位姿容出众的女子，身段婀娜，容颜娇媚，宛如风中仙子。\n");
	set("gender", "女性");
	set("age", 20);
	set("attitude", "friendly");
	set("no_bark",1);
	set("per", 25);
	set("str", 30);
	set("dex", 30);
	set("con", 25);
	set("int", 40);
	set("shen", 1000);

	set("combat_exp", 2700000);
	set("max_qi", 5500);
	set("max_jing", 3600);
	set("eff_jingli",2000);
	set("max_neili", 2000);
	set("neili", 5000);
	set("jiali",30);
	set("unique", 1);

	set_skill("parry", 100);
	set_skill("force", 100);
	set_skill("dodge", 100);
	set_skill("sword", 100);
	set_skill("throwing", 100);
	set_skill("whip", 100);
	set_skill("meinu-quanfa", 100);
	set_skill("cuff", 100);
	set_skill("yunu-shenfa", 100);
	set_skill("yinsuo-jinling", 100);
	set_skill("yunu-jianfa", 100);
	set_skill("yunu-xinjing", 100);
	set_skill("literate", 140);

	map_skill("force", "yunu-xinjing");
	map_skill("dodge", "yunu-shenfa");
	map_skill("cuff", "meinu-quanfa");
	map_skill("sword", "yunu-jianfa");
	map_skill("whip", "yinsuo-jinling");
	map_skill("parry","yinsuo-jinling");
	prepare_skill("cuff", "meinu-quanfa");

	set("inquiry", ([
		//"玉蜂" : (: ask_job :),
		//"合修" : (: ask_hexiu :),
	]));
      
	setup();
	carry_object("/d/gumu/obj/buxue1")->wear();
	carry_object(ARMOR_D("cloth"))->wear(); 
}
