// lutianshu.c

inherit NPC;
#include <ansi.h>
#include "lhlsnpc.h"
string ask_diyun();
#include "/d/suzhou/npc/lchj.h"
void create()
{
       set_name("陆天抒", ({ "lu tianshu", "lu" }));
       set("long", 
       "他就是南四奇“落花流水”中的老大。\n"
       "南四奇横行江南，行侠仗义，陆天抒更是仗义疏财，大有侠名。\n");
       set("gender", "男性");
       set("nickname", HIG"仁义陆大刀"NOR);
       set("age", 51);
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

       set_skill("force", 480);
       set_skill("yijin-jing", 480);
       set_skill("dodge", 480);
       set_skill("shaolin-shenfa", 480);
       set_skill("taizu-quan", 480);
       set_skill("parry", 480);
       set_skill("blade", 480);
       set_skill("xiuluo-dao", 480);
       set_skill("literate", 220);

       map_skill("force", "yijin-jing");
       map_skill("dodge", "shaolin-shenfa");
	   map_skill("cuff", "taizu-quan");

       map_skill("parry", "xiuluo-dao");
       map_skill("blade", "xiuluo-dao");
	   prepare_skill("cuff","taizu-quan");

       set("chat_chance", 20);
       set("chat_msg", ({
              "陆天抒提起中气，纵声长啸：“落～～花流水……”啸声雄浑，远远群山回应不绝。\n",
	   }));
	   set("chat_chance_combat", 60);
		set("inquiry", ([
		"狄云" : (: ask_diyun :),
		"name": "你问这干嘛，我就是仁义大刀陆天抒，你有什么事情？",
		//"落花流水" : (: ask_lhls :),
		//"": (: ask_qiyu :),
	])); 
		set("chat_chance_combat", 70);

      set("chat_msg_combat", ({
			(: perform_action, "blade.xiuluo" :),
			(: exert_function, "jingang" :),
			(: perform_action, "cuff.hengsao" :),

		}));
       setup();
       carry_object("/clone/weapon/gangdao")->wield();
}

string ask_diyun()
{
	object me;
	me=this_player();
	if (me->query_temp(QUESTDIR3+"jingjieok")||me->query(QUESTDIR3+"jingjieok"))
	{	
		command("say 你说的是那个秃头小瘪三啊，我正想找他呢，听曾听我二弟说过，你去问问他！\n");
		command("say 我曾听说这小子把我心爱的弟子打了，还抢了我们四弟的女儿，真是可恶！\n");
		me->set_temp(QUESTDIR3+"asklu",1);
		return "那小子看起来贼腻兮兮的，也不是什么好鸟！\n";

	}
	command("say 莫名其妙，来此作甚？\n");
	return "哼！\n";
}		
