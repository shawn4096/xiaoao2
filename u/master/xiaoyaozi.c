// xiaoyaozi.c 逍遥子
// shilling 97.2

inherit NPC;
inherit F_MASTER;
#include <ansi.h>

// string ask_wyz();
void create()
{
	set_name("逍遥子", ({ "xiaoyao zi", "xiaoyao","zi" }));
	set("title", "逍遥派开山祖师");
	set("long", 
		"他就是逍遥派开山祖师、但是因为逍遥派属于一个在江湖中\n"
		"的秘密教派，所以他在江湖中不是很多人知道，但其实他的\n"
		"功夫却是。。。。他年满七旬，满脸红光，须眉皆白。\n");
	set("gender", "男性");
	set("age", 75);
	set("class", "scholar");
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 60);
	set("int", 60);
	set("con", 60);
	set("dex", 60);
	set("per", 60);
	
	set("max_qi", 15500);
	set("max_jing", 13000);
	set("neili", 33000);
	set("eff_jingli", 13000);
	set("max_neili", 33000);
	set("jingli", 13000);
	set("jiali", 200);
	set("combat_exp", 8000000);
	set("score", 200000);
	set("quest/天龙八部/武功/yuxiang",1);
	set("quest/天龙八部/武功/pass",1);

	set_skill("force", 450);
	set_skill("beiming-shengong", 450);
	set_skill("dodge", 200);
	set_skill("lingbo-weibu", 450);
	set_skill("liuyang-zhang", 450);
	set_skill("parry", 450);
	set_skill("blade", 450);
	set_skill("ruyi-dao", 450);
	set_skill("zhemei-shou", 450);
	set_skill("art", 200);
	set_skill("hand", 450);
	set_skill("literate", 300);
	set_skill("strike", 450);
	set_skill("sword", 450);
	set_skill("qingyun-shou", 450);
	set_skill("piaomiao-shenfa", 450);
	map_skill("force", "beiming-shengong");
	map_skill("dodge", "lingbo-weibu");
	map_skill("hand", "zhemei-shou");
	map_skill("hand", "zhemei-shou");
	map_skill("strike", "liuyang-zhang");
	
	map_skill("parry", "ruyi-dao");
	map_skill("blade", "ruyi-dao");

	prepare_skill("hand","zhemei-shou");
	prepare_skill("strike","liuyang-zhang");
	set("chat_chance_combat", 90);  
	set("chat_msg_combat", ({
		(: perform_action, "blade.wanshi" :),
		(: perform_action, "blade.ruyi" :),
	}) );

	create_family("逍遥派", 1, "开山祖师");
	set("class", "taoist");

	setup();
	carry_object(__DIR__"obj/blade")->wield();
}

void attempt_apprentice(object ob)
{
	if ((int)ob->query_skill("beiming-shengong", 1) < 180) {
		command("say 我逍遥派内功的源泉来自于北冥神功的心法。"); 
		command("say " + RANK_D->query_respect(ob) + "的北冥神功是否还应该有所提高啊？");
		return;
	}
       
	if (ob->query_int() < 35) {
		command("say 我逍遥派武功最重视“逍遥”二字。");
		command("say 而何谓“逍遥”，这只能靠你自己去领悟。");
		command("say 但是" + RANK_D->query_respect(ob) + "的悟性似乎还有待提高啊。");
		return;
	}
	if ((string)ob->query("gender")=="男性")
	{
		command("smile");
		command("say 想不到在这世上竟然还有人可以继承我的逍遥心法！");
		command("recruit " + ob->query("id"));
		ob->set("title", "逍遥派逍遥子传人");
		return;
	}
	else
	{
		message_vision("我逍遥派从不收女流之辈?”\n",ob);
		return;
	}
}
