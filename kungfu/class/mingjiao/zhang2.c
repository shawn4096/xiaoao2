// zhang.c 张中
// Modify By River@sj 99.06

#include <ansi.h>
inherit NPC;
inherit F_MASTER;



void create()
{
	set_name("张中", ({ "zhang zhong", "zhang", "zhong" }) );
	set("nickname","铁冠道人");
	set("title", "明教五散人");
	set("gender", "男性");
	set("age",51);
	set("long", "他就是明教五散人之一，人称铁冠道人的张中。\n");
	set("rank_info/respect","道长");
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	set("shen_type",0);
	set("combat_exp", 5600000);
	set("unique", 1);
	set("no_get","张中对你来说太重了。\n");

	set_skill("sword",380);
	set_skill("literate",380);
	set_skill("force",380);
	set_skill("liehuo-jian",385);
	set_skill("dodge",380);
	set_skill("parry", 380);
	set_skill("cuff",380);
	set_skill("taizu-quan",385);
	set_skill("piaoyi-shenfa",385);
	set_skill("shenghuo-shengong",385);
	map_skill("cuff","taizu-quan");
	map_skill("force","shenghuo-shengong");
	map_skill("dodge","piaoyi-shenfa");
	map_skill("sword","liehuo-jian");
	map_skill("parry","liehuo-jian");
	prepare_skill("cuff", "taizu-quan");
	create_family("明教", 36, "散人");
	set("max_qi",1500);
	set("max_jing",1200);
	set("jiali",50);
	set("eff_jingli",1100);
/*
	set("inquiry", ([
		"宝鼎"  : (: ask_gold :),
		"太极拳经"  : (: ask_me :),
		"秘籍"  : (: ask_me :),
		"画印"  : (: ask_xunluo :),
	]));
*/
	set("xl", 2);
	set("xl2", "zhang-zhong");
	setup();
	carry_object("/d/mingjiao/obj/yel-cloth")->wear();
	carry_object(BINGQI_D("changjian"))->wield();
}

