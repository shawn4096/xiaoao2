// wan.c 嵩山派第四代弟子 万大平
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("万大平", ({ "wan daping", "wan", "daping" }));
        set("nickname", "千丈松");
        set("long", "这是邓八公的徒弟，他是位身材甚高的黄衫汉子。\n");
        set("gender", "男性");
        set("age", 29);
        set("per", 20);
        set("attitude", "heroism");
        set("class", "songshan");
        set("shen_type", -1);
        set("str", 26);
        set("int", 20);
        set("con", 23);
        set("dex", 23);
        set("unique", 1);

        set("max_qi", 1500);
        set("max_jing", 1000);
        set("eff_jingli", 1000);
        set("jiali", 20);
        set("combat_exp", 650000);
        set("shen", -6500);
		
		set_skill("songyang-jue", 90);
		set_skill("whip", 200);
		set_skill("songyang-bian", 200);

		set_skill("force", 200);
		set_skill("hanbing-zhenqi", 200);
		set_skill("dodge", 200);
		set_skill("zhongyuefeng", 200);
		set_skill("hand", 200);
		set_skill("songyang-shou", 200);
		set_skill("parry", 200);
		//set_skill("sword", 100);
		//set_skill("songshan-jian", 100);
		set_skill("literate", 50);
		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songshan-jian");
		map_skill("whip", "songyang-bian");
		prepare_skill("hand", "songyang-shou");
		set("chat_chance_combat", 10);
		set("chat_msg_combat", ({
			(: perform_action, "whip.luan" :),
			(: perform_action, "hand.junji" :),
			(: exert_function, "juhan" :),
		}));
		create_family("嵩山派", 4, "弟子");
		setup();
		set("inquiry", ([
			"辟邪剑法" : "此事好像是沙天江师兄在负责此事。\n",
			//"辟邪剑法" : "我们五岳剑派在武林之中势力巨大，可与少林、武当抗衡。\n",
		]) );
		carry_object(ARMOR_D("changpao1"))->wear();
		carry_object(BINGQI_D("changbian"))->wield();
}

void attempt_apprentice(object ob)
{
	if (!ob->query("quest/ss/rumen/pass"))
	{
		command("say 你先通过狄修师弟的考验再说！\n");
		command("say 你有何德何能拜我为师？\n");
		command("say 我又何原何故收你为徒？\n");
		command("say 大嵩山需要忠诚的门徒，你还是先做给我看吧？\n");
		return;
	}
	if (ob->query("family/family_name")!="嵩山派")
	{
		command("say 一看就是鬼鬼祟祟之徒，为何到此？\n");
		return;
	}
	if(ob->query("party/gongji") < 100 ){
		command("say 你的门派功绩不够1000，别来找我！");
		return;
	}
	/*if(ob->query_skill("hanbing-zhenqi",1) < 100 ){
		command("say 你的寒冰真气太弱了，不足120别来找我！");
		return;
	}*/
	if(ob->query("shen") > -10000 ){
		command("say 嵩山剑法以狠辣著称（<-100k），你这娘娘腔一看就不够心狠手辣，快滚！");
		return;
	}
	command("say 好吧，师傅正要我多培育一些弟子来发扬嵩山派呢。");
	command("recruit " + ob->query("id"));
}
