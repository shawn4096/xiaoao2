// Npc: /kungfu/class/shaolin/xuan-bei.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

string ask_me();
string ask_cibei();
void create()
{
	set_name("玄悲大师", ({
		"xuanbei dashi",
		"xuanbei",
		"dashi",
	}));
	set("long",
		"他是一位白须白眉的老僧，身穿一袭银丝棕黄袈裟。他身材甚高，\n"
		"但骨瘦如柴，顶门高耸，双目湛然有神。\n"
	);

    set("no_get",1);
	set("nickname", "达摩院主持");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 70);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 20000);
	set("max_jing", 8000);
	set("neili", 30000);
	set("max_neili", 2000);
	set("jiali", 200);
	set("combat_exp", 9500000);
	set("score", 500000);

	set_skill("force", 450);
	set_skill("yijin-jing", 450);
	set_skill("dodge", 450);
	set_skill("shaolin-shenfa", 450);
	set_skill("hand", 450);
	set_skill("claw", 450);
	set_skill("blade", 450);
	set_skill("sword", 450);
	set_skill("parry", 450);
	set_skill("qianye-shou", 450);
	set_skill("longzhua-gong", 450);
	set_skill("cibei-dao", 450);
	set_skill("damo-jian", 450);
	set_skill("finger", 450);
	set_skill("yizhi-chan", 450);
	set_skill("buddhism", 150);
	set_skill("literate", 150);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("hand", "qianye-shou");
	map_skill("claw", "longzhua-gong");
	map_skill("blade", "cibei-dao");
	map_skill("sword", "damo-jian");
	map_skill("parry", "yizhi-chan");
	map_skill("finger", "yizhi-chan");
	

	prepare_skill("finger", "yizhi-chan");
	prepare_skill("claw", "longzhua-gong");
    set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
		(: perform_action, "finger.wofo" :),
	    (: perform_action, "finger.qiankun" :),
		(: perform_action, "claw.lianhuan" :),
		(: exert_function, "jingang" :),
	}));
	create_family("少林派", 36, "弟子");

	set("inquiry", ([
		"三长老": (:ask_me:),
		"慈悲刀绝技": (:ask_cibei:)
	]));

	setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void du1(object ob)
{
	object du;

	say("你的眼前一花，一个瘦小的身影闪了进来。\n");
	du=new("/kungfu/class/shaolin/du-nan2");
	du->move(environment());
	EMOTE_D->do_emote(du, "buddhi", query("id"));
	command("buddhi " + du->query("id"));
}
 
void charse_du(object ob)
{
	new("/d/shaolin/npc/xiao-bei")->move(environment());
	say("小沙弥走了进来。\n小沙弥对着玄悲大师说道：渡难长老闻听此讯马上就到。\n");
	call_out("du1", 20, ob);
}

string ask_me()
{
	mapping skill;
	string *skl;
	object ob = this_player(), tmp;
	int i;

	if (present("du nan", environment())) {
		command("? " + ob->query("id"));
		return "渡难长老不是在这里吗？";
	}
	if (ob->query_temp("pending/waitdu"))
		return "大师请耐心等候片刻。";

	if (ob->query("family/family_name") != "少林派") {
		command("sneer " + ob->query("id"));
		return "不知道。";
	}

    if (ob->query("pass_xin"))
        return "你不是已经通过心禅七老的考验了吗？";
	if (ob->query("passdu"))
		return "你不是已经通过了渡难大师的考验了吗？\n";

	if (ob->query("family/generation") != 37) {
		return "三长老在金刚伏魔圈面壁禅修。";
	}
	skill = ob->query_skills();
    if (!skill) return RANK_D->query_respect(ob) + "的武功差强人意，不可勉强自己。";
	skl = keys(skill);
	i = sizeof(skl);
    if (i < 8) return RANK_D->query_respect(ob) + "的武功差强人意，不可勉强自己。";
	while (i--) {
		if (skill[skl[i]] < 120 && skl[i] != "medicine")
			return RANK_D->query_respect(ob) + "是否在" + CHINESE_D->chinese(skl[i]) + "上多下些功夫？";
	}
	if ((tmp = present("xiao shami", environment()))) {
		ob->set_temp("pending/waitdu", 1);
		command("nod");
		say("玄悲大师俯身对着小沙弥耳语几句。\n小沙弥快步走了出去。\n");
		destruct(tmp);
		call_out("charse_du", 20, ob);
		return "好吧，" + RANK_D->query_respect(ob) + "请先稍侯一会。";
	}
	return "阿弥陀佛，小沙弥不在，你过段时间再来吧。";
}

void attempt_apprentice(object ob)
{
	object me; 
	mapping ob_fam, my_fam;
	string name;

	me = this_object();
	my_fam  = me->query("family");

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
/*
	if ( ob_fam["generation"] <= my_fam["generation"] )
	{
		command("say " + RANK_D->query_respect(ob) + "，贫僧哪里敢当 !");
		return;
	}
*/
	if ( ob_fam["generation"] <= (my_fam["generation"] + 1) )
	{
		command("say " + ob_fam["master_name"] + "的徒弟怎么跑到我这儿来了，哈哈哈 !");
		command("recruit " + ob->query("id"));
	}
	else
	{
		command("say " + RANK_D->query_respect(ob) + "，你辈份不合，不能越级拜师。");
		return;
	}

	return;
}

string ask_cibei()
{
	object me=this_player();
	if (me->query("family/family_name")!="少林派")
	{
		command("say 我佛慈悲，你不是我少林中弟子，来此作甚？\n");
		return "慈悲刀乃蕴含我佛慈悲真意,唯懂者识之！\n";
	}
	if (time()-me->query("quest/sl/cbd/time")<86400)
	{
		command("say 少林武功重要的是顿悟，你来的太频繁了！\n");
		return "顿悟啊！\n";
	}
	if (me->query("quest/sl/cbd/pass"))
	{
		command("say 你已经修习成功了慈悲刀的真意！\n");
		return "你乃是我大少林的栋梁之才啊！\n";
	}
	command("say 这慈悲刀本是我少林绝技之一，其核心本意在于慈悲二字。\n");
	command("say 但兵者，凶器也，既然手中持刀，就存了杀人之心。\n");
	command("say 既然存了杀人之心，又奈何叫做慈悲？这和我佛本意相悖。\n");
	command("say 所以，这慈悲刀虽然是我少林绝技，但一直没有人能练成。\n");
	command("say 但是，百年之内，有一个叫心观和尚的奇才却无意中练成了这慈悲刀真意。\n");
	command("say 他后来游行天下，据说现在在宁波天童寺中当主持。\n");
	command("say 你若想学可以跟他请教这慈悲刀真意。\n");
	me->set_temp("cbd/askxuanbei",1);
	return;
}