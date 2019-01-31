#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string ask_guo();
string ask_jinyan();
string ask_shangtianti();
string ask_sanhua();
string ask_chongyang();
string* badman=({"������","������","ɳͨ��","��������","ŷ����","Ǯ�ཡ","�����","������","������","��ͨ��"});
string ask_yusuo();
string ask_wangshi();
string ask_dingyangtitle();
int do_answer(string arg);
void create()
{
        set_name("����", ({"ma yu", "ma"}));
        set("gender", "����");
        set("age", 42);
        set("class", "taoist");
        set("nickname",MAG"������"NOR);
        set("long",
                "�������������Ĵ���ӣ�ȫ������֮�ף����������������ˡ�\n"
				"������һ�񹦷�������ޣ��������������Ϊ����������ߡ�\n"
                "����ü��Ŀ���Ͱ����ף���Ц�ſ����㡣\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 28);
        set("int", 32);
        set("con", 31);
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
        set("miji_count",1);
        set("inquiry", ([
             "����" : (:ask_guo:),
			 "���㹦" : (:ask_jinyan:),
			 "������" : (:ask_shangtianti:),
			"�����۶���" : (:ask_sanhua:),
			"���������ƾ���" : (:ask_chongyang:),
			"���������ʮ�ľ�" : (:ask_yusuo:),
			"ȫ�������" : (:ask_wangshi:),
			"���춨��" : (:ask_dingyangtitle:),
        ]) );
		set("chat_chance_combat", 50);
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

string ask_dingyangtitle()
{
	string new_title,title,*title1,*title2;
	object me;
	me=this_player();
	title1 =({ "��","ƽ","��","Ǭ","��","��","��","ڤ","��" });	
	title2 =({ "����","���" });
	if (me->query("mytitle/quest/dingyangtitle")) return "���ѵù̶�ͷ�Ρ�\n";
	if (me->query("quanzhen/force")=="pass") 
		{			
			title= "ȫ��̡�"+title1[random(sizeof(title1))]+"��"+title2[random(sizeof(title2))];
			me->set("title",HIB+title+NOR);
			me->set("mytitle/quest/dingyangtitle",HIB+title+NOR);
			command("say ��Ȼ��ˣ�����"+title+"��\n");
			return "��������";
		}
		return "�Ǻǡ�����������\n";
}
string ask_guo()
{
	object me;
	me=this_player();
	if (me->query("family/family_name")!="ȫ���")
	{
		return "�㲻����ȫ��̵��ӣ�\n";
	}
	command("say �������ǽ����߹ֵĵ��ӣ�����Ϊ�˺���ʦ�ܴ�ģ�������Զ����Į���̵����ӣ�\n");
	command("say ��Լʮ������ڼ�������¥�������Ӯ��\n");
	command("say ��֪��ȫ����ڹ�Խ����������Խ�������ԭ��������ʦ�ܵ��ӵĶ��֣�\n");
	command("say ������������˵������ĳ������Ծ���Զ����Į�̵����⺢�����꣡\n");
	command("say ��ʱ�������ľ�����ȫ��̵��ڹ���ȫ���Ṧ----���㹦��\n");
	me->set_temp("jyg/askma",1);
	return "�������ƣ���������������ἰ����Ȼ���˶����������мӣ�\n";
}
//���������������칦һ��ָ��ʾ

string ask_wangshi()
{
	object me;
	me=this_player();
	if (me->query("family/family_name")!="ȫ���"
		||!me->query("quest/qz/dichuan"))
	{
		return "�㲻����ȫ��̺��ĵ��ӣ�\n";
	}
	if (!me->query("quest/qz/xtg/wuqi/pass"))
	{
		return "���칦��û�������Ҫ������������Ԫ��û����͸�������ѧ�ᶨ���������\n";
	}
	if (me->query("con")<40)
	{
		return "��������ǲ���40�������˶������ѧ��\n";
	}
	if (me->query("quest/qz/xtg/dingyang/start"))
	{
		return "���Ѿ��������ƪ���ĵ���Ϣ�������Ͻ�ȥ�ҵ���\n";
	}
	if (time()-me->query("quest/qz/xtg/dingyang/time")<86400)
	{
		return "������̫Ƶ����!\n";
	}

	command("say ���֪����ȫ������������ڹ���ʲô��ʽ����\n");
	add_action("do_answer","answer");
	me->set_temp("marks/wangshi",1);
	return "�������ƣ�����Ҳ�գ�\n";
}
int do_answer(string arg)
{
	object me=this_player();
	if (!arg||arg!="���칦������")
	{	
		command("kick "+me->query("id"));
		command("say ���ģ����Ҵ�ȫ��̵����칦�������񼼶���֪����\n");
		return 1;
	}
	if (me->query_temp("marks/wangshi"))
	{
		me->delete_temp("marks");
		command("say Ϲ��ͷ�ش�ʲô��\n");
		return 1;
	}
	command("say �����칦������������ȫ��̵�һ�ڹ���\n");
	command("say Ҳ�����µ�һ�ȵ��ڹ��ķ���\n");
	command("say ����������ʦ�������²���û�ɽ�۽���һ�ĸ�����\n");
	command("say ������ʦƾ�����������������ľ�����а���������ϵۡ���ؤ��\n");
	command("say ��õ�һ�󣬻���˱��桶�����澭����Ȩ����\n");
	command("say ��������ŷ���治��������ͼ���ᡶ�����澭������ʦ��ʱ���岻�á�\n");
	command("say Ϊ�˷�ֹŷ�����Ժ����ң��������һ��ı����\n");
	tell_object(me,HIY"�����÷ǳ������������ڵĽ������·�ص��Ǹ����Ķ��ǵ�ҹ��\n"NOR);
	me->set_temp("quest/qz/xtg/dingyang/start",1);
	//tell_object(me,HIG"ʱ��һ��Ť��....��\n"NOR);

	me->move("d/quanzhen/lingtang");
	return 1;

}
string ask_yusuo()
{
	object me,ob;
	me=this_player();
	if (me->query("family/family_name")!="ȫ���")
	{
		command("say �㲻����ȫ��̵��ӣ�\n");
		return "�ߣ�\n";
	}
	if (!me->query("quest/qz/dichuan"))
	{
		command("say �㲻����ȫ��̺��ĵ��ӣ�\n");
		return "�ߣ�\n";
	}
	if (me->query_skill("xiantian-gong",1)<350)
	{
		command("say ������칦����350�������������Ź���\n");
		return "��!\n";
	}
	if (present("yusuo jingyao",me)||me->query_temp("yusuo/askma"))
	{
		command("say �����ϲ������������ľ�Ҫô����\n");
		return "poor \n";
	}
	command("say ����������ʮ�ľ��������칦�������ķ��ھ���\n");
	command("say ����������ȫƾһ����������������˵��Ҳ�̺�Ī��������\n");
	command("say ����������������磬ժҶ�ɻ�Ҳ�����ˣ��������ҽ̲���֮�أ�\n");
	command("say ���Ź���ȫƾ���˲������ã����˶��죬���˲�ͬ\n");
	command("say �ܹ��о��ؾ��磬�������������ֵز�ȫ��������Ժ������ˣ�\n");
	command("say ��ȫ������칦���µ�һ����Ҫ����Ϊ֮����������\n");
	command("say �����Ȿ�������ġ������������Ҫ��������ȥ�Ҹ���������������\n");
	ob=new("/d/quanzhen/obj/yusuojue3");
	ob->move(me);
	me->set_temp("yusuo/askma",1);

	return "";
}
string ask_jinyan()
{
	object me;
	me=this_player();
	if (me->query("family/family_name")!="ȫ���")
	{
		return "�㲻����ȫ��̵��ӣ�\n";
	}
	if (!me->query_temp("jyg/askma"))
	{
		return "������ȫ�������Ҫ���Ṧ����\n";
	}
	command("say �ҵ����������ɹ�أ��޷����Դ��ڹ������գ�\n");
	command("say ֻ�Ǵ�������һЩ�������ͺ���֮����\n");
	command("say ��������㹦����Ҫ�ķ����ǡ������ݡ�������\n");
	command("say ƾ�˾����������ڴ�ɽ���ּ��ݺ��ް���\n");
	
	me->set_temp("jyg/askjyg",1);
	return "���㹦�����裬�������ǲ��������о��ϵģ�\n";
}
string ask_shangtianti()
{
	object me;
	me=this_player();
	if (me->query("family/family_name")!="ȫ���")
	{
		return "�㲻����ȫ��̵��ӣ�\n";
	}
	if (!me->query_temp("jyg/askjyg"))
	{
		return "������ȫ�������Ҫ���Ṧ����\n";
	}
	 if (me->query_skill("xiantian-gong",1) < 450) {
               command("say ��ȫ���һ����ȫ�����칦�������칦����450��������������");
               return "";
       }
	   if (me->query_skill("jinyan-gong",1) < 450) {
               command("say ����㹦����450��������������");
               return "";
       }	   
	   if (me->query("dex") < 35) {
               command("say ����㹦��Ҫ������������35��������������");
               return "";
       }
	   	if (me->query("quest/qz/jyg/shangtianti/pass"))
		{
			return "��Ľ��㹦�����ݵ����ž����Ѿ��⿪�ˡ���\n";
		}
		if (time()-me->query("quest/qz/jyg/shangtianti/time")<86400)
		{
			return "������̫Ƶ���ˣ�����������\n";
		}
		if (me->query("party/gongji")<100)
		{
			return "�����ɹ��׹�������100��\n";
		}
		me->add("party/gongji",-100);
	   command("say ���������������������Ҫ�۳�������ɹ���ֵÿ��100�㣬���������û�ʸ�����ҡ�\n\n\n\n");

       command("say �ðɣ���Ȼ�����Ŭ�����Ҿ͸��������о��ϡ�\n");
		command("say �����������ݾ����ǵ������ɹŵ�һ�����´���ϰ���ģ�\n");
		command("say �Ṧ����ȫ�������������������ľ�ȥ�Ķ����һ�Ե�����ܷ���������\n");
	
	me->set_temp("jyg/askstt",1);
	return "ɽ�����ǽ��㹦�ľ������ڣ�\n";
}

//�����۶���
//������ȥɱ��������

string ask_sanhua()
{
	object me;
	string bad;
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
	   if (me->query("party/gongji") < 100) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڽ��ɹ������棬" + RANK_D->query_respect(me) +
                       "�Ƿ����ò�����(��Ҫ100�����ɹ���ֵ)\n");
               return "";
       }
	   if (!me->query("quest/qz/dichuan"))
	   {
		       command("say ��������еմ����ӣ�����������");
              return "";

	   }
	   if (me->query_skill("xiantian-gong",1) < 350) {
               command("say ��ȫ���һ����ȫ�����칦�������칦����350��������������");
               return "";
       }
	   if (me->query_skill("haotian-zhang",1) < 350) {
               command("say ������Ʋ���200��������������");
               return "";
       }
	   	if (me->query("quest/qz/htz/sanhua/pass"))
		{
			return "�������Ƶ������۶����Ѿ��⿪�ˡ���\n";
		}
		if (time()-me->query("quest/qz/htz/sanhua/time")<86400)
		{
			return "������̫Ƶ���ˣ�����������\n";
		}
		if (!me->query_temp("quest/qz/htz/sanhua/killed"))
		{
			command("say �������۶���������ȫ��̶����书֮һ��������ѧ����Ҫ����ȥɱ�������ˣ�\n");
			bad=badman[random(sizeof(badman))];
			command("say ���������ȥɱ��"HIY+bad+NOR"���������\n");
			me->set_temp("quest/qz/htz/sanhua/askma",1);
			me->set_temp("quest/qz/htz/sanhua/killtarget",bad);
			return "��������¸ɾ�����Ȼ�����а��ض��밵�����ң�\n";
		}

	   command("say ���������������������Ҫ�۳�������ɹ���ֵÿ��100�㣬���������û�ʸ�����ҡ�\n\n\n\n");

       command("say �ðɣ���Ȼ�����Ŭ�����Ҿ͸��������о��ϡ�\n");
       command("whisper "+me->query("id"));
	   
	   if (me->is_busy())
	   {
		  return "��������æ������!\n";
	   }
		me->start_busy(10);
		
		me->add("party/gongji",-100);

		message_vision(HIC"$N����$n������˵���������ɵ������������ͬ���죬�������޳��������۶��ƣ������д��ȥ�ġ�\n"
							"���Ȼ������˳̶ȣ��Ҿʹ��������С������۶��ơ��İ��أ��Ҹ�����ʾһ�飬�����Լ��������ˡ�\n"+
					   HIR"\n\n\n$N����վ������Ȼ������Ծ�𣬶�ʱ�������������ۼ�ͷ�����Ʒ�������������С��\n"NOR,this_object(),me);
		
	 
		i = 20;
		if(me->query("m-card-vip")) i =  18;
		if(me->query("y-card-vip")) i =  15;
		if(me->query("buyvip"))     i =  10;
		i=random(i);
		j=random(me->query("kar"));
		command("say �㿴����ô��\n");
		command("pat "+me->query("id"));
		if( i<3
			&& me->query("kar")<31
			&& j >= 25 ) 
		{
			tell_object(me,HIC"\n�����˵����ڵ�����ָ�㣬�����������Լ���������Ƶ������ĵã�����ӡ�ա�\n"NOR);
			tell_object(me,HIR"\n��Ȼ�͹�Ѩһ�ɴ������������ʱ�о��Ʒ�����������˲���������������۶��Ƶ��������š�\n"
						NOR);
			me->set("quest/qz/htz/sanhua/pass",1);
			log_file("quest/qzsanhua", sprintf("%8s(%8s) ʧ��%d�κ�ѧ�������۶��ƾ���,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), me->query("quest/qz/htz/sanhua/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			command("haha"+me->query("id"));		
			me->delete_temp("quest/qz/htz");
			return "��ϲ���������۶��ƾ����ɹ�!\n";
			
		}	
	   else
		{
			log_file("quest/qzsanhua", sprintf("%8s(%8s) ���������۶����ƾ�������ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), me->query("quest/qz/htz/sanhua/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			
			tell_object(me,HIY"���������ڵ�ָ�㣬���Ƕ�����ƾ������۶��ƾ����İ���ȫȻ����Ҫ�졣\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			me->add("quest/qz/htz/sanhua/fail",1);
			me->set("quest/qz/htz/sanhua/time",time());
			me->start_busy(2+random(3));
			me->delete_temp("quest/qz/htz");

			return "�ǳ��ź����������֮�����۶��ƾ���ʧ��"+me->query("quest/qz/htz/sanhua/fail")+"�Ρ�\n";
		}

   
}

//������Ʒ

int accept_object(object who,object obj)
{
	object obb;
	
	if (obj->query("kill_by"))
	{
		obb=obj->query("kill_by");
	}
	if (who->query_temp("quest/qz/htz/sanhua/killtarget")
		&&obb->query("id")==who->query("id")
		&&obj->query("name")==who->query_temp("quest/qz/htz/sanhua/killtarget")+"���׼�")
	{
		
		command("haha "+who->query("id"));
		command("say ���ܽ�"+obj->query("victim_name")+"�����������ɱ�ˣ��Һܸ��ˣ�\n");
		command("pat "+who->query("id"));
		command("say ��˵��������书���������Һܿ����㣡\n");
		command("say ������ȥ�ú���Ϣ�ɣ�\n");

		message_vision(RED"\n\n$n˦�ֽ�"+obj->query("name")+RED"�������������У�\n"NOR,who,this_object());
		destruct(obj);
		who ->set_temp("quest/qz/htz/sanhua/killed",1);
	}	

	return 1;
}

//����������
string ask_chongyang()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="ȫ���")
	{
		return "�㲻����ȫ��̵��ӣ�\n";
	}
	if (!me->query("quest/qz/htz/sanhua/pass"))
	{
		return "�����۶�����������������Ļ������㲻�������۶��������ϰ����������\n";
	}
	if (me->query("shen") < 2000000) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڵ��з��棬" + RANK_D->query_respect(me) +
                       "�Ƿ����ò�����(2m)");
               return "";
       }
	   if (me->query("party/gongji") < 100) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڽ��ɹ������棬" + RANK_D->query_respect(me) +
                       "�Ƿ����ò�����(��Ҫ100�����ɹ���ֵ)\n");
               return "";
       }
	   if (!me->query("quest/qz/dichuan"))
	   {
		       command("say ��������еմ����ӣ�����������");
              return "";

	   }
	   if (me->query_skill("xiantian-gong",1) < 450) {
               command("say ��ȫ���һ����ȫ�����칦�������칦����450��������������");
               return "";
       }
	   if (me->query_skill("haotian-zhang",1) < 450) {
               command("say ������Ʋ���450��������������");
               return "";
       }
	   	if (me->query("quest/qz/hzt/chongyang/pass"))
		{
			return "�������Ƶ������������Ѿ��⿪�ˡ���\n";
		}
		if (time()-me->query("quest/qz/hzt/chongyang/time")<86400)
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
		
		me->add("party/gongji",-100);

		message_vision(HIC"$N����$n������˵���������ɵ������������ͬ���죬��������������Ҫ�����ϱ������ǹ�ͬ���򷽿���Ч��\n"
						"���Ʒ���������ȫ��û��ѧ�ᣬ���Ҽ���ʦ�������������������ǳ�����������ͬ���\n"+
					   HIR"\n\n\n$N˵��������������ϰ���ž�������õ���ʦ�չ�֮�������Ǹ����ع���̨�Ͽ��Բ������ž�������\n"
						+"�мǣ��мǣ���Ҫ�ϣ���ʦ����ȫ�棬��ʵ���ס���Ҫǫ����ȥ�ɣ����Ե���ɽɽ����ʦ�չ�֮�������Ƿ��д˻�Ե��\n"NOR,this_object(),me);
		me->set_temp("quest/qz/htz/chongyang/askma",1);
		return "����̨�����ã�����Ե�ɺ��ܲ����Ƕ�֮��������죡\n";
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

	   if ((int)ob->query("shen") < 2000000) {
               command("say ��ȫ������������������ɣ��Ե���Ҫ���ϡ�");
               command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                       "�Ƿ����ò�����(2m)");
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
	   if (ob->query_skill("xiantian-gong",1) < 350) {
               command("say ��ȫ���һ����ȫ�����칦�������칦����350��������������");
               return;
       }
	 
       command("say �ðɣ�ƶ�����������ˡ�");
       command("recruit " + ob->query("id"));
       ob->set("title", "ȫ�������״�����");
       ob->set("class","taoism");
	   return;
}