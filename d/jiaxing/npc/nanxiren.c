// nanxiren.c 南希仁
// Created by Zhuifeng@sjfy 08/8/2010

inherit NPC;
#include <ansi.h>
void create()
{
   set_name("南希仁",({"nan xiren","nan","xiren"}));
   set("gender","男性");
   set("long","江南七怪老四,\n");
   set("shen",80000);
   set("combat_exp",4500000);
   set("nickname","南山樵子");
   set("title","江南七怪老四");
   
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
   set_skill("blade",350);
   set_skill("strike",350);
   set_skill("nanshan-dao",350);
   set_skill("kaishan-zhang",350);
   set_skill("literate",90);
   set_skill("caoshang-fei",350);
   //   set_skill("baduan-jin",350);

   map_skill("dodge","caoshang-fei");
   map_skill("strike","kaishan-zhang");
   map_skill("blade","nanshan-dao");
   map_skill("parry","nanshan-dao");

   prepare_skill("strike","kaishan-zhang");
   set("chat_chance_combat", 50);
		set("chat_msg_combat", ({
			(: perform_action, "blade.fanpi" :),
		
		}));

   setup();
   add_money("silver",70);
carry_object("d/jiaxing/obj/cloth")->wear();
carry_object("clone/weapon/blade")->wield();
}
