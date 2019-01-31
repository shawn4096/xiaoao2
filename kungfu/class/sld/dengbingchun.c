// yunsumei.c
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string ask_yaochu();
string ask_zhongyao();
string ask_fangqi();

void create()
{
	set_name("�˱���", ({"deng bingchun", "deng","bingchun"}));
	set("long", "����һ�������̺��������ӣ�����Ӵ��е��Ӱ�ʦ���ˣ�����Ӣ��������\n");

	set("gender", "����");
	set("attitude", "peaceful");
	
	set("str",30);
	set("dex",30);
	set("con",20);
	set("int",20);
	set("per",20);

	set("age", 10+random(10));
	set("shen_type", -1);
	set("str", 25+random(10));
	set("dex", 25+random(10));
	set("con", 25+random(10));
	set("int", 25+random(10));
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
	set_skill("shenlong-tuifa", 150);
	set_skill("dulong-dafa", 150);
	set_skill("youlong-shenfa", 150);
	set_skill("poison", 100);
	set_skill("shenlong-yaoli", 100);
	//set_skill("", 150);
	map_skill("parry","shenlong-tuifa");
	map_skill("leg","shenlong-tuifa");
	map_skill("force","dulong-dafa");
	map_skill("dodge","youlong-shenfa");

	prepare_skill("leg","shenlong-tuifa");
	set("title", "�����̳����ŵ��Ĵ�����");
	
	create_family("������",4,"����");
	set("inquiry", ([
		"ҩ��": (: ask_yaochu :), 
		"��ҩ��": (: ask_zhongyao :), 
		"����": (: ask_fangqi :), 
//		"ҩ��": (: ask_yaopu :), 
//		"��ҩ": (: ask_makeyao :),
//		"��ҩ": (: ask_makeyao :),
//		"ҩ¯": (: ask_yaolu :),
//		"ҩ��": (: ask_yaozhong :),
	]));

	setup();
	
	carry_object("/d/sld/npc/obj/gcp")->wear();

	add_money("silver",15);
}
/*
void init()
{
	object ob;

	::init();

	if( interactive(ob = this_player()) && !is_fighting() ) {
		//remove_call_out("greeting");
		//call_out("greeting", 10, ob);
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
	   if(ob->query("gender")!="����")
	   {
           command("say ��ֻ�����Ե��ӣ�Ů������ëʦ�ð�ʦ��\n");
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
string ask_yaochu()
{
	object me,obj;
	me=this_player();
	if(me->query("family/family_name") != "������")
	{
      command("say ��Ǳ��̵��ӣ�����������\n");
	  return "��!\n";
    }
	if(present("yao chu",me))
	{
      command("say �㲻����һ��ҩ��ô��\n");
	  return "��!\n";
    }
	obj=new("d/sld/obj/yaochu");
	command("say "+me->query("name")+"��������ڿ��Ҿ͸����ҩ������Ū����!\n");
	obj->move(me);
	return me->query("name")+"ҩ��������!\n";
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
	if(!present("yao chu",me))
	{
      command("say ��û����Ӧ�Ĺ������ȥ��ҩ��\n");
	  return "��!\n";
    }
	if(me->query_temp("sld/zhongyao/start"))
	{
      command("say ����ô��ûȥ��ҩ��\n");
	  return "��!\n";
    }

	command("say "+me->query("name")+"�������ɽ����д�ս�����Ա��������һЩҩ��!\n");
	command("say "+me->query("name")+"������½��������ǰ�������Ұ���һЩ����ȥ��ֲҩ��!\n");
	command("say "+me->query("name")+"�����Ȼ��ȥ��ֲҩ�ݣ�����Ҫȥ�Һ��ʵ�ҩ��!\n");
	command("say "+me->query("name")+"�����Ѽ���Щ���ʵ�ҩ�ֶ��ŵ�ҩ��ǽ�ǣ���ȥ���ҿ�!\n");
	command("say "+me->query("name")+"�����ҵ�ҩ�־�ȥ������ҩ��֮�У��ཽˮ��ֱ����Ϊ�ϸ�ҩ�����ͽ�����!\n");
	command("pat "+me->query("id"));
	me->set_temp("sld/zhongyao/start",1);
	return me->query("name")+"������ֲ�������Ҹ���˵�ˣ��Ͻ�ȥ!\n";
}


string ask_fangqi()
{
	object me=this_player();
	if (me->query_temp("sld/zhongyao/start"))
	{
		command("say ��Ȼ�����Ѷȣ�������Ҳûʲô����ȥЪϢ��ɣ�\n");
		me->delete_temp("sld");
		me->apply_condition("job_busy",5);
		me->apply_condition("sldjob_zhongyao",5);

		return "���ڵ��µ�������һ������һ���ˣ�\n";
	}
	command("say û�²�Ҫ��ɧ���ң�\n");
	return me->query("name")+"����!\n";

}

//������Ʒ
int accept_object(object who, object ob)
{
	
	int sum,gold,getshen;
	object sil;
	sum=10+random(10);
	
	if (ob->query("owner")==who->query("id")
		&& who->query_temp("sld/zhongyao/miaook")		
		&& ob->query("id")=="yao cao")
	{
		getshen=-1;
		gold=1+random(1);				
		
	//	who->set("job_name","������ҩ");			
		who->apply_condition("job_busy",3);		
		who->delete_temp("sld/zhongyao");
		who->delete_temp("sld");
		command("thumb "+who->query("id"));

		tell_object(who,RED"\n�˱������˵�ͷ����"+ob->query("name")+RED+"���뻳�У�\n"NOR);
		command("say �ܺã�"+who->query("name")+"����Ȼ�����������ˣ��Ҿ�Ӧ�ý����㣡\n");
		
		tell_object(who,GRN"\n�˱����ó����ɼ�¼��������"+who->query("name")+HIY+chinese_number(gold)+GRN"������ɹ����Ľ�����\n"NOR);
		who->add("party/gongji",gold);
		
		if (who->query("combat_exp")<300000)
		{
			tell_object(who,GRN"\n�˱��������ó�Щ���ӣ��ݸ�"+who->query("name")+HIY+chinese_number(sum)+GRN"����������ȥ�Ⱦ�ȥ�ɣ�\n"NOR);
			sil=new("clone/money/silver");
			sil->set("set_amount",sum);
			sil->move(who);
			TASKREWARD_D->get_reward(who,"������ҩ",getshen,0,0,4+random(3),0,0,0,this_object());
		}

		//TASKREWARD_D->get_reward(who,"����ѵ��",getshen,0,0,3+random(4),0,0,0,this_object());

			
		who->set("job_name", "������ҩ");
		if (who->query("combat_exp")>600000)
		{
			who->add("job_time/������ҩ",1);
		}
		who->apply_condition("job_busy",3);
		who->apply_condition("sldjob_zhongyao",3);
		destruct(ob);
		return 1;
	}

}