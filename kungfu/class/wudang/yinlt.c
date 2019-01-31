// yinliting.c����ͤ

inherit NPC;

int ask_me();
int ask_menggu();
void create()
{
        set_name("����ͤ", ({ "yin liting", "yin" }));
        set("nickname", "�䵱����");
        set("long", 
                "�����������������������ͤ��\n"
                "����һ���˲ţ��Ҿ����䵱�������������Խ�����\n");
        set("gender", "����");
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
        create_family("�䵱��", 2, "����");
        set("inquiry", ([
                "����ܽ" : (: ask_me :),
				"�ɹ�����" : (: ask_menggu :),
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
           command("say ϰ��֮��Ӧ־�ڳ�����ƣ�"+RANK_D->query_respect(me)+"Ŀ¶��������Υ��ѧ֮����");
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
        if (me->query("family/family_name")=="����")
		 {
			command("heng "+me->query("id"));
			command("say ħ�̽�ͽ���������ɣ�");
		    this_object()->kill(me);
		  }
		else
	    {
		  command("blush "+(string)me->query("id"));
          command("say ��Ȼ���Ǽ͹�������ѣ��Ǿ͸����и������ !\n");		    
          command("open door");
          message_vision("����ͤһ������$N�ý���СԺ��\n",me);
	      me->move("/d/wudang/houyuan");
          tell_room(environment(me), me->name()
		  + "�ӱ�����ּ�С�����˹�����\n",({me}));
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
			command("say �����ڻ�����������Ҫ����8�����Բ���ȥ�����������䵱�����似��\n");
			command("say �治���䵱δ���Ϳ�����ˣ�\n");
			return 0;
        }
		if (me->query("mwd/over"))
        {
			command("pat "+me->query("id"));
			command("say ���Ѿ�����䵱��Σ���ҷǳ������㣡\n");
		//	command("say �治���䵱δ���Ϳ�����ˣ�\n");
			return 0;
        }
		if (me->query("family/family_name")!="�䵱��")
		{
			command("sigh "+me->query("id"));
			command("say �㲻���䵱���ӣ���Ҫ�����ҵ���Ц�ˣ�");
		   // this_object()->kill(me);
		   return 1;
		  }
		if (me->query("family/family_name")=="����")
		{
			command("heng "+me->query("id"));
			command("say ħ�̽�ͽ���������ɣ�");
		    this_object()->kill(me);
		  }
		else
	    {
		  command("say ��������ɽ��ΪһȺ�������������ָ���ȫ��ս�������а������Դ�ʦ��\n");
          command("say �ҵ�ʱ����Ⱥ��˵���������֣������䵱�� !\n");		    
          command("say �ҵ�������͵Ϯ�䵱ɽ����Ͻ��Ȼ��䵱ɽȥ����ʦ����\n");
		  command("say ʦ��̫���˼���ʹ�������ʧ�����������󲻵á�\n");
		  command("say ��Ҫ�������ſ�ʼ������С�Ŀ��죬�Է��м�϶�����䵱ɽ��\n");
		  command("say ���صĵ��˲�֪���ж��٣����Դ����˾������������Ҫնɱ�ɾ���\n");
          message_vision("����ͤ˵���������������ӣ�������ࡣ\n",me);
	      me->move("/d/wudang/wdroad8");
          tell_room(environment(me), me->name()
		  + "��ɫ���ǣ����Ҵҵ����˹�����\n",({me}));
		  me->set_temp("mwd/start",1);
          return 1;
		 }
}
