// ��ͷ��

inherit F_MASTER;
inherit NPC;

int ask_book();

void create()
{
	set_name("��ͷ��", ({ "pang toutuo","toutuo","pang" }));
	set("long","���ݵó��棬����Ƥ����ͷ��˫�����ݣ�������罩ʬһ�㣬�������磬\nͷ��һ��ͭ����ס���������ϴ������ۣ�������������ǹ����¼���һ�㣬\n���������̵Ļ�����\n");
	set("gender", "����");
	set("title", "�����̻���");	
	set("age", 40);       
	set("str", 40);
	set("int", 12);
	set("con", 22);
	set("dex", 22);
	set("per", 10);
	set("combat_exp", 9700000);
	set("shen", -50000);
	set("attitude", "peaceful");
	set("max_qi",22500);
	set("max_jing",6500);
	set("neili",28000);
	set("max_neili",28000);
	set("jingli",5000);
       set("eff_jingli",5000);
	set("jiali",190);
	set("score", 20000);

	set_skill("force", 400);
	set_skill("dodge", 400);
	set_skill("parry",400);
	set_skill("strike",400);
	set_skill("leg",400);
	set_skill("hook",400);
	set_skill("shenlong-tuifa",400);
	set_skill("canglang-goufa",400);
	set_skill("huagu-mianzhang", 400);
	set_skill("youlong-shenfa",400);
	set_skill("dulong-dafa",400);
      
	map_skill("force", "dulong-dafa");
	map_skill("dodge", "youlong-shenfa");
    map_skill("strike", "huagu-mianzhang");
    map_skill("hook","canglang-goufa");
	map_skill("leg","shenlong-tuifa");
	map_skill("parry","huagu-mianzhang");

	prepare_skill("strike","huagu-mianzhang");
	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
		//(: perform_action, "leg.zhuiming" :) ,
		(: perform_action, "strike.bujue" :) ,
		(: perform_action, "strike.jingtao" :) ,
		(: perform_action, "strike.mianzhang" :) ,
		(: perform_action, "hook.diqing" :) ,
		(: perform_action, "hook.luda" :) ,
		(: perform_action, "hook.zixu" :) ,
		(: exert_function, "wudi" :) ,
		(: exert_function, "shexin" :) ,
		(: exert_function, "pendu" :) ,
	}));      
	set("inquiry", ([
		"��������" : (: ask_book :),
		"book" : (: ask_book :),
	]) );
         set("chat_chance", 3);
        set("chat_msg", ({
                "��ͷ��˵������ϧ����������Ȼ���������Ǹ��ط�������û��˭��ȥ�һ���������\n",
        }) );

      create_family("������",2, "����");
      setup();
      carry_object("d/sld/npc/obj/bupao")->wear(); 
      carry_object("d/sld/npc/obj/hook")->wield();    
}

int ask_book()
{
	object book;
	mapping myfam;
	object me=this_player();

	myfam = (mapping)me->query("family");
	if(!myfam || myfam["family_name"] != "������")
		return 0;

	book= unew("d/sld/npc/obj/hook-book");
	if (!book)  
	{
		command("say ���������Ѿ������������ˣ�");
		return 1;
	}

	command("say �ðɣ��Ȿ������������"+me->query("name")+"�����ȥ�úÿ����ɡ�");
	book->move(me);      
        me->start_busy(2);

	return 1;
}

int prevent_learn(object me, string skill)
{
	return 0;
}

int recognize_apprentice(object ob)
{
	mapping myfam;
	object hw;

	myfam = (mapping)ob->query("family");
	if(myfam && (myfam["family_name"] == "������")&&(ob->query("shen",1) >0))  {
		command("say �ߣ��㾹Ȼ�ҺͰ׵����˸���һ���ǲ��ǲ�����ˣ���ȥ���ݺú÷�ʡ��ʡ�ɣ�");
		if(!objectp(hw=find_object("/d/sld/npc/obj/heiwu")))
			hw=load_object("/d/sld/npc/obj/heiwu");
		ob->set("in_heiwu",time());
		ob->move(hw);        
		return 0;
	}
       if(myfam && (myfam["family_name"] == "������")&&(ob->query("shen",1) < -30000)
          && (ob->query_skill("dulong-dafa",1)>=100) && 
          (ob->query_skill("huagu-mianzhang",1)>=100))
        {
             return 1;
        }
    	return 0;
}
