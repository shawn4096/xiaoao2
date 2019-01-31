// deng.c 嵩山派第三代弟子 邓八公
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
int ask_zisong();
inherit F_MASTER;
void create()
{
        set_name("邓八公", ({ "deng bagong", "deng", "bagong" }));
        set("nickname", HIC"神鞭"NOR);
        set("long", "这是一名瘦削的老者，一手嵩阳鞭舞的出神入化。\n");
        set("gender", "男性");
        set("unique", 1);
        set("age", 45);
        set("per", 20);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 26);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("unique", 1);

        set("max_qi", 3000);
        set("max_jing", 2000);
        set("eff_jingli", 2000);
        set("jiali", 50);
        set("combat_exp", 2000000);
        set("eff_neili", 4000);
        set("shen", -15000);
		set_skill("songyang-jue", 180);

		set_skill("literate", 100);
		set_skill("force", 355);
		set_skill("parry", 360);
		set_skill("whip", 400);
		//set_skill("sword", 350);
		set_skill("dodge", 350);
		set_skill("hand", 350);
		set_skill("zhongyuefeng", 350);
		set_skill("songyang-shou", 350);
		set_skill("songyang-bian", 400);
		set_skill("hanbing-zhenqi", 350);
		//set_skill("songshan-jian", 350);

		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("whip", "songyang-bian");
		map_skill("parry", "songyang-bian");
		//map_skill("sword", "songshan-jian");
		prepare_skill("hand", "songyang-shou");

		create_family("嵩山派", 3, "弟子");

		set("class", "sword");
		set("chat_chance_combat", 10);
		set("chat_msg_combat", ({
			(: perform_action, "hand.junji" :),
			(: exert_function, "juhan" :),
		}));
		set("inquiry", ([
			"嵩山派" : "我们嵩山派是五岳剑派之首！\n",
			"五岳剑派" : "我们五岳剑派在武林之中势力巨大，可与少林、武当抗衡。\n",
			"左冷禅" : "他就是我们的掌门人，功夫深不可测。\n",
			"紫松鞭": (: ask_zisong() :),

		]) );
			setup();
			carry_object(ARMOR_D("changpao1"))->wear();
			carry_object(BINGQI_D("whip"))->wield();
}


int ask_zisong()
{
	object me=this_player();
	//message_vision(HIC""NOR,me);
	if (!me->query_temp("ss/hb_1"))
	{
		command("say 你是否有不良企图，来打听我嵩山的秘籍么？\n");
		command("heng ");
		return 1;
	}
	command("sigh ");
	command("say 当年师兄曾命我修炼嵩阳鞭法，我终于修炼有成。\n");
	command("say 本想凭此立足江湖，于是我就去寻找师兄来演练此技。\n");
	command("say 当时那场战斗是在大铁梁峡，我手里握住的正是本门著名的紫松鞭。\n");
	command("say 结果一不小心，为师兄寒冰真气所反震，将这个重宝失手跌落到崖底。\n");
	command("say 谁要是替我寻找回来，我必当重谢，唉！！！！。\n");
	command("say 哪儿比较凶险，要下去最好去问问乐师兄，他对那一带比较熟悉。\n");
	me->set_temp("ss/zsb_3",1);
	return 1;
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
	if(ob->query("party/gongji") < 2000 ){
		command("say 你的门派功绩不够1000，别来找我！");
		return;
	}
	if(ob->query_skill("hanbing-zhenqi",1) < 200 ){
		command("say 你的寒冰真气太弱了，不足120别来找我！");
		return;
	}
	if(ob->query("shen") > -100000 ){
		command("say 嵩山剑法以狠辣著称（<-100k），你这娘娘腔一看就不够心狠手辣，快滚！");
		return;
	}
	command("say 好吧，师傅正要我多培育一些弟子来发扬嵩山派呢。");
	command("recruit " + ob->query("id"));
}
