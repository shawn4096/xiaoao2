// Code of ShenZhou 
// /clone/beast/xbaozi.c
// С����
// sdong 08/98
// Modified by xQin 11/00

#include <ansi.h>
inherit NPC;


void create()
{
		  set_name("С����", ({ "xiao baozi", "baozi" }) );
		  set("race", "Ұ��");
		  set("age", 1);
		  set("long", "һֻ���岻����Ǻܽ�ʵ��С���ӣ����������۾������㡣\n");
		  set("attitude", "peaceful");
          set_weight(200000);
		  set("max_qi", 100);
		  set("max_jing", 100);
		  set("max_jingli", 100);
		  set("limbs", ({ "ͷ��", "����", "β��" }) );
          set("verbs", ({ "bite" }) );


		  set("str", 30);
		  set("con", 80);
		  set("dex", 30);
		  set("int", 10);

		  set("combat_exp", 20000);

		  set_temp("apply/attack", 10);
		  set_temp("apply/damage", 10);
		  set_temp("apply/armor", 10);

		  setup();
}

/*
void die()
{
		  object ob,ob2=this_object();

		//  ob = new(DRUG_D("baodan"));
		//  ob->move(environment(this_object()));
		  //message_vision("$N�Һ�һ�������ˣ�\n", this_object());
		  ::die();
}
*/

