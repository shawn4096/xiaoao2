// yunsumei.c
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string ask_shuitong();
string ask_piao();
string ask_zhongyao();

void create()
{
	set_name("ë����", ({"mao dongzhu", "mao","dongzhu"}));
	set("long", "����һ��������Ů���ӣ�һϮ���£�����������ɫ��\n");

	set("gender", "Ů��");
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
	set("title", "�����̳����ŵ��Ĵ�����");
	
	create_family("������",4,"����");
	set("inquiry", ([
		"ˮͰ": (: ask_shuitong :), 
		"ư": (: ask_piao :), 
		"��ҩ��": (: ask_zhongyao :), 
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
	   if(myfam && myfam["family_name"] != "������")
	   {
           command("say ��Ǳ��̵��ӣ������������Ϊͽ��\n");
		   return;
       }
	   if(ob->query("shen") > -10000)
	   {
           command("say �㻹�����ĺ�����(-10k)����ȥ��ɱ�����׵����˰�.\n");
		  return;
	   }
	   if(ob->query("gender")!="Ů��")
	   {
           command("say ��ֻ��Ů�Ե��ӣ��е����ҵ�ʦ�ְ�ʦ��\n");
		  return;
	   }
	   if(ob->query("combat_exp")>10000 )
       {
			command("say �㾭��ֵ���Ѿ�10k�ˣ��������ҡ��Ҵ�����Ҫ�����ҳϵ��ӣ�\n");
            command("shake "+ob->query("id"));
			return;
	   }
       command("say �ðɣ��Ҿ����������ҵĵ��ӡ�");
	   command("recruit " + ob->query("id"));
       
	   return;	
}


string ask_shuitong()
{
	object me,obj;
	me=this_player();
	if(me->query("family/family_name") != "������")
	{
      command("say ��Ǳ��̵��ӣ�����������\n");
	  return "��!\n";
    }
	if(present("shui tong",me))
	{
      command("say �㲻����һ��ˮͰô��\n");
	  return "��!\n";
    }
	obj=new("d/sld/obj/shuitong");
	command("say "+me->query("name")+"��������ڿ��Ҿ͸��㸶ˮͰ����Ū����!\n");
	obj->move(me);
	return me->query("name")+"ˮͰ������!\n";
}


string ask_piao()
{
	object me,obj;
	me=this_player();
	if(me->query("family/family_name") != "������")
	{
      command("say ��Ǳ��̵��ӣ�����������\n");
	  return me->query("name")+"��������!\n";
    }
	if(present("shui piao",me))
	{
      command("say �㲻����һưô��\n");
	  return me->query("name")+"��������!\n";
    }
	obj=new("d/sld/obj/piao");
	command("say "+me->query("name")+"��������ڿ��Ҿ͸���ˮư����Ū����!\n");
	obj->move(me);
	return me->query("name")+"ư������!\n";
}


string ask_zhongyao()
{
	object me,obj;
	me=this_player();
	if(me->query("family/family_name") != "������")
	{
      command("say ��Ǳ��̵��ӣ�����������\n");
	  return "��!\n";
    }
	command("say ҩ�Ե���������ɵ�ʦ�ֹ�������Ը�������£�\n");
	return me->query("name")+"�úø�!\n";
}
