// Npc: /kungfu/class/shaolin/cheng-xin2.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

string ask_ranmu();

void create()
{
	set_name("澄信", ({
		"chengxin luohan",
		"chengxin",
		"zhuangyan",
		"luohan",
	}));
	set("long",
		"他是一位须发花白的老僧，身穿一袭金边黑布袈裟。他身材瘦高，\n"
		"太阳穴高高鼓起，似乎身怀绝世武功。\n"
	);

	set("nickname", "庄严罗汉");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 60);
	set("shen", 5000);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	set("max_qi", 3500);
	set("max_jing", 2000);
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 50);
	set("combat_exp", 150000);
    set("unique", 1);

	set_skill("force", 120);
	set_skill("yijin-jing", 120);
	set_skill("dodge", 120);
	set_skill("shaolin-shenfa", 120);
	set_skill("blade", 120);
	set_skill("xiuluo-dao", 120);
	set_skill("parry", 120);
        set_skill("cuff", 120);
        set_skill("jingang-quan", 120);
	set_skill("buddhism", 150);
	set_skill("literate", 140);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("blade", "xiuluo-dao");
	map_skill("parry", "xiuluo-dao");
    map_skill("cuff", "jingang-quan");
    prepare_skill("cuff", "jingang-quan");

	create_family("少林派", 37, "弟子");
    set("inquiry", ([			
			    "燃木绝技"       : (: ask_ranmu :),
    ]));


	setup();

        carry_object("/d/shaolin/obj/jiedao")->wield();
        carry_object("/d/shaolin/obj/cheng-cloth")->wear();
}


#include "/kungfu/class/shaolin/cheng.h"

string ask_ranmu()
{
	object muchai;
	object me=this_player();
	if (!me->query_temp("rmdf/askkuranmu"))
	{
		command("say 这里是般若堂六部刀法精要所在地，你鬼鬼祟祟来此作甚？\n");
		return "没有玄苦大师的指示书都别想偷学！\n";
	}
	if (!present("mu chai",environment(me)))
	{
		muchai=new("d/shaolin/obj/muchai");
		muchai->move("d/shaolin/banruo6");
		command("say 好，既然是玄苦大师派你来学习的，我就帮你一个忙，喏！哪儿是一堆木柴，你自己去练习吧！\n");

	}
	command("say 玄苦大师曾经说过，要练好这燃木刀法，须得以木刀去劈这木柴！\n");
	command("say 每次劈出均需要以极为快速招式劈出，直到你劈出九九八十一刀为止！\n");
	command("say 这才是刚刚开始！\n");
	command("say 你若能一次将这木刀和空气摩擦引燃这木刀方为功成！\n");
	command("say 这也是燃木刀法的由来！\n");
	command("say 少林百年以来只有玄苦大师修习成功，可见这门功法有多么艰难！\n");
	command("say 你若想学就去试试，看能否达到这个效果，若练不出来我看就放弃吧！\n");
	me->set_temp("rmdf/askchengxin",1);
	return "燃木刀重要的是靠功力深厚！\n";

}