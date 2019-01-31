// Modify By River 98/12
#include <ansi.h>

inherit NPC;
string ask_duan();

void create()
{
        set_name("黄眉和尚", ({ "huangmei heshang", "heshang", "huangmei" }) );
        set("title", "拈花寺主持");
		set("nickname",HIY"黄眉僧"NOR);
        set("gender", "男性" );
        set("age", 65);
        set("str", 35);
        set("con", 30);
        set("dex", 23);
        set("int", 20);
        set("unique", 1);

        set("max_qi", 25000);
        set("max_jing", 5000);
        set("eff_jingli", 5000);
        set("max_neili", 25000);
        set("jiali", 200);       

        create_family("福建莆田少林寺", 10, "弟子");
        set("long", 
        "一个满脸皱纹、身形高大的老僧。这老僧两道焦黄长眉，眉尾下垂。\n");

        set("combat_exp", 10000000);
        set("score", 20000);       
	
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 450);
        set_skill("finger", 450);
        set_skill("buddhism", 200);
        set_skill("literate", 220);
        set_skill("yijin-jing", 450);
        set_skill("nianhua-zhi", 450);
        set_skill("shaolin-shenfa", 450);
        map_skill("dodge", "shaolin-shenfa");
        map_skill("parry", "nianhua-zhi");
        map_skill("finger", "nianhua-zhi");
        map_skill("force", "yijin-jing");
        prepare_skill("finger","nianhua-zhi");      
		set("inquiry", ([
			//"段誉" : (: ask_duan :),
			"救人" : (: ask_duan :),       
		]));
		set("chat_chance_combat", 60);
		set("chat_msg_combat",({
			(: perform_action, "finger.fuxue" :),
			(: exert_function, "jingang" :),
		}));

        setup();
        carry_object("/d/shaolin/obj/cheng-cloth")->wear();
}


string ask_duan()
{
      object me=this_player();
	  message_vision(HIC"\n\n$N鞠躬向黄眉僧说道，“大师您好，王爷让我来此给您捎个口信。”\n\n"NOR,me);
	  
	  if (!me->query_temp("yyzhi/four/fightok"))
		return "段王子我曾见过，聪慧伶俐，大智若愚。\n";
	  else {
	     me->set_temp("yyzhi/four/askhuang",1);
		 me->delete_temp("yyzhi/four/fightok");
         command("say 既然是段王爷有请，我又岂能置身事外？\n");
		 command("say 也罢，去年为百姓求情，免去一年的税粮，老僧我也算是报答皇上的皇恩了。\n");
		 command("say 你回去跟王爷说声，就说届时老僧一定会到。\n");
		 return "黄眉僧说完偏低头沉思，再也不言语。";
        
	  }
	  
}
