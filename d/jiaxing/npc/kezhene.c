// kezhene.c �����
// Created by Zhuifeng@sjfy 08/8/2010

inherit NPC;
#include <ansi.h>
void create()
{
   set_name("�����",({"ke zhene","ke","zhene"}));
   set("gender","����");
   set("long","�����ǽ����߹�֮�ף�������������˫�۽�ä���ڼ���һ��������ʤ��\n");
   set("shen",90000);
   set("combat_exp",1800000);
   set("nickname","��������");
   set("title","�����߹�֮��");
   
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
	set("env/�������","����޼");
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
		"�����������" : "��������",
		"����" : "222",
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
