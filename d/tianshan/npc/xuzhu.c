// /NPC xuzhu.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string ask_jhg();
string ask_tstl();
void create()
{
	set_name("虚竹", ({ "xu zhu", "xu", "zhu" }));
	set("long",
	    "这是一个二十五六岁的年轻人, 浓眉大眼,\n"+
	    "大大的鼻子扁平下塌, 容貌颇为丑陋. \n"+
	    "身穿一件华贵雅致的长袍, 倒使他更显几分精神.\n"+
	    "他就是天山童姥的救命恩人.\n");
	set("title", "灵鹫宫掌门人");
	set("gender", "男性");
	set("age", 26);
	set("nickname", HIR "梦郎" NOR);
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
	create_family("灵鹫宫",2, "弟子");
        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                //(: perform_action, "sword.kuangwu" :),
                //(: perform_action, "sword.shandian" :),
                (: perform_action, "strike.baihong" :),
               (: perform_action, "hand.zhemei" :),
					(: exert_function, "duzun" :),
        }));

	set("inquiry", ([

		//"剑湖宫" : (: ask_jhg :),
			"天山童姥" : (: ask_tstl :),
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
	 if (ob->query("family/family_name")=="灵鹫宫"&& ob->query("family/master_name")=="虚竹")
	 {
		 command("say 你这是来折腾为师么？");
		 command("heng "+ob->query("id"));
		 return;
	 }
     
	  if (ob->query("tstl/askxuzhu")&&ob->query_temp("tstl_askxuzhu"))
	  {
		  command("say 你和我没关系，你和灵鹫宫也没有关系,赶紧离开！\n");
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
		    command("say 你入我灵鹫宫，不散掉"+to_chinese(sk[i])+"，如何能修习天山绝学，不怕走火入魔？\n");
			return;
		  }
	 	  /*else {
			message_vision(HIY"虚竹运起内功，伸掌按在$N的泥丸宫，$N只觉一股极热的内力涌动，化掉了你的先前的内功。\n"NOR,ob);
			ob->delete("family");
			continue;   
			}*/
      }   
  
  
   if ((int)ob->query_skill("zhemei-shou", 1) < 220) 
   {
		command("say 折梅手220才算打下基础，" + RANK_D->query_respect(ob) + "是否还应该多练练折梅手？");
		return;
	}  
   if ((int)ob->query_skill("liuyang-zhang", 1) < 220) 
   {
		command("say 六阳掌220才算打下基础，" + RANK_D->query_respect(ob) + "是否还应该多练练六阳掌？");
		return;
	   }  
   if (ob->query("quest/tonglao/pass")){

		message_vision(HIC"虚竹垂目沉思片刻, 说道：“既然你已经深得童姥真传, 我就代替童姥收下你了。”\n"NOR,ob);
        command("recruit " + ob->query("id"));
		 command("chat 我灵鹫宫又增加了一位英雄豪杰！");
		 command("chat* pat "+ob->query("id"));
		 command("chat* laugh ");
		if (ob->query("gender")=="男性")
			{
			 ob->set("title",HIY "灵鹫宫使者" NOR);
            
			 }
		else ob->set("title",HIM "灵鹫宫仙子" NOR);
        return;
	   }
   else
      {
		message_vision("虚竹瞪着你看了半天,说道：“阁下不会是想来抢我的生意吧?”\n",ob);
       return;
	   }
}
/*

string ask_jhg()
{
	object ob = this_player();
	mapping fam = ob->query("family");
	if (!fam || fam["family_name"] != "灵鹫宫" )
		return RANK_D->query_respect(ob)+"，无崖子前辈是有叫我去剑湖宫找一位女子学功夫，只是我现在走不开。";
        if (ob->query_skill("bahuang-gong", 1) < 300 )
	return "这位"+ RANK_D->query_respect(ob) +"，无崖子前辈是有叫我去剑湖宫找一位女子学功夫，只是我现在走不开。";


if(  ob->query("marks/xiaoyao") || ob->query("quest/xiaoyao/pass") || ob->query_temp("marks/ljg/gotolqs"))
      return "这位"+ RANK_D->query_respect(ob) +"，我不是已经让你去剑湖宫打探情况了吗？";
	
       ob->set_temp("marks/ljg/gotolqs", 1);
	command("nod " + ob->query("id"));
	return "无崖子前辈是有叫我去剑湖宫找一位女子学功夫，那位女子似乎与我灵鹫宫渊源颇深，你有时间的话可以去碰碰运气？";       
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
		command("say 你已经转换过一次了，怎么又来？\n ");
		return "赶紧离开！\n";
	}*/
	if ((int)ob->query_skill("zhemei-shou", 1) < 220) 
    {
		command("say 折梅手220才算打下基础，" + RANK_D->query_respect(ob) + "是否还应该多练练折梅手？");
		return;
	}  
    if ((int)ob->query_skill("liuyang-zhang", 1) < 220) 
    {
		command("say 六阳掌220才算打下基础，" + RANK_D->query_respect(ob) + "是否还应该多练练六阳掌？");
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
		    command("say 你入我灵鹫宫，不散掉"+to_chinese(sk[i])+"，如何能修习天山绝学，不怕走火入魔？\n");
			return;
		  }
	   /*else {
			message_vision(HIY"虚竹运起内功，伸掌按在$N的泥丸宫，$N只觉一股极热的内力涌动，化掉了你的先前的内功。\n"NOR,ob);
			ob->delete("family");
			continue;   
			}*/
      }   


	
	if (ob->query("quest/tonglao/pass") )
	{
		

		command("say 既然童姥已经传了你天山武技，你若想入我灵鹫宫，你必须把其他门派内功都放弃掉。\n ");
        message_vision(HIY"虚竹运起内功，伸掌按在$N的泥丸宫，$N只觉一股极热的内力涌动，化掉了你的先前的内功。\n"NOR,ob);		
				
		ob->delete("family");	
		
		ob->set("tstl/askxuzhu",1);
		ob->set_temp("askxuzhu",1);
		ob->map_skill("force", "none");//防止呼吸bug by renlai
		call_out("attempt_apprentice",0,ob);
		return "你直觉浑身燥热，但瞬间却清凉一片,原来为虚竹将你内功以北冥心法化掉，你可以重新拜师了。\n";
	}
    return "你来跟我抢生意么？";       
}

