// huatiegan.c

inherit NPC;
#include <ansi.h>
#include "lhlsnpc.h"
#include "/d/suzhou/npc/lchj.h"
string ask_diyun();

void create()
{
       set_name("花铁干", ({ "hua tiegan", "hua" }));
       set("long", 
       "他就是南四奇“落花流水”中的老二。\n"
       "南四奇横行江南，行侠仗义，花铁干一手中平枪，号称中平无敌。可是他的为人却不咋的。\n");
       set("gender", "男性");
       set("nickname", HIR"中平无敌"NOR);
       set("age", 45);
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
       set("combat_exp", 9700000);
       set("shen_type", 0);

       set_skill("force", 450);
       set_skill("huntian-qigong", 450);
       set_skill("dodge", 450);
       set_skill("xiaoyaoyou", 450);
       set_skill("hand", 450);
       set_skill("suohou-shou", 100);
       set_skill("parry", 450);
       set_skill("spear", 450);
       set_skill("zhong-qiang", 450);
       set_skill("literate", 140);
      
       map_skill("force", "huntian-qigong");
       map_skill("dodge", "xiaoyaoyou");
       map_skill("hand", "suohou-shou");
       map_skill("spear", "zhong-qiang");
       map_skill("parry", "zhong-qiang");
       prepare_skill("hand", "suohou-shou");

       set("chat_chance", 20);
       set("chat_msg", ({
              "花铁干缓缓提起中气，啸声如潮涌出：“落花～～流水……”震人耳馈。\n",
       }));
		set("inquiry", ([
		"狄云" : (: ask_diyun :),
		"name": "你问这干嘛，我就是中平枪花铁干，你有什么事情？",
		//"落花流水" : (: ask_lhls :),
		//"": (: ask_qiyu :),
		])); 

	   set("chat_chance_combat", 70);
       set("chat_msg_combat", ({
			(: perform_action, "spear.huimaqiang" :),
			(: perform_action, "spear.fanzhuan" :),
			(: exert_function, "huntian" :),
			(: perform_action, "hand.suohou" :),
			(: perform_action, "hand.qinna" :),

		}));
       setup();
       carry_object("/clone/weapon/changqiang")->wield();
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
	if (!me->query_temp(QUESTDIR3+"asklu"))
	{
		command("say 我与你非亲非故，真是莫名其妙，来此作甚？\n");
		return "哼！\n";
	}
	command("say 你说的是那个秃头小瘪三啊，我正想找他呢，听曾听我三弟说过，你去问问他！\n");
	command("say 我曾听说这小子把我心爱的弟子打了，还抢了我们四弟的女儿，真是可恶！\n");
	me->set_temp(QUESTDIR3+"askhua",1);
	return "那小子看起来贼腻兮兮的，也不是什么好鸟！\n";
}
