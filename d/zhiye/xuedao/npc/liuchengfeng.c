// liuchengfeng.c

inherit NPC;
#include <ansi.h>;
#include "lhlsnpc.h"

#include "/d/suzhou/npc/lchj.h"
string ask_diyun();

void create()
{
       set_name("刘承风", ({ "liu chengfeng", "liu" }));
       set("long", 
       "他就是南四奇“落花流水”中的老三。\n"
       "南四奇横行江南，行侠仗义，刘承风一手太极剑，更是声震大江南北。\n");
       set("gender", "男性");
       set("nickname", HIY"柔云剑"NOR);
       set("age", 41);
       set("attitude", "peaceful");
       set("shen_type", 0);
       set("str", 35);
       set("int", 38);
       set("con", 35);
       set("dex", 35);

       set("max_qi", 12000);
       set("max_jing", 5000);
       set("neili", 12000);
       set("max_neili", 12000);
       set("jiali", 130);
       set("combat_exp", 9800000);
       set("shen_type", 1);

       set_skill("force", 450);
       set_skill("yinyun-ziqi", 450);
       set_skill("dodge", 450);
       set_skill("tiyunzong", 450);
       set_skill("cuff", 450);
       set_skill("taiji-quan", 450);
       set_skill("parry", 450);
       set_skill("sword", 450);
       set_skill("taiji-jian", 450);
       set_skill("literate", 170);

       map_skill("force", "yinyun-ziqi");
       map_skill("dodge", "tiyunzong");
       map_skill("cuff", "taiji-quan");
       map_skill("parry", "taiji-jian");
       map_skill("sword", "taiji-jian");
	   prepare_skill("cuff", "taiji-quan");
		set("inquiry", ([
		"狄云" : (: ask_diyun :),
		"name": "你问这干嘛，我就是柔云剑刘承风，你有什么事情？",
		//"落花流水" : (: ask_lhls :),
		//"": (: ask_qiyu :),
		])); 

       set("chat_chance", 70);
       set("chat_msg", ({
              "刘乘风忽然纵声长啸：“落花流～～水……”中气充沛，远远传了出去。\n",
	}));
		set("chat_chance_combat", 70);

      set("chat_msg_combat", ({
			(: perform_action, "sword.chan" :),
			(: perform_action, "sword.lian" :),
			(: perform_action, "sword.sanhuan" :),
			(: perform_action, "sword.raozhi" :),
			
			(: perform_action, "cuff.dongjing" :),
			(: perform_action, "cuff.luanhuan" :),

		}));
       setup();
       carry_object("/clone/weapon/mujian")->wield();
}

void die()
{
	object me,ob;
	object lastob = query_temp("last_damage_from");
	
	//这里判断杀死自己的是不是自己的任务人
	me = this_object();	
	if (me->query_temp("target")) 
		ob = find_player(me->query_temp("target"));
	else destruct(me);
	
	if (!ob) {
		//command("say 莫名其妙，我去也。");	
		//write(me), "\n"+me->query("name")+"大喊一声：扯呼！转身几个起落就不见了。\n");	
		destruct(me);
		return;
	}
	if (ob!=lastob) 
	{
      command("say 你我无怨无仇，何苦追杀于我。");
	  
	  return;//不死
     }
	
	::die();
}


string ask_diyun()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR3+"askhua"))
	{
		command("say 我与你非亲非故，真是莫名其妙，来此作甚？\n");
		return "哼！\n";
	}
	command("say 你说的是那个秃头小瘪三啊，我正想找他呢，听曾听我四弟说过，你去问问他！\n");
	command("say 我曾听说这小子把我心爱的弟子打了，还抢了我们四弟的女儿，真是可恶！\n");
	me->set_temp(QUESTDIR3+"askliu",1);
	return "那小子看起来贼腻兮兮的，也不是什么好鸟！\n";
}
