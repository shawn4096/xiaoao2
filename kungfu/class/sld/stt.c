// 胖头陀

inherit F_MASTER;
inherit NPC;

int ask_huxi();
int leg=3;
int time=0;

void create()
{
	set_name("瘦头陀", ({ "shou toutuo","toutuo","shou" }));
	set("long","他又矮又胖，肉墩墩地像个园球，秃顶无发，身上穿件布袍，他是神龙教的护法。\n");
	set("gender", "男性");
	set("title", "神龙教护法");	
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

	prepare_skill("leg","shenlong-tuifa");

	set("inquiry", ([
		"护膝" : (: ask_huxi :),
		"huxi" : (: ask_huxi :),
	]) );
      
      create_family("神龙教",2, "护法");
      setup();
      carry_object("/d/sld/npc/obj/bupao")->wear(); 
      carry_object("/d/sld/npc/obj/huxi")->wear(); 
}

int ask_huxi()
{
	object huxi;
	mapping myfam;
	object me=this_player();

	myfam = (mapping)me->query("family");
	if(!myfam || myfam["family_name"] != "神龙教")
		return 0;

	if(time=0)
		time=time();
	else if((time()-time)>=900)
	{
		time=time();
		leg=3;
	}

	if (leg<=0) {
		command("say 护膝都给别人拿走了！");
		return 1;
	}

	huxi= new("/d/sld/npc/obj/huxi");
	if (!huxi)  return notify_fail("异常错误！\n");

	command("say 好吧，这副护膝"+me->query("name")+"你就拿去吧。");
	huxi->move(me);      

	leg--;
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
	if(myfam && (myfam["family_name"] == "神龙教")&&(ob->query("shen",1) >0))  {
		command("say 哼！你竟然敢和白道中人搞在一起，是不是不想活了？！去黑屋好好反省反省吧！");
		if(!objectp(hw=find_object("/d/sld/npc/obj/heiwu")))
			hw=load_object("/d/sld/npc/obj/heiwu");
		ob->set("in_heiwu",time());
		ob->move(hw);        
		return 0;
	}
       if(myfam && (myfam["family_name"] == "神龙教")&&(ob->query("shen",1) < -30000)
          && (ob->query_skill("dulong-dafa",1)>=100) && 
          (ob->query_skill("huagu-mianzhang",1)>=100))
        {
             return 1;
        }
    	return 0;
}