// hao.c �´�ͨ
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_ruqin();
string ask_xiaoxi();

string* weizhi=({"��ɽͤ","�Խ���","����̨","���С��","ɽ´","����ɽ��","���湬"});

void create()
{
        set_name("�´�ͨ", ({"hao datong", "hao"}));
        set("gender", "����");
        set("age", 34);
        set("class", "taoist");
        set("nickname",HIG"������"NOR);
        set("long",
                "������ȫ�������еĺ´�ͨ�����ˡ������΢�֣��������ģ\n"
                "�������ϴ��ĵ���˫����ޡ�\n" );
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 30);
        set("int", 29);
        set("con", 29);
        set("dex", 29);

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
                "ȫ���" :  "��ȫ��������µ����������ڡ�\n",
			    "�ֿ��ɹ�����" : (:ask_ruqin:),
				"��Ϣ" : (:ask_xiaoxi:),

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

string ask_ruqin()
{
	//�ĳɵ��˸��� by renlai
	object me,ob;
	int max,i;
	string place,cplace;

	object obj1;
	object *ob_list;
	object ob2;	
	object fbroom;
	object *team;
	me = this_player();
	
	ob = this_object();

	
	team = me->query_team();
	//��������ģʽ
	if (team){		
	   return "�㲻��ɢ������ν�����";
	}
	/*if (!wizardp(me))	
              return "��ʱ�ر�,������������֪ͨ!";*/
	if (me->query("shen")<2000000)
	{
		return "һ���������������֮�����Ȱ����������˵��\n";
	}
	if (me->query_skill("force",1)<450)
	{
		return "��Ļ����ڹ�����450������Ҫ���ܣ�\n";
	}

	if (me->query("menggu"))
	{
		return "���Ѿ�Ͷ�����ɹţ��ѵ�Ҫ����ô����\n";
	}
	if ( me->query_temp("mgrq_job") )
		return "�㲻���Ѿ��ӹ��ɹ����ֵ���������";	
	
	
	if( !wizardp(me))
	{
		if ( me->query_condition("job_busy") || me->query_condition("mgrq_job"))
			return "���ϴ����������ˣ���������Ϣһ����˵�ɡ�";

		if (me->query("job_name") == "�����ɹ�����")
			return "���ϴ����������ˣ���������Ϣһ����˵�ɡ�\n";
		
		if ( me->query("job_name")=="������Ħ��" )
		return "���������Ħ������";
			
		if( me->query_temp("mgrq_job") )
			return "���Ѿ����������ˣ��㻹վ��������ʲô��\n";
//����
	}

			
	command("say �ҸղŽӵ���־ƽ�ķɸ봫�飬�ɹ��Խ��ַ���Ϊ����Ĵ������ֽ�Χ�����̡�\n" );
	command("say ����ԭ����Σ�ڵ�Ϧ��������������ϸ������ұ��̵ֵ����Σ����\n" );	
	
	me->set_temp("mgrq_job",1);
	
	/*
	cplace=weizhi[random(sizeof(weizhi))];
	
	if (cplace=="") cplace=="�Խ���";
	switch (cplace)
	{
		case "�Խ���":
			place="/d/quanzhen/shijianyan";
			break;
		case "��ɽͤ":
			place="/d/quanzhen/banshanting";
			break;
		case "���湬":
			place="/d/quanzhen/yuzhengong";
			break;
		case "����̨":
			place="/d/quanzhen/guanritai";
			break;
		case "ɽ´":
			place="/d/gumu/shanlu1";
			break;
		case "����ɽ��":
			place="/d/gumu/shanxia";
			break;
		case "���С��":
			place="/d/gumu/xiaolu3";
			break;
	}
	*/
	
	// ������Ϣ
	me->set_temp("mgrq_job/asked",1);
	me->apply_condition("job_busy", 30);	
	command("say "+ me->query("name")+CYN",����"+HIY+"���湬"+CYN"�����ɹ���ʿ�����ıؾ�֮�أ�������ͨ�����̰������������Ա��赲�������ֱ��̡�\n");	
	//me->set_temp("qz/mgrqjob/cplace",cplace);
	
	    fbroom= new("/u/anger/yuzhengongfb");
        fbroom->set("backroom","/d/quanzhen/yuzhengong");//����·��	
        fbroom->set("leader",me);//����ӳ�		
		me->set_temp("fbroom",fbroom);//��¼�������䣬��Ϊcond���ж�����
	    me->set("job_name", "�����ɹ�����");
	
	if (wizardp(me)) {
		me->apply_condition("mgrq_job", 6);
		me->set("neili", me->query("max_neili")*2);
		me->move(fbroom);
		//me->move(place);
	}
	else
		me->apply_condition("mgrq_job", 10);
	
	 
	 message_vision(HIC"$N���°������أ���Ӱһ�����Ѳ���ԭ����\n"NOR,me);
	 me->move(fbroom);

	return "������ʿ�в������֣�������С�ģ��Բ���ȫ���м��мǡ�\n";
	
}

string ask_xiaoxi()
{
	object me,ob;
	me=this_player();
	if (me->query("quest/qz/xtg/wuqi/start"))
	{
		
		command("say �ã��ã����Ĳ���\n");
		command("thrumb "+me->query("id"));
		command("say ȫ��̺��ĸ������������칦�ϣ���Ҳ����ʦ���������˻������ͨ�ƺŵĸ�����\n");
		command("say ��Ȼ�����Ŭ�����Ҿ͸�����һ������ʦ���������칦֮�أ�\n");
		command("say �κ��˵ĳɹ����������õ�����һ��������ǧ����࣡\n");
		command("say ���칦�����۶���������Ԫ�Ĺ��������칦�ĸ�����\n");
		if ( me->query("marry"))
		{	
			command("look "+me->query("id"));
			command("say "+me->query("name")+"�����޲�����ϧ��������Ԫ����\n");
			command("say ����������ܷ�ͻ�ƾͿ���������ˣ�\n");
		}

		if (me->query("con")<40)
		{
			command("say ��ϧ����������С��40���޷�ȥ������̫��ϧ��\n");
			return "�㵱Ŭ��������ǿ���壡\n";
		}
		command("say ȫ����ڹ��Դ�ʦ�ֵ���Ϊ��ߣ�ȫ���ȫ���Ĺ������������칦�ϣ�\n");
		command("say ��ʦ�����ἰ��ʦ�����������ں�ɽ��һ�������ܶ��չأ���������֮�������޳�������Ԫ��\n");
		
		command("say ������ȥ��ȥ���������ɣ����ܷ�����һ��¥��\n");
		command("say �۳���100�㹱��ֵ����ȥ�ɣ�\n");
		me->add("party/gongji",-100);

		me->set_temp("quest/qz/xtg/wuqi/askhao",1);
	}else {
		command("say �㵱�ú�����ȫ��̣�Ϊ�Ҵ�ȫ��ֵ��ɹ����֣�\n");
	}
	return "ȫ������칦���µ�һ��\n";
}