#include <ansi.h>;
#include <job_mul.h>

inherit NPC;
inherit F_MASTER;
int ask_shouwei();
int ask_over();
int ask_fangqi();
int ask_lilian();
int check(object ob);
int ask_qingjiao();
int do_copyy(object me,object ob);

//"�����"
string* zhuxiong=({"�����","����","�����","��Ħ��","������","������","����ֹ"});
string* name=({"/d/quanzhen/shijie1","/d/quanzhen/shijie2","/d/quanzhen/shijie3",
"/d/quanzhen/shijie4","/d/quanzhen/shijie5","/d/quanzhen/shijianyan","/d/quanzhen/banshanting",
"/d/quanzhen/shijie8","/d/quanzhen/shijie9","/d/quanzhen/guanritai","/d/quanzhen/jiaobei",
"/d/quanzhen/shijie6","/d/quanzhen/shijie7","/d/quanzhen/dajiaochang","/d/quanzhen/fangzhenqiao",
"/d/quanzhen/damen","/d/quanzhen/datang1","/d/quanzhen/datang2","/d/quanzhen/datang3",
"/d/quanzhen/baihuagu","/d/quanzhen/baihuagurukou","/d/quanzhen/cetang","/d/quanzhen/chanfang1",
"/d/quanzhen/chanfang2","/d/quanzhen/chanfang3","/d/quanzhen/chufang","/d/quanzhen/cundaota1",
"/d/quanzhen/cundaota2","/d/quanzhen/cundaota3","/d/quanzhen/cundaota4","/d/quanzhen/diziju",
"/d/quanzhen/guangning","/d/quanzhen/guozhendian","/d/quanzhen/houshan","/d/quanzhen/houtang1",
"/d/quanzhen/houtang2","/d/quanzhen/houtang3","/d/quanzhen/huajing1","/d/quanzhen/huajing2",
"/d/quanzhen/huajing3","/d/quanzhen/huizhentang","/d/quanzhen/jingxiushi","/d/quanzhen/laojundian",
"/d/quanzhen/liangong","/d/quanzhen/maocaowu","/d/quanzhen/nairongdian","/d/quanzhen/piandian",
"/d/quanzhen/pingdi","/d/quanzhen/qingjing","/d/quanzhen/rongwutang","/d/quanzhen/shandong",
"/d/quanzhen/shantang","/d/quanzhen/shiweishi","/d/quanzhen/tongtiandian","/d/quanzhen/wanwutang",
"/d/quanzhen/wuchang1","/d/quanzhen/wuchang2","/d/quanzhen/shulin1","/d/quanzhen/shulin2",
"/d/quanzhen/shulin3","/d/quanzhen/shulin4","/d/quanzhen/shulin5","/d/quanzhen/shulin6",
"/d/quanzhen/xianzhentang","/d/quanzhen/xiaohuayuan1","/d/quanzhen/xiaohuayuan2","/d/quanzhen/xiaohuayuan3",
"/d/quanzhen/xiaolu1","/d/quanzhen/xiaolu2","/d/quanzhen/xiaolu3","/d/quanzhen/yaojishi",
"/d/quanzhen/yuanshidian","/d/quanzhen/yuzhengong"});
void create()
{
        set_name("��־ƽ", ({"yin zhiping", "yin"}));
        set("gender", "����");
        set("class", "taoist");
        set("nickname", HIM"�������"NOR);
        set("age", 24);
        set("long",
                "�����𴦻��ĵ���������־ƽ������ü���ۣ�������ЩӢ����\n"
                "�ţ���ȫ��̵����������������������Ϊ����Ĳ��ߣ�ü���\n"
		"�ƺ���һ������֮ɫ�����ĵ��ǳ�ü��Ŀ����ò���ţ�������룬\n"
		"��ϧ��ȸ���������в��͡�\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 28);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
		set("no_get","��־ƽ�������̫���ˡ�");
	    set("no_bark",1);
		set("job_npc", 1);


        set("qi", 15000);
        set("max_qi", 15000);
        set("jing", 6000);
        set("max_jing", 6000);
        set("neili", 20000);
        set("max_neili", 20000);
        set("jiali", 200);
		set("jingli",6000);
		set("max_jingli",6000);
        set("eff_jingli", 6000);

        set("combat_exp", 8200000);
		set("quest/qz/xtg/daojue/pass",1);
		set("quest/qz/jyg/shangtianti/pass",1);

        set_skill("force", 420);
        set_skill("xiantian-gong", 420);
        set_skill("sword", 400);
        set_skill("quanzhen-jianfa", 400);
        set_skill("dodge", 400);
        set_skill("jinyan-gong", 400);
        set_skill("parry", 400);
        set_skill("leg", 400);
        set_skill("yuanyang-lianhuantui", 400);
        set_skill("literate",160);
        set_skill("taoism",200);
        set_skill("tiangang-beidouzhen",400);
        set_skill("strike",400);
        set_skill("haotian-zhang", 400);
        set_skill("tiangang-beidouzhen", 400);
        set_skill("jinguan-yusuojue", 400);

		map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("leg", "yuanyang-lianhuantui");
        map_skill("strike", "haotian-zhang");

		prepare_skill("strike", "haotian-zhang");
		prepare_skill("leg", "yuanyang-lianhuantui");

        create_family("ȫ���", 3, "����");
		
		set("chat_chance_combat", 65);
		set("chat_msg_combat", ({
			(: perform_action, "sword.ding" :),
			(: perform_action, "sword.sanqing" :),
			(: perform_action, "sword.lian" :),
			(: exert_function, "daojue" :),
		//	(: exert_function, "daojue" :),
		}));

        set("inquiry", ([
                "ȫ���"   :  "��ȫ��������µ����������ڡ�\n",
				"С��Ů"   :  "����һƳ����Ϊ���ˣ���Ĺ���ԣ����ɾ���\n",

				"������Ĺ" : (: ask_shouwei :),
				
				"����" : (: ask_fangqi :),
				"��ɽ����" : (: ask_lilian :),
				//"�������" : (: ask_qingjiao :),
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
 	   if (ob->query_skill("xiantian-gong",1) < 250) {
               command("say ��ȫ���һ����ȫ�����칦�������칦����250��������������");
               return;
       }
	   if (ob->query_skill("yuanyang-lianhuantui",1) < 250) {
               command("say ���ԧ�������Ȳ���250��������������");
               return;
       }
	   if (ob->query_skill("haotian-zhang",1) < 250) {
               command("say �������Ʋ���250��������������");
               return;
       }		
       command("say �ðɣ�ƶ�����������ˡ�");
       command("recruit " + ob->query("id"));
       ob->set("class","taoism");
	   return;

}
int ask_shouwei()
{
	object me=this_player();
	//object ob=this_object();
	if (me->query("family/family_name")!="ȫ���")
	{
		command("say "+me->query("name")+",�㲻���ҽ��е��ӣ�����������\n");
		return 1;
	}
	if (me->query_skill("xiantian-gong",1)<100)
	{
		command("say "+me->query("name")+",������칦̫���ˣ�����������\n\n");
		return 1;
	}
	
	if (me->query("combat_exp") < 150000)
	{
		command("say "+me->query("name")+",���ʵս���鲻��150k��������ȥ�ܶ��ɣ�\n\n");
		return 1;
	}
	
	if(me->query("job_name") == "������Ĺ") 
	{
        command("say "+me->query("name")+",��ս���������Ĺ����������Ϣһ��ɡ�");
	    return 1;

	}
	if(me->query("shen") <0) 
	{
        command("say "+me->query("name")+",����аħ���֮����������ȫ�����Ұ���ѵ��������Լ���̫Ӳ��ô��");
	    return 1;

	}
	if (me->query_temp("qz/shouwei/target")&&me->query_temp("qz/shouwei/answeryes"))
	{
		command("say �Ҳ�������ȥɱ"+me->query_temp("qz/shouwei/target")+"��ô������ô����ȥ��!\n");
		return 1;
	}
	if (me->query_temp("qz/shouwei"))
	{
		command("say "+me->query("name")+",����һ������û����ء�\n");
	    return 1;
	}
	if (me->query_condition("job_busy"))
	{
		command("say "+me->query("name")+",����������æ�У���������Ϣһ��ɡ�\n");
	    return 1;
	}
	command("say "+me->query("name")+",����������Ϣ����һ��������ʿ��������ɽ���¼��ᡣ\n");
	command("say �ݿɿ���Ϣ����������ͼ���Ĺ����������顣\n");
	command("blush ");
	command("say ��ʦ����������ҵ���Ҫ������Ĺ�����ַ���\n");
	command("say �ҿ�����������ȥ����Ĺ�ıؾ�֮·��"+me->query("name")+"�����������Ķ����Է��������˵��ҡ�\n");
	command("say "+me->query("name")+"���������Ƚϼ�ޣ������ɺ�������ͷ���ң�\n");

	me->apply_condition("job_busy",20);
	me->apply_condition("qzsw_job_busy",20);
	
	//ɾ����� ������bug
	me->delete_temp("qz/shouwei/twice");

	me->set_temp("qz/shouwei/askyin",1);
	return 1;

}

int accept_object(object who, object ob)
{
	object sil;
	string arg;
	int gold,getshen,jobs;
	arg=zhuxiong[random(sizeof(zhuxiong))];
	
	jobs=who->query("job_time/������Ĺ");

	gold=30+random(20);
	//��������ͷ
	if (ob->query("kill_by")==who
		&&ob->query("id")=="shouji"
		&& who->query_temp("askyin/xiashan")
		&& ob->query("victim_id")=="huo du")
	{
		command("say "+who->query("name")+"�ã��ǳ�����������ɱ�˻������������\n");
		command("say ����������Ϳ��԰��ĵ����ˣ�\n");
		command("say �㿴����ʵ������Ȼ��ˣ��Ҿ������㵽�����ȥѰ�����Ǳ���ͬ�齣��������ƪ�似\n");
		command("say �Ǳ��ؼ�����λʦ������������Ϊ��Ԥ�����������Ķ�ͷŷ����������\n");
		command("say ���ǹ����ڶ����ڿ��Դ��������������ȱ���Ƿ��ز��㣬�м��мǣ�\n");
		command("say ���ڵķ�Ծ���Ժ�ȫ�潣�������һ�����йؼ��;����㻹������������̣�\n");
		who->set("quest/qz/tgjf/pass",1);
		who->delete_temp("askyin");
		message_vision(HIY"$N������ڴ�����ۿ�ͬ�齣���Ļ��ᣡ\n"NOR,who);
		return 1;
	}
	if (ob->query("kill_by")==who
		&& who->query_temp("qz/shouwei/guard")
		&& ob->query("id")=="shouji")
	{
	
		getshen=1;
		//����
	//	TASKREWARD_D->get_reward(me,"ȫ���ҩ",getshen,0,0,random(2)-1,0,0,0,this_object());
		if (ob->query("name")==who->query_temp("qz/shouwei/target")+"���׼�"
			&&who->query_temp("qz/shouwei/answeryes"))
		{
			command("hoho ");
			
			who->set_temp("qz/shouwei/twice",1);
		}

		sil=new("clone/money/silver");
		sil->set("set_amount",gold);
		sil->move(who);
		
		who->set("job_name","������Ĺ");
	//	who->add("job_time/ȫ���ҩ",1);
		
		who->apply_condition("job_busy",3);

		who->add("party/gongji",1+random(1));
		
		
		tell_object(who,RED"\n��־ƽ���ֽ�"+ob->query("name")+RED+"˦������������Ԩ��\n"NOR);
		destruct(ob);

		command("say �ܺã�"+who->query("name")+"����Ȼ�������������ɱ�ˣ��Ҿ͸�����¾�Ǯ��\n");

		tell_object(who,HIY"\n��־ƽ����"+who->query("name")+HIY+chinese_number(gold)+"�������Ľ�����\n"NOR);

		//Ԥ��������ʾ�ӿ�
		if (random(who->query("job_time/������Ĺ"))>1000
			&&random(who->query("kar"))>26 
			&& !who->query("quest/qz/dichuan"))
		{
			
				message_vision(HIC"��־ƽ��Զ����$N�����˴�Ĵָ��˵�������������飬�ҽ���$NΪ��ȫ����ĵմ����ӡ�\n"NOR,who);
				who->set("title","ȫ��̵մ�����");
				who->set("quest/qz/dichuan",1);
		}
		who->set("job_name", "������Ĺ");

		//���ȥɱһЩ���ĹǸ�
		if (!who->query_temp("qz/shouwei/target")
			&&who->query("combat_exp")>4500000
			//&&!random(6))
			&&who->query("quest/qz/dichuan"))
		{
			message_vision(HIY"��־ƽ��$N����С��˵�����������Ѿ����ˣ��˴�����Ϯ���������������"HIR+arg+HIY"���������\n"NOR,who);
			
			
			who->set_temp("qz/shouwei/target",arg);
			message_vision("��־ƽҪ��ȥɱ"+arg+",�����Ը�������(answer yes ),��Ը�������(answer no)��\n",who);
			add_action("do_answer","answer");
			return 1;
		}
				//���������Ƚ���exp

		if (who->query_temp("qz/shouwei/twice") && who->query("quest/qz/dichuan") && !QUEST_D->queryquest(who,"qz/qzjf/lianhuan/start"))
		{
			command("say "+who->query("name")+"�ã��ǳ����������ĺܺã�\n");
			TASKREWARD_D->get_reward(who,"������Ĺ",getshen,0,0,3+random(2),0,0,0,this_object());
			//�������������ʾ
			
			if (QUEST_D->job_questing(who,1,"qz/qzjf/lianhuan/start","������Ĺ",4000,"������",-1,""))	               			
			{
				message_vision(HIY"��־ƽ��$n˵��������ǰ������©��һ��ȫ�潣���ؼ�����������˹����������ķ��š�\n"NOR,who);
				message_vision(HIR"��־ƽ��$n˵�����������ҵ�ɽ�����ֻ���һ��ȥ���ң����ܷ��ҵ�����\n"NOR,who);
				//who->set("quest/qz/qzjf/lianhuan/start",1);
			}

		}
		else TASKREWARD_D->get_reward(who,"������Ĺ",getshen,0,0,1+random(2),0,0,0,this_object());
		
		who->delete_temp("qz/shouwei");
		who->delete_temp("qz");
		return 1;
	}
}

int do_answer(string arg)
{
	object me,ob;
	object objwhere;
	string pos;
	me=this_player();
	
	pos=name[random(sizeof(name))];
	if (pos="")
	{
		pos=name[1];
	}
	if (!objectp(objwhere=find_object(pos)))
	{
		objwhere=load_object(pos);
	}
	if (!me->query_temp("qz/shouwei/target"))
	{
		command("say ����û�н����񣬻ش�ʲô��\n");
		return 1;
	}
	if (arg=="yes")
	{
		me->set_temp("qz/shouwei/answeryes",1);
		message_vision(HIY"$N����־ƽ���˵�ͷ��˵��������Ȼ��"+me->query_temp("qz/shouwei/target")+"�⹷�����ģ��Ǿ�ɱ�������ˣ���\n"NOR,me);
		
		
		switch (me->query_temp("qz/shouwei/target"))
		{
			case "�����":
				ob=new("/d/xingxiu/npc/maguangzuo");				
				tell_object(me,"��־ƽ��"+me->query("name")+"����˵�������������δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!��\n");				
				break;
			case "��Ħ��":
				ob=new("/d/xueshan/npc/nimoxing");				
				//tell_object(me,"��־ƽ��"+me->query("name")+"����˵��������Ħ����δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!��\n");				
				command("tell "+ me->query("id")+" ��Ħ����δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!\n");
				break;				
			case "����":
				ob=new("/kungfu/class/xueshan/huodu");				
				//tell_object(me,"��־ƽ��"+me->query("name")+"����˵������������δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!��\n");				
				command("tell "+ me->query("id")+" ������δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!\n");
				break;				

			case "������":
				ob=new("/d/kunlun/npc/xiaoxiangzi");				
				//tell_object(me,"��־ƽ��"+me->query("name")+"����˵��������������δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!��\n");				
				command("tell "+ me->query("id")+" ��������δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!\n");
				break;				

			case "������":
				ob=new("/d/kunlun/npc/yinkexi");				
				//tell_object(me,"��־ƽ��"+me->query("name")+"����˵��������������δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!��\n");				
				command("tell "+ me->query("id")+" ��������δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!\n");
				break;				

			case "�����":
				ob=new("/d/xueshan/npc/daerba");				
				//tell_object(me,"��־ƽ��"+me->query("name")+"����˵�������������δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!��\n");				;
				command("tell "+ me->query("id")+" �������δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!\n");
				break;				
			case "����ֹ":
				ob=new("/d/gumu/jqg/npc/gsz");				
				//tell_object(me,"��־ƽ��"+me->query("name")+"����˵����������ֹ��δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!��\n");				
				command("tell "+ me->query("id")+" ����ֹ��δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!\n");
				break;
			default :
			    ob=new("/d/gumu/jqg/npc/gsz");				
				//tell_object(me,"��־ƽ��"+me->query("name")+"����˵����������ֹ��δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!��\n");				
				command("tell "+ me->query("id")+" ����ֹ��δ�뿪ȫ����������"+objwhere->query("short")+"����һ���!\n");
				break;           				
		}		
		
								
				message_vision(HIY"��־ƽ������ֻ�а�������ɱ�˲��ܳ�����ֹ���Ƕ��������ɧ�ţ���\n"NOR,me);
				tell_object(me,"��־ƽ��"+me->query("name")+"����˵��������ȥ����ɱ�ˣ�����ͷ����!��\n");
				ob->apply_condition("npcdie_job",120);
				ob->set("owner",me->query("id"));
				ob->set("long",ob->query("long")+"\n�������"+me->query("name")+"("+me->query("id")+")"+"Ҫ׷ɱ������ͷ�ӣ�\n");
				do_copyy(me,ob);
				ob->move(objwhere);		
			//remove_action("do_answer","answer");
		return 1;
	}
	if (arg=="no")
	{
		

		message_vision(HIY"$N����־ƽҡ��ҡͷ��˵������"+me->query_temp("qz/shouwei/target")+"�⹷����ɱ�������ñ��������ˣ���\n"NOR,me);
		command("sigh "+me->query("id"));
		command("say �������˾������ɣ�Ҳ����Ϊ���ˣ�ȥ�ɣ�\n");
		me->delete_temp("qz/shouwei/target");
		me->delete_temp("qz");
		TASKREWARD_D->get_reward(me,"������Ĺ",1,0,0,1+random(2),0,0,0,this_object());
		//remove_action("do_answer","answer");
		return 1;
	}

}
int ask_fangqi()
{
	object me=this_player();
	
	if (me->query_temp("qz/shouwei"))
	{
		
	    message_vision(HIC"��־ƽ��"+me->query("name")+"��̾һ����������Ȼ�겻��Ҳû��ϵ���´������ɡ���\n"NOR,me);
		me->delete_temp("qz");
		me->clear_conditions_by_type("qzsw_job_busy");
		me->add_condition("job_busy",4+random(2));

		return 1;
	}
	
	command("say "+me->query("name")+",�㵽��Ϲ�ܣ�ʲô��û�ɳɣ�Ҫ����ɶ�ء�\n");
	
	return 1;

}

void die()
{
	object ob;
	ob=this_object();
//	room=find_object("d/quanzhen/jiaobei");
	
	if (!query_temp("living"))
	{
		
			ob = new("/kungfu/class/quanzhen/yinzhiping");
			
			ob->move("/d/quanzhen/jiaobei");
		
	}
	::die();
}
//��ɽ�������

int ask_lilian()
{
	object me=this_player();
	//object ob=this_object();
	if (me->query("family/family_name")!="ȫ���")
	{
		command("say "+me->query("name")+",�㲻���ҽ��е��ӣ�����������\n");
		return 1;
	}
	if (me->query_skill("xiantian-gong",1)<200)
	{
		command("say "+me->query("name")+",������칦̫����,����200������������\n\n");
		return 1;
	}
	if(random(me->query("job_time/������Ĺ"))<500) 
	{
        command("say "+me->query("name")+",��������Ĺ�������㣬�Ҳ����㡣");
	    return 1;

	}
	if(me->query("shen") <0) 
	{
        command("say "+me->query("name")+",����аħ���֮����������ȫ�����Ұ���ѵ��������Լ���̫Ӳ��ô��");
	    return 1;

	}
	
	if (me->query_temp("askyin/xiashan"))
	{
		command("say "+me->query("name")+",�Ҳ��Ǹո���˵��ô�������Ͻ�ȥ?\n\n");
	    return 1;
	}
	
	command("say "+me->query("name")+",����������Ϣ����һ��������ʿ��������ɽ���¼��ᡣ\n");
	command("say �Ҵ�̽����ˣ��Ǹ���ͷ���˽л�����\n");
	command("angry ");
	command("say ������������Ȼ������Ĺ��������������ޣ����ǻ�ò��ͷ��ˡ�\n");
	command("say ������ȥ�ѻ���ɱ�ˣ���ͷ������������Ҫ���ѵ���������书�ܸߡ�\n");
	command("say �ұ��봫��һ���ڶ��������������Ľ������Ϳ����ǲ���������ˡ�\n");

	command("say "+me->query("name")+"���������Ƚϼ�ޣ�������ͷ���ң�\n");

	me->set_temp("askyin/xiashan",1);
	return 1;

}

//��ɲз�
// �����������������͡��������������ӡ���Ħ��
int do_copyy(object me,object ob)
{
	int i;
	if(!me) destruct(ob);
    i = me->query("max_pot") - (70 + random(10));
    
	if(i < 350) i = 350;
    ob->set("combat_exp", me->query("combat_exp")/5*4);
	ob->set("max_qi", me->query("max_qi")/3*2); 
    ob->set("max_jing", me->query("max_jing")/3*2); 
    ob->set("max_neili", me->query("max_neili")/3*2);
    ob->set("jiali", ob->query_skill("force",1)/3);
    ob->reincarnate(); 
    ob->set("eff_jing", me->query("eff_jing")/3*2);
    ob->set("jingli", me->query("jingli")/3*2);
    ob->set("neili", me->query("max_neili")/3*2);
    ob->set("qi", me->query("max_qi")/3*2);

	ob->set_skill("force",i);
	ob->set_skill("parry",i);
	ob->set_skill("dodge",i);
	ob->set_skill("strike",i);
	ob->set_skill("hand",i);
	ob->set_skill("finger",i);
	ob->set_skill("cuff",i);
	ob->set_skill("leg",i);
	ob->set_skill("claw",i);
	//û���⼼�ܻ��������Ӹ��ж� by renlai
	if (ob->query_skill_mapped("strike")) ob->set_skill(ob->query_skill_mapped("strike"),i);
	if (ob->query_skill_mapped("hand")) ob->set_skill(ob->query_skill_mapped("hand"),i);
	if (ob->query_skill_mapped("leg")) ob->set_skill(ob->query_skill_mapped("leg"),i);
	if (ob->query_skill_mapped("finger")) ob->set_skill(ob->query_skill_mapped("finger"),i);
	if (ob->query_skill_mapped("cuff")) ob->set_skill(ob->query_skill_mapped("cuff"),i);
	if (ob->query_skill_mapped("claw")) ob->set_skill(ob->query_skill_mapped("claw"),i);

	if (ob->query_skill_mapped("sword")) ob->set_skill(ob->query_skill_mapped("sword"),i);
	if (ob->query_skill_mapped("blade")) ob->set_skill(ob->query_skill_mapped("blade"),i);
	if (ob->query_skill_mapped("brush")) ob->set_skill(ob->query_skill_mapped("brush"),i);
	if (ob->query_skill_mapped("club")) ob->set_skill(ob->query_skill_mapped("club"),i);
	if (ob->query_skill_mapped("whip")) ob->set_skill(ob->query_skill_mapped("whip"),i);
	if (ob->query_skill_mapped("hammer")) ob->set_skill(ob->query_skill_mapped("hammer"),i);
	if (ob->query_skill_mapped("staff")) ob->set_skill(ob->query_skill_mapped("staff"),i);

	ob->set_skill(ob->query_skill_mapped("dodge"),i);
	ob->set_skill(ob->query_skill_mapped("parry"),i);
	ob->set_skill(ob->query_skill_mapped("force"),i);
	/*
	ob->set("chat_chance", 10);
	ob->set("chat_msg", ({
		(: random_move :)
	}) );
	*/
	return 1;
}
