// /d/thd/npc/huangrong.c
// Modified by action@sj
//射雕英雄传第28回

#include <ansi.h>
inherit NPC;
int say_lu1();
int say_lu2();

void create()
{
	set_name("黄蓉", ({ "huang rong", "huang", "rong" }));
	set("long",
			"她方当韶龄，不过十五六岁年纪，肌肤胜雪，娇美无比，容色绝丽，不可逼视。\n"
			"她长发披肩，全身白衣，头发上束了一条金带，灿然生光。一身装束犹如仙女一般。\n");
	set("gender", "女性");
	set("rank_info/rude", "小妖女");
	set("title","丐帮帮主");
	set("age",38);
	set("attitude","peaceful");
	set("str", 16);
	set("dex", 26);
	set("con", 28);
	set("int", 50);
	set("per", 50);
	set("shen_type", 0);

	set("tu", 1);
	set("shu", 1);
	set("shouhuan",1);

	set("jiali",200);
	set_skill("force", 500);
	set_skill("huntian-qigong", 500);
	set_skill("bihai-chaosheng", 500);
	set_skill("dodge", 500);
	set_skill("xiaoyaoyou", 500);
	set_skill("parry", 500);
	set_skill("strike", 500);
	set_skill("luoying-zhang", 500);

	set_skill("hand", 500);
	set_skill("lanhua-shou", 500);
	set_skill("finger", 500);
	set_skill("tanzhi-shentong", 500);
	set_skill("sword", 500);
	set_skill("yuxiao-jian", 500);
	set_skill("literate",500);
	set_skill("qimen-bagua", 500);
	set_skill("bangjue",200);
	set_skill("dagou-bang",500);
	set_skill("stick",500);

	map_skill("force", "huntian-qigong");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("strike", "luoying-zhang");
	map_skill("hand", "lanhua-shou");
	map_skill("finger", "tanzhi-shentong");
	map_skill("parry", "dagou-bang");
	map_skill("sword", "yuxiao-jian");
	map_skill("stick", "dagou-bang");
	prepare_skill("hand", "lanhua-shou");

	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: perform_action, "stick.chuo" :),
		(: perform_action, "stick.ban" :),
		(: perform_action, "stick.yin" :),
		(: perform_action, "stick.chuo" :),
		(: perform_action, "stick.chan" :),
		(: perform_action, "stick.wugou" :),
		(: exert_function, "huntian" :),
	}));

	set("combat_exp", 12500000);
	set("max_qi", 35000);
	set("max_jing", 14000);
	set("neili", 38500);
	set("max_jingli", 8500);
	set("eff_jingli", 8500);
	set("max_neili", 38500);

	set("inquiry", ([
	
		"郭靖" : "靖哥哥虽然有点傻乎乎的，对我却是真心的。",	
	//	"周伯通" : (: ask_jiuyin :),
		"八卦阵" : "是爹爹按八卦的卦象排的，不同的方向表示爻的变化与否，每三爻为一卦，八卦按顺序都走对就过阵了。",
	/*	
		"洪七公" : (: ask_h7g :),
		"降龙十八掌" : (: ask_xlz :),
		"靖哥哥" : (: ask_guojing :),
		"神龙摆尾" : (: ask_slbw :),
		"手环" : (: ask_shouhuan :),
		"夫君" : (: ask_husband :),
		
// here add thd-job "ask huang" by Numa 19990911
		"师母": (: ask_job_s :),
		"守墓": (: ask_job :),
// ask job times by Numa 19991005
		"功劳": (: ask_job_time :),
// add for taohua quest
		"梅超风": (: ask_quest :),
		"陈玄风": (: ask_quest :),
// for hetu/luoshu
		"奇门八卦": (: ask_book :),
		"裘千丈": (: ask_qqzhang :),
		"裘千尺": (: ask_qqchi :),
//		"裘千仞": (: ask_qqren :),*/
	]) );

//here set do job's number
	set("thd/havejob",1);

	setup();

	carry_object("/d/city/obj/necklace.c")->wear();
	carry_object("/d/city/obj/goldring.c")->wear();
	carry_object("/clone/weapon/zhubang")->wield();
}

int say_lu1()
{
	command("say 鲁长老，这丐帮帮主之位我是不感兴趣的。\n");
	command("say 平时也是你在主持工作，我想今近日就把这打狗棒棒诀传授于你。\n");
	command("sigh");
	command("say 我今日身子不是太好，你要勤加练习，好好把这丐帮绝技习得。也好了却我的一桩心事。\n");
	command("consider");
}

int say_lu2()
{
	command("say 这丐帮打狗棒由招式和口诀组合而成，只懂其一，都不能发挥出威力。");
	command("say 前几日我已经将招式传授于你，你温习的也差不多了。");
	command("say 这打狗棒共有绊、劈、缠、戳、挑、引、封、转八诀。闻名天下乃丐帮镇帮绝技\n");
	command("say 以轻、灵、奇、巧诸称，舞将起来是四处只见棒影不见人影。武学中有言道：“四两拨千斤”");
	command("say 实乃打狗棒法的精妙招数精髓体现。前几日我已经将招式传授于你，你温习的也差不多了。 ");
	command("say 今天我就将这打狗棒口诀传授于你，你要听好了。\n");
}
