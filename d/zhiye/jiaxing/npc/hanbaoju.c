// hanbaoju.c 韩宝驹
// Created by Zhuifeng@sjfy 08/8/2010

inherit NPC;
#include <ansi.h>
void create()
{
   set_name("韩宝驹",({"han baoju","han","baoju"}));
   set("gender","男性");
   set("long","江南七怪老三,舞的一手金龙鞭法\n");
   set("shen",80000);
   set("combat_exp",1200000);
   set("nickname","马王神");
   set("title","江南七怪老三");
   
   set("age",28);
   set("pur",30);
   set("kar",25);
   set("per",20);
   set("str",26);
	 set("int",20);
	 set("con",25);
	 set("dex",18);
	 set("max_qi", 6000);
	 set("eff_qi", 6000);

	 set("max_jing", 3000);
	 set("eff_jing", 3000);

	 set("max_jingli", 3000);
	 set("eff_jingli", 3000);
	 set("neili", 6000);
	 set("max_neili", 6000);
	 set("jiali", 120);

   set_skill("dodge",350);
   set_skill("force",350);
   set_skill("parry",350);
   set_skill("whip",350);
   set_skill("jinlong-bianfa",350);
   set_skill("literate",50);
   set_skill("caoshang-fei",350);
   map_skill("dodge","caoshang-fei");
   map_skill("whip","jinlong-bianfa");
   map_skill("parry","jinlong-bianfa");
   set("chat_chance_combat", 50);
   set("chat_msg_combat", ({
			(: perform_action, "whip.taoma" :),
			(: perform_action, "whip.jinlong" :),
	
		}));

   setup();
   add_money("silver",70);
	carry_object("d/jiaxing/obj/cloth")->wear();
	carry_object("clone/weapon/changbian")->wield();
}
