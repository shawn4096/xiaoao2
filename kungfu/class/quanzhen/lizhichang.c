inherit NPC;
inherit F_MASTER;
#include <ansi.h>;
string ask_rumen();

void create()
{
        set_name("��־��", ({"li zhichang", "li"}));
        set("gender", "����");
        set("age", 24);
        set("class", "taoist");
        set("long",
                "������ȫ��̵����������еĺ��֣����ڵĴ������־����\n"
                "����òƽ����һ��������\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 26);
        set("int", 25);
        set("con", 25);
        set("dex", 26);


        set("qi", 15000);
        set("max_qi", 15000);
        set("jing", 5800);
        set("max_jing", 5800);
		set("jingli", 4800);
        set("max_jingli", 4800);

        set("neili", 15000);
        set("max_neili", 15000);
        set("jiali", 60);
        set("level", 8);
        set("combat_exp", 160000);

        set_skill("force", 350);
        set_skill("xiantian-gong", 350);
        set_skill("sword", 350);
        set_skill("quanzhen-jianfa",350);
        set_skill("dodge", 350);
        set_skill("jinyan-gong", 350);
        set_skill("parry", 350);
        set_skill("strike",350);
        set_skill("haotian-zhang", 350);
		set_skill("leg",350);
        set_skill("yuanyang-lianhuantui", 350);
        set_skill("jinguan-yusuojue", 350);

        set_skill("literate",160);
        set_skill("taoism",160);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
        prepare_skill("strike", "haotian-zhang");
        map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("leg", "yuanyang-lianhuantui");

        create_family("ȫ���", 3, "����");
		set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: perform_action, "sword.ding" :),
			(: perform_action, "sword.sanqing" :),
			(: perform_action, "sword.lian" :),
			(: exert_function, "daojue" :),
		//	(: exert_function, "daojue" :),
		}));

        set("inquiry", ([
                "��ʦ" : (: ask_rumen :),
        ]) );

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
		   command("say �㻹��ȥѰ����ʦ���徲ɢ���ﲻ�����µ��ӳ�����ʦ�ã������Ƿ����㣿\n");
		   return ;

       }

	   if ((int)ob->query("shen") < 1000000) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(1m)");
               return;
       }
	   if (ob->query("party/gongji") < 1500) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڽ��ɹ������棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(��Ҫ1500�����ɹ���ֵ)\n");
               return;
       }
	   if (!ob->query("quest/qz/dichuan"))
	   {
		       command("say ��������еմ����ӣ�����������");
              return;

	   }
	   if (ob->query_skill("xiantian-gong",1) < 200) {
               command("say ��ȫ���һ����ȫ�����칦�������칦����200��������������");
               return;
       }
	   if (ob->query_skill("yuanyang-lianhuantui",1) < 200) {
               command("say ��ԧ�������Ȳ���200��������������");
               return;
       }		
       command("say �ðɣ�ƶ�����������ˡ�");
       command("recruit " + ob->query("id"));
       ob->set("class","taoism");
	   return;
}
string ask_rumen()
{
	object me=this_player();

			command("say ���칦�����г�200����\n");
			command("say ԧ�����������ǻ�������������200Ҳ������\n");

		command("say ������ܹ���1500�����ɹ��ף��ҷ�������Ϊͽ��\n");
		command("say 1M�����һ�����1500�㹱��ֵ�Ϳ��Թ�����������\n");
		return "��Ҫ�������ⷽ�ɰ����Ҵ�ȫ���";
	
}