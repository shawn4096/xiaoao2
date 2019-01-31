// 樵子 by River@SJ 2002.6.5

inherit NPC;
#include <ansi.h>
inherit F_MASTER;

void create()
{
	set_name("樵子", ({ "jiao zi", "jiao", "zi" }) );
	set("long", "见他容色豪壮，神态虎虎，举手迈足间似是大将军有八面威风。\n"+
		"若非身穿粗布衣裳而在这山林间樵柴，必当他是个叱咤风云的统兵将帅。\n");
	set("gender", "男性" );
	set("age", 45);
	set("str", 35);
	set("con", 30);
	set("dex", 25);
	set("int", 25);
	set("per", 25);
	set("unique", 1);
	set("attitude", "friendly");

	set("max_qi", 25000);
	set("max_jing", 4800);
	set("eff_jingli", 3600);
	set("neili", 18000);
	set("qi", 25000);
	set("jingli", 3600);
	set("max_neili", 18000);
	set("jiali", 150);

	set("combat_exp", 4500000);
	set("score", 5000);

	set_skill("parry", 350);
	set_skill("dodge", 350);
	set_skill("force", 350);
	set_skill("axe", 350);
	set_skill("literate", 200);
	set_skill("qiantian-yiyang", 350);
	set_skill("pangen-fu", 350);
	set_skill("tianlong-xiang", 350);
	//set_skill("finger", 350);
	//set_skill("yiyang-zhi", 350);
	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "pangen-fu");
	map_skill("force", "qiantian-yiyang");
	map_skill("finger", "yiyang-zhi");
	map_skill("axe","pangen-fu");
	prepare_skill("finger","yiyang-zhi");
	set("chat_chance_combat",60);
	set("chat_msg_combat", ({
		(: perform_action, "axe.jingtian" :),
	
		(: perform_action, "axe.pangen" :),
		(: exert_function, "yiyang" :),
		
		(: perform_action, "axe.cuojie" :),
		
	}));
	create_family("天龙寺", 13, "俗家弟子");

	setup();
	carry_object(BINGQI_D("axe"))->wield();
	carry_object(ARMOR_D("b_cloth"))->wear();
	carry_object(ARMOR_D("caoxie"))->wear();
}

void init()
{
	object ob;

	::init();
	if (base_name(environment()) != query("startroom")) return;

	if( interactive(ob = this_player()) && visible(ob) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_answer", "answer");
}

void greeting(object me)
{
	if (! me || me->query_temp("yideng/answer")) return;
	command("say 天津桥上，凭栏遥望，舂陵王气都凋丧。树苍苍，水茫茫，云台\n"+
		"不见中兴将，千古转头归灭亡。功，也不久长！名，也不久长！");
	remove_call_out("greeting1");
	call_out("greeting1", 5, me);
}

void greeting1(object me)
{
	if (! me) return;
	command("say 峰峦如聚，波涛如怒，山河表里潼关路。望西都，意踟蹰。伤心\n"+
		"秦汉经行处，宫阙万间都做了土。兴，百姓苦！亡，百姓苦！");
	me->set_temp("yideng/answer", 1);
}

int do_answer(string arg)
{
	object jiaozi;
	object me = this_player();
    
	if (! me->query_temp("yideng/answer")) return 0;
	if ( me->query_temp("yideng/jiaozi_pass")) return 0; 

	if ( ! arg ) return 0;

	if ( arg != "青山相待，白云相爱。梦不到紫罗袍共黄金带。一茅斋，野花开，管甚谁家兴废谁成败？陋巷单瓢亦乐哉。贫，气不改！达，志不改！"){
		command("shake");
		return 1;
	}
	message_vision(CYN"\n$N回道：「青山相待，白云相爱。梦不到紫罗袍共黄金带。一茅斋，野花开，\n"+
		"管甚谁家兴废谁成败？陋巷单瓢亦乐哉。贫，气不改！达，志不改！」\n"NOR, me);
   /*
	if (me->query_temp("nqg/askyingok"))
    {
	    if (!objectp(jiaozi=present("jiao zi",environment(me))))
	    {
			jiaozi=new("d/dali/yideng/npc/jiaozi");
			jiaozi->move(environment(me));
	    }
		command("hehe ");
		command("hehe "+me->query("id"));
		command("say 回答的倒挺好，好像是有那么回事似的，居然是一副道貌岸然的样子！\n");
		command("say 好小子，还真不赖，居然从老四那边跑了过来！\n");
		command("say 纳命来吧！");
		tell_object(me,HIR"\n\n\n这个樵夫不知道发了什么疯，抡起手中的斧头向你砍去！\n"NOR);
		jiaozi->kill_ob(me);
		me->kill_ob(jiaozi);
		me->add_busy(1);
		//call_out("check_jiaozi",1,me);
		return 1;
    }
    else {
*/
		message_vision(CYN"\n$N听得心中大悦，心旷神怡之际，向山边一指，道：上去罢！\n"NOR, this_object());
		me->set_temp("yideng/jiaozi_pass", 1);
	//}
	return 1;
}
/*
int check_jiaozi(object me)
{
	object jiaozi;
	
	jiaozi=present("jiao zi",environment(me));
    if (objectp(jiaozi)&& me->is_fighting(jiaozi))
    {
		//remove_call_out("check_jiaozi");
		call_out("check_jiaozi",1,me);
		//return 0;
    }
	if (!objectp(me)) return 0;
	
	me->set_temp("yideng/jiaozi_pass", 1);

	message_vision("你哼了一声道，没有你的帮助我照样能爬过去。。\n", me);
	return 1;
	

}*/


void attempt_apprentice(object ob)
{
	
	
	if ((string)ob->query("gender") != "男性" ){
		command ("say 我向来不收女弟子，别来烦我！");
		return;
	}
	if ((string)ob->query("class")=="bonze" ){
		command ("say 阿弥陀佛！我不收出家弟子。");
		return;
	}
	if ((int)ob->query_skill("qiantian-yiyang", 1) < 300 ){
		command("say 朱某人我不收练功不勤之人，你还是多练练你的乾天一阳到250吧。");
		return;
	}
	if ((int)ob->query_skill("force", 1) < 300 ){
		command("say 武某人不收练功不勤之人，你还是多练练你的基本内功到250吧。");
		return;
	}
	if ((int)ob->query("shen") < 1000000){
		command("say 大理段氏乃是名门正派，你不足1m正神别来找我。");
		return;
	}

	command("say 真不错的一个苗子，本师的一身武功俱都在这柄斧头上，你以后可要好好用心了。\n");
	command("say 既然有缘我就收下你了！\n");
	command("haha ");
	command("recruit " + ob->query("id"));
	ob->set("title", "天龙寺第十四代俗家弟子");
}
