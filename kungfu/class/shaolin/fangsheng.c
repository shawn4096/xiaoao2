inherit NPC;

string ask_me_1(object);
string ask_me_2(object);
string askme3();
string askme4();
string askme5();
string ask_rysx();

void create()
{
	set_name("方生大师", ({"fangsheng dashi", "fangsheng", "dashi" }));
	set("long","他是一位身材矮小的老年僧人，面上皱纹堆垒。\n"
		"慈眉善目，露出悲天悯人之像。\n");
	set("nickname", "心禅堂首座");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 80);
	set("shen", 1);

	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 24000);
	set("max_jing", 5300);
	set("neili", 18000);
	set("eff_jingli", 5300);
	set("max_neili", 18000);
	set("jiali", 200);
	set("combat_exp", 9600000);

	set_skill("force", 450);
	set_skill("dodge", 450);
	set_skill("parry", 450);
	set_skill("strike", 450);
	set_skill("finger", 450);
	set_skill("leg", 450);
	set_skill("cuff", 450);

	set_skill("banruo-zhang", 450);
	set_skill("club", 450);
	set_skill("zui-gun", 450);
	set_skill("jingang-quan",450);
	set_skill("yizhi-chan",450);
	set_skill("yijin-jing", 450);
	set_skill("shaolin-shenfa", 450);
	set_skill("ruying-suixingtui",450);
	set_skill("buddhism", 180);
	set_skill("literate", 150);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("parry", "banrou-zhang");
	map_skill("strike", "banruo-zhang");
	map_skill("leg", "ruying-suixingtui");
	map_skill("cuff", "jingang-quan");
	map_skill("finger", "yizhi-chan");

	prepare_skill("strike", "banruo-zhang");
	prepare_skill("cuff", "jingang-quan");
	create_family("少林派", 35, "弟子");
	set("inquiry", ([
		"钢杵" : (: ask_me_1, "gangchu" :),
		"柴刀" : (: ask_me_1, "chaidao" :),
		"挠钩" : (: ask_me_2, "naogou" :),
		"套索" : (: ask_me_2, "taosuo" :),
		"少林武技" : (: askme3 :),
		"因果" : (: askme5 :),
		"原因" : (: askme5 :),
		"后山" : (: askme4 :),
		"如影随形腿绝技" : (: ask_rysx :),
	]));

	set("weapon_count", 10);

	setup();

	carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void reset()
{
	set("weapon_count", 10);
}

string ask_rysx()
{
	mapping fam;
	object me=this_player();

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "少林派")
		return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";

	if (me->query_skill("ruying-suixingtui",1)<450)
		return RANK_D->query_respect(this_player()) +"你的如影随形腿等级不足450级，请继续努力！";

	if (time()-me->query("quest/sl/rysxt/time")<86400)
	{
		return RANK_D->query_respect(this_player()) +"少林最重顿悟，你来的太频繁了，请继续努力！";

	}
	command("say 这如影随形腿乃是少林七十二绝技腿法中的极致。\n");
	command("say 一腿踢出，如影随形，亦步亦趋，直到将对方打倒为止。\n");
	command("say 我也没有练成，不过当初鸠摩智大师来少林一战，如影随形腿名扬天下。\n");
	command("say 你如果想学就在此认真参禅(canchan 如影随形腿绝技)吧。\n");
	me->set_temp("rysxt/askfangsheng",1);
	return "如影随形腿从不弱于人！你要好好修习。\n";

}
string ask_me_1(string name)
{
	mapping fam;
	object ob;

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "少林派")
		return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";

	if (  present(name, this_player()))
		return RANK_D->query_respect(this_player()) +"你现在身上不是有这样东西吗，怎麽又来要了？ 真是贪得无餍！";

	if (query("weapon_count") < 1)
		return "抱歉，你来得不是时候，东西已经发完了。";

	ob = new("/d/shaolin/obj/" + name);
	ob->move(this_player());
	add("weapon_count", -1);
	message_vision("方生给$N一件" + ob->query("name") + "。\n", this_player());
	return "拿去吧。用此物为寺中服务。\n";
}

string askme5()
{
	object me=this_player();

	if(me->query("wxz/quest")<2)
		return 0;
	if( me->query("wxz/quest")== 2 )
		me->set("wxz/quest",3);
	command("say 本寺七十二绝技，每一项功夫都能伤人要害、取人性命，凌厉狠辣，大\n"
		+"干天和，是以每一项绝技，均须有相应的慈悲佛法为之化解。只是一人练到四五\n"
		+"项绝技之后，在禅理上的领悟，自然而然的会受到障碍。只有佛法越高，慈悲之\n"
		+"念越盛，武功绝技才能练得越深。");
	command("say 本寺之中，自然也有人佛法修为不足，却要强自多学上乘武功的，但练将\n"
		+"下去，不是走火入魔，便是内伤难愈。玄澄大师一身超凡绝俗的武学修为，先辈\n"
		+"高僧均许为本寺二百年来武功第一。但一夜之间，突然筋脉俱断，成为废人，那\n"
		+"便是如此了。");
	return "我听说有几位前辈高僧在后山隐居，或许可以向他们请教慈悲佛法。只是此举\n"
		+"凶险无比，"+RANK_D->query_respect(me)+"又何苦如此执著？";
}

string askme4()
{
	object me=this_player();

	if(me->query("wxz/quest")<3)
		return 0;
	if( me->query("wxz/quest")== 3 )
		me->set("wxz/quest",4);
	return "从这里往北就可以到达后山，不过悬崖绝壁，非常难走，如果没有钩、索之类攀\n"
		+"爬工具，实在无法到达。";
}

string askme3()
{
	object me=this_player();

	if (!me->query("wxz/quest")
	|| !me->query_temp("wxz/quest"))
		return 0;
	if (me->query_temp("wxz/quest")) {
		me->delete_temp("wxz/quest");
		me->set("wxz/quest",2);
	}
	return "我少林武功博大精深，可是从来没有一名少林弟子能够练到十门以上，"+
		RANK_D->query_respect(me)+"可知道其中的因果？";
}

string ask_me_2(string name)
{
	object ob;
	if (this_player()->query("family/family_name") != "少林派")
		return RANK_D->query_respect(this_player()) +
		"与本派素无来往，不知此话从何谈起？";
	if (this_player()->query("wxz/quest")<4)
		return RANK_D->query_respect(this_player())+"此话从何谈起？\n";
	if (  present(name, this_player()) )
		return RANK_D->query_respect(this_player()) + "你现在身上不是有这样东西吗，怎麽又来要了？ 真是贪得无餍！";

	ob = new("/d/shaolin/obj/" + name);
	ob->move(this_player());

	add("tool_count", -1);

	message_vision("方生给$N一件" + ob->query("name") + "。\n", this_player());

	return "拿去吧。你可用此物翻过断崖，去拜见几位前辈高僧。";
}

void attempt_apprentice(object ob)
{
        object me=this_object();
        mapping ob_fam, my_fam;
        string name, new_name;
//      me=this_object();
        my_fam =me->query("family");
        name = ob->query("name");

        if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "少林派")
        {
                command("say " + RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return;
        }
        if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "少林派")
        {
                command("say " + RANK_D->query_respect(ob) + "是俗家弟子，不能在寺内学艺。");
                return;
        }

        if ( !(ob->query("pass_xin")))
        {
          command("say "+RANK_D->query_respect(ob) +"是怎么进来的?");
           return;
       }
        if ( ob_fam["generation"] <= my_fam["generation"] )
        {
                command("say " + RANK_D->query_respect(ob) + "，贫僧哪里敢当 !");
                return;
        }
        if ( ob_fam["generation"] == (my_fam["generation"] + 1) && name[0..1] == "玄")
        {
                command("say " + ob_fam["master_name"] + "的徒弟怎么跑到我这儿来了，哈哈哈 !");
                command("recruit " + ob->query("id"));
        }

        if ( ob_fam["generation"] == (my_fam["generation"] + 2)){
		name = ob->query("name");
		new_name = "玄" + name[2..3];
		command("say 老衲垂死之年，又得一可塑之才，真是可喜可贺 !");
		ob->set("name", new_name);
		ob->set("title", "心禅堂职事僧");
		command("say 今后你的法名叫做"+new_name+"，恭喜你成为少林玄字辈圣僧之一。\n");
		command("say 从今以后你就是心禅堂职事高僧了，望你好好深造！\n");
		command("recruit " + ob->query("id"));
	}
	else
		command("say " + RANK_D->query_respect(ob) + "，你是从哪蹦出来的，你不能越级拜师。");
        return;
}
