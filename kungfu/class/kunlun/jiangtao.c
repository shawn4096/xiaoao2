// jiangtao.c (kunlun)
// 男弟子第一个师傅，拳法
inherit NPC;
inherit F_MASTER;
#include <ansi.h>

void create()
{
	set_name("蒋涛", ({ "jiang tao", "jiang"}));
	set("long",
		"他穿青色长袍，背上斜插长剑，二十八九岁年纪。\n"
		"脸罩寒霜，一副要惹事生非的模样。\n");
	set("gender", "男性");
	set("age", 20);
	set("attitude", "heroism");
	set("shen_type", 1);
	set("str", 26);
	set("int", 24);
	set("con", 24);
	set("dex", 25);

	set("max_qi", 5500);
	set("max_jing", 3450);
	set("neili", 5500);
	set("max_neili", 5500);
	set("jiali", 130);
	set("combat_exp", 2800000);
	set("score", 10000);
	
	set_skill("art", 80);
	set_skill("liangyi-jue", 80);

	set_skill("force", 180);
	set_skill("xuantian-wuji", 180);
	set_skill("dodge", 180);
	set_skill("taxue-wuhen", 180);
	set_skill("parry", 180);
	set_skill("sword", 180);
	set_skill("liangyi-jian", 180);
	set_skill("cuff",180);
	set_skill("zhentian-quan",180);

	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
    map_skill("sword", "liangyi-jian");
    map_skill("parry", "xunlei-jian");
    map_skill("cuff", "zhentian-quan");

	prepare_skill("cuff", "zhentian-quan");
	set("chat_chance_combat", 25);
	set("chat_msg_combat", ({
  		(: perform_action, "cuff.zhentian" :),
  	}));

	create_family("昆仑派", 5, "弟子");
	setup();
   // carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/kunlun/obj/pao3")->wear();
}

void attempt_apprentice(object ob)
{
        if(ob->query("gender")=="女性"){
	   command("fear");
	   command("say "+RANK_D->query_respect(ob)+"师傅不准我收女弟子，你去找我师姊去吧。");
 	   return;
	 }
         if(ob->query("appren_hezudao", 1) == 1) {
	   command("say 师祖怎敢开如此玩笑，晚辈却是万万不敢的！");
	   return;
	 }
	 command("say 好吧，我就收下你，教你一些皮毛功夫。");
	 command("say 既然"+RANK_D->query_respect(ob)+"你刚来昆仑，不了解情况，可以去找詹春师姐打听下，看能做点什么事。");
	 command("say 我大昆仑讲究的是门派贡献，千万记住，切莫自误前程。");
//	 command("say 你从我这出徒后，可以去请教我师兄高则城！\n");
	 command("recruit " + ob->query("id"));
	 ob->set("title","昆仑派第六代弟子");
}
