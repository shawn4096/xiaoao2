// yunsumei.c
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string ask_yaochu();
string ask_zhongyao();
string ask_fangqi();

void create()
{
	set_name("邓炳春", ({"deng bingchun", "deng","bingchun"}));
	set("long", "这是一个神龙教黑龙门男子，负责接待男弟子拜师事宜，长得英俊潇洒。\n");

	set("gender", "男性");
	set("attitude", "peaceful");
	
	set("str",30);
	set("dex",30);
	set("con",20);
	set("int",20);
	set("per",20);

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
	//set_skill("", 150);
	map_skill("parry","shenlong-tuifa");
	map_skill("leg","shenlong-tuifa");
	map_skill("force","dulong-dafa");
	map_skill("dodge","youlong-shenfa");

	prepare_skill("leg","shenlong-tuifa");
	set("title", "神龙教赤龙门第四代弟子");
	
	create_family("神龙教",4,"弟子");
	set("inquiry", ([
		"药锄": (: ask_yaochu :), 
		"种药草": (: ask_zhongyao :), 
		"放弃": (: ask_fangqi :), 
//		"药圃": (: ask_yaopu :), 
//		"炼药": (: ask_makeyao :),
//		"制药": (: ask_makeyao :),
//		"药炉": (: ask_yaolu :),
//		"药种": (: ask_yaozhong :),
	]));

	setup();
	
	carry_object("/d/sld/npc/obj/gcp")->wear();

	add_money("silver",15);
}
/*
void init()
{
	object ob;

	::init();

	if( interactive(ob = this_player()) && !is_fighting() ) {
		//remove_call_out("greeting");
		//call_out("greeting", 10, ob);
	}
}*/
    
void attempt_apprentice(object ob)
{
       mapping myfam;

       myfam = (mapping)ob->query("family");
	   if(myfam && myfam["family_name"] != "神龙教")
	   {
           command("say 你非本教弟子，我如何能收你为徒？\n");
		   return;
       }
	   if(ob->query("shen") > -10000)
	   {
           command("say 你还不够心黑手辣(-10k)，再去多杀几个白道中人吧.\n");
		  return;
	   }
	   if(ob->query("gender")!="男性")
	   {
           command("say 我只收男性弟子，女弟子找毛师妹拜师！\n");
		  return;
	   }
	   if(ob->query("combat_exp")>10000 )
       {
			command("say 你经验值都已经10k了，别来找我。我大神龙要的是忠诚弟子！\n");
            command("shake "+ob->query("id"));
			return;
	   }
       command("say 好吧，我就收下你做我的弟子。");
	   command("recruit " + ob->query("id"));
       
	   return;	

} 
string ask_yaochu()
{
	object me,obj;
	me=this_player();
	if(me->query("family/family_name") != "神龙教")
	{
      command("say 你非本教弟子，来此作甚？\n");
	  return "哼!\n";
    }
	if(present("yao chu",me))
	{
      command("say 你不是有一把药锄么？\n");
	  return "哼!\n";
    }
	obj=new("d/sld/obj/yaochu");
	command("say "+me->query("name")+"，你如此勤快我就给你把药锄，别弄丢了!\n");
	obj->move(me);
	return me->query("name")+"药锄给你了!\n";
}

string ask_zhongyao()
{
	object me,obj;
	me=this_player();
	if(me->query("family/family_name") != "神龙教")
	{
      command("say 你非本教弟子，来此作甚？\n");
	  return "哼!\n";
    }
	if(!present("yao chu",me))
	{
      command("say 你没有相应的工具如何去种药？\n");
	  return "哼!\n";
    }
	if(me->query_temp("sld/zhongyao/start"))
	{
      command("say 你怎么还没去种药？\n");
	  return "哼!\n";
    }

	command("say "+me->query("name")+"，本门派近期有大战，所以必须多配制一些药草!\n");
	command("say "+me->query("name")+"，正好陆高轩长老前几天找我安排一些弟子去种植药草!\n");
	command("say "+me->query("name")+"，你既然想去种植药草，就先要去找合适的药种!\n");
	command("say "+me->query("name")+"，我搜集了些合适的药种都放到药室墙角，你去找找看!\n");
	command("say "+me->query("name")+"，若找到药种就去栽种在药圃之中，多浇水，直到成为合格药草再送交给我!\n");
	command("pat "+me->query("id"));
	me->set_temp("sld/zhongyao/start",1);
	return me->query("name")+"关于种植的事宜我给你说了，赶紧去!\n";
}


string ask_fangqi()
{
	object me=this_player();
	if (me->query_temp("sld/zhongyao/start"))
	{
		command("say 既然你有难度，做不了也没什么，下去歇息会吧！\n");
		me->delete_temp("sld");
		me->apply_condition("job_busy",5);
		me->apply_condition("sldjob_zhongyao",5);

		return "现在的新弟子真是一代不如一代了！\n";
	}
	command("say 没事不要来骚扰我！\n");
	return me->query("name")+"蠢货!\n";

}

//接受物品
int accept_object(object who, object ob)
{
	
	int sum,gold,getshen;
	object sil;
	sum=10+random(10);
	
	if (ob->query("owner")==who->query("id")
		&& who->query_temp("sld/zhongyao/miaook")		
		&& ob->query("id")=="yao cao")
	{
		getshen=-1;
		gold=1+random(1);				
		
	//	who->set("job_name","神龙种药");			
		who->apply_condition("job_busy",3);		
		who->delete_temp("sld/zhongyao");
		who->delete_temp("sld");
		command("thumb "+who->query("id"));

		tell_object(who,RED"\n邓炳春点了点头，将"+ob->query("name")+RED+"收入怀中！\n"NOR);
		command("say 很好，"+who->query("name")+"，既然你把任务完成了，我就应该奖励你！\n");
		
		tell_object(who,GRN"\n邓炳春拿出门派记录本，给了"+who->query("name")+HIY+chinese_number(gold)+GRN"点的门派功绩的奖励！\n"NOR);
		who->add("party/gongji",gold);
		
		if (who->query("combat_exp")<300000)
		{
			tell_object(who,GRN"\n邓炳春随手拿出些银子，递给"+who->query("name")+HIY+chinese_number(sum)+GRN"两白银，拿去喝酒去吧！\n"NOR);
			sil=new("clone/money/silver");
			sil->set("set_amount",sum);
			sil->move(who);
			TASKREWARD_D->get_reward(who,"神龙种药",getshen,0,0,4+random(3),0,0,0,this_object());
		}

		//TASKREWARD_D->get_reward(who,"神龙训蛇",getshen,0,0,3+random(4),0,0,0,this_object());

			
		who->set("job_name", "神龙种药");
		if (who->query("combat_exp")>600000)
		{
			who->add("job_time/神龙种药",1);
		}
		who->apply_condition("job_busy",3);
		who->apply_condition("sldjob_zhongyao",3);
		destruct(ob);
		return 1;
	}

}