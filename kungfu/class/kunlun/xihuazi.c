// xihuazi.c (kunlun)

inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int ask_gold(object);

int ask_leg();

void create()
{
	set_name("西华子", ({ "xi huazi", "xi" }));
	set("long",
		"他是昆仑派第四代弟子，满腮虬髯，性子十分暴躁。\n");
	set("gender", "男性");
	set("age", 26);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 36);
	set("int", 23);
	set("con", 25);
	set("dex", 28);

	set("max_qi", 8800);
	set("qi", 8800);
	set("max_jing", 4600);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 150);
	set("combat_exp", 4500000);
	set("score", 1000);
	set("inquiry", ([
		"贡献" : (: ask_gold :),
            //  "补偿" : (: ask_leg :),
	]) );

	set_skill("force", 350);
	set_skill("xuantian-wuji", 350);
	set_skill("dodge", 350);
	set_skill("taxue-wuhen", 350);
	set_skill("parry", 350);
	set_skill("sword", 350);
	set_skill("liangyi-jian", 350);
	set_skill("cuff", 350);
	set_skill("zhentian-quan", 350);

	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("sword", "liangyi-jian");
	map_skill("cuff", "zhentian-quan");
    map_skill("parry", "xunlei-jian");
	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
  		(: perform_action, "sword.jinzhen" :),
  		(: perform_action, "sword.feipu" :),	
		(: exert_function, "wuji" :),			
  		(: perform_action, "dodge.taxue" :),
	}));
	prepare_skill("cuff", "zhentian-quan");

    create_family("昆仑派", 4, "弟子");
	setup();
	carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/kunlun/obj/pao3")->wear();
}

void attempt_apprentice(object ob)
{
	if(ob->query("gender")=="女性"){
		command("fear");
		command("say "+RANK_D->query_respect(ob)+"师傅不准我收女弟子，你去找我师姊去吧。");
		return;
	}
	if(ob->query_skill("xuantian-wuji",1) < 200){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你的玄天无极功太差,不足200级别，我可不想收你。");
		return;
	}
	if(ob->query_skill("zhentian-quan",1) < 200){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你的镇天拳太差,不足200级别，我可不想收你。");
		return;
	}
	if(ob->query_skill("taxue-wuhen",1) < 200){
		command("hmm");
		command("say "+RANK_D->query_respect(ob)+"你的踏雪无痕太差,不足200级别，我可不想收你。");
		return;
	}
	if(ob->query("appren_hezudao", 1) == 1) {
		command("say 前辈怎敢开这等玩笑，真是折杀做晚辈的了。");
		return;
	}
	command("say 既然"+RANK_D->query_respect(ob)+"这么努力，我就收下你吧。");
	command("recruit " + ob->query("id"));
	ob->set("title","昆仑派第五代弟子" );
}

int ask_gold(object who)
{
	object me = this_player();
	

	if( me->query("family/family_name") != "昆仑派" ) {
		command("hmm "+(string)me->query("id"));
		command("say 你非我派弟子，也敢来滥竽充数！\n");
		return 1;
	}

        if( (int)me->query_skill("xuantian-wuji", 1) < 40 ) {
		command("pat "+(string)me->query("id"));
		command("say 你是那个师兄派来的啊，想套我口风！\n");
		return 1;
	}

	if( (int)me->query("kl_given") <(int)me->query("age")){
		 command("nod "+(string)me->query("id"));
               who->add_money("gold",(int)(me->query_skill("xuantian-wuji", 1)/2) );
               command("give "+me->query("id")+" "+(int)(me->query_skill("xuantian-wuji", 1))/2+" gold");
                me->set("kl_given",(int)me->query("age"));
	command("say "+RANK_D->query_respect(me)+"真是有眼光啊，你怎么知道我一定会成为代掌门啊？不过...");
	command("say 我将这月的利钱存入你的钱庄，以后还请多多支持啊！");
}
	return 1;
}
/*
int ask_leg()
{
        object ob;
        mapping myfam;
        ob = this_player();

        myfam = (mapping)ob->query("family");
        
        if(!myfam || myfam["family_name"] != "昆仑派")
        return 0;
        if(ob->query("kl_leg")){
                command("say 你不是已经补偿过了么？");
                return 1;
        }
       ob->set_skill("leg",201);
       ob->set("kl_leg",1);
       write("你的基本腿法补偿完毕，祝游戏愉快!\n");
       return 1;
}


*/