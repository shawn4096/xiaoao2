// yinliting.c殷梨亭

inherit NPC;

int ask_me();
int ask_menggu();
void create()
{
        set_name("殷梨亭", ({ "yin liting", "yin" }));
        set("nickname", "武当六侠");
        set("long", 
                "他就是张三丰的六弟子殷梨亭。\n"
                "长得一表人才，且精于武当剑法，就是生性较腼腆。\n");
        set("gender", "男性");
        set("age", 28);
        set("attitude", "peaceful");
        set("shen", 9000);
        set("str", 26);
        set("int", 30);
        set("con", 26);
        set("dex", 28);
        set("unique", 1);
        set("max_qi", 28000);
        set("max_jing", 10000);
        set("neili", 25000);
        set("max_neili", 25000);
        set("jiali", 150);
        set("combat_exp", 6000000);

        set_skill("force", 380);
        set_skill("yinyun-ziqi", 380);
        set_skill("dodge", 380);
        set_skill("tiyunzong", 380);
        set_skill("cuff", 380);
        set_skill("taiji-quan", 380);
        set_skill("parry",380);
        set_skill("sword", 380);
        set_skill("taiji-jian", 380);
        set_skill("taoism", 150);
        set_skill("literate", 100);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        prepare_skill("cuff", "taiji-quan");
        create_family("武当派", 2, "弟子");
        set("inquiry", ([
                "纪晓芙" : (: ask_me :),
				"蒙古入侵" : (: ask_menggu :),
        ]));

        setup(); 
        carry_object("/d/wudang/obj/white-robe")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}
void kill_ob(object me)
{
          set("chat_chance_combat", 40);
	      set("chat_msg_combat", ({
	       (: perform_action, "sword.lian" :),
               (: perform_action, "dodge.zong" :),
               (: perform_action, "cuff.luanhuan" :),
          }));
          ::kill_ob(me);
}
/*
int accept_fight(object me)
{
        if((int)me->query("shen") < 1) {
           command("say 习武之人应志在锄恶济善，"+RANK_D->query_respect(me)+"目露瘴气，有违武学之本？");
           return 0;
        }
        ::fight_ob(me);
         return 1;
}
*/
int ask_me()
{
        object me=this_player();
        if(base_name(environment(this_object())) != query("startroom")) return 0;
        if (me->query("family/family_name")=="明教")
		 {
			command("heng "+me->query("id"));
			command("say 魔教教徒，纳命来吧！");
		    this_object()->kill(me);
		  }
		else
	    {
		  command("blush "+(string)me->query("id"));
          command("say 既然你是纪姑娘的朋友，那就给你行个方便吧 !\n");		    
          command("open door");
          message_vision("殷梨亭一侧身，把$N让进了小院。\n",me);
	      me->move("/d/wudang/houyuan");
          tell_room(environment(me), me->name()
		  + "从北面的林间小径走了过来。\n",({me}));
          command("close door");
          return 1;
		 }
}

int ask_menggu()
{
        object me=this_player();
        if(base_name(environment(this_object())) != query("startroom")) return 0;
        if (me->query("relife/gifts/total")<8)
        {
			command("pat "+me->query("id"));
			command("say 你现在还很弱，至少要参悟8点属性才能去体验真正的武当绝世武技。\n");
			command("say 真不错，武当未来就看你的了！\n");
			return 0;
        }
		if (me->query("mwd/over"))
        {
			command("pat "+me->query("id"));
			command("say 你已经解救武当安危，我非常敬佩你！\n");
		//	command("say 真不错，武当未来就看你的了！\n");
			return 0;
        }
		if (me->query("family/family_name")!="武当派")
		{
			command("sigh "+me->query("id"));
			command("say 你不是武当弟子，不要来开我的玩笑了！");
		   // this_object()->kill(me);
		   return 1;
		  }
		if (me->query("family/family_name")=="明教")
		{
			command("heng "+me->query("id"));
			command("say 魔教教徒，纳命来吧！");
		    this_object()->kill(me);
		  }
		else
	    {
		  command("say 我在明教山脚为一群高手所困，少林高手全部战死，其中包括空性大师。\n");
          command("say 我当时听那群人说“先诛少林，后灭武当” !\n");		    
          command("say 我担心他们偷袭武当山，你赶紧先回武当山去保护师傅。\n");
		  command("say 师傅太老人家年纪大，怕有闪失，此事万万耽误不得。\n");
		  command("say 你要从玄岳门开始，步步小心勘察，以防有间隙混入武当山。\n");
		  command("say 暗藏的敌人不知道有多少，但对待敌人绝不能手软，务必要斩杀干净！\n");
          message_vision("殷梨亭说完后忧心忡忡的样子，甚是凄苦。\n",me);
	      me->move("/d/wudang/wdroad8");
          tell_room(environment(me), me->name()
		  + "神色焦虑，急匆匆的走了过来。\n",({me}));
		  me->set_temp("mwd/start",1);
          return 1;
		 }
}
