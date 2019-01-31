
//�����飬�Ĵ�����
//jiqingxu.c
//sohu@xojh
//Ů��ʦ��
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string ask_rumen();

void create()
{
        set_name("������", ({"ji qingxu", "ji", "qingxu"}));
        set("gender", "Ů��");
        set("age", 24);
        set("class", "taoist");
        set("long",
                "����һλ�����������ò�����ȫ��Ů��ʿ���ݳ�����Ϊʦ,������Ӵ�Ů����Ұ�ʦ���\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 26);
        set("int", 25);
        set("con", 25);
        set("dex", 26);
		set("no_throw",1);
		set("no_steal",1);
        set("per", 26);

		set("qi", 3000);
        set("max_qi", 3000);
		//set("eff_qi",5000);
        set("jing", 2500);
        set("max_jing", 2500);
		//set("eff_jing",4000);
        set("jingli", 3000);
        set("max_jingli", 3000);
				set("eff_jingli",3000);

        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 50);

        set("combat_exp", 500000);

        set_skill("force", 220);
        set_skill("xiantian-gong", 220);
        set_skill("leg", 220);
        set_skill("yuanyang-lianhuantui",220);
        set_skill("dodge", 220);
        set_skill("jinyan-gong", 220);
        set_skill("parry", 220);
        set_skill("whip",220);
        set_skill("qiufeng-chenfa", 220);
        set_skill("literate",150);
        set_skill("taoism",100);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
		map_skill("whip", "qiufeng-chenfa");

        map_skill("parry", "qiufeng-chenfa");
        map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("leg", "yuanyang-lianhuantui");
		
		set("chat_chance_combat", 40);
		set("chat_msg_combat", ({
			(: exert_function, "daojue" :),
			(: exert_function, "yusuo" :),
			(: perform_action, "whip.sao" :),
			(: perform_action, "whip.chan" :),
			(: perform_action, "whip.lihua" :),
		}));

        create_family("ȫ���", 4, "����");

        set("inquiry", ([
                "ȫ���" :  "��ȫ��������µ�����������,�����������������ú����������������ʰ�㣡\n",			      
                "���" : (: ask_rumen :),
			   // "��ҩ" : (: ask_caiyao :),
               //	"���й���" : (: ask_gongji :),
                 
        ]) );
		setup();

        carry_object("/clone/weapon/fuchen")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();



}

string ask_rumen()
{
	object me=this_player();

	if (!me->query("family/master_id"))
	{
		command("say ����δ��ʦ��������ȥ¹����ʦ�ִ���ȡ���񣬾�����ܹ��£��ҷ�������Ϊͽ��\n");
		command("say 100k�����һ�����500�㹱��ֵ�Ϳ��Թ�����������\n");
		return "��Ҫ�������ⷽ�ɰ����Ҵ�ȫ���";
	}
	command("say �㲻���Ѿ�����ȫ�����ô��\n");
	return "��͵�������칦�����µ�һ�ȵ��ڹ���\n";
}

void attempt_apprentice(object ob)
{
       if (ob->query("gender")!="Ů��")
       {
		   command("say ��һ�����˼�������Ϊʦ���ѵ�����ʲô��ͼ���ɣ���\n");
		   command("say ��ȫ��һ��������ȫ���ڵ���Ϊ�ϣ�����Ǭ���������Ҳ��ó���\n");
		   command("say �㻹��ȥѰ����ʦ����־�����µ���¹����ʦ�֣������Ƿ����㣿\n");
		   return ;

       }

	   if ((int)ob->query("shen") < 50000) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(50k)");
               return;
       }
	   if (ob->query("party/gongji") < 500) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڽ��ɹ������棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(��Ҫ500�����ɹ���ֵ)\n");
               return;
       }
	   if (!ob->query("party/rumen")) {
               command("say �㻹ûͨ��ȫ���¹ʦ�ֵĿ����أ��Ͻ��ɻ�ȥ��\n");
               return;
       }
	
       command("say �ðɣ�ƶ�����������ˡ�");
       command("recruit " + ob->query("id"));
       ob->set("class","taoism");
	   return;
}
