// yunsumei.c
#include <ansi.h>

inherit NPC;
string ask_lianyao();
string ask_fangqi();
string ask_fire();

void create()
{
	set_name("����÷", ({"yun sumei", "yun","sumei"}));
	set("long", "����һ�������̺�����Ů�����ӣ�����������ɫ��\n");

	set("gender", "Ů��");
	set("attitude", "peaceful");
	
	set("str",30);
	set("dex",30);
	set("con",20);
	set("int",20);
	set("per",20);
	set("no_kill",1);
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
	set_skill("whip", 150);
	set_skill("lingshe-bianfa",150);
	map_skill("parry","shenlong-tuifa");
	map_skill("leg","shenlong-tuifa");
	map_skill("force","dulong-dafa");
	map_skill("dodge","youlong-shenfa");
	map_skill("whip","lingshe-bianfa");

	prepare_skill("leg","shenlong-tuifa");
	set("title", "�����̳����ŵ��Ĵ�����");

	create_family("������",4,"����");
	set("inquiry", ([
		"����": (: ask_fire :), 
//		"��ҩ��": (: ask_zhongyao :), 
	//	"����": (: ask_fangqi :), 
//		"ҩ��": (: ask_yaopu :), 
		"��ҩ": (: ask_lianyao :),
//		"��ҩ": (: ask_makeyao :),
//		"ҩ¯": (: ask_yaolu :),
		"����": (: ask_fangqi :),
	]));

	setup();
	
	carry_object("/d/sld/npc/obj/gcp")->wear();

	add_money("silver",15);/*	*/
}

string ask_fire()
{
	object me,ob;
	me=this_player();
	if (me->query("family/family_name")!="������")
	{
		command("say �㲻���������̵��ӣ�����������\n");
		return "";
	}
	if (me->query("party/gongji")<100)
	{
		return "������ɹ�������100���������ң�\n";
	}
	if (present("fire",me))
	{
		return "�Ҳ��Ǹ���һ�������ô��\n";
	}

	me->add("party/gongji",-100);


	ob=new("/clone/misc/fire");
	ob->move(me);
	return "�۳���100���ɹ������ú��ã������ɽҰ��϶࣬��������֣�\n";
}

string ask_lianyao()
{
	object me,*obj;
	int x;
	me=this_player();
	obj = users();
	x = sizeof(obj);
	//�ų�������
	while(x--) {
		  if ( obj[x]->query_temp("lianyao/start")
			  && obj[x]!=me
			  && environment(me)==environment(obj[x]))
			 {
				  message_vision(HIY"$N��ͼ��ʼ��ҩ������ȴ����"+obj[x]->query("name") +HIY"�Ѿ����Ķ���ʼ��ҩ�ˣ�\n"NOR,me);	
				  //me->move("d/quanzhen/liangong");
				  return me->query("name")+"����������\n";
			}
			
	}
	
	if (me->query("family/family_name")!="������")
	{
		return "�㲻���������̵��ӣ�����������\n";
	}
	if (me->query_skill("dulong-dafa",1)<250)
	{
		return "��Ķ����󷨲���250��������ҩ��\n";
	}
	if (me->query_skill("shenlong-yaoli",1)<200)
	{
		return "�������ҩ����200��û���κξ���������ҩ��\n";
	}
	if (me->query_skill("poison",1)<150)
	{
		return "��Ķ��Ʋ���150��û���κξ���������ҩ��\n";
	}
	if (me->query_skill("yaozhi",1)<200)
	{
		return "���ҩֲ������200���������ң�\n";
	}

	if (me->query("combat_exp")<2000000)
	{
		return "��ľ���ֵ����2m�����ܲ���ҩ�������ħӰ�죿\n";
	}
	if (me->query_temp("lianyao/start"))
	{
		return "������ȥ��ҩ��Ϊɶ�ڴ�ɵ���ţ�\n";
	}
	if (me->query("job_name")=="������ҩ")
	{
		return "�㷽�Ÿո���ҩ��ϣ���Ϣ��������\n";
	}
	if (me->query_condition("job_busy"))
	{
		return "�����ڹ���æµ����Ϣ��������\n";
	}
	if (me->query_condition("sldjob_lianyao"))
	{
		return "��������������ҩ�����У���Ϣ��������\n";
	}


	me->set_temp("lianyao/start",1);
	command("say "+me->query("name")+",��Ȼ����Ҫ��ʼ��ҩ����ȥ�ɣ�\n");
	command("say ��ҩ�����У���ϸ�鿴ҩ¯Ҫ�󣬰������̹淶��ÿһ�����̶�Ҫ����Դ���\n");

	command("say ��Ҫע���������ҩ����Ϊ���Ի�Ч����������ħ������ħ��Ϊ������"+me->query("name")+"����Ҫ���ģ�\n");
	command("say "+me->query("name")+"����ҩ���˽�ҩ���ң��н�����ȥ�ɣ�\n");
	me->apply_condition("sldjob_lianyao",40);
	return "�Ҵ�������ҩ��һ�Ų������ѧ�ʣ�\n";
}
string ask_fangqi()
{
	object me,ob,lu;
	me=this_player();
	if (me->query("family/family_name")!="������")
	{
		command("say �㲻���������̵��ӣ�����������\n");
		return "";
	}
	

	lu=present("yao lu",environment(this_object()));
	/*
	if (lu->query("lianyao"))
	{
		command("say ë��ë��,һ�㶼����ʡ�ģ�\n");
		return "���Ȱ�ҩ¯�Ļ�������˵��\n";
	}*/
	
	command("say ��Ȼ�������˾Ͳ�Ҫ�ٷѾ��ˣ���ȥ��ЪϢȥ�ɣ�\n");
	me->delete_temp("lianyao");
	
	me->apply_condition("job_busy",4);
	me->clear_condition("sldjob_lianyao");
	lu->delete("lianyao");
	me->add_busy(1);
	if (!me->query_temp("lianyao"))
	{
		command("say ɶ��û������Ҫ����ɶ��\n");
		return "";

	}
	return "�ߣ��׳԰׺Ȳ��ɻ\n";
}
//������Ʒ

int accept_object(object me, object ob)
{
	//��ҩ
	//����Խ�࣬����ֵԽ��
	int jobs;
	jobs=me->query("job_time/������ҩ");

	if (ob->query("owner")==me->query("id")
		&&ob->query("id")==me->query_temp("lianyao/yaoid"))
	{
		message_vision(HIY"����÷�������"+ob->query("name")+"�����ֿ������Ǻ��棡\n"NOR,me);
		

		message_vision(HIC"����÷��"+me->query("name")+"���˵�˵���������������Ȼ������һ�Ž���"+HIY+ob->query("name")+HIC"�ĵ�ҩ���Һ���Ľ��!��\n"NOR,me);
		me->add("party/gongji",2);
		message_vision(HIM"����÷�ó����ͱ���"+me->query("name")+"�����˶������ɹ���ֵ!��\n"NOR,me);

		command("smile "+me->query("id"));
		//�ж����ԣ�����Խ�࣬����ֵԽ��
		TASKREWARD_D->get_reward(me,"������ҩ",-1,0,0,1+random(4),0,0,0,this_object());
		me->set("job_name", "������ҩ");
		me->delete_temp("lianyao");
		me->apply_condition("job_busy",3);
		
		destruct(ob);
		//�ж��綾����
				//Ԥ��������ʾ�ӿ�
		//�մ�
		//�������35���ϣ�25��������
		if (random(me->query("job_time/������ҩ"))>4000
			&& random(me->query("kar"))>26
			&& me->query("con")>35
			&& !me->query("quest/sld/dldf/pendu/start")
			&& jobs % 20 ==0	
			&& me->query("quest/qz/dichuan"))
		{
			
				message_vision(HIC"����÷��$N�����˴�Ĵָ��˵���������������Ϊ�Ҵ�����������ҩ����ǽ��е��ӿ�ģ����\n"NOR,me);
				command("say "+me->query("name")+"���Ҿͽ��������綾�������Ϣ͸©���㣡\n");
				command("say "+me->query("name")+"���������̶���ҩ���о���������ҵ�ʦ��½������\n");
				command("say "+me->query("name")+"��������ν���ҩ�����ڹ���ѧ�����������ľ�����\n");

				command("chat* thumb "+me->query("id"));
				command("rumor "+me->query("name")+"�������÷����������ý����綾���ܵĻ��ᣡ\n");
				command("chat "+me->query("name")+"���Ҵ������ĺ��ĵ��ӣ�������ͬ������չˣ�\n");
				me->set("quest/sld/dldf/pendu/start",1);
		}
		
		return 1;
	}
	
}

void die()
{
	object ob,room;
	ob=this_object();
	//room=load_object("d/sld/lgxroom");

	if (!query_temp("living"))
	{
		ob = new("/d/sld/npc/yunsumei");
		ob->move("/d/sld/lianyaoshi");
	}
	::die();
}

