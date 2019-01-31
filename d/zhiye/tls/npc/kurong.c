//update by cool 98.2.18
//added by tangfeng 2004
inherit F_MASTER;
inherit NPC;
#include <ansi.h>

#define QUESTDIR "quest/�����˲�/"
#define QUESTDIR1 "quest/�����˲�/�貨΢��ƪ/"
#define QUESTDIR2 "quest/�����˲�/����Ӫ��ƪ/"
#define QUESTDIR3 "quest/�����˲�/��������ƪ/"
#define QUESTDIR4 "quest/�����˲�/���ɾ�Ԯƪ/"
#define QUESTDIR5 "quest/�����˲�/��������ƪ/"
#define QUESTDIR6 "quest/�����˲�/�书/"

string askduanyu();
string tianlonghelp();
string asksave();
string askxiaofeng();
string askjiumozhi();

int ask_xingyue(object who);
string ask_liumai1();
string ask_liumai2();
string ask_krcg();
string ask_lmjj();

int ask_dudan(object who);   

void create()
{
		object ob;
        set_name("���ٳ���", ({ "kurong zhanglao","kurong","zhanglao"}) );
        set("nickname", "�����³���");
		set("long", 
" ���ٳ�����������֮������ߵ�һ����ɫ����
Ƥ���⻬������Ӥ�����ұߵ�һ��ȴ��ݹǣ�����
һ�Ž��Ƶ���Ƥ֮��ȫ�޼��⣬��ͷͻ�˳�������
Ȼ���ǰ�����ù�ͷ�������������б�����ߣ���
������ο�������ʮ�꣬��������ɮ�ڣ�˭Ҳû��
��������Ŀ��\n");
        set("gender", "����" );
        set("class","bonze");   
        set("unique", 1);
        set("age", 99);
        set("str", 30);
        set("con", 27);
        set("dex", 32);
        set("int", 35);
        set("per",23);

        set("max_jing",8000);
        set("eff_jingli", 8500);
        set("max_qi", 40500);
        set("jiali",200);
        set("neili",45000);
        set("max_neili",45000); 
        set("rank_info/respect", "��ɮ");
        create_family("������", 12, "ɮ��");
        set("combat_exp", 16350000);
        set("score", 1000);
		set("liumai-shenjian/shaoshang",1);
		 	 
		set("env/liumai","shaoshang");
        set("chat_chance_combat", 80);
        set("chat_msg_combat",({ 
                (: exert_function, "kurong" :),
				(: exert_function, "ku" :),
				(: exert_function, "rong" :),
                (: perform_action, "finger.yizhisanmai" :),
                (: perform_action, "finger.sandie" :),
        }));
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 550);
        set_skill("finger", 550);
        set_skill("whip", 500);
        set_skill("liumai-jianzhen",500);
        set_skill("cihang-bian", 500);
     
        
		set_skill("strike", 500);
        set_skill("buddhism", 200);
        set_skill("literate", 200);
        set_skill("liumai-shenjian", 150);
        set_skill("kurong-changong", 550);
        set_skill("yiyang-zhi", 550);
        set_skill("tianlong-xiang", 500);
 
        map_skill("whip", "cihang-bian");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "kurong-changong");
        map_skill("finger", "yiyang-zhi");
        map_skill("strike","kurong-changong");
        map_skill("force", "kurong-changong");
        prepare_skill("finger","yiyang-zhi"); 

        set_temp("apply/armor", 200);
        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);

        set("inquiry", ([
		"name": "ƶɮ���ǿ���",
		"����" : (: ask_xingyue :),
		"����" : (: ask_dudan :),
		"��������" : (: ask_krcg :),
		//"���ƶ�" : (: ask_liumai2 :), liumai/fightzhiok
		"�Ħ�ǰ���" : (: ask_liumai1 :),
            		"����" : (: askduanyu :),
		            "����" : "������Ǵ���",
		            "������" : "�������������£�����μ���ѧ�����֮�ء�",
		            "��������" : (: tianlonghelp :),
		            "Ӫ��" : (: asksave :),
		            "���" : (: asksave :),
		            "����" : "�����˳���Ľ�ݡ������壬�˵�һ���ú���",
		            "Ӫ�ȶ���" : (: asksave :),
		            "Ӫ������" : (: askxiaofeng :),
		            "Ľ�ݸ�" : "�����˳���Ľ�ݡ������壬��˵Ľ�ݹ����꼶���ᣬȴ����������",
		            "Ľ�ݲ�" : "����˵�ǣ�����Ľ�ݲ����Ľܲţ���ϧӢ�����š�",
		            "�Ħ��" : (: askjiumozhi :),
		            "������" : (: ask_liumai2 :),
					"������������" : (: ask_lmjj :),
		]));
     
        set("env/һ��ָ",3);
        setup();
        /*
        if (clonep(this_object())) {
		   if (ob = carry_object("/clone/weapon/xingyue"))
		   ob->wield(); 
	    }*/
		carry_object("/d/tls/obj/jiasha")->wear();
		carry_object("/d/tls/obj/sengxie")->wear();
}

void reset()
{
	object ob;
	if (clonep() && (ob = unew(BINGQI_D("xingyue")))) {
		ob->move(this_object());
		//command("wield xingyue puti");
    }
}

#include "kurong.h"
string askjiumozhi()
{
	object me;
	me = this_player();
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "��˵�������µ�һ��ɮ�Ħ�ǽ����������·𷨽����������Ҵ���֮�Ұ���";
	}
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
  	  command("? "+me->query("id"));
		  return "��ħɮ��Ȼ����۸��Ҵ������ˣ���Ϊ��ެ����һ�𷨸�ɮ��";
	}
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		return "�Ħ����Ϊ�����һ�𷨸�ɮ����ν����������ȫ��һ�ɺ��ԡ�";
	}

	command("nod");
	return "���������Ħ������ެ���Ļ�������������˵���ߴ��ǻۣ���ͨ�𷨣������书Ҳ�Ǿ��ˡ�";
}

string ask_krcg()
{
	object me;
	int i,j;
	me = this_player();
	if (!me->query("family")||me->query("family/master_id")!="kurong zhanglao")
	{
  		  command("? "+me->query("id"));
		  return "��˵����ͬ�ҷ��׷ǹʣ���Ϊ������";
	}
	if (me->query_skill("kurong-changong",1)<500)
	{
  		  command("kick");
  		  command("? "+me->query("id"));
		  return "��Ŀ���������500����������������ʲô���֣�";
	}
	if (me->query("quest/tls/kurong/pass"))
	{
  		  command("kick");
  		  command("? "+me->query("id"));
		  return "�㲻���Ѿ�����ô����������ʲô��";
	}
	if (time()-me->query("quest/tls/kurong/time")<86400)
	{
  		  command("sigh "+me->query("id"));
		  return "��������ô�ڿ죿";
    }
	i=random(10);
	j=random(me->query("kar"));
	command("say ���ſ�����������ע�ط��������Ϸ��ţ���ȫ�������ͨ����ôҲ�ܷ��������������һ����ǧ��Ҫ��ס��\n");
	command("pat "+me->query("id"));
	if( i==2 
		&& me->query("kar")<31
		&& j > 27 ) 
	{
		tell_object(me,HIY"\n�����˿��ٴ�ʦ��ָ�㣬�Կ����������������ĵá�\n"NOR);
		tell_object(me,HIG"\n����ͼ����Ϣ��ת�ζ��������ƺ�����һ����Ҫ�Ĺؿڣ������Ķ���\n"
			           HIR+"\n��ֻ�����һƬ�������Ҳ������¯��ȫ�������ƺ�Ҫ���Ʋ�ס��\n"
					   HIC+"�����㲻֪����֮�ʣ�һ�ԵĿ�����ʦ��Ȼ�����ָ������ӡ��Ѩ��\n"
						 +"�����ж�Ѩ����ɱ�����Ѿõľ�������й��ĳ���һ����й���С�\n"
						HIG +"���֮�䣬�������������������������ٵ���߾��硣\n"NOR);
		me->set("quest/tls/kurong/pass",1);
		log_file("quest/kurong", sprintf("%8s(%8s) ʧ��%d�κ󣬲���͸����������߾��硣�����iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/tls/kurong/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));
		me->set("title",HIY"������������"NOR);
		
		return "��ϲ���ܿ��������ɹ�!\n";
		//me->add(QUESTDIR4+"shenzhao",1);//
	}
	
   else
	{
		log_file("quest/kurong", sprintf("%8s(%8s) ���ܿ���������߾���ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n", 
			me->name(1),me->query("id"), me->query("quest/tls/kurong/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"�����˿��ٳ��ϵ�ָ�㣬���ǶԿ��������İ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/tls/kurong/fail",1);
		me->set("quest/tls/kurong/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź����ܿ���������߾����������ʧ��"+me->query("quest/tls/kurong/fail")+"�Ρ�\n";
	}

}
string askxiaofeng()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR3+"start"))
  {
  	  command("hoho");
  		return "�����˳���Ľ�ݡ������壬�˵�һ���ú�������Ԯ��֮˵��";
  }
	if (me->query(QUESTDIR3+"start") && !me->query(QUESTDIR3+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��˵������飬ֻ���������������漰����֮����";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
		  return "�Ƿ壬�Ѳ��������ȳ���ԭ��������ν��Ȳ�֪���⣡";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��˵������飬ֻ���������������漰����֮����";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "��˵������飬ֻ���������������漰����֮����";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "��˵��һս��"+me->query("name")+"�����������֣��˵���������";
  }
  command("hoho");
	return "�����˳���Ľ�ݡ������壬�˵�һ���ú�������Ԯ��֮˵��";
}
string asksave()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start") &&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "С����������ϲ��ѧ��ֻ�����׾���ƽ�׽��ˣ�����Ԯ��֮˵��";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��˵��ǰ��ʱ��С���Ӻ����������ǳ���һ��������δ�лؼң���֪"+RANK_D->query_respect(me) +"�ɷ��������һ�¡�";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��˵������飬ֻ���������������漰����֮����";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "�ҷ�ȱ���ֻ���Դ���ٹȻ�����С���Ӿ����㱣���֪���кζ������ܺ������ˡ�";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "�ҷ�ȱ���С��������ٹȻ�����������Ѫ�������������죬�ű�������������������ˡ�";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "�ҷ�ȱ�����Ȼ�ǳ��Ħ����ȸ��֣���Ը���Ӽ������డ��";
	}
	command("hoho");
	return "С����������ϲ��ѧ��ֻ�����׾���ƽ�׽��ˣ�����Ԯ��֮˵��";
}
string askduanyu()
{
	object me;
	me = this_player();
	if(!me->query(QUESTDIR1+"start" )&&!me->query(QUESTDIR2+"start"))
	{
  	  command("hoho");
  		return "���������������������������Ĺ��ӣ���˵���ʴ��������Դ���ֻ��������ϲ��ѧ��ֻ�����׾���";
	}
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��˵��ǰ��ʱ��С���Ӻ����������ǳ���һ��������δ�лؼҡ�";
	}
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "��˵������飬ֻ���������������漰����֮����";
	}
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "�ҷ�ȱ�����л"+RANK_D->query_respect(me) +"���С���ӡ�";
	}
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "�ҷ�ȱ���С��������ٹȻ�����������Ѫ�������������죬�ű���������������ˡ�";
	}
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "�ҷ�ȱ�����Ȼ�ǳ��Ħ����ȸ��֣���Ը���Ӽ������డ��";
	}
	command("hoho");
	return "���������������������������Ĺ��ӣ���˵���ʴ��������Դ���";
}
string tianlonghelp()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"over"))
  {
  	  command("haha");
  		return "���������Ҷμ���ѧ�����֮�أ��������ƣ��벻ҪΣ��������";
  }
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "��˵�������¸�ɮ�Ħ�ǲ��ս����������£���֪��ϲ�ǻ���";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("heng");
		  return "�ҷ�ȱ�����ħɮ��Ȼ����۸��Ҵ������ˣ���Ϊ��ެ����һ�𷨸�ɮ��";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("thank "+me->query("id"));
		  return "�ҷ�ȱ�����л"+RANK_D->query_respect(me) +"�����ⳡ����Σ���������Ҵ���С���ӵ��Խ�ȡ�";
  }
  command("hoho");
	return "�ҷ�ȱ������������Ҷμ���ѧ�����֮�أ��������ƣ��벻ҪΣ��������";
}
//�����𲽽׶�

string ask_liumai1()
{
    object ob;
    
	ob=this_player();
	
	if(!ob->query("quest/�����˲�/����Ӫ��ƪ/over"))
		return "����Ҫ�ȰѶ����Ȼ�����˵,�������Ӫ��ƪ��\n";
    if (ob->query("family/family_name")!="������" || ob->query("family/master_id")!="kurong zhanglao")
		return "�㲻���ҵĵ��ӣ���Ϊ������\n";
	
	
	if (ob->query("yyz/degree")>3)
	{
		command("say ֻ��һ��ָ�ﵽ��Ʒ���Ϸ�����һ��ָ���㻹���Զ�ء�\n");			

	}
		
	if ((time()-ob->query("quest/tls/liumai_1/time"))<86400)
	{
		command("say ����Ļ����Ѿ�û�ˣ�����������\n");
		return "";
	}

	if (ob->query("quest/tls/liumai_1/pass"))
	{
		command("say �㲻�ǽ⿪һ���˶�ô����\n");
		return "";
	}		
		
	command("say ���ã������������Ħ�����ã��ҿ������߲��ƣ�������һ��ȥ��Ĳ���ÿ�����\n");
	ob->set_temp("tls/fight1",1);
	return "�����ӷ� \n";	
	
}

int prevent_learn(object ob, string skill)
{
	if (skill == "yiyang-zhi"){
		command("һ��ָ�����Ҵ�������֮�����������޴����߲��ö�����\n");
		return 1;
	}
	return 0;
}