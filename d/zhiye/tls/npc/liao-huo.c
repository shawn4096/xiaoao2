//added by tangfeng@SJ 2004


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
string ask_for_join();
string ask_baijian();

void create()
{
        set_name("�˻���ʦ", ({ "liaohuo chanshi","liaohuo","chanshi"}) );
        set("nickname", "©������");
        set("long", "�˻���ʦ�Ǳ����ɵĵ���λ���ӣ�����Լ��ʮ��
������档���������д���ӭ��ְ֮������Ц�ݿ�
�ϣ�����ȴ�������ء����š�\n");
        set("gender", "����" );
        set("class", "bonze");
        set("attitude", "friendly");
        set("age", 41);
        set("shen_type", 1);
        set("str", 22);
        set("int", 22);
        set("con", 23);
        set("dex", 22);
        create_family("������", 14, "����");
        set("unique", 1);
        set("qi", 8000);
        set("max_qi", 8000);
        set("jing", 4000);
        set("max_jing", 4000);
        set("neili", 5400);
        set("max_neili", 5400);
        set("jiali", 90);
        set("combat_exp", 3500000);
        set("score", 5000);

        set_skill("force", 280);
        set_skill("qiantian-yiyang", 290);
        set_skill("dodge", 280);
        set_skill("tianlong-xiang", 280);
        set_skill("parry", 280);
        set_skill("duanjia-jianfa", 280);
        set_skill("strike", 280);
        set_skill("sword", 280);
        set_skill("buddhism", 180);
        set_skill("literate", 180);
        set_skill("qingyan-zhang", 280);
        map_skill("force", "qiantian-yiyang");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "duanjia-jianfa");
        map_skill("sword", "duanjia-jianfa");
        map_skill("strike", "qingyan-zhang");
        prepare_skill("strike","qingyan-zhang");                
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: exert_function, "qi" :),
				(: exert_function, "jingxin" :),
				(: perform_action, "sword.fenglei" :),
		 }));

		set("inquiry",([
                "���"  : (: ask_for_join :),
                "����"  : (: ask_for_join :),
				"�ݼ����ٴ�ʦ"  : (: ask_baijian :),
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
		            "������" : "��˵������������߾�ѧ���ҹ����Ⱳ��Ҳδ�ܼ�����",
	]));
        setup();
        carry_object(BINGQI_D("changjian"))->wield(); 
        carry_object("/d/tls/obj/jiasha1")->wear(); 
        carry_object("/d/tls/obj/sengxie")->wear();
}
#include "liao.h";
void init()
{
	object me;
	me = this_player();
	::init();
	if (interactive(me) && living(me)) {
	 	if(me->query(QUESTDIR2+"start")&& !me->query(QUESTDIR2+"over"))
		{
    	command("look "+me->query("id"));
    	command("touch "+me->query("id"));
    	command("say ����λ������æ�����µ��ɸ��������ˡ�"); 
		}
	}
	
}
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
		  return "��ħɮ��Ȼ����۸��Ҵ������ˣ�ʲô��ެ����һ�𷨸�ɮ����P��P��";
  }
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "�Ħ����Ϊ�����һ�𷨸�ɮ����ν����������ȫ��һ�ɺ��ԡ�";
  }
  /*
  ���������Ħ������ެ���Ļ�����������ֻ��˵���ߴ��ǻۣ���ͨ�𷨣�ÿ�����꣬��̳����˵�����������ø��صĸ�ɮ��£�
  �Ƽ���ѩɽ�����£�ִ�����ѣ������ڵ䣬�ŷ��ȱϣ��޲���ϲ��̾��ȥ��
  */
  command("nod");
	return "���������Ħ������ެ���Ļ�������������˵���ߴ��ǻۣ���ͨ�𷨣������书Ҳ�Ǿ��ˡ�";
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
		  return "�Ƿ壬�Ѳ��������ȳ���ԭ��������ν��Ȳ�֪ʲô��˼�������ʣ�";
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
		  return "��˵��ǰ��ʱ��С���Ӻ����������ǳ���һ��������δ�лؼң���֪�����ɷ��������һ�¡�";
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
		  return "ֻ���Դ���ٹȻ�����С���Ӿ����㱣���֪���кζ������ܺ������ˡ�";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "С��������ٹȻ�����������Ѫ�������������죬�ű�������������������ˡ�";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "��Ȼ�ǳ��Ħ����ȸ��֣���Ը���Ӽ������డ��";
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
  		return "С����������ϲ��ѧ��ֻ�����׾���";
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
		  return "��л�������С���ӡ�";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "С��������ٹȻ�����������Ѫ�������������죬�ű���������������ˡ�";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "��Ȼ�ǳ��Ħ����ȸ��֣���Ը���Ӽ������డ��";
  }
  command("hoho");
	return "��������������֮�ӡ�";
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
  	  command("sigh");
		  return "��ħɮ��Ȼ����۸��Ҵ������ˣ�ʲô��ެ����һ�𷨸�ɮ����P��";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("thank "+me->query("id"));
		  return "��л���������ⳡ����Σ���������Ҵ���С���ӵ��Խ�ȡ�";
  }
  command("hoho");
	return "���������Ҷμ���ѧ�����֮�أ��������ƣ��벻ҪΣ��������";
}

string ask_baijian()
{
	object me;
	me = this_player();
	
	if (!me->query_temp("jueji/askhyd"))
	{
  		  command("nod "+me->query("id"));
		  command("say ��˵�������µ�һ��ɮ�Ħ�ǽ����������·𷨽����������Ҵ���֮�Ұ���");
		  return "����������������˵������";
	}
	command("? ");
    me->delete_temp("jueji/askhyd");
	me->set_temp("jueji/baijian",1);
	return "��ӭ�Ħ�Ǵ�ʦ�ĵ������ݼ��������£���������ʲôƾ֤û�У�";	

}

int accept_object(object who, object obj)
{
	
	if (who->query_temp("jueji/baijian")
		&& obj->query("id")=="huangjin baitie"
		)
	{
		who->set_temp("hydjj/receive",1);
		write(HIY"�㽫�ƽ�����ݸ����˻���ʦ���˻���ʦ�ӹ�����ϸ�����·�Ƥ����Ȼ�Ǵ����������Ħ�ǵ��ױ���ʡ�\n"NOR);
		command("say ��Ȼ���Ħ�Ǵ�ʦ���״����ӣ��Ǿ����Ե�һ���Ҹ����洫������");
		command("chat ��ӭ�����������Ħ�����µ���"+who->query("name")+"ǰ�������£�");
		//command("chat ��ӭ�����������Ħ�����µ���ǰ�������£�����"+);
		write(HIC"����ᣬ�˻���ʦ�����˻�����˵������ʦ��������µ�Ĳ���ã�����\n"NOR);
		obj->move(this_object());
		destruct(obj);
		who->delete_temp("jueji/baijian");		
		return 0;
	}
}