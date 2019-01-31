// zdy.c 张淡月
// Modified by Lklv add ask xionghuangjiu
#include <ansi.h>

inherit F_MASTER;
inherit NPC;
string ask_jiu();
string ask_xunshe();
string ask_fangqi();

void create()
{
	set_name("张淡月", ({ "zhang danyue","zhang" }));
	set("long", "他四十来岁年纪，是神龙教黑龙门掌门使,精通神龙腿法和灵蛇鞭法。\n");
	set("gender", "女性");
	set("title", "神龙教黑龙门掌门使");
	set("age", 42);
	set("str", 20);
	set("int", 22);
	set("con", 22);
	set("dex", 22);
	set("per", 25);
	set("combat_exp", 200000);
	set("shen", -50000);
	set("attitude", "peaceful");
	set("max_qi",8000);
	set("max_jing",2000);
	set("neili",3000);
	set("max_neili",3000);
	set("jingli",2800);
	set("eff_jingli",2800);
	set("jiali",80);
	set("score", 20000);

	set_skill("force", 350);
	set_skill("dodge", 350);
	set_skill("parry",350);
	set_skill("whip",350);
	set_skill("lingshe-bianfa", 350);
	set_skill("youlong-shenfa",350);
	set_skill("dulong-dafa",350);
	set_skill("shenlong-yaoli",180);
    set_skill("leg", 350);

	set_skill("shenlong-tuifa", 350);
	map_skill("leg", "shenlong-tuifa");

	map_skill("force", "dulong-dafa");
	map_skill("dodge", "youlong-shenfa");
	map_skill("parry","huagu-mianzhang");
	prepare_skill("leg", "shenlong-tuifa");

	create_family("神龙教",3, "掌门使");
    set("inquiry", ([
            "神龙教" : "哈哈！我们神龙教最是逍遥自在。\n",
            "雄黄酒" : (: ask_jiu :),
			"训蛇任务" : (: ask_xunshe :),
			"放弃" : (: ask_fangqi :),
        ]));
	setup();
	carry_object("/d/sld/npc/obj/bcp")->wear();
}

void attempt_apprentice(object ob)
{
	mapping myfam;
	object ob1;

	myfam = (mapping)ob->query("family");
	if(!myfam || myfam["family_name"] != "神龙教"){
		if(ob->query("app/sld")!=1){
			command("say 好吧，我就收下你做我的弟子。");
			ob->set("app/sld",1);
			command("recruit " + ob->query("id"));
			tell_object(ob, "你把这碗雄黄酒喝了，就可以不怕蛇咬了。\n");
			ob1 = new("/d/sld/npc/obj/xionghuangjiu");
			if(!ob1->move(ob))
				ob1->move(environment(ob));
			tell_room(environment(ob), "张淡月给了"+ob->name()+"一碗雄黄酒。\n");
		}
		else{
		command("say 神龙教不收你这种叛教之人！你走吧!");
		}
	}
}

int recognize_apprentice(object ob)
{
	mapping myfam;
	object hw;

	myfam = (mapping)ob->query("family");
	if(!myfam || (myfam["family_name"] != "神龙教")) return 0;
	if(!ob->is_apprentice_of(this_object())) return 0;
	if(myfam 
		&& (myfam["family_name"] == "神龙教")
		&&(ob->query("shen",1) >0))
	{
		command("say 哼！你竟然敢和白道中人搞在一起，是不是不想活了？！去黑屋好好反省反省吧！");
		if(!objectp(hw=find_object("/d/sld/npc/obj/heiwu")))
			hw=load_object("/d/sld/npc/obj/heiwu");
		ob->set("in_heiwu",time());
		ob->move(hw);
		return 0;
	}
	return 1;
}

string ask_jiu()
{
        object ob, me = this_player();

	if (me->query("family/family_name") != "神龙教")
                return "去找别人吧，我可不告诉你！";
        if (me->query("xionghuangjiu"))
                return "你好象已经喝过雄黄酒了，再喝不怕喝死你？";

        if (present("xionghuang jiu", me))
                return "你身上还有雄黄酒吧。";

        ob = new("/d/sld/npc/obj/xionghuangjiu");
        ob->move(me);
        message_vision("张淡月递给$N一碗雄黄酒。\n", me);
        return "你把这碗雄黄酒喝了，就不怕蛇咬了。";
}


string ask_xunshe()
{
        object ob, me;
		me= this_player();
		
		if (me->query("family/family_name") != "神龙教")
                return "去找别人吧，我可不告诉你！";
		if (me->query_temp("sld/qushe/start"))
                return "你好象刚才已经问我了？\n";
		if (me->query_condition("job_busy")||me->is_busy()||me->query_condition("sldjob_xunshe"))
                return "你现在忙于工作中,待会再来？\n";
        if (present("zhu di",me))
                return "你身上还有竹笛，为啥不赶快去。\n";
		if (me->query("job_name")=="神龙训蛇")
                return "你刚做完神龙训蛇任务,待会再来？\n";
        if (present("cuizhu di",me))
			return "你身上不是有一只翠竹笛么？？\n";
		
		ob = new("/d/sld/npc/obj/zhudi");
        ob->set("owner",me->query("id"));
		ob->move(me);
        message_vision(HIG"张淡月递给$N一个翠竹笛，说道，“神龙教训蛇是极为重要的任务，你既然想做去吧”。\n"NOR, me);
		command("say 不用使用用look zhudi来看使用说明！\n");
		command("say 最好在毒蛇经常出没的区域去训蛇，否则你再怎么吹也招不来蛇！\n");
        message_vision(HIY"张淡月对$N说道，“这是驱蛇曲调的旋律，你需要在五分钟完成任务，切记！”。\n"NOR, me);

		me->set_temp("sld/qushe/start",1);

        return "驱蛇术只能由此获得，你要珍惜这机会,别为此耽误了以后的大事。\n";
}
//接受物品
int accept_object(object who, object ob)
{
	
	int sum,gold,getshen,jobs;
	object sil;
	sum=40+random(10);
	jobs=who->query("job_time/神龙训蛇");

	if (ob->query("taskok")
		&& ob->query("owner")==who->query("id")
		&& who->query_temp("sld/qushe/taskok")		
		&& ob->query("id")=="cuizhu di")
	{
		getshen=-1;
		gold=1+random(1);				
		
		who->set("job_name","神龙训蛇");			
		who->apply_condition("job_busy",3);		
		who->delete_temp("sld/qushe");
		who->delete_temp("sld");
		command("thumb "+who->query("id"));

		tell_object(who,RED"\n张淡月点了点头，将"+ob->query("name")+RED+"收入怀中！\n"NOR);
		command("say 很好，"+who->query("name")+"，既然你把任务完成了，我就应该奖励你！\n");
		tell_object(who,GRN"\n张淡月拿出门派记录本，给了"+who->query("name")+HIY+chinese_number(gold)+GRN"点的门派功绩的奖励！\n"NOR);
		who->add("party/gongji",gold);
		tell_object(who,GRN"\n张淡月随手拿出些银子，递给"+who->query("name")+HIY+chinese_number(sum)+GRN"两白银，拿去喝酒去吧！\n"NOR);

		sil=new("clone/money/silver");
		sil->set("set_amount",gold);
		sil->move(who);

		//预留入门提示接口
		
		if (random(jobs)>1000
			&&random(who->query("kar"))>26 
			&& !who->query("quest/sld/dichuan"))
		{
			
				message_vision(HIC"张淡月在远处对$N竖起了大拇指，说道，“经过考验，我接受$N为大神龙核心嫡传弟子”\n"NOR,who);
				who->set("title","神龙教嫡传弟子");
				who->set("quest/sld/dichuan",1);
		}
			
		TASKREWARD_D->get_reward(who,"神龙训蛇",getshen,0,0,3+random(4),0,0,0,this_object());
		who->set("job_name", "神龙训蛇");
	//	who->delete_temp("sldjob");
		who->apply_condition("job_busy",3);
		
		if (random(jobs)>10000
			&&random(who->query("kar"))>27
			&& jobs % 20 == 0
			&& who->query_skill("dulong-dafa",1)>350
			&& !who->query("quest/sld/dldf/dulong/start")
			&& who->query("quest/sld/dichuan"))
		{
			
				message_vision(HIY"张淡月看着$N一眼，不紧不慢地说道，“方才教主夫人跟我说了，让我通知你去找她说有要事！”\n"NOR,who);
				
				who->set("quest/sld/dldf/dulong/start",1);
		}		
		destruct(ob);
		return 1;
	}

}
string ask_fangqi()
{
	object ob;
	object me=this_player();
	if (me->query_temp("sld/qushe/start"))
	{
		command("say 既然你有难度，做不了也没什么，下去歇息会吧！\n");
		me->delete_temp("sld");
		me->apply_condition("job_busy",5);
		me->apply_condition("sldjob_xunshe",5);
		if (objectp(ob=present("cuizhu di",me)))
		{
			destruct(ob);
		}
		return "现在的新弟子真是一代不如一代了！\n";
	}
	command("say 没事不要来骚扰我！\n");
	return "哼！\n";

}