// sun.c 孙婆婆
// By River@SJ 2001.02.28

#include <ansi.h>
inherit NPC;
string ask_job();
int ask_hexiu();
void create()
{
	set_name("孙婆婆", ({ "sun popo", "sun", "popo" }));
	set("long","这位老妇长着一张生满鸡皮疙瘩的丑脸，正瞪眼瞧着你。\n");
	set("gender", "女性");
	set("age", 60);
	set("attitude", "friendly");
	set("no_bark",1);
	set("per", 10);
	set("str", 30);
	set("dex", 30);
	set("con", 25);
	set("int", 40);
	set("shen", 1000);

	set("combat_exp", 6700000);
	set("max_qi", 13500);
	set("max_jing", 3600);
	set("eff_jingli",2000);
	set("max_neili", 15000);
	set("neili", 5000);
	set("jiali",30);
	set("unique", 1);

	set_skill("parry", 400);
	set_skill("force", 400);
	set_skill("dodge", 400);
	set_skill("sword", 400);
	set_skill("throwing", 400);
	set_skill("whip", 400);
	set_skill("meinu-quanfa", 400);
	set_skill("cuff", 400);
	set_skill("yunu-shenfa", 400);
	set_skill("yinsuo-jinling", 400);
	set_skill("yunu-jianfa", 400);
	set_skill("yunu-xinjing", 400);
	set_skill("literate", 140);

	map_skill("force", "yunu-xinjing");
	map_skill("dodge", "yunu-shenfa");
	map_skill("cuff", "meinu-quanfa");
	map_skill("sword", "yunu-jianfa");
	map_skill("whip", "yinsuo-jinling");
	map_skill("parry","yinsuo-jinling");
	prepare_skill("cuff", "meinu-quanfa");

	set("inquiry", ([
		//"玉蜂" : (: ask_job :),
		"合修" : (: ask_hexiu :),
	]));
      
	setup();
	carry_object("/d/gumu/obj/buxue1")->wear();
	carry_object(ARMOR_D("cloth"))->wear(); 
}

int ask_hexiu()
{
	object me=this_player();
	if (me->query("family/family_name")!="古墓派")
	{
		command("hehe");
		command("say 你跟我古墓无缘无故，怎么和修？");
		command("say 你...");
		return 1;
	}
	if (me->query_skill("yunu-xinjing",1)<100)
	{
		command("say 你的玉女心经修为不足100，赶紧努力去吧？");
		command("say 你...");
		return 1;
	}
	if (me->query("quest/gumu/ynxj/pass"))
	{
		command("say 你已经解开了玉女心经第一段武功，无需合修了！\n");
		command("say 好好努力，别让老婆子我失望！\n");
		return 1;
	}
	if (me->query("gender")=="男性")
	{
		command("say 合修？你一个臭男人和我合修，滚！");
		command("say 你真变态和无耻...");
		return 1;
	}
	
		command("hehe");
		command("say 既然你没伴，正好老身我也嫌着无聊，就陪你玩玩吧.");
		command("say 你先到果园那一带的红花丛中，哪儿比较开阔。我随后就到。\n");
		command("hehe");
		me->set_temp("ynxj/hexiusun",1);
		return 1;
}