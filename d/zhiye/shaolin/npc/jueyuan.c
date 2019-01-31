// jueyuan.c 觉远大师
// cre by sohu@xojh
#include <ansi.h>

inherit NPC;
void create()
{
	set_name("觉远和尚", ({
		"jueyuan dashi",
		"jueyuan",
		"dashi",
	}));
	set("long",
		"看这僧人时，只见他长身玉立，恂恂全儒雅，若非光头僧服，宛然便是位书生相公。\n"
		+"和他相比，黄药师多了三分落拓放诞的山林逸气， 朱子柳又多了三分金马玉堂的朝廷贵气。\n"
		+"这觉远五十岁左右的年纪， 当真是腹有诗书气自华，俨然、宏然，恢恢广广，昭昭荡荡，\n"
		+"便如是一位饱学宿儒、经术名家。\n"
	);
	set("title",HIC"藏经阁监管"NOR);

	set("gender", "男性");
	set("attitude", "peaceful");
	set("class", "bonze");

	set("chat_msg",({

	//(: this_object(), "my_move" :),
	"觉远和尚喃喃自语：这几天也真怪，藏经阁竟然经常有人来偷东西，连书都偷！\n",

	}));

	set("age", 55);
	set("shen_type", 1);
	set("str", 30);
	set("int", 20);
	set("con", 30);
	set("dex", 20);
	set("max_qi", 63000);
	set("max_jing", 8150);
	set("neili", 50100);
	set("max_neili", 50100);
	set("combat_exp", 15000000);
	set("score", 200);
	set("chat_chance", 20);

	set_skill("force", 550);
	set_skill("dodge", 550);
	set_skill("cuff", 550);
	set_skill("parry", 550);
	set_skill("jiuyang-shengong",550);
	set_skill("shaolin-shenfa",550);
	set_skill("luohan-quan",550);
	map_skill("force","jiuyang-shengong");
	map_skill("cuff","luohan-quan");
	map_skill("parry","luohan-quan");
	map_skill("dodge","huashan-shenfa");
	prepare_skill("cuff","luohan-quan");
	setup();

}

