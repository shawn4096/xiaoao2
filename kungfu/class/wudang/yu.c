// yu.c ������
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_me();
void create()
{
        set_name("������", ({ "yu lianzhou", "yu" }));
        set("nickname", "�䵱����");
        set("long", 
                "������������Ķ����������ۡ�\n"
                "��������ʮ�꣬��Ŀ��࣬�������ء�\n"
                "�����䵱�����������ڶ�������ȴ�����\n");
        set("gender", "����");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen", 12000);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 28);
        set("unique", 1);
        set("max_qi",45000);
        set("eff_jingli",15000);
        set("max_jing", 15000);
        set("neili",45000);
        set("max_neili", 45000);
        set("jiali", 150);
        set("combat_exp",12500000);

        set_skill("force", 460);
        set_skill("yinyun-ziqi", 460);
        set_skill("dodge",460);
        set_skill("tiyunzong",460);
        set_skill("wudang-quan",460);
        set_skill("cuff",460);
        set_skill("hand",460);
        set_skill("taiji-quan", 460);
        set_skill("juehu-shou",460);
        set_skill("parry", 460);
        set_skill("sword", 460);
        set_skill("taiji-jian", 460);
        set_skill("taoism", 200);
        set_skill("literate", 200);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("parry", "taiji-quan");
        map_skill("sword", "taiji-jian");
        map_skill("cuff", "wudang-quan");
        map_skill("hand", "juehu-shou");

        prepare_skill("cuff", "wudang-quan");
        prepare_skill("hand", "juehu-shou");
        set("inquiry", ([
                "������" : (: ask_me :),
               // "��צ" : (: ask_me :),
               ]));
        create_family("�䵱��", 2, "����");

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
        carry_object("/d/wudang/obj/daolv")->wear();
}

void kill_ob(object me)
{
        set("neili", 5000); 
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
              (: perform_action, "dodge.zong" :),
        }));
        ::kill_ob(me);
}

void attempt_apprentice(object ob)
{
        object me;
        me=this_player();
        if ((int)ob->query("shen") < 1500000) {
                command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�����1.5m�����������");
                command("say " + RANK_D->query_respect(ob) + "��������" +
                   "��������֮�£��ҾͿ������㡣");
                return;
        }
	   if ((int)ob->query_skill("taoism",1) < 180) {
                command("say ��ĵ�ѧ��Ϊ������ֻ�������ѧ�˻�צ�����ֺ��ȥ���ˣ�");
                return;
        }
	   if ((int)ob->query_skill("yinyun-ziqi",1) < 300) {
                command("say �����������Ϊ����300��ֻ�������ѧ�˻�צ�����ֺ��ȥ���ˣ�");
                return;
        }
	    if (ob->query("gender") != "����" && ob->query("gender") != "Ů��") {
                command("say �������������������ѧ�����֣�");
                return;
        }
        if (present("letters", me)){
        	destruct(present("letters",me));
                command("say �ðɣ���Ȼ" + RANK_D->query_respect(ob) + "����ʦ�ܵĽ����ţ�Ҳ��" +
                        "�ұ����ˣ������������ɡ�");
                command("recruit " + ob->query("id"));
        }
        else
                command("say �ҶԵ���Ҫ���ϡ����ĵ������߲���ѧ�һ�צ������!");
        return;
          
}
string ask_me()
{
  object me;
        me=this_player();
		 if (me->query("family/family_name") != "�䵱��" || me->query("family/master_id") != "yu lianzhou")
			 return "\n�㲻���ҵĵ��ӣ������ʲô��\n";
         if ((int)me->query("shen") < 5000) {
                command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
                command("say " + RANK_D->query_respect(me) + "��������" +
                   "��������֮�£��ҾͿ������㡣");
                return;
        }
	     if ((int)me->query_skill("taoism",1) < 100) {
                command("say ��ĵ�ѧ��Ϊ������ֻ�������ѧ�˻�צ�����ֺ��ȥ���ˣ�");
                return;
        }
	    if (me->query("gender") != "����" && me->query("gender") != "Ů��") {
                command("say �������������������ѧ�����֣�");
                return;
        }
        
	   //����ʱ��;���������
	   
	    if(me->query("jh_time")&& (time()-me->query("jh_time",1))<86400)
	    {
		   command("shake "+me->query("id"));
		   if(random(2)) return "�����æ�ˣ�"+RANK_D->query_respect(me) +"������Ϣȥ�ɣ�";
		   else return "ѧϰ������Ҳ���ü���һʱ��"+RANK_D->query_respect(me) +"������Ϣȥ�ɣ�";
	    }
		if (me->query("quest/wudang/juehu"))
		{
			command("heng ");
			command("say �㲻���Ѿ��⿪��������ô�������˸��҆���ʲô��\n");
			return;
		}
        me->set("jh_time",time());
	    //me->set(QUEST_JH+"combat_exp",me->query("combat_exp")); 
		
		if (random(me->query("kar")) > 20)
	     { 
            command("haha");
		    command("pat "+me->query("id"));
		    message_vision(HIY"�����۸�������Ķ�������˵��һ������.....\n"NOR,me);
		    me->set("quest/wudang/juehu",1);
		    command("admire "+me->query("id"));
			return;
		 }	 
		 return "������˵������������������������鲻�ã����������ɣ���\n";
		
}
int do_kill(string arg)
{
        object ob,me = this_player();

        if (!living(this_object())) return 0;
        if (!arg) return 0;
        if (!(ob = present(arg, environment()))) return 0;
        if (ob == me) return 0;
        if (ob->query("family/family_name") != "�䵱��") return 0;
        
        command("say �󵨿�ͽ���������䵱����������");
        command("stare "+this_player()->query("id"));
        message_vision("�����۹�����Ц������\n", this_player());
        kill_ob(me);
        return 1;
}

void init()
{
        ::init();
        if (query("startroom") != base_name(environment())) return;
        add_action("do_kill", "kill");
        add_action("do_kill","hit");
}
