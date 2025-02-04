// sgjn.c  上官剑南

#include <ansi.h>
inherit NPC;

int ask_wumu();
int ask_dongxi();
int ask_xinyuan();
int ask_jueji();
int ask_baowu();

void create()
{
	set_name("上官剑南", ({ "shangguan jiannan", "shangguan", "jiannan"}));
        set("long",
        "他满脸的胡须，散乱的头发垂在面前，看起来很神秘！\n"
        "他齐膝以下的双腿赫然断去，琵琶骨亦被一条铁链穿过，固定在一侧的石壁上。\n");
        set("gender", "男性");
        set("age", 75);
        set("attitude", "peaceful");
        set("unique", 1);
        set("shen_type", 20);
        set("str", 35);
        set("int", 30);
        set("con", 1);
        set("dex", 1);

        set("max_qi", 34000);
        set("max_jing", 8000);
        set("neili", 25000);
        set("max_neili", 25000);
        set("jiali", 200);
		set("eff_jingli",8000);
		set("max_jingli",8000);
		set("jingli",8000);
        set("combat_exp", 10800000);
        set("score", 400000);

        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
				//(: perform_action, "strike.tiezhang" :),
                (: perform_action, "strike.tianlei" :),
                (: perform_action, "strike.lianhuan" :),
				(: perform_action, "strike.qinna" :),
                (: perform_action, "strike.zhangdao" :),
				(: perform_action, "strike.pushan" :),
                (: perform_action, "strike.lianhuan" :),
                (: perform_action, "strike.heyi" :),
				(: exert_function, "guiyuan" :),
                (: perform_action, "strike.duoming" :)
        }));

        set_skill("force", 480);
		set_skill("axe", 480);
		set_skill("lietian-fu", 480);
        set_skill("guiyuan-tunafa", 480);
        set_skill("dodge", 480);
        set_skill("shuishangpiao", 480);
        set_skill("strike", 480);
        set_skill("tiezhang-zhangfa", 480);
        set_skill("parry", 480);
        set_skill("literate", 180);
        set_skill("blade", 480);
	//	set_skill("brush", 480);
	//	set_skill("yingou-bifa", 480);
        set_skill("liuye-daofa", 480);
        set_skill("tiezhang-xinfa",200);

        map_skill("force", "guiyuan-tunafa");
        map_skill("strike", "tiezhang-zhangfa");
        map_skill("parry", "tiezhang-zhangfa");
        prepare_skill("strike", "tiezhang-zhangfa");
        map_skill("blade", "liuye-daofa");
		map_skill("axe", "lietian-fu");

        create_family("铁掌帮", 13, "帮主");

        set("inquiry", ([
		"name" : "老夫复姓上官，名剑南。乃是铁掌帮的第十三代帮主。\n",
		"here" : "裘千仞为了将我囚禁起来，特地派人在山腹中凿了这间石室！哼！\n",
		"忘恩负义的东西" : (: ask_dongxi :),
		"武穆遗书" : (: ask_wumu :),
		"心愿" : (: ask_xinyuan :),
		"绝技" : (: ask_jueji :),
		"宝物" : (: ask_baowu :),
        ]));

        setup();

        set("chat_chance", 1);
        set("chat_msg", ({
		"上官剑南怒道：如若老夫得以重见天日，定要将那忘恩负义的东西碎尸万段！！！\n",
		"上官剑南叹道：唉！不知那武穆遗书现在何处，真让人担心呀！唉！！\n",
	}) );
}

void attempt_apprentice(object ob)
{

 string name, new_name;
name = ob->query("name");
new_name = "上官" + name[<4..<1];
	if ((int)ob->query("shen") <=10000) {
		command("shake");
		command("say 你目露凶光，满脸阴鸷之气，非老朽中意之人，你还是回去吧！");
		return;
        }
	if ((int)ob->query_skill("guiyuan-tunafa", 1) < 140) {
                command("shake");
                command("say 铁掌帮的武功乃是以归元吐呐法为基础的！");
                command("say 你的基本功还未练好，现在我没什么可以教你的！");
                command("sigh");
                return;
        }
	if ((int)ob->query_skill("tiezhang-zhangfa", 1) < 140) {
                command("shake");
                command("say 铁掌掌法乃我帮镇帮绝技！");
                command("say 你的基本功还未练好，现在我没什么可以教你的！");
                return;
        }
	if ((int)ob->query_temp("mark/还书")) {
                command("say 好吧，我就收下你了。希望你不要让我失望！");
ob->set("name", new_name);
 command("say 从今以后你就叫做" + new_name + "，希望你能把铁掌功夫发扬光大！");
                command("recruit " + ob->query("id"));
                command("say 现在你既入我的门下，就当刻苦练习铁掌绝技。我帮\n"
                        "开山建帮，数百年来扬威中原，靠的就是这套掌法。威猛虽不及降龙\n"
                        "十八掌，可是掌法精奇巧妙，犹在降龙十八掌之上。");
                command("haha");
                command("look " + ob->query("id"));
                command("hmm");
                command("say 你的铁掌掌法练得已算不错，但仍未得神髓。铁掌的\n"
                        "威力所在，乃是要与归元吐呐法相结合，于战斗中，可以使出一招绝\n"
                        "技，唤做——天雷气，威力绝伦，无坚不摧。");
                command("pat " + ob->query("id"));
                command("say 现在为师就将此绝技传授于你！");
                }
                else
                {
                command("say 老夫一直很惦记武穆遗书，你能否去把它找来给我！\n");
                return;
	}
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                add("apprentice_available", -1);
            ob->set("title", "铁掌帮上官帮主弟子");
	ob->set("class","brigand");
}
int ask_dongxi()
{
command("say 唉！裘千仞本是我最得意的弟子，他当年曾救我一命，因此我也毫无保留\n"
"的倾囊以授，盼他在我百年后能传我衣钵。怎奈他年轻气盛，基础还未打好，就要学铁掌\n"
"的绝技，我因他基础未固，所以未加传授。他因此怀恨在心，以为老夫藏私。遂趁老夫酒\n"
"醉之际，将我双腿打断，用铁链穿过琵琶骨，关在这间石室之中，逼老夫将绝技传授于他！\n");
	this_player()->set_temp("marks/asksgjn",1);
	command("sigh");
	return 1;
}

int ask_jueji()
{
	command("say 这项绝技名叫--天雷气，于战斗中perform tianlei，即可释放出无坚不摧\n"
	"的罡气，当者非死即伤，十分霸道！\n");
	return 1;
}

int ask_wumu()
{
	object ob = this_player();

	if (!present("zitie", ob) || ob->query_temp("marks/asksgjn")!=1) {
		command("say 嘿嘿，武穆遗书的下落乃是关系到民族兴亡的大事，我如何能放心告诉你？\n");
		return 1;
	}
	command("look " + ob->query("id"));
	command("say 这位" + RANK_D->query_respect(ob) + "既然身揣《满江红》的字帖，定是我辈中人了，好吧，老夫就\n"
	"将武穆遗书的事告诉你吧！\n");
	command("say 武穆遗书乃是岳武穆死后留下的一部兵法，其中记载了行军打仗的要诀。\n"
	"老夫当年曾是韩世忠将军的部下，岳将军死后，我一气之下，落草为寇，后来入了铁掌帮。\n"
	"几年后我听说这部遗书藏在皇宫之中，就尽点帮中高手，将它偷了回来。本想将之交给一\n"
	"个忠心爱国的将领。唉！怎奈我忽然身遭巨变，这个心愿也未能达成。\n");
	this_player()->set_temp("marks/遗书1", 1);
	return 1;
}

int ask_xinyuan()
{
	if ((int)this_player()->query_temp("marks/遗书1")) {
		command("say 老夫当年曾画过一张山水画，其中暗藏着放遗书的地点，我将这副画放在了\n"
		"牛家村,如果你能找到这副画，就可以按画中所指，去拿武穆遗书了。\n");
		this_player()->set_temp("find_shanshui", 1);
		return 1;
	}
	command("say 老夫却有个未了的心愿，但不能告诉你！\n");
	return 1;

}

int accept_object(object who, object ob)
{
        if ((string)ob->query("name")=="「武穆遗书」") {

                command(
"say 啊！这正是我要找的武穆遗书，这本宝书能重见天日，真是上苍有眼啊！\n"
"你帮我找回这本书，我不会亏待你的！\n");

                this_player()->set_temp("mark/还书", 1);
                }
       else return notify_fail("上官剑南说道：" + RANK_D->query_respect(who) +
"送老夫这些东西，不知是何用意？\n");

        return 1;
}

int ask_baowu()
{
        object me  = this_player();
        mapping fam = me->query("family");

        if(!fam || fam["family_name"] != "铁掌帮"){
                command("say "+RANK_D->query_respect(me) + "与本派素无来往，不知此话从何谈起？");
                return 0;
                }

         if(fam["master_name"] != "上官剑南" ){
                command("say 你是什么东西，给我滚出去! ");
                write(HIY"一股巨大的气流，迎面扑来，把你推出了石室"NOR);
                me->move("/d/tiezhang/wmfeng");
                return 1;
                }
         else{
         command("say 这个秘密我只告诉你，附耳过来。");
         write("宝物在第二指节的洞穴里。\n");
         me->set_temp("marks/baowu", 1);
         return 1;
         }
}
