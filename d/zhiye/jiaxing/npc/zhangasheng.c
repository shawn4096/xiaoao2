// zhangasheng.c
// Created by Zhuifeng@sjfy 08/9/2010

inherit NPC;
#include <ansi.h>
void create()
{
   set_name("张阿生",({"zhang asheng","zhang","asheng"}));
   set("gender","男性");
   set("long","江南七怪老五\n");
   set("shen",80000);
   set("combat_exp",1200000);
   set("nickname","笑弥陀");
   set("title","江南七怪老五");
   
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
   set_skill("cuff",350);
   set_skill("tiexian-quan",350);
   set_skill("caoshang-fei",350);
   map_skill("dodge","xiaoyaoyou");
   map_skill("cuff","tiexian-quan");
   map_skill("parry","tiexian-quan");
   prepare_skill("cuff","tiexian-quan");
   set("chat_chance_combat", 50);
   set("chat_msg_combat", ({
			(: perform_action, "cuff.biebushan" :),
			(: perform_action, "cuff.tiexian" :),
		}));

   setup();
   add_money("silver",70);
	carry_object("d/jiaxing/obj/cloth")->wear();
}
