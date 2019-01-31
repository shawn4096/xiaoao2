// quanjinfa.c
// Created by Zhuifeng@sjfy 08/9/2010
//edit by sohu@xojh
//呼延枪法，

inherit NPC;
#include <ansi.h>
void create()
{
   set_name("全金发",({"quan jinfa","quan","jinfa"}));
   set("gender","男性");
   set("long","江南七怪老六\n");
   set("shen",80000);
   set("combat_exp",1200000);
   set("nickname","闹市侠隐");
   set("title","江南七怪老六");
  
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
	   set_skill("literate",140);
	   set_skill("trade",200);
	   set_skill("spear",350);
	   set_skill("caoshang-fei",350);
	   set_skill("huyan-qiang",350);
	   map_skill("dodge","caoshang-fei");
	   map_skill("spear","huyan-qiang");
	   set("chat_chance_combat", 65);
	   set("chat_msg_combat", ({
			(: perform_action, "spear.ci" :),
			(: perform_action, "spear.shanji" :),			
		}));

	setup();
	add_money("silver",70);
	carry_object("d/jiaxing/obj/jinpao")->wear();
	carry_object("clone/weapon/changqiang.c")->wield();
	
}
