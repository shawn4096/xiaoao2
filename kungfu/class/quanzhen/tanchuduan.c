// tan.c ̷����

#include <ansi.h>
//#include "/kungfu/class/quanzhen/qz_perform.h"

inherit NPC;
inherit F_MASTER;

string ask_sanhua();

void create()
{
        set_name("̷����", ({"tan chuduan", "tan"}));
        set("gender", "����");
        set("age", 40);
        set("class", "taoist");
        set("nickname",HIY"������"NOR);
        set("long",
                "������ȫ���ͽ̷����̷���ˣ�����Ŀ��࣬Ũü���ۣ�ɤ��\n"
                "����������������Ϊʦǰ�������������Ʒ����У��ж���ר����\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 34);
        set("int", 28);
        set("con", 28);
        set("dex", 28);

        set("title","ȫ������֮��");

        set("qi", 24000);
        set("max_qi", 24000);
        set("jing", 6000);
        set("max_jing", 6000);
        set("neili", 20200);
        set("max_neili", 20200);
        set("jiali", 200);

        set("level", 20);
        
		set("combat_exp", 10500000);

        set_skill("force", 470);
        set_skill("xiantian-gong", 470);
        set_skill("sword", 470);
        set_skill("quanzhen-jianfa",470);
        set_skill("dodge", 470);
        set_skill("jinyan-gong", 470);
        set_skill("parry", 470);
        set_skill("strike", 470);
        set_skill("haotian-zhang", 470);
        set_skill("literate",180);
        set_skill("taoism",200);
	    set_skill("leg",470);
		set_skill("yuanyang-lianhuantui",470);
	    set_skill("tiangang-beidouzhen", 470);
	
        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
        prepare_skill("strike","haotian-zhang");
        map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("leg", "yuanyang-lianhuantui");

        create_family("ȫ���", 2, "����");
	    set("inquiry", ([               
                //"�����۶��ƾ���" : (: ask_sanhua :),
			   
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
        set("book_count",1);

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