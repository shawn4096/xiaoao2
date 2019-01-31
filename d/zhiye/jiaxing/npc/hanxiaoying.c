// hanxiaoying.c 韩小莹
// Created by Zhuifeng@sjfy 08/8/2010

inherit NPC;
#include <ansi.h>
void create()
{
   set_name("韩小莹",({"han xiaoying","han","xiaoying"}));
   set("gender","女性");
   set("long","江南七怪老七,\n");
   set("shen",80000);
   set("combat_exp",1200000);
   set("nickname","越女剑");
   set("title","江南七怪老七");
   
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
   set_skill("sword",350);
   set_skill("yuenu-jian",350);
   set_skill("literate",120);
   set_skill("caoshang-fei",350);
   map_skill("dodge","caoshang-fei");
   map_skill("sword","yuenu-jian");
   map_skill("parry","yuenu-jian");

   setup();
   add_money("silver",70);
	carry_object("d/menggu/npc/obj/cloth")->wear();
	carry_object("clone/weapon/sword")->wield();
}
