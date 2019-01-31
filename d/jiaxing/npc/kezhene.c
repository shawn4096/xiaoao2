// kezhene.c 柯镇恶
// Created by Zhuifeng@sjfy 08/8/2010

inherit NPC;
#include <ansi.h>
void create()
{
   set_name("柯镇恶",({"ke zhene","ke","zhene"}));
   set("gender","男性");
   set("long","他乃是江南七怪之首，飞天蝙蝠柯镇恶，双眼皆盲，在嘉兴一带侠名甚胜！\n");
   set("shen",90000);
   set("combat_exp",1800000);
   set("nickname","飞天蝙蝠");
   set("title","江南七怪之首");
   
   set("age",40);
   set("pur",30);
   set("kar",35);
   set("per",20);
   set("str",30);
	 set("int",25);
	 set("con",20);
	 set("dex",30);
	 set("max_qi", 6000);
	 set("max_jing", 4000);
	 set("eff_jingli", 4000);
	 set("neili", 4000);
	 set("max_neili", 4000);
	 set("jiali", 120);
	set("env/听风辨器","铁蒺藜");
	set("quest/bx/anqi/pass",1);
   set_skill("dodge",400);
   set_skill("force",400);
   set_skill("parry",400);
   set_skill("strike",400);
   set_skill("staff",400);
   set_skill("throwing",400);
   set_skill("tingfeng-bianqi",400);
   set_skill("fengmo-zhang",400);
   set_skill("literate",160);
   set_skill("feitianshu",400);
   map_skill("dodge","feitianshu");
   map_skill("staff","fengmo-zhang");
   map_skill("parry","fengmo-zhang");
   
   set("inquiry", ([
		"听风辨器绝技" : "待开发中",
		"郭靖" : "222",
	]));

		set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: perform_action, "staff.fengmo" :),
			(: perform_action, "staff.feizhang" :),
		}));

   setup();
   add_money("silver",80);
    carry_object("clone/weapon/tiejili");
	carry_object("clone/weapon/tiejili");
	carry_object("clone/weapon/tiejili");
	carry_object("clone/weapon/tiejili");
	carry_object("clone/weapon/tiejili");
	carry_object("clone/weapon/tiejili");
	carry_object("d/menggu/npc/obj/cloth")->wear();
	carry_object("d/menggu/npc/obj/tiezhang")->wield();
}
