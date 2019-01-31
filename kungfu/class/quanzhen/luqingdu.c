//¹����
//luqingdu.c
//sohu@xojh
//ȫ���������ʦ��֮һ
//
#include <job_mul.h>

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_rumen();
string ask_caiyao();
string ask_gongji();

int do_answer(string arg);

void create()
{
        set_name("¹����", ({"lu qingdu", "lu"}));
        set("gender", "����");
        set("age", 24);
        set("class", "taoist");
        set("long",
                "���������⣬���ǿ���������ʿ����ȫ�������ʦ��֮һ���ƺ������ա�\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 26);
        set("int", 25);
        set("con", 25);
        set("dex", 26);
		//�趨��ɱ֮��
		set("no_kill",1);
		set("no_throw",1);
		set("no_steal",1);

        set("qi", 5000);
        set("max_qi", 5000);
        set("jing", 4000);
        set("max_jing", 4000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 110);
        set("combat_exp", 500000);

        set_skill("force", 220);
        set_skill("xiantian-gong", 220);
        set_skill("leg", 220);
        set_skill("yuanyang-lianhuantui",220);
        set_skill("dodge", 220);
        set_skill("jinyan-gong", 220);
        set_skill("parry", 220);
       // set_skill("strike",140);
        //set_skill("haotian-zhang", 140);
        set_skill("literate",150);
        set_skill("taoism",100);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "yuanyang-lianhuantui");
        map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("leg", "yuanyang-lianhuantui");
		set("chat_chance_combat", 40);
		set("chat_msg_combat", ({
			(: perform_action, "leg.yuanyang" :),
			//(: perform_action, "leg.lianhuan" :),
			
		}));

        create_family("ȫ���", 4, "����");

        set("inquiry", ([
                "ȫ���" :  "��ȫ��������µ�����������,�����������������ú����������������ʰ�㣡\n",			      
                "���" : (: ask_rumen :),
			    "��ҩ" : (: ask_caiyao :),
               	"���й���" : (: ask_gongji :),
                 
        ]) );

        setup();

      //  carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

int init()
{
	add_action("do_answer","answer");

}
string ask_rumen()
{
	object me;
	me=this_player();
	if (me->query("family")&&me->query("family/family_name")!="ȫ���")
	{
		command("say ����������϶Ҳ̫���˰ɣ�\n");
		command("say ���Ѿ��������ɣ��������ң�\n");
		return "����";
	}
	if (me->query("combat_exp")>10000)
	{
		command("say �������ϵ�������·��������ɣ�\n");
		command("say ȫ������ֻ�վ���ֵ10k���µĵ��ӣ�\n");

		return "�汿!\n";
	}
	if (me->query("shen")<0)
	{
		command("say ��һ���������������������ɺò��ã�\n");
		return "������ͷ!\n";

	}
	if (me->query_temp("qz/answeryes"))
	{
		command("say ��Ȼ���Ѿ���Ӧ�ˣ��Ǿ�����ʱ�������¼������ӣ����ҵ�ǲ��\n");
		if (me->query("gender")=="Ů��")
		{
			command("say ��������Ů�ӣ��������ŵ���ʽ���ǲ��ܷ��˵ģ������˹���ֵ��ȥ�ݼ�����ʦ�ã�\n");
		}

		me->set("title","ȫ��̵������������");
		me->set("family/family_name","ȫ���");
		me->set("family/generation",5);
		me->set("party/jiming","¹����");//�������ӱ��
		me->delete_temp("qz");
		return "�úø�,���һ�����Ĺ���ǰ;��\n";
	}
	command("sing ");
	command("say ��������������ȫ���ɣ������ͨ���ҵĿ��в��У�\n");
	command("say ���Ӿ���ר�Ÿ���Ϊ��ȫ�������˲ŵ�\n");
	command("say ����Ը�⣬�����������Щ����������ȥ�������ĺã��ҿ��Կ�������Ϊͽ��\n");
	command("say ��ɿ��������ô��\n");
	me->set_temp("qz/rumen",1);
	return "������������ڵĴ�ȫ��̣�\n";
}
int do_answer(string arg)
{
	object me;
	me=this_player();
	if (!me->query_temp("qz/rumen"))
	{
		command("say ��Ե�޹ʣ��Ǽ鼴����\n");
		return 1;
	}
	if (!arg||arg!="Ը��")
	{
		return notify_fail("��Ϲ��Ӧʲô��\n");
	}
	message_vision(HIY"$N������Ц����¹����������Ӧ��˵������Ը�⡱��\n"NOR,me);
	me->set_temp("qz/answeryes",1);
	return 1;
}
string ask_caiyao()
{
	object me=this_player();
	if (me->query("family/family_name")!="ȫ���")
	{
		command("say "+me->query("name")+"��������������϶Ҳ̫���˰ɣ�\n");
		command("say "+me->query("name")+"���������ң�\n");
		return "���ɻ���أ���\n";
	}
	if (me->query_temp("qz/caiyao"))
	{
		command("say "+me->query("name")+"���Ҳ��ǰ�����ȥ��ҩȥ��ô���ǲ���͵���ˣ�\n");
		return "����ƭ�ҹ��أ����Σ�\n";
	}
	if (me->query_condition("job_busy"))
	{
		command("say "+me->query("name")+"�������ڹ���æµ�У�����������\n");
		return "����ƭ�ҹ��أ�\n";

	}
	//���ƾ���ֵ
	//if (me->query("combat_exp")>200000)
	//{
		//command("say �㾭��ֵ�Ѿ��ܸ��ˣ��������ɵĻ�����ʦ�����ɺ��ˣ�\n");
		//return "��һ��Ͷ��ȡ�ɵģ�����ֵ����ô����ô��\n";
	//}
	tell_object(me,"¹���ƶ�"+me->query("name")+"˵����������������,��ҩ�������������ˣ���Ҫһ���в�ҩ����\n");
	tell_object(me,"¹���ƶ�"+me->query("name")+"˵����������ȥ����ɽ�¼����еĴ�����ѯ�������������Ķ��Ƿ���ҩ������\n");
	tell_object(me,"¹���ƶ�"+me->query("name")+"˵��������ȥ��ѯ��������ƾ��ȫ��̵����壬����Ҳ������Ϊ�㣡��\n");

	tell_object(me,"¹���ƶ�"+me->query("name")+"˵������Ȼ����ȥȫ��̸���������������ȥ��Ѱҩ�Ŀ�������\n");
	tell_object(me,"¹���ƶ�"+me->query("name")+"˵��������ҩҪ����һ�Ƕ��������ҵ�������ҩ���ڲɣ���ס��ô������\n");
	me->set_temp("qz/caiyao",1);
	
	tell_object(me,"¹���ƶ�"+me->query("name")+"˵�������ں�ҩ�ĺ�����������ڵ���ҩ�����ͣ���ȥ��أ���\n");
	return "���ҵ������£��������ڵĴ�ȫ��̱ؽ����\n";

}

string ask_gongji()
{
	int i;
	object me=this_player();
	if (me->query("family/family_name")!="ȫ���")
	{
		command("say ����������϶Ҳ̫���˰ɣ�\n");
		command("say �������ң�\n");
		return "���ɻ���أ���\n";
	}
	i=me->query("party/gongji");

	command("say "+me->query("name")+"�����ڽ��й���Ϊ"+chinese_number(i)+"�㹱��ֵ��\n");
	
	return "�����Ŭ������ȫ��ؽ��������£�\n";

}

int accept_object(object who, object ob)
{
	object sil;
	int gold,getshen;
	//if (ob=all) return 1;
	
	gold=40+random(10);
	//shen=50+random(50);
	if (ob->query("player")==who->query("id")
		//&& who->query_temp("herb/got")
		&&(ob->query("id")=="fu ling"||ob->query("id")=="ju geng"||ob->query("id")=="huang lian"||ob->query("id")=="chuan bei"
		||ob->query("id")=="he shouwu"||ob->query("id")=="jinyin hua"||ob->query("id")=="sheng di"||ob->query("id")=="gouzhi zi"))
	{
	
		getshen=1;
		//����
		if (who->query("combat_exp")<200000) 
		{
			TASKREWARD_D->get_reward(who,"ȫ���ҩ",getshen,0,0,random(2)-1,0,0,0,this_object());


			sil=new("clone/money/silver");
			sil->set("set_amount",gold);
			sil->move(who);
			tell_object(who,HIY"\n¹��������˦��"+who->query("name")+HIY+chinese_number(gold)+"�������Ľ�����\n"NOR);

		}
		who->set("job_name","ȫ���ҩ");
	//	who->add("job_time/ȫ���ҩ",1);
		
		who->apply_condition("job_busy",4);
		//who->apply_condition("job_busy",3);

	//	who->add("shen",shen);

		who->add("party/gongji",2+random(1));//����2��
		who->delete_temp("qz");
		who->delete_temp("herb");

		command("say "+who->query("name")+"���ܺã���Ȼ�����ҩ�ĸ��������ˣ��Ҿ͸�����¾�Ǯ��\n");


		//Ԥ��������ʾ�ӿ�
		if (random(who->query("party/gongji"))>500 && !who->query("party/rumen"))
		{
			command("pat "+who->query("id"));

			tell_object(who,HIY"\n¹������������"+who->query("name")+"������������һ��ʱ��Ĺ۲죬�Ҿ�����Կ����ͣ����Ĳ���ĺ����ӣ���\n"NOR);
			tell_object(who,HIY"\n¹������������"+who->query("name")+"��������Ը���Ҿ��������㣡��\n"NOR);
			who->set("party/rumen",1);
		}
		return 1;
	}

}

void attempt_apprentice(object ob)
{
       
	   if (ob->query("gender")!="����")
       {
		   command("say ��һ�������������Ϊʦ���ѵ�����ʲô��ͼ���ɣ���\n");
		   command("say ��ȫ��һ��������ȫ���ڵ���Ϊ�ϣ����������������Ҳ��ó���\n");
		   command("say �㻹��ȥѰ����ʦ����������µ��Ӽ�����ʦ�ã������Ƿ����㣿\n");
		   return ;

       }
	   if (ob->query("party/jiming")!="¹����")
       {
		   command("say �㲻����¹���Ƶļ������ӣ��ҿɲ������㣡\n");
		   command("say Ҫ���Ϊ�ҵļ������Ӻܼ򵥣�����Ҹɻ���ҿ���˳�ۣ�\n");
		   return ;
       }
	   if ((int)ob->query("shen") < 50000) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(5k)");
               return;
       }

	   if (ob->query("party/gongji") < 500) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڽ��ɹ������棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(��Ҫ500�����ɹ���ֵ)\n");
               return;
       }
	
	   if (!ob->query("party/rumen")) {
               command("say �㻹ûͨ���ҵĿ����أ��Ͻ��ɻ�ȥ��\n");
               return;
       }
       command("say �ðɣ�ƶ�����������ˡ�");
       command("recruit " + ob->query("id"));
       ob->set("class","taoism");
	   return;
}
