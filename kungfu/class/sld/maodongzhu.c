// yunsumei.c
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string ask_shuitong();
string ask_piao();
string ask_zhongyao();

void create()
{
	set_name("毛东珠", ({"mao dongzhu", "mao","dongzhu"}));
	set("long", "这是一个神龙教女弟子，一袭红衣，长得颇有姿色。\n");

	set("gender", "女性");
	set("attitude", "peaceful");

	set("age", 10+random(10));
	set("shen_type", -1);
	set("str", 25+random(10));
	set("dex", 25+random(10));
	set("con", 25+random(10));
	set("int", 25+random(10));
	set("per",26);
	set("qi", 4000);
	set("max_qi", 4000);
	set("jing", 4000);
	set("max_jing", 4000);
	set("jingli", 2500);
	set("max_jingli", 2500);
	set("eff_jingli", 2500);
	set("neili", 2000);
	set("max_neili", 2000);
	set("jiaji",100);
	set("combat_exp", 500000+random(100000));

	set_skill("force", 150);
	set_skill("dodge", 150);
	set_skill("parry", 150);
	set_skill("leg", 150);
	set_skill("whip", 150);
	set_skill("shenlong-tuifa", 150);
	set_skill("dulong-dafa", 150);
	set_skill("youlong-shenfa", 150);
	set_skill("poison", 100);
	set_skill("shenlong-yaoli", 100);
	set_skill("lingshe-bianfa", 150);
	map_skill("parry","lingshe-bianfa");
	map_skill("leg","shenlong-tuifa");
	map_skill("force","dulong-dafa");
	map_skill("dodge","youlong-shenfa");
	map_skill("whip","lingshe-bianfa");
	prepare_skill("leg","shenlong-tuifa");
	set("title", "神龙教赤龙门第四代弟子");
	
	create_family("神龙教",4,"弟子");
	set("inquiry", ([
		"水桶": (: ask_shuitong :), 
		"瓢": (: ask_piao :), 
		"种药草": (: ask_zhongyao :), 
	]));
	setup();
	
	carry_object("/d/sld/npc/obj/gcp")->wear();
	carry_object("/clone/weapon/changbian")->wield();
	add_money("silver",15);
}
/*
void init()
{
	object ob;

	::init();

	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 10, ob);
	}
}*/

     
void attempt_apprentice(object ob)
{
       mapping myfam;

       myfam = (mapping)ob->query("family");
	   if(myfam && myfam["family_name"] != "神龙教")
	   {
           command("say 你非本教弟子，我如何能收你为徒？\n");
		   return;
       }
	   if(ob->query("shen") > -10000)
	   {
           command("say 你还不够心黑手辣(-10k)，再去多杀几个白道中人吧.\n");
		  return;
	   }
	   if(ob->query("gender")!="女性")
	   {
           command("say 我只收女性弟子，男弟子找邓师兄拜师！\n");
		  return;
	   }
	   if(ob->query("combat_exp")>10000 )
       {
			command("say 你经验值都已经10k了，别来找我。我大神龙要的是忠诚弟子！\n");
            command("shake "+ob->query("id"));
			return;
	   }
       command("say 好吧，我就收下你做我的弟子。");
	   command("recruit " + ob->query("id"));
       
	   return;	
}


string ask_shuitong()
{
	object me,obj;
	me=this_player();
	if(me->query("family/family_name") != "神龙教")
	{
      command("say 你非本教弟子，来此作甚？\n");
	  return "哼!\n";
    }
	if(present("shui tong",me))
	{
      command("say 你不是有一对水桶么？\n");
	  return "哼!\n";
    }
	obj=new("d/sld/obj/shuitong");
	command("say "+me->query("name")+"，你如此勤快我就给你付水桶，别弄丢了!\n");
	obj->move(me);
	return me->query("name")+"水桶给你了!\n";
}


string ask_piao()
{
	object me,obj;
	me=this_player();
	if(me->query("family/family_name") != "神龙教")
	{
      command("say 你非本教弟子，来此作甚？\n");
	  return me->query("name")+"别来烦我!\n";
    }
	if(present("shui piao",me))
	{
      command("say 你不是有一瓢么？\n");
	  return me->query("name")+"别来烦我!\n";
    }
	obj=new("d/sld/obj/piao");
	command("say "+me->query("name")+"，你如此勤快我就给你水瓢，别弄丢了!\n");
	obj->move(me);
	return me->query("name")+"瓢给你了!\n";
}


string ask_zhongyao()
{
	object me,obj;
	me=this_player();
	if(me->query("family/family_name") != "神龙教")
	{
      command("say 你非本教弟子，来此作甚？\n");
	  return "哼!\n";
    }
	command("say 药圃的相关事宜由邓师兄管理，你可以跟他请教下！\n");
	return me->query("name")+"好好干!\n";
}
