// /NPC xuzhu.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string ask_jhg();
string ask_tstl();
void create()
{
	set_name("����", ({ "xu zhu", "xu", "zhu" }));
	set("long",
	    "����һ����ʮ�������������, Ũü����,\n"+
	    "���ı��ӱ�ƽ����, ��ò��Ϊ��ª. \n"+
	    "��һ���������µĳ���, ��ʹ�����Լ��־���.\n"+
	    "��������ɽͯ�ѵľ�������.\n");
	set("title", "���չ�������");
	set("gender", "����");
	set("age", 26);
	set("nickname", HIR "����" NOR);
	set("shen_type",1);
	set("attitude", "peaceful");

	set("str", 50);
	set("int", 55);
	set("con", 50);
	set("dex", 50);
	set("per", 1);

	set("qi", 55000);
	set("max_qi", 55000);
	set("jing", 12000);
	set("max_jing", 12000);
	set("neili", 48000);
	set("max_neili", 48000);
	set("jiali", 200);

	set("combat_exp", 15500000);
	set("score", 20000);
	set_skill("force", 520);
	set_skill("yangyanshu", 200);
	set_skill("dodge", 520);
	set_skill("parry", 520);
	set_skill("sword", 500);
	set_skill("hand",500);
	set_skill("strike", 500);
	//set_skill("finger", 200);
	//set_skill("claw", 200);
	//set_skill("cuff", 200);
	//set_skill("leg", 200);
	//set_skill("sword", 500);
	set_skill("hand",500);
	set_skill("medicine",200);
	//set_skill("longzhua-gong",200);
	//set_skill("yizhi-chan",200);
	set_skill("buddhism",200);
	set_skill("literate",100);
	set_skill("zhemei-shou",520);
	set_skill("liuyang-zhang",520);
	set_skill("yueying-wubu",500);
	set_skill("bahuang-gong", 500);
    set_skill("tianyu-qijian",500);
	map_skill("force", "bahuang-gong");
	map_skill("finger", "yizhi-chan");
	map_skill("claw", "longzhua-gong");
	map_skill("sword", "tianyu-qijian");
	map_skill("strike","liuyang-zhang");
	map_skill("dodge", "yueying-wubu");
	map_skill("unarmed", "liuyang-zhang");
	map_skill("hand", "zhemei-shou");
	map_skill("parry", "liuyang-zhang");

	prepare_skill("hand","zhemei-shou");
	prepare_skill("strike","liuyang-zhang");	
	create_family("���չ�",2, "����");
        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                //(: perform_action, "sword.kuangwu" :),
                //(: perform_action, "sword.shandian" :),
                (: perform_action, "strike.baihong" :),
               (: perform_action, "hand.zhemei" :),
					(: exert_function, "duzun" :),
        }));

	set("inquiry", ([

		//"������" : (: ask_jhg :),
			"��ɽͯ��" : (: ask_tstl :),
	]));
    setup();
	carry_object("/clone/armor/changpao1")->wear();
	add_money("silver",50);
}

void attempt_apprentice(object ob)
{
     mapping skl = ob->query_skills();
     string *sk;	
     int i;		
 	 sk = keys(skl);
     i = sizeof(sk);
	 if (ob->query("family/family_name")=="���չ�"&& ob->query("family/master_name")=="����")
	 {
		 command("say ������������Ϊʦô��");
		 command("heng "+ob->query("id"));
		 return;
	 }
     
	  if (ob->query("tstl/askxuzhu")&&ob->query_temp("tstl_askxuzhu"))
	  {
		  command("say �����û��ϵ��������չ�Ҳû�й�ϵ,�Ͻ��뿪��\n");
		  return;
	  }
	  while (i--) {
        if (
		//	sk[i] == "jiuyang-shengong" || sk[i] == "jiuyin-zhengong" ||sk[i] == "lengquan-shengong" || sk[i] == "shenzhao-jing"
        //|| sk[i] == "hamagong" || sk[i] == "kuihua-shengong"|| sk[i] == "taixuan-gong" || sk[i] == "xixing-dafa" 
		//|| sk[i] == "beiming-shengong"
        // || sk[i] == "bahuang-gong" 
		//|| sk[i] == "xiaowu-xianggong" 
		 sk[i] == "xiantian-gong" || sk[i] == "tianmo-gong"
        || sk[i] == "yunu-xinjing"|| sk[i] == "huashan-qigong"|| sk[i] == "zixia-gong"|| sk[i] == "yinyun-ziqi"|| sk[i] == "bihai-chaosheng"
        || sk[i] == "hanbing-zhenqi"|| sk[i] == "longxiang-boruo"|| sk[i] == "huntian-qigong"|| sk[i] == "xuantian-wuji"|| sk[i] == "guiyuan-tunafa"
        || sk[i] == "yijin-jing"|| sk[i] == "qiantian-yiyang"|| sk[i] == "kurong-changong"|| sk[i] == "linji-zhuang"|| sk[i] == "huagong-dafa"||sk[i] == "tianmo-gong" 
        || sk[i] == "shenyuan-gong"|| sk[i] == "shenghuo-shengong" || sk[i] == "dulong-dafa") 
		 {
		    command("say ���������չ�����ɢ��"+to_chinese(sk[i])+"���������ϰ��ɽ��ѧ�������߻���ħ��\n");
			return;
		  }
	 	  /*else {
			message_vision(HIY"���������ڹ������ư���$N�����蹬��$Nֻ��һ�ɼ��ȵ�����ӿ���������������ǰ���ڹ���\n"NOR,ob);
			ob->delete("family");
			continue;   
			}*/
      }   
  
  
   if ((int)ob->query_skill("zhemei-shou", 1) < 220) 
   {
		command("say ��÷��220������»�����" + RANK_D->query_respect(ob) + "�Ƿ�Ӧ�ö�������÷�֣�");
		return;
	}  
   if ((int)ob->query_skill("liuyang-zhang", 1) < 220) 
   {
		command("say ������220������»�����" + RANK_D->query_respect(ob) + "�Ƿ�Ӧ�ö����������ƣ�");
		return;
	   }  
   if (ob->query("quest/tonglao/pass")){

		message_vision(HIC"����Ŀ��˼Ƭ��, ˵��������Ȼ���Ѿ����ͯ���洫, �Ҿʹ���ͯ���������ˡ���\n"NOR,ob);
        command("recruit " + ob->query("id"));
		 command("chat �����չ���������һλӢ�ۺ��ܣ�");
		 command("chat* pat "+ob->query("id"));
		 command("chat* laugh ");
		if (ob->query("gender")=="����")
			{
			 ob->set("title",HIY "���չ�ʹ��" NOR);
            
			 }
		else ob->set("title",HIM "���չ�����" NOR);
        return;
	   }
   else
      {
		message_vision("��������㿴�˰���,˵���������²������������ҵ������?��\n",ob);
       return;
	   }
}
/*

string ask_jhg()
{
	object ob = this_player();
	mapping fam = ob->query("family");
	if (!fam || fam["family_name"] != "���չ�" )
		return RANK_D->query_respect(ob)+"��������ǰ�����н���ȥ��������һλŮ��ѧ����ֻ���������߲�����";
        if (ob->query_skill("bahuang-gong", 1) < 300 )
	return "��λ"+ RANK_D->query_respect(ob) +"��������ǰ�����н���ȥ��������һλŮ��ѧ����ֻ���������߲�����";


if(  ob->query("marks/xiaoyao") || ob->query("quest/xiaoyao/pass") || ob->query_temp("marks/ljg/gotolqs"))
      return "��λ"+ RANK_D->query_respect(ob) +"���Ҳ����Ѿ�����ȥ��������̽�������";
	
       ob->set_temp("marks/ljg/gotolqs", 1);
	command("nod " + ob->query("id"));
	return "������ǰ�����н���ȥ��������һλŮ��ѧ������λŮ���ƺ��������չ�ԨԴ�������ʱ��Ļ�����ȥ����������";       
}


*/

string ask_tstl()
{
	object ob = this_player();
	mapping skl = ob->query_skills();
    string *sk;	
    int i;		
 	
	
	sk = keys(skl);
    i = sizeof(sk);
	
	/*if (ob->query("tstl/askxuzhu"))
	{
		command("say ���Ѿ�ת����һ���ˣ���ô������\n ");
		return "�Ͻ��뿪��\n";
	}*/
	if ((int)ob->query_skill("zhemei-shou", 1) < 220) 
    {
		command("say ��÷��220������»�����" + RANK_D->query_respect(ob) + "�Ƿ�Ӧ�ö�������÷�֣�");
		return;
	}  
    if ((int)ob->query_skill("liuyang-zhang", 1) < 220) 
    {
		command("say ������220������»�����" + RANK_D->query_respect(ob) + "�Ƿ�Ӧ�ö����������ƣ�");
		return;
	   }  
	
	
	while (i--) {
        if (
		//	sk[i] == "jiuyang-shengong" || sk[i] == "jiuyin-zhengong" ||sk[i] == "lengquan-shengong" || sk[i] == "shenzhao-jing"
        //|| sk[i] == "hamagong" || sk[i] == "kuihua-shengong"|| sk[i] == "taixuan-gong" || sk[i] == "xixing-dafa" 
		//|| sk[i] == "beiming-shengong"
        // || sk[i] == "bahuang-gong" 
		//|| sk[i] == "xiaowu-xianggong" 
		 sk[i] == "xiantian-gong" || sk[i] == "tianmo-gong"
        || sk[i] == "yunu-xinjing"|| sk[i] == "huashan-qigong"|| sk[i] == "zixia-gong"|| sk[i] == "yinyun-ziqi"|| sk[i] == "bihai-chaosheng"
        || sk[i] == "hanbing-zhenqi"|| sk[i] == "longxiang-boruo"|| sk[i] == "huntian-qigong"|| sk[i] == "xuantian-wuji"|| sk[i] == "guiyuan-tunafa"
        || sk[i] == "yijin-jing"|| sk[i] == "qiantian-yiyang"|| sk[i] == "kurong-changong"|| sk[i] == "linji-zhuang"|| sk[i] == "huagong-dafa"||sk[i] == "tianmo-gong" 
        || sk[i] == "shenyuan-gong"|| sk[i] == "shenghuo-shengong" || sk[i] == "dulong-dafa")
		 {
		    command("say ���������չ�����ɢ��"+to_chinese(sk[i])+"���������ϰ��ɽ��ѧ�������߻���ħ��\n");
			return;
		  }
	   /*else {
			message_vision(HIY"���������ڹ������ư���$N�����蹬��$Nֻ��һ�ɼ��ȵ�����ӿ���������������ǰ���ڹ���\n"NOR,ob);
			ob->delete("family");
			continue;   
			}*/
      }   


	
	if (ob->query("quest/tonglao/pass") )
	{
		

		command("say ��Ȼͯ���Ѿ���������ɽ�似���������������չ������������������ڹ�����������\n ");
        message_vision(HIY"���������ڹ������ư���$N�����蹬��$Nֻ��һ�ɼ��ȵ�����ӿ���������������ǰ���ڹ���\n"NOR,ob);		
				
		ob->delete("family");	
		
		ob->set("tstl/askxuzhu",1);
		ob->set_temp("askxuzhu",1);
		ob->map_skill("force", "none");//��ֹ����bug by renlai
		call_out("attempt_apprentice",0,ob);
		return "��ֱ���������ȣ���˲��ȴ����һƬ,ԭ��Ϊ�������ڹ��Ա�ڤ�ķ���������������°�ʦ�ˡ�\n";
	}
    return "��������������ô��";       
}

