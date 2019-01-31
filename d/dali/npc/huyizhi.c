//huyizhi.c
//百胜刀王 胡逸之
// by sohu
//inherit F_MASTER;
inherit NPC;
//inherit FIGHTER;
#include <ansi.h>

void create()
{
	set_name("胡逸之", ({ "hu yizhi", "hu", "yizhi" }) );
	set("gender", "男性" );
	set("title", HIC"百胜刀王"NOR);
	//set("nick","美刀王");
	set("age", 26);
	set("long", 
	    "一代刀王胡逸之，长得身材修长，一表人才，刀法冠绝武林。\n"
	    "此人风流英俊，当年说是武林中第一美男子，江湖人称“美刀王”\n"
		"不过此时居然扮作了个傻里傻气的乡巴佬！\n"NOR);
	set("str", 25+random(30));
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", 1);
	set("feidao",1);
	set("unique", 1); //千万别出问题阿，这个设定
  
	set_skill("force", 450);
    set("no_get", 1);
    set("no_bark", 1);
	set_skill("dodge", 450);
	set_skill("parry", 450);
	set_skill("blade", 530);
	set_skill("cuff",450); 
	set_skill("taxue-wuhen",450);
	set_skill("zhentian-quan",450);
	set_skill("lengquan-shengong",450);
	set_skill("hujia-daofa",500);
	map_skill("force","lengquan-shengong");
	map_skill("cuff","zhentian-quan");
	map_skill("dodge","taxue-wuhen");
	map_skill("blade","hujia-daofa");
	map_skill("parry","hujia-daofa");
	set("double_attack",1);
    prepare_skill("cuff", "zhentian-quan");
	set("combat_exp", 12000000);
	set("max_qi", 30000);
	set("max_jing", 30000);
	set("max_neili", 35000);
	set("eff_jingli",30000);
	set("qi",30000);
	set("jing",30000);
	set("jingli",30000);
	set("neili", 35000);
    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
       (: exert_function, "lengquan" :),
       (: perform_action, "blade.feidao" :),
		   (: perform_action, "blade.yunlong" :),
		   (: perform_action, "blade.roudao" :),
		   (: perform_action, "blade.fanshen" :),
       (: perform_action, "blade.luandao" :)
     }));
    set("inquiry", ([
 //   "胡一刀" : (: ask_huyidao :),
   // "hu yidao" : (: ask_huyidao :),
	]));
	setup();
	set("chat_chance", 1);
	set("chat_msg", ({
		"唉，哪怕我看一眼也心满意足。\n",
	}));
	carry_object("/clone/weapon/blade/blade.c")->wield();
	carry_object("/clone/weapon/blade/blade.c");
	carry_object("/clone/armor/baihu-qiu.c")->wear();
} 
