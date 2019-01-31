// shuidai.c

inherit NPC;
#include <ansi.h>;
#include "lhlsnpc.h"
#include "/d/suzhou/npc/lchj.h"
string ask_diyun();


void create()
{
       set_name("水岱", ({ "shui dai", "shui" }));
       set("long", 
       "他就是南四奇“落花流水”中的老四。\n"
       "南四奇横行江南，行侠仗义，水岱虽富甲东南，现在却深有忧色。\n");
       set("gender", "男性");
       set("nickname", HIC"冷月剑"NOR);
       set("age", 39);
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
       set("jiali", 180);
       set("combat_exp", 9800000);
       set("shen_type", 1);
       set("huashan", "剑宗");

       set_skill("force", 480);
       set_skill("huashan-qigong", 480);
       set_skill("dodge", 480);
       set_skill("huashan-shenfa", 480);
       set_skill("strike", 480);
       set_skill("hunyuan-zhang", 480);
       set_skill("parry", 480);
       set_skill("sword", 480);
       set_skill("huashan-jianfa", 480);
       set_skill("literate", 180);

       map_skill("force", "huashan-qigong");
       map_skill("dodge", "huashan-shenfa");
       map_skill("strike", "hunyuan-zhang");
       map_skill("parry", "huashan-jianfa");
       map_skill("sword", "huashan-jianfa");
       prepare_skill("strike", "hunyuan-zhang");
   
	   set("chat_chance", 20);
		set("inquiry", ([
		"狄云" : (: ask_diyun :),
		"name": "你问这干嘛，我就是冷月剑水岱，你有什么事情？",
		//"落花流水" : (: ask_lhls :),
		//"": (: ask_qiyu :),
		])); 

       set("chat_msg", ({
              "水岱急提中气，啸声如虹：“落花流水～～……”声势劲急，远远传开。\n",
	}));
	set("chat_chance_combat", 100);

        set("chat_msg_combat", ({
			(: perform_action, "sword.jianzhang" :),
			(: perform_action, "sword.fengyi" :),
			(: perform_action, "sword.lianhuan" :),
			(: perform_action, "sword.shijiushi" :),
			(: perform_action, "sword.luomu" :),
			(: perform_action, "sword.kuaijian" :),
			(: exert_function, "juli" :),
			(: exert_function, "yujianshi" :),

		}));
       setup();
       carry_object("/clone/weapon/changjian")->wield();
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
	if (!me->query_temp(QUESTDIR3+"askliu"))
	{

		command("say 我与你非亲非故，真是莫名其妙，来此作甚？\n");
		return "哼！\n";
	}
	command("say 既然是我三哥让你来找我的，我就跟你说下这小子!\n");

	command("say 你说的是那个秃头小瘪三啊，我正想找他呢，听曾听我四弟说过，你去问问他！\n");
	command("say 我曾听说这小子把我心爱的弟子打了，还抢了我的女儿水笙，真是可恶！\n");
	command("say 我抓住他一定将他挫骨扬灰，气死我也！！\n");
	command("say 我女儿和他表哥曾经在一起，你问问他也许知道我女儿的下落！\n");
	
	me->set_temp(QUESTDIR3+"askshui",1);
	return "你若是发现那淫贼或者我女儿一定要通知我，在下不胜感激！\n";
}