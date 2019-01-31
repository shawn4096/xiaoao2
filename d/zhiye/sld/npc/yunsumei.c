// yunsumei.c
#include <ansi.h>

inherit NPC;
string ask_lianyao();
string ask_fangqi();
string ask_fire();

void create()
{
	set_name("云素梅", ({"yun sumei", "yun","sumei"}));
	set("long", "这是一个神龙教黑龙门女弟子子，长得颇有姿色。\n");

	set("gender", "女性");
	set("attitude", "peaceful");
	
	set("str",30);
	set("dex",30);
	set("con",20);
	set("int",20);
	set("per",20);
	set("no_kill",1);
	set("age", 10+random(10));
	set("shen_type", -1);
	set("str", 25+random(10));
	set("dex", 25+random(10));
	set("con", 25+random(10));
	set("int", 25+random(10));
	set("qi", 4000);
	set("max_qi", 4000);
	set("jing", 4000);
	set("max_jing", 4000);
	set("jingli", 2500);
	set("max_jingli", 2500);
	set("eff_jingli", 2500);
	set("neili", 2000);
	set("max_neili", 2000);
	set("jiaji",100);
	set("combat_exp", 500000+random(100000));

	set_skill("force", 150);
	set_skill("dodge", 150);
	set_skill("parry", 150);
	set_skill("leg", 150);
	set_skill("shenlong-tuifa", 150);
	set_skill("dulong-dafa", 150);
	set_skill("youlong-shenfa", 150);
	set_skill("poison", 100);
	set_skill("shenlong-yaoli", 100);
	set_skill("whip", 150);
	set_skill("lingshe-bianfa",150);
	map_skill("parry","shenlong-tuifa");
	map_skill("leg","shenlong-tuifa");
	map_skill("force","dulong-dafa");
	map_skill("dodge","youlong-shenfa");
	map_skill("whip","lingshe-bianfa");

	prepare_skill("leg","shenlong-tuifa");
	set("title", "神龙教赤龙门第四代弟子");

	create_family("神龙教",4,"弟子");
	set("inquiry", ([
		"火折": (: ask_fire :), 
//		"种药草": (: ask_zhongyao :), 
	//	"放弃": (: ask_fangqi :), 
//		"药圃": (: ask_yaopu :), 
		"炼药": (: ask_lianyao :),
//		"制药": (: ask_makeyao :),
//		"药炉": (: ask_yaolu :),
		"放弃": (: ask_fangqi :),
	]));

	setup();
	
	carry_object("/d/sld/npc/obj/gcp")->wear();

	add_money("silver",15);/*	*/
}

string ask_fire()
{
	object me,ob;
	me=this_player();
	if (me->query("family/family_name")!="神龙教")
	{
		command("say 你不是我神龙教弟子，来此作甚？\n");
		return "";
	}
	if (me->query("party/gongji")<100)
	{
		return "你的门派功绩不够100，别来烦我！\n";
	}
	if (present("fire",me))
	{
		return "我不是给你一根火柴了么！\n";
	}

	me->add("party/gongji",-100);


	ob=new("/clone/misc/fire");
	ob->move(me);
	return "扣除你100门派功绩，好好用，这里荒山野岭较多，怕引起火灾！\n";
}

string ask_lianyao()
{
	object me,*obj;
	int x;
	me=this_player();
	obj = users();
	x = sizeof(obj);
	//排除干扰项
	while(x--) {
		  if ( obj[x]->query_temp("lianyao/start")
			  && obj[x]!=me
			  && environment(me)==environment(obj[x]))
			 {
				  message_vision(HIY"$N试图开始炼药工作，却发现"+obj[x]->query("name") +HIY"已经在哪儿开始炼药了！\n"NOR,me);	
				  //me->move("d/quanzhen/liangong");
				  return me->query("name")+"待会再来！\n";
			}
			
	}
	
	if (me->query("family/family_name")!="神龙教")
	{
		return "你不是我神龙教弟子，来此作甚？\n";
	}
	if (me->query_skill("dulong-dafa",1)<250)
	{
		return "你的毒龙大法不足250，炼不了药？\n";
	}
	if (me->query_skill("shenlong-yaoli",1)<200)
	{
		return "你的神龙药理不足200，没有任何经验来此炼药？\n";
	}
	if (me->query_skill("poison",1)<150)
	{
		return "你的毒计不足150，没有任何经验来此炼药？\n";
	}
	if (me->query_skill("yaozhi",1)<200)
	{
		return "你的药植术不够200，别来烦我！\n";
	}

	if (me->query("combat_exp")<2000000)
	{
		return "你的经验值不足2m，会受不了药引起的心魔影响？\n";
	}
	if (me->query_temp("lianyao/start"))
	{
		return "我让你去炼药，为啥在此傻呆着？\n";
	}
	if (me->query("job_name")=="神龙制药")
	{
		return "你方才刚刚炼药完毕，休息会再来？\n";
	}
	if (me->query_condition("job_busy"))
	{
		return "你正在工作忙碌，休息会再来？\n";
	}
	if (me->query_condition("sldjob_lianyao"))
	{
		return "你现在神龙岛炼药任务中，休息会再来？\n";
	}


	me->set_temp("lianyao/start",1);
	command("say "+me->query("name")+",既然你想要开始炼药，就去吧！\n");
	command("say 炼药过程中，仔细查看药炉要求，按照流程规范，每一个过程都要认真对待！\n");

	command("say 需要注意的是这炼药会因为有迷幻效果，产生心魔，这心魔极为厉害，"+me->query("name")+"，你要当心！\n");
	command("say "+me->query("name")+"，炼药完了将药给我，有奖励，去吧！\n");
	me->apply_condition("sldjob_lianyao",40);
	return "我大神龙制药是一门博大精深的学问！\n";
}
string ask_fangqi()
{
	object me,ob,lu;
	me=this_player();
	if (me->query("family/family_name")!="神龙教")
	{
		command("say 你不是我神龙教弟子，来此作甚？\n");
		return "";
	}
	

	lu=present("yao lu",environment(this_object()));
	/*
	if (lu->query("lianyao"))
	{
		command("say 毛手毛脚,一点都不让省心！\n");
		return "你先把药炉的火灭了再说！\n";
	}*/
	
	command("say 既然你做不了就不要再费劲了，下去先歇息去吧！\n");
	me->delete_temp("lianyao");
	
	me->apply_condition("job_busy",4);
	me->clear_condition("sldjob_lianyao");
	lu->delete("lianyao");
	me->add_busy(1);
	if (!me->query_temp("lianyao"))
	{
		command("say 啥都没有做，要放弃啥？\n");
		return "";

	}
	return "哼，白吃白喝不干活！\n";
}
//接受物品

int accept_object(object me, object ob)
{
	//炼药
	//属性越多，经验值越大
	int jobs;
	jobs=me->query("job_time/神龙制药");

	if (ob->query("owner")==me->query("id")
		&&ob->query("id")==me->query_temp("lianyao/yaoid"))
	{
		message_vision(HIY"云素梅拿起这颗"+ob->query("name")+"看了又看，甚是好奇！\n"NOR,me);
		

		message_vision(HIC"云素梅对"+me->query("name")+"高兴地说道，“你真棒，居然又练了一颗叫做"+HIY+ob->query("name")+HIC"的丹药，我很仰慕你!”\n"NOR,me);
		me->add("party/gongji",2);
		message_vision(HIM"云素梅拿出功劳本给"+me->query("name")+"增加了二点门派贡献值!”\n"NOR,me);

		command("smile "+me->query("id"));
		//判断属性，属性越多，经验值越大
		TASKREWARD_D->get_reward(me,"神龙制药",-1,0,0,1+random(4),0,0,0,this_object());
		me->set("job_name", "神龙制药");
		me->delete_temp("lianyao");
		me->apply_condition("job_busy",3);
		
		destruct(ob);
		//判断喷毒机会
				//预留入门提示接口
		//嫡传
		//先天根骨35以上，25整数整除
		if (random(me->query("job_time/神龙制药"))>4000
			&& random(me->query("kar"))>26
			&& me->query("con")>35
			&& !me->query("quest/sld/dldf/pendu/start")
			&& jobs % 20 ==0	
			&& me->query("quest/qz/dichuan"))
		{
			
				message_vision(HIC"云素梅对$N竖起了大拇指，说道，“你如此辛苦为我大神龙教炼制药物，真是教中弟子楷模”！\n"NOR,me);
				command("say "+me->query("name")+"，我就将毒龙大法喷毒的相关信息透漏给你！\n");
				command("say "+me->query("name")+"，我神龙教对于药物研究最深的是我的师傅陆高轩！\n");
				command("say "+me->query("name")+"，关于如何将毒药融入内功的学问是神龙岛的绝技！\n");

				command("chat* thumb "+me->query("id"));
				command("rumor "+me->query("name")+"获得云素梅的青睐，获得解密喷毒技能的机会！\n");
				command("chat "+me->query("name")+"是我大神龙的核心弟子，望江湖同道多多照顾！\n");
				me->set("quest/sld/dldf/pendu/start",1);
		}
		
		return 1;
	}
	
}

void die()
{
	object ob,room;
	ob=this_object();
	//room=load_object("d/sld/lgxroom");

	if (!query_temp("living"))
	{
		ob = new("/d/sld/npc/yunsumei");
		ob->move("/d/sld/lianyaoshi");
	}
	::die();
}

