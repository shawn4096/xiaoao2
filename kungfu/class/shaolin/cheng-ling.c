// Npc: /kungfu/class/shaolin/cheng-ling.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

int ask_me();

void create()
{
    set_name("澄灵", ({
		"chengling luohan",
		"chengling",
		"riyue",
		"luohan",
	}));
	set("long",
		"他是一位须发花白的老僧，身穿一袭金边黑布袈裟。他身材瘦高，\n"
		"太阳穴高高鼓起，似乎身怀绝世武功。\n"
	);


	set("nickname", "日月罗汉");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 60);
	set("shen", 5000);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	set("max_qi", 2500);
	set("max_jing", 1000);
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 100);
	set("combat_exp", 600000);
    set("unique", 1);

	set_skill("force", 120);
	set_skill("yijin-jing", 120);
	set_skill("dodge", 120);
	set_skill("shaolin-shenfa", 120);
	set_skill("leg", 120);
	set_skill("shaolin-tantui", 120);
	set_skill("parry", 120);
	set_skill("buddhism", 120);
	set_skill("literate", 120);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("leg", "shaolin-tantui");
	map_skill("parry", "shaolin-tantui");
 
    prepare_skill("leg", "shaolin-tantui");
    set("inquiry", ([
                "铁帚腿功"       : (: ask_me :),
           //     "罗汉大阵"         : (: ask_me :)
        ]));

	create_family("少林派", 37, "弟子");

	setup();

        
        carry_object("/d/shaolin/obj/cheng-cloth")->wear();

}


#include "/kungfu/class/shaolin/cheng.h"

int ask_me()
{
	object me=this_player();
	if (!me->query_temp("rysxt/askstart"))
	{
		command("say 此地乃少林般若堂专研腿法所在，你鬼鬼祟祟来此作甚？\n");
		return 1;
	}
	command("say 好，既然有师叔所命，你就在此地好好参禅修行吧。(canchan xx)！\n");
	me->set_temp("rysxt/askchengling",1);
	return 1;

}