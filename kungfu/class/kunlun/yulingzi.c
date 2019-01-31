// yulingzi.c (kunlun)

inherit NPC;
inherit F_MASTER;
//昆仑女弟子第一个师傅
void create()
{
	set_name("玉灵子", ({ "yuling zi","yuling", "zi" }));
	set("long",
		"她是昆仑派第五代弟子，容颜俏丽，身材丰满，举手投足间带着点挑逗之意。\n");
	set("gender", "女性");
	set("age", 28);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 30);
	set("int", 23);
	set("con", 25);
	set("dex", 28);

	set("max_qi", 600);
	set("max_jing", 400);
	set("eff_jingli", 500);
	set("neili", 500);
	set("max_neili", 500);
	set("jiali", 30);
	set("combat_exp", 70000);
	set("score", 5000);

	set_skill("force", 140);
	set_skill("xuantian-wuji", 165);
	set_skill("dodge", 160);
	set_skill("taxue-wuhen", 165);
	set_skill("parry", 155);
	set_skill("sword", 160);
	set_skill("liangyi-jian", 165);
	set_skill("leg", 150);
	set_skill("chuanyun-tui", 160);

	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("leg", "chuanyun-tui");
    map_skill("sword", "liangyi-jian");
    map_skill("parry", "liangyi-jian");


    prepare_skill("leg", "chuanyun-tui");
	create_family("昆仑派", 5, "弟子");
	setup();
	carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/kunlun/obj/pao3")->wear();
}

void attempt_apprentice(object ob)
{
        if(ob->query("gender")=="男性"){
	    command("fear");
	    command("say "+RANK_D->query_respect(ob)+"师傅不准我收男弟子，你去找我师兄去吧。");
   	    return;
	}
	if(ob->query("appren_hezudao") == 1) {
	    command("say 师祖怎敢开如此玩笑，晚辈却是万万不敢的！");
	    return;
	}
	command("say 好吧，我就收下你，教你一些皮毛功夫。");
		 command("say 既然"+RANK_D->query_respect(ob)+"你刚来昆仑，不了解情况，可以去找詹春师姐打听下，看能做点什么事。");
	 command("say 我大昆仑讲究的是门派贡献，千万记住，切莫自误前程。");

	command("recruit " + ob->query("id"));
	return;
}
