#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_tiejiao();

void create()
{
        set_name("����һ", ({"wang chuyi", "wang"}));
        set("gender", "����");
        set("age", 35);
        set("class", "taoist");
        set("nickname",RED"������"NOR);
        set("long",
                "������ȫ������֮������һ�����ˡ�������޳����������࣬\n"
                "��縺���Ʈ����ǰ����̬���������߽�����Ѱ�����㴫��,����\n"
				"������վ������������ҹ����������Ⱥ�ܣ��˳ơ������ɡ�");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 32);
        set("int", 30);
        set("con", 32);
        set("dex", 30);

        set("title","ȫ������֮��");

        set("qi", 34500);
        set("max_qi", 34500);
		set("eff_qi",34500);
        set("jing", 5200);
        set("max_jing", 5200);
        set("neili", 24700);
        set("max_neili", 24700);
        set("jiali", 200);
        set("level", 18);
        set("combat_exp", 9400000);

        set_skill("force", 450);
        set_skill("xiantian-gong", 450);
        set_skill("sword", 450);
        set_skill("quanzhen-jianfa",450);
        set_skill("dodge", 450);
        set_skill("jinyan-gong", 450);
        set_skill("parry", 450);
        set_skill("literate",250);
        set_skill("strike", 450);
        set_skill("haotian-zhang", 450);
        set_skill("taoism",200);
	    set_skill("medicine", 200);
        set_skill("tiangang-beidouzhen", 450);
		set_skill("leg", 200);
        set_skill("yuanyang-lianhuantui", 450);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
		map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("strike","haotian-zhang");
		prepare_skill("leg", "yuanyang-lianhuantui");

        create_family("ȫ���", 2, "����");

        set("book_count",1);
	    set("inquiry", ([               
               "���ž���" : (: ask_tiejiao :),
			   
        ]));	
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                 (: perform_action, "sword.sanqing" :),
                (: perform_action, "sword.qixing" :),
                (: perform_action, "sword.ding" :),
				(: perform_action, "sword.jianqi" :),
                (: perform_action, "sword.lian" :),
				(: exert_function, "daojue" :),
				(: exert_function, "wuqi" :),
				(: exert_function, "yusuo" :),
        }));
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

void attempt_apprentice(object ob)
{
       if (ob->query("gender")!="����")
       {
		   command("say ��һ��Ů�˼�������Ϊʦ���ѵ�����ʲô��ͼ���ɣ���\n");
		   command("say ��ȫ��һ��������ȫ���ڵ���Ϊ�ϣ����������������Ҳ��ó���\n");
		   command("say �㻹��ȥѰ����ʦ���徲ɢ���ﲻ���������Ƿ����㣿\n");
		   return ;

       }

	   if ((int)ob->query("shen") < 1500000) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(1.5m)");
               return;
       }
	   if (ob->query("party/gongji") < 3000) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڽ��ɹ������棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(��Ҫ3000�����ɹ���ֵ)\n");
               return;
       }
	   if (!ob->query("quest/qz/dichuan"))
	   {
		       command("say ��������еմ����ӣ�����������");
              return;

	   }
	   if (ob->query_skill("xiantian-gong",1) < 300) {
               command("say ��ȫ���һ����ȫ�����칦�������칦����300��������������");
               return;
       }
	 
       command("say �ðɣ�ƶ�����������ˡ�");
       command("recruit " + ob->query("id"));
       ob->set("title", "ȫ�������״�����");
       ob->set("class","taoism");
	   return;
}

string ask_tiejiao()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="ȫ���")
	{
		return "�㲻����ȫ��̵��ӣ�\n";
	}
	if (me->query("shen") < 500000) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڵ��з��棬" + RANK_D->query_respect(me) +
                       "�Ƿ����ò���500k��(1m)");
               return "";
       }
	   if (me->query("party/gongji") < 2500) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڽ��ɹ������棬" + RANK_D->query_respect(me) +
                       "�Ƿ����ò�����(��Ҫ2500�����ɹ���ֵ)\n");
               return "";
       }
	   if (!me->query("quest/qz/dichuan"))
	   {
		       command("say ��������еմ����ӣ�����������");
              return "";

	   }
	   if (me->query_skill("xiantian-gong",1) < 200) {
               command("say ��ȫ���һ����ȫ�����칦�������칦����200��������������");
               return "";
       }
	   if (me->query_skill("yuanyang-lianhuantui",1) < 200) {
               command("say ��ԧ�������Ȳ���200��������������");
               return "";
       }
	   	if (me->query("quest/qz/yylht/tiejiao/pass"))
		{
			return "�������ԧ���ȵ����ž����Ѿ��⿪�ˡ���\n";
		}
		if (time()-me->query("quest/qz/yylht/tiejiao/time")<86400)
		{
			return "������̫Ƶ���ˣ�����������\n";
		}
	   command("say ���������������������Ҫ�۳�������ɹ���ֵÿ��100�㣬���������û�ʸ�����ҡ�\n\n\n\n");

       command("say �ðɣ���Ȼ�����Ŭ�����Ҿ͸��������о��ϡ�\n");
       command("whisper "+me->query("id"));
	   if (me->is_busy())
	   {
		  return "��������æ������!\n";
	   }
		me->start_busy(10);
		if (me->query("party/gongji")<100)
		{
			return "������ɹ���ֵ����100�㣬�����Ŭ��ȥΪ���ɷܶ���\n";
		}
		me->add("party/gongji",-100);

		message_vision(HIC"$N����Ŀ���$n������˵���������ɵ�������ʵ�ɿ������ɸ��䣬����������ɶ���̫��ͬ��\n"
							"���Ȼ������˳̶ȣ��Ҿʹ��������С����ž������İ��أ��Ҹ�����ʾһ�飬�����Լ��������ˡ�\n"+
					   HIR"\n\n\n$N����վ������Ȼ������Ծ��˫�������߳����ߵĿ��������ۡ����죡\n"NOR,this_object(),me);
		
	 
		i = 20;
		  if(me->query("m-card-vip")) i =  18;
		  if(me->query("y-card-vip")) i =  15;
		  if(me->query("buyvip"))     i =  10;
		  i=random(i);
		j=random(me->query("kar"));
		command("say �㿴����ô��\n");
		command("pat "+me->query("id"));
		if( i<5
			&& me->query("kar")<31
			&& j >= 22 ) 
		{
			tell_object(me,HIC"\n�����˵�����һ������ָ�㣬�����������Լ���������ԧ���ȵ������ĵã�����ӡ�ա�\n"NOR);
			tell_object(me,HIR"\n��Ȼ�ŵ�ӿȪѨһ�ɴ������������ʱ�о��������࣬�Ȳ�����������˲���������������������š�\n"
						NOR);
			me->set("quest/qz/yylht/tiejiao/pass",1);
			log_file("quest/qztiejiao", sprintf("%8s(%8s) ʧ��%d�κ�ѧ�������ɾ���,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), me->query("quest/qz/yylht/tiejiao/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			command("haha"+me->query("id"));		
			
			return "��ϲ���������ɾ��������ɹ�!\n";
			
		}	
	   else
		{
			log_file("quest/qztiejiao", sprintf("%8s(%8s) ���������ɾ�������ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), me->query("quest/qz/yylht/tiejiao/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			
			tell_object(me,HIY"����������һ��ָ�㣬���Ƕ�����ԧ���Ⱦ������ɾ����İ���ȫȻ����Ҫ�졣\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			me->add("quest/qz/yylht/tiejiao/fail",1);
			me->set("quest/qz/yylht/tiejiao/time",time());
			me->start_busy(1+random(3));
			
			return "�ǳ��ź���������ԧ����֮�����ɾ���ʧ��"+me->query("quest/qz/yylht/tiejiao/fail")+"�Ρ�\n";
		}

     
}

