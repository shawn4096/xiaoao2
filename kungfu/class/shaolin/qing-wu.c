// Npc: /kungfu/class/shaolin/qing-wu.c
// Date: YZC 96/01/19
#include <ansi.h>

inherit NPC;
inherit F_MASTER;

int ask_job();
int ask_over();

void create()
{
	set_name("清无比丘", ({
		"qingwu biqiu",
		"qingwu",
		"biqiu",
	}));
	set("long",
		"他是一位体格强健的壮年僧人，他身得虎背熊腰，全身似乎蕴含\n"
		"着无穷劲力。他身穿一袭白布黑边袈裟，似乎身怀武艺。\n"
	);


	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");
	set("title", "接待僧人");

	set("age", 30);
	set("shen_type", 1);
	set("str", 23);
	set("int", 17);
	set("con", 20);
	set("dex", 24);
	set("max_qi", 350);
	set("max_jing", 200);
	set("neili", 350);
	set("max_neili", 350);
	set("jiali", 30);
	set("combat_exp", 50000);
	set("score", 100);

	set_skill("force", 60);
	set_skill("hunyuan-yiqi", 60);
	set_skill("dodge", 60);
	set_skill("shaolin-shenfa", 60);
	set_skill("hand", 60);
	set_skill("fengyun-shou", 60);
	set_skill("parry", 60);
	set_skill("buddhism", 60);
	set_skill("literate", 60);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("hand", "fengyun-shou");
	map_skill("parry", "fengyun-shou");

    prepare_skill("hand", "fengyun-shou");

	create_family("少林派", 40, "弟子");
	set("inquiry", 
    ([
         "义工" : (: ask_job :),
          "复命" : (: ask_over :),
    ]));

	setup();

      //  carry_object("/d/shaolin/obj/jiedao")->wield();
        carry_object("/d/shaolin/obj/qing-cloth")->wear();
}

#include "/kungfu/class/shaolin/qing.h"


int ask_job()
{
	object me,shi,ob;

	me=this_player();
	if (me->query_temp("sljob/qingwu/askqingwu"))
	{	
		command("say 你无缘无故不要来调戏贫僧！\n");
		command("say 我不是已经安排你去做"+me->query_temp("sljob/qingwu/jobname")+"了么？还不快去？\n");
		return 1;
	}
	if (me->query("gender")!="男性")
	{	
		command("say 你无缘无故不要来调戏贫僧！\n");
		command("say 本寺出家只招募男人！\n");
		return 1;
	}
	if (me->query("combat_exp")>500000)
	{	
		command("say 你如此高的经验值就不要在此混了，去干点别的吧！\n");
		return 1;
	}
	if (me->query("family"))
	{	
		command("say 你已经有门有派，难道想混入本寺奸细？！\n");
		return 1;
	}
	if (me->query("shen")<0)
	{	
		command("say 你满脸凶煞之相，来此作甚？！\n");
		return 1;
	}
	if (me->query_condition("job_busy"))
	{	
		command("say 你现在正在工作繁忙中，待会再来？！\n");
		return 1;
	}


	if (me->is_busy()||me->is_fighting()||me->query_condition("job_busy"))
	{
		command("say 你现在正在忙乱中，待会再来！\n");
		return 1;
	}
	message_vision(HIY"$N向$n打听如何来为寺庙周围的人做点义工的事情，做些善举！\n"NOR,me,this_object());
	command("say "+me->query("name")+"，既然你有如此善心就先做些义工吧！\n");
	command("say 人在做，天在看！\n");

	switch (random(2))
	{
		case 0:
			tell_object(me,"清无比丘说道，"+me->query("name")+"，最近山下乔大妈来信说老乔好几天没来了，你到山下小屋去看看！\n");
			tell_object(me,"清无比丘说道，“乔大妈让你做的事你要做好！”\n");
			command("say 善哉！善哉！");
			me->set_temp("sljob/qingwu/weizhu",1);
			me->set_temp("sljob/qingwu/jobname","喂猪");
			me->apply_condition("sljob_qingwu",10);
			break;
		case 1:
			tell_object(me,"清无比丘说道，"+me->query("name")+"，最近上山的善男善女很多，有点忙不过来！\n");
			tell_object(me,"清无比丘说道，你既然想为寺里做点事情就先去迎客亭找虚通问问！\n");
			me->set_temp("sljob/qingwu/yingke",1);
			me->set_temp("sljob/qingwu/jobname","迎客");
			me->apply_condition("sljob_qingwu",10);
			ob=new("/d/shaolin/obj/yingke-ling");
			ob->set_temp("sljob/qingwu/yingke",1);
			ob->set("owner",me->query("id"));
			ob->move(me);
			tell_object(me,"清无比丘说道，我给你一块令牌，你到了山下迎客亭后递给虚明，他自会安排！\n");
			command("say 阿弥陀佛！");
		break;
		default:break;
	}
	tell_object(me,"快去快回，这也是一种考验！\n");
	return 1;
}

int ask_over()
{
	object me,ob;

	me=this_player();
	
	if (me->query_temp("sljob/qingwu/weizhuok"))
	{
		tell_object(me,me->query("name")+"，你干的很不错，乔大妈说你喂猪很尽心，很负责，真不错，下去休息去吧！\n");
		//me->set("job_name","少林打杂");

	}
	if (me->query_temp("sljob/qingwu/yingked"))
	{
		tell_object(me,me->query("name")+"，你干的很不错，虚明师弟说了，你工作很负责，真不错，下去休息去吧！\n");
		//me->set("job_name","少林迎客");

	}
	if (!me->query_temp("sljob/qingwu/weizhuok")&&!me->query_temp("sljob/qingwu/yingked"))
	{
		command("say 你没好也没事，下次再开始一次,从头再来！\n");
		me->delete_temp("sljob");
		me->clear_condition("sl_yingke");

		me->add_busy(2);
		return 1;
	}
	me->set("job_name","少林打杂");

	me->apply_condition("job_busy",2);
	me->apply_condition("sljob_qingwu",3);
	if (me->query("combat_exp")<100000)
	{
		tell_object(me,"不错，这次善举善行很值得称赞！好苗子，我很看好你。\n");
		TASKREWARD_D->get_reward(me,"少林打杂",1,0,0,1,0,0,0,"清无比丘");  
	}else{
		tell_object(me,"不错，善有善报，好好干，贫僧只能给你些正神和潜能！\n");
		me->add("potential",10);
		me->add("shen",100);
	}
	
	if (random(me->query("job_time/少林打杂"))>200
		&&!me->query("quest/sl/chujia/pass")
		&&random(me->query("kar"))>25 )
	{			
		message_vision(HIG"清无比丘微笑地对$N双手合十，“阿弥陀佛，施主具有善心慧根，很有佛缘，你若愿成为少林寺出家弟子，我可以给你推荐！”\n"NOR,me);
		ob=new("/d/shaolin/obj/jujianxin");
		ob->set("owner",me->query("id"));
		ob->move(me);
		me->set("quest/sl/chujia/pass",1);
	}
	me->delete_temp("sljob");
	tell_object(me,"快去快回，这也是一种考验！\n");
	return 1;
}