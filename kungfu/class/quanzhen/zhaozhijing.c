// zhao.c ��־��
// By Lgg,1998.10

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_yanlian();
string ask_start();
string ask_stop();

int do_zhifu(string arg);


void create()
{
        set_name("��־��", ({"zhao zhijing", "zhao"}));
        set("gender", "����");
        set("age", 26);
        set("class", "taoist");
        set("long",
                "������ȫ��̵����������еĺ��֣�����һ�Ĵ������־���� \n"
                "����ò��������ü����ƺ�������һ˿�ƻ�����ɫ��\n"
		"����һ��������ˣ�������ȴ��Щɷ����\n");
        set("attitude", "friendly");
        set("shen_type",-1);
        set("str", 25);
        set("int", 26);
        set("con", 26);
        set("dex", 25);

        set("qi", 15000);
        set("max_qi", 15000);
        set("jing", 5000);
        set("max_jing", 5000);
		set("jingli", 6000);
        set("max_jingli", 6000);
        set("eff_jingli", 6000);

        set("neili", 15000);
        set("max_neili", 15000);
        set("jiali", 200);

        set("combat_exp", 6600000);
		set("quest/qz/xtg/daojue/pass",1);
		set("quest/qz/jyg/shangtianti/pass",1);
		set("quest/quanzhen/sword/lianhuan",1);

        set_skill("force", 380);
        set_skill("xiantian-gong", 380);
        set_skill("sword", 380);
        set_skill("quanzhen-jianfa",380);
        set_skill("dodge", 380);
        set_skill("jinyan-gong", 380);
        set_skill("parry", 380);
        set_skill("strike",380);
        set_skill("haotian-zhang", 380);
        set_skill("literate", 160);
        set_skill("taoism", 160);      
        set_skill("tiangang-beidouzhen", 380);
        set_skill("leg", 380);      
        set_skill("yuanyang-lianhuantui", 380);
        set_skill("jinguan-yusuojue", 350);

		map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
		map_skill("leg", "yuanyang-lianhuantui");

        prepare_skill("strike", "haotian-zhang");
		prepare_skill("leg", "yuanyang-lianhuantui");

        create_family("ȫ���", 3, "����");
		set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: perform_action, "sword.ding" :),
			(: perform_action, "sword.sanqing" :),
			(: perform_action, "sword.lian" :),
			(: exert_function, "daojue" :),
			(: perform_action, "dodge.yanwu" :),
		}));

        set("inquiry", ([
                "ȫ���" :  "��ȫ��������µ����������ڡ�\n",  
				"�������������" :  (:ask_yanlian:), 
				"������������" :  (:ask_start:),  
				"����" :  (:ask_stop:),  
        ]) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

void attempt_apprentice(object ob)
{
       if (ob->query("family")!="ȫ���")
       {
		   command("say �㲻��ȫ��̵��Ӿ�Ȼ�����Ұ�ʦ����ϸ�ɣ�\n");
		   return ;

       }
	   if (ob->query("gender")!="����")
       {
		   command("say ��һ��Ů�˼�������Ϊʦ���ѵ�����ʲô��ͼ���ɣ���\n");
		   command("say ��ȫ��һ��������ȫ���ڵ���Ϊ�ϣ����������������Ҳ��ó���\n");
		   command("say �㻹��ȥѰ����ʦ���徲ɢ���ﲻ�����µ��ӳ�����ʦ�ã������Ƿ����㣿\n");
		   return ;

       }
	   if ((int)ob->query("shen") < 1200000) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(1.2m)");
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
 	   if (ob->query_skill("xiantian-gong",1) < 220) {
               command("say ��ȫ���һ����ȫ�����칦�������칦����220��������������");
               return;
       }
	   if (ob->query_skill("yuanyang-lianhuantui",1) < 220) {
               command("say ���ԧ�������Ȳ���220��������������");
               return;
       }
	   if (ob->query_skill("haotian-zhang",1) < 220) {
               command("say �������Ʋ���220��������������");
               return;
       }		
       command("say �ðɣ�ƶ�����������ˡ�");
       command("recruit " + ob->query("id"));
       ob->set("class","taoism");
	   return;

}
int init()
{
	add_action("do_zhifu",({"zhifu","duihuan","jiaohuan"}));
}


string ask_yanlian()
{
		object ob;
		ob=this_player();
		message_vision(HIG"$N�Ϲ��Ͼ�����$n��ʾ�ܷ�����Լ������������������飡\n"NOR,ob,this_object());
		if ((int)ob->query("shen") < 2000000)
		{
               command("say ��̫�ͣ�����2m,�м���˼�������޷���ζ���ĵġ�");
               command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(2m)");
               return "��������\n";
       }
	   if (ob->query_temp("qz/yanlian/zhifu"))
	   {
		   return "���Ѿ�֧�����������ã��Ͻ������!\n";
	   }
	   if (ob->query("family/family_name")!="ȫ���")
       {
		   command("say �㲻��ȫ��̵��Ӿ�Ȼ�����������������󣬼�ϸ�ɣ�\n");
		   return "��Ц֮����\n";

       }
	   if (ob->query("party/gongji") < 5000) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڽ��ɹ������棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(��Ҫ5000�����ɹ���ֵ)\n");
              return "��������\n";
       }
	   if (!ob->query("quest/qz/dichuan"))
	   {
		       command("say ����ҽ��еմ����ӣ�����������");
             return "��������\n";

	   }
 	   if (ob->query_skill("xiantian-gong",1) < 350) {
               command("say ��ȫ���һ����ȫ�����칦�������칦����350��������������");
               return "��������\n";
       }
	   if (ob->query_skill("quanzhen-jianfa",1) < 350) {
               command("say ���ȫ�潣������350��������������");
               return "��������\n";
       }
	   if (ob->query_skill("tiangang-beidouzhen",1) < 350) {
               command("say ������������350���޷���ζ������ķ����أ���");
              return "��������\n";
       }
	   
       command("say "+ob->query("name")+"���������ˣ�����û����ѵ���ͣ�����������������������Ҫ�߸��ˡ�\n");
       command("say ���Ƿֱ��ǣ���־��,����־�桢��־������־����־�ϡ�\n");
	   ob->set_temp("lianzhen/zhao",1);
	   if (!ob->query_temp("lianzhen/cui")||!present("cui zhifang",environment(this_object()))) return "���Ǹ���˵��ô�������־��ʦ��ô��\n";
	   if (!ob->query_temp("lianzhen/shen")||!present("shen zhifan",environment(this_object()))) return "���Ǹ���˵��ô��������־��ʦ��ô��\n";
	   if (!ob->query_temp("lianzhen/chen")||!present("chen zhiyi",environment(this_object()))) return "���Ǹ���˵��ô�������־��ʦ��ô��\n";
	   if (!ob->query_temp("lianzhen/fang")||!present("fang zhiqi",environment(this_object()))) return "���Ǹ���˵��ô�����־��ʦ��ô��\n";
	   if (!ob->query_temp("lianzhen/qi")||!present("qi zhicheng",environment(this_object()))) return "���Ǹ���˵��ô��������־��ʦ��ô��\n";
	   command("say �ã���Ȼ�˴����ˣ��Ϳ����������������ˣ�\n");
	   command("say ��������������������������Ҫ�ó�������ɹ���ֵ��֧����\n");
	   command("say ÿ��������Ҫ�ķ�һǧ��(1000)�����ɹ��ף�\n");
	   command("say ���⣬���Ǽ���ʦ�ֵ���������һ������ÿ����Ҫ֧��һ�����ƽ�ֱ�Ӵ������Ͽ۵���\n");
	   command("smile "+ob->query("id"));

	   command("say "+ob->query("name")+"����֪�����Ƿ�Ը��֧��(zhifu)��Щ����ô��\n");

	   ob->set_temp("qz/yanlian/askzhao",1);
	   return "�����������̫�����ˣ�\n";
}
int do_zhifu(string arg)
{	
	object me,ob;
	me=this_player();
	ob=this_object();
	if (!arg||arg!="����ֵ�������������")
	{
		command("say ��Ҫ˵[zhifu ����ֵ�������������]��\n");
		return 1;
	}
	if (me->query("party/gongji")<1000)
	{
		command("say ������ɹ���ֵ������\n");
		return 1;
	}
	if (me->query("balance")<1000000)
	{
		command("say �������˺����㣬��������ǲ���ӣ�\n");
		return 1;
	}

	message_vision(HIC"$NԸ�⽻���Լ����ܵ���ٵ����ɹ���ֵ��һ�����ƽ��$n��������������������!\n"NOR,me,ob);
	message_vision(HIR"$n������˵����������Ȼ�������ɹ���ֵ�������������߻�û����������ʧ�ܣ�������û���κι�ϵ��!\n"NOR,me,ob);
	//message_vision(HIR"$n������˵����������Ȼ�������ɹ���ֵ�������������߻�û����������ʧ�ܣ�������û���κι�ϵ��!\n"NOR,me,ob);
	me->delete_temp("qz/yanlian");
	
	me->add("party/gongji",-500);
	me->add("balance",-1000000);
	me->set_temp("qz/yanlian/zhifu",1);
	return 1;
	
}

string ask_stop()
{
	object me;
	me=this_player();
	if (!me->query_temp("qz/yanlian/askzhao"))
	{
		return "����,˭û�³Ա��˳ŵ������棿\n";
	}
	command("say ��Ȼ��λʦ��Ը��֧���ҵȷ��ã��ǾͿ�ʼ����(lianzhen)����ɣ�\n");

	me->delete_temp("lianzhen");
	me->delete_temp("qz");
	return "���а���\n";
}

string ask_start()
{
	object me;
	me=this_player();
	if (!me->query_temp("qz/yanlian/zhifu"))
	{
		return "�㲻Ը��֧�����ã�˭û�³Ա��˳ŵ������棿\n";
	}
	command("say ��Ȼ��������Ǿ����ˣ�\n");

	message_vision(HIY"������־���Ļ������䣬������������ռ�������ǵĸ���λ�ã�\n"
	+"��־����ռ�ˡ�"HIC"��Ȩ"NOR"��λ\n"
	+"��־����ռ�ˡ�"HIG"����"NOR"��λ\n"
	+"��־����ռ�ˡ�"HIY"���"NOR"��λ\n"
	+"��־����ռ�ˡ�"HIM"����"NOR"��λ\n"
	+"��־����ռ�ˡ�"HIW"���"NOR"��λ\n"
	+"��־����ռ�ˡ�"HIB"����"NOR"��λ\n"
	+"$N�漴̤����֮�У���ռ��"HIR"ҡ��"NOR"λ\n"NOR,me);
	
	command("say ���������Ҫ���������,����Ҫ���롰lianzhen name1 name2 name3 name4 name5 name6������\n");
	command("say ���磺lianzhen zhang cui chen .....\n ");
	command("say �������˾Ϳ������������ˣ�\n");
	if (me->query("job_name")=="ȫ������")
	{
		command("say �㷽��������ϣ�����Ϣ�ᣡ\n");
		return "��ȥæ���ģ�\n";

	}
	me->set_temp("lianzhen/start",1);
	return "���������������ȫ��Ĳ���֮�أ�\n";
}