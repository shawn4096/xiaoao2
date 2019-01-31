// NPC: /d/huashan/npc/yuebuqun.c
// Date: Look 99/03/25
// Modify by Looklove 2000,12,15
// By Spdierii@ty 重要npc.杀不死
// by lsxk@hsbbs  统一奖励算法 2007/1/10

inherit NPC;


#include <ansi.h>

void create()
{
	set_name("蒙面人",({"yue buqun", "yue", "buqun" }));
	//set("title","蒙面人");
	//set("nickname",HIG"君子剑"NOR);
	set("long", "一看就是一名武林高手。\n");
	set("age", 40);
	set("attitude", "friendly");
	set("no_bark",1);
	set("shen_type", 1);
	set("job_npc", 1);
	set("no_get", 1);

	set("per", 25);
	set("pur", 10);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);

	set("max_qi",23800);
	set("qi", 23800);
	set("max_jing", 6400);
	set("jing",6400);
	set("eff_jingli", 5700);
	set("jingli", 5700);
	set("max_neili", 25500);
	set("neili", 25500);
	set("jiali", 200);
	set("combat_exp", 9800000);
	set("score", 30000);
	set("chat_chance_combat",80);
	set("chat_msg_combat", ({
		(: perform_action, "sword.jianzhang" :),
		//(: perform_action, "sword.kuaijian" :),
		(: perform_action, "sword.fengyi" :),
		(: exert_function, "zixia" :),
		(: exert_function, "jianyi" :),
		(: exert_function, "jianqi" :),
		//(: perform_action, "sword.kuaijian" :),
		(: perform_action, "sword.lianhuan" :),
		(: perform_action, "sword.cangsong" :),
		(: perform_action, "sword.luomu" :),
		
	}));
	set("quest/hsjf/cangsong","pass");
	set_skill("poyu-quan", 450);
	set_skill("cuff", 450);
	set_skill("sword",  450);
	set_skill("dodge",  450);
	set_skill("force",  450);
	set_skill("parry",  450);
	set_skill("literate",400);
	set_skill("zixia-gong", 450);
    set_skill("huashan-qigong", 450);
	set_skill("huashan-jianfa",  450);
	set_skill("huashan-shenfa",  450);
	set_skill("zhengqi-jue", 200);
    set_skill("hunyuan-zhang", 450);
    set_skill("strike", 450);
    map_skill("strike", "hunyuan-zhang");
	map_skill("dodge", "huashan-shenfa");
	map_skill("force","zixia-gong");
	map_skill("sword","huashan-jianfa");
	map_skill("parry","huashan-jianfa");
	map_skill("cuff","poyu-quan");
	prepare_skill("cuff","poyu-quan");
	//create_family("华山派",13,"掌门");
/*
	set("inquiry", ([
		"紫霞秘籍"	: (: ask_zixia :),
		"失败"		: (: ask_fail :),
		"fail"		: (: ask_fail :),
		"惩恶扬善"	: (: ask_me1 :),
		"job"		: (: ask_me1 :),
		"复命"		: (: ask_me2 :),
		"完成"		: (: ask_me2 :),
		"finish"	: (: ask_me2 :),
		"正气诀"	: (: ask_zhengqi :),
		"有凤来仪"	: (: ask_fengyi :),
        "剑气之争"      : (: ask_qizong :),
        "华山剑宗"      : (: ask_jianzong :),
	]));
*/
	setup();
	carry_object(BINGQI_D("sword"))->wield();
	carry_object(ARMOR_D("cloth"))->wear();
}
