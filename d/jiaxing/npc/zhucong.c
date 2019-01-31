// zhucong.c 朱聪
// Created by Zhuifeng@sjfy 08/8/2010

inherit NPC;
#include <ansi.h>
void create()
{
   set_name("朱聪",({"zhu cong","zhu","cong"}));
   set("gender","男性");
   set("long","江南七怪老二,手上功夫了得!\n");
   set("shen",80000);
   set("combat_exp",1200000);
   set("nickname","妙手书生");
   set("title","江南七怪老二");
   
   set("quest/bx/cgs/kongkong/pass",1);
   set("env/妙手空空","稀有品");

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
  // set_skill("sword",200);
   set_skill("hand",350);
   set_skill("stealing",400);
   set_skill("cuogu-shou",350);
   set_skill("literate",200);
   set_skill("xiaoyaoyou",350);
   map_skill("dodge","xiaoyaoyou");
   map_skill("hand","cuogu-shou");
   map_skill("parry","cuogu-shou");
   prepare_skill("hand","cuogu-shou");

   set("chat_chance_combat", 65);
   set("chat_msg_combat", ({
			(: perform_action, "hand.kongkong" :),
			(: perform_action, "hand.cuogu" :),
	
		}));

   setup();
   add_money("silver",70);
	carry_object("d/jiaxing/obj/cloth")->wear();
	carry_object("d/menggu/npc/obj/zheshan");
}
