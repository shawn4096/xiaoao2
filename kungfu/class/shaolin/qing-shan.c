// Npc: /kungfu/class/shaolin/qing-shan.c
// Date: YZC 96/01/19

inherit NPC;
string ask_me_1();
string ask_me_2();

void create()
{
	set_name("清善比丘", ({
		"qingshan biqiu",
		"qingshan",
		"biqiu",
	}));
	set("long",
		"他是一位体格强健的壮年僧人，他身得虎背熊腰，全身似乎蕴含\n"
		"着无穷劲力。他身穿一袭白布黑边袈裟，似乎身怀武艺。\n"
	);


	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 30);
	set("shen_type", 1);
	set("str", 21);
	set("int", 18);
	set("con", 20);
	set("dex", 25);
	set("max_qi", 350);
	set("max_jing", 200);
	set("neili", 350);
	set("max_neili", 350);
	set("jiali", 30);
	set("combat_exp", 50000);
	set("score", 100);

	set_skill("force", 60);
	set_skill("yijin-jing", 60);
	set_skill("dodge", 60);
	set_skill("shaolin-shenfa", 60);
	set_skill("strike", 65);
	set_skill("weituo-zhang", 65);
	set_skill("parry", 60);
	set_skill("buddhism", 60);
	set_skill("literate", 60);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("strike", "weituo-zhang");
	map_skill("parry", "weituo-zhang");

	prepare_skill("strike", "weituo-zhang");

	create_family("少林派", 40, "弟子");

        set("inquiry", ([
		"手谕"       : (: ask_me_1 :),
		"七十二绝艺" : (: ask_me_1 :),
		"达摩令" :     (: ask_me_2 :)
	]));

	setup();

        carry_object("/d/shaolin/obj/qing-cloth")->wear();
}

string ask_me_1()
{
	mapping fam, skl; 
	object ob;
	string *sname;
	int i;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "少林派")
		return RANK_D->query_respect(this_player()) + 
		"与本派素无来往，不知此话从何谈起？";

        if ( (int)this_player()->query("guilty") > 0 )
		return RANK_D->query_respect(this_player()) + 
		"你累犯数戒，身带重罪，我如何能给你这手谕！";

        if ( (int)this_player()->query_int() < 30 )
		return RANK_D->query_respect(this_player()) + 
		"资质不够，不能进入藏经楼。";

	skl = this_player()->query_skills();
	sname  = sort_array( keys(skl), (: strcmp :) );

	for(i=0; i<sizeof(skl); i++) {
		if (skl[sname[i]] < 50) 
		return RANK_D->query_respect(this_player()) + 
		"功力不够，不够资格领取手谕。";
	}

        if ( (int)this_player()->query_skill("buddhism",1) < 80 )
		return RANK_D->query_respect(this_player()) + 
		"想学习上乘武功，先要以高深佛法化解它们的戾气。";

	ob = new("/d/shaolin/obj/allow-letter");
	ob->move(this_player());
	message_vision("$N获得一封手谕。\n",this_player());

	return "好吧，凭这封手谕，你可自由进入藏经阁二楼研习上乘武功。";

}

string ask_me_2()
{
	mapping fam, skl; 
	object ob;
	string *sname;
	int i;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "少林派")
		return RANK_D->query_respect(this_player()) + 
		"与本派素无来往，不知此话从何谈起？";

	skl = this_player()->query_skills();
	sname  = sort_array( keys(skl), (: strcmp :) );

	for(i=0; i<sizeof(skl); i++) {
		if (skl[sname[i]] < 30) 
		return RANK_D->query_respect(this_player()) + 
		"功力不够，不能领取达摩令。";
	}

	ob = new("d/shaolin/obj/damo-ling");
	ob->move(this_player());
	message_vision("$N获得一面达摩令。\n",this_player());

	return "好吧，凭这面达摩令，你可自由向你的师尊挑战。";

}



#include "/kungfu/class/shaolin/qing.h"

