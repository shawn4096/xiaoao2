// NPC: lu.c 鲁有脚
// Lklv 2001.9.28 update
// By Spiderii@ty srf,tjf不可以ask job跑tj.
#include <ansi.h>
inherit NPC;
int say_huang1();
int say_huang2();
//#include "gb_lujob.h"
void create()
{
	set_name("鲁有脚", ({"lu youjiao", "lu", "youjiao"}));
	set("title", HIW"丐帮九袋长老"NOR);
	set("nickname", "掌棒龙头");
	set("gender", "男性");
	set("age", 45);
	set("long", "他在丐帮中有仁有义，行事光明磊落，深得洪七公的器重。\n");

        set("attitude", "peaceful");
        set("str", 25);
        set("int", 12);
        set("con", 25);
        set("dex", 20);
        set("unique", 1);
        set("no_bark",1);
        set("job_npc",1);
        set("no_get","鲁有脚对你来说太重了。\n");

        set("qi", 13500);
        set("eff_jingli", 8000);
        set("max_qi", 13500);
        set("jing", 8000);
        set("max_jing", 8000);
        set("eff_jing", 8000);
        set("neili", 24200);
        set("max_neili", 24200);
        set("jiali", 200);

        set("combat_exp", 9400000);
        set("score", 20000);

	    set_skill("force", 450); // 基本内功
        set_skill("huntian-qigong", 450); // 混天气功
        set_skill("strike",450); // 基本拳脚
        set_skill("xianglong-zhang", 450); // 降龙十八掌
        set_skill("dodge", 450); // 基本躲闪
        set_skill("xiaoyaoyou", 450); // 逍遥游
        set_skill("parry", 450); // 基本招架
        set_skill("literate", 100);
        set_skill("stick", 450); // 基本棍杖
        set_skill("begging", 200);

        map_skill("force", "huntian-qigong");
        map_skill("strike", "xianglong-zhang");
        map_skill("parry","xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");

        prepare_skill("strike", "xianglong-zhang");

    	set("chat_msg_combat", ({
        	(: perform_action, "strike.xiao" :),
        	(: perform_action, "strike.feilong" :),
        	(: exert_function, "huntian" :),
        }));
        create_family("丐帮", 18, "九袋长老");
        set("inquiry", ([
               // "棒法图解" : (:ask_me:),
               // "报效国家" : (:ask_job:),
               // "功劳": (: ask_num :),
                //"补偿": (: ask_gift :),

                "洪七公": "我们平常都叫他“帮主”，亲近一点的叫他“七公”。\n",
        ]));
        set("count",1);
        setup();
        carry_object(ARMOR_D("bainayi"))->wear();
        carry_object(ARMOR_D("caoxie"))->wear();

       // carry_object("d/gb/obj/gb_budai9")->wear();
}

int say_huang1()
{
	command("say 黄帮主，你看我这性子就是比较着急，一时之间也学不会。\n");
	command("say 容我慢慢练习，看能否学会！\n");
	return 1;

}
int say_huang2()
{
	command("blush ");
	command("sigh ");
	command("say 你的意思我明白了，这棒诀我先记下来，然后再慢慢琢磨。\n ");
	command("say 我再练会。\n");
	return 1;
}