// yinggu.c 瑛姑 鬼谷算数
// created by campsun 2003/12/2
//是否处于鬼谷算术状态的判断为query_temp("ggs/started") 在做相关修改的时候要特别注意。
//LinuX@SJ 2004.2.28


#include <ansi.h>
inherit NPC;

int ask_ggs();
int ask_ggso();
int ask_duan();
int ask_nqg();
int ask_nqgjj();
//int do_answer(string arg);
int do_huida(string arg);
int ask_fox();
int ask_zhou();
int accept_object(object who, object obj);

void create()
{
	seteuid( getuid() );
        set_name("瑛姑", ({ "ying gu","ying"}));
        set("nickname",HIW"鬼谷算术专家"NOR);
        set("title",HIR"神算子"NOR);
        set("gender", "女性");
        set("age", 35);
        set("long", "她是个看起来似乎有几分美貌的女子。但是确是一头白发如雪，两只眸子里都是幽怨和感伤。\n");
        set("attitude", "peaceful");
        set("shen_type", 0);
	    set("no_get","瑛姑对你而言太重了。");
        set("str", 30);
        set("int", 35);
        set("con", 30);
        set("dex", 26);
	set("per", 28);
	set("quest/dali/ailao/pass",1);
	
	set("jiali",200);
	set_skill("force", 450);
	set_skill("huntian-qigong", 450);
	set_skill("qiantian-yiyang", 450);
	set_skill("dodge", 450);
	set_skill("niqiu-gong", 450);
	set_skill("parry", 450);
	set_skill("strike", 450);
	set_skill("qingyan-zhang", 450);
	set_skill("sword", 450);
	set_skill("duanjia-jianfa", 450);
	set_skill("cuff", 450);
	set_skill("kongming-quan", 450);
	set_skill("literate",400);
	set_skill("qimen-bagua", 200);
	


	map_skill("force", "qiantian-yiyang");
	map_skill("dodge", "niqiu-gong");
	map_skill("strike", "qingyan-zhang");
	//map_skill("strike", "qingyan-zhang");
	map_skill("parry", "duanjia-jianfa");
	map_skill("sword", "duanjia-jianfa");
	map_skill("cuff", "kongming-quan");
	prepare_skill("strike", "qingyan-zhang");

	set("chat_chance_combat", 100);
	set("chat_msg_combat", ({
		(: perform_action, "strike.qingyan" :),
		(: perform_action, "strike.piaomiao" :),
		(: exert_function, "yiyang" :),
		(: exert_function, "liao" :),
	}));

	set("combat_exp", 10500000);
	set("max_qi", 35000);
	set("max_jing", 8000);
	set("neili", 25000);
	set("max_jingli", 8000);
	set("eff_jingli", 8000);
	set("max_neili", 25000);


    set("inquiry", ([
                "rumors" : "这道题怎么那么难算啊？不知道上次来求医的小姑娘什么时候才能再来。",
                //"周伯通" : "听说他被困在桃花岛上，我苦心研究鬼谷算数就是为了能去救他。",
                "四张机" : "四张机，鸳鸯织就欲双飞....",
                "鬼谷算术" : (: ask_ggs :),
                "开始" 	: (: ask_ggs :),
                "start" : (: ask_ggs :),
                "结束" 	: (: ask_ggso :),
                "休息" 	: (: ask_ggso :),
                "over" 	: (: ask_ggso :),
				//黯然
				"九尾灵狐" : (: ask_fox :),
				"周伯通" : (: ask_zhou :),
				//杀人
				//"段皇爷" : (: ask_duan :),
				//"泥鳅功" : (: ask_nqg :),
				"泥鳅功绝技" : (: ask_nqgjj :),
        ]));

        setup();
		carry_object("clone/weapon/bishou")->wield();
        carry_object(ARMOR_D("pink_cloth"))->wear();

}
void init()
{
	add_action("do_huida","answer");

}
//承接史家兄弟捉灵狐捉不住
int ask_fox()
{
	object me=this_player();
	if (me->query_temp("quest/shendiao/大雪风陵渡/askheal"))
	{
		command("say 你若真想要这灵狐之血，你就替我去把周伯通叫来！\n");
		command("say 只要他来了，我就给你灵狐之血。\n");
		command("say 否则，我宁可和这灵狐玉石俱焚！\n");
		me->set_temp("quest/shendiao/大雪风陵渡/askyingfox",1);
	}else {
		command("九尾灵狐乃是我私人的宠物，凭什么给你？\n");
	}
	return 1;

}
//找到老顽童后可以去捉狐狸并解密泥鳅功
int ask_zhou()
{
	object me=this_player();
	if (me->query_temp("quest/shendiao/大雪风陵渡/zhouok"))
	{
		command("say 瑛姑听闻你的诉说，激动的眼泪横流！\n");
		command("say 不断在骂道，“这个冤家，这个冤家！”。\n");
		command("thank "+me->query("id"));
		command("blush");
		command("say 既然你为我办成了这件事，我就把这灵狐的捉法告诉你。\n");
		command("say 这九尾灵狐乃罕见之物，也不用杀死，就采集它心头的几滴鲜血即可。\n");
		command("say 前一个阶段，我将灵狐放养在襄阳城外的树林中。\n");
		me->set_temp("quest/shendiao/大雪风陵渡/yingok",1);
		me->set("quest/shendiao/大雪风陵渡/yingok",1);

	}else
	{
		command("say 你连周伯通都请不来，到我这里作甚？\n");
	}
	return 1;

}

int ask_ggs()
{
	object me,ob;
	int this_week = time()/86400/7;
	ob = this_object();
	me = this_player();
	
	
	if (me->query("registered")!=3)
	{
		tell_object(me, "对不起啊，目前鬼谷算术只对贵宾VIP用户开放强化学习功能。\n");
		return 1;
	} 
	
	if(!me->query("ggs/last_week") || me->query("ggs/last_week")=="" || me->query("ggs/last_week")!=this_week)
	{
		me->set("ggs/last_week", this_week);
		me->set("ggs/started",0);
		me->set("ggs/start_time","");
		me->set("ggs/over_time","");
		me->set("ggs/left_time",10*3600);
	}

	//For all Bug By Ciwei@SJ
	while(me->query("ggs/left_time")>10*3600)
		me->add("ggs/left_time",-10*3600);

	if(me->query("ggs/left_time") < 1)
	{
		command("say 你虽然天资聪慧，但是贪多嚼不烂，不能再冒进了，请下周再来询问吧。");
		return 1;
	}
	if(me->query("ggs/started")==1)
	{
		if(!me->query_temp("ggs/started"))
		{
			tell_object(me, "你先要问我休息，才能再开始使用鬼谷算术。\n");
		}
		else
		{
			tell_object(me, "你不是正在研习修炼鬼谷算术中么？还不快点抓紧时间……\n");
			command("kick " + me->query("id"));
		}
		return 1;
	}
	
	me->set("ggs/started",1); //使用状态标记
	me->set_temp("ggs/started",1); //使用状态标记
	me->set("ggs/start_time",time()); //使用状态标记
	
	me->apply_condition("guigushu",1); //这个condition 不会自动减少
	
	command("say 鬼谷算术，是我这些年精心研究的修心妙法，若能参悟，可以加倍提高学习领悟的能力。");
	command("say 不过鬼谷算术博大渊深，甚劳心神，每周最多也就应用十个小时吧。");
	command("look " + me->query("id"));
	command("say 现在是 "+ CHINESE_D->chinese_date(time(),1) + "。");
	command("say 你本周还可以使用鬼谷算术"+CHINESE_D->chinese_time(me->query("ggs/left_time"))+"，现在开始计时了。");
	log_file( "quest/ggs",sprintf("%s(%s)在第%d周开始鬼谷算术,剩:%s.\n",
			me->name(),
			me->query("id"),
			this_week,
			CHINESE_D->chinese_time(me->query("ggs/left_time"))
			));
	
return 1;
}

int ask_ggso()
{
	object me,ob;
	int user_time;
	//int an_hour = 60*60*60;
	int this_week = time()/86400/7;
	ob = this_object();
	me = this_player();
	
	if (me->query("registered")!=3)
	{
		tell_object(me, "对不起啊，目前鬼谷算术只对贵宾VIP用户开放强化学习功能。\n");
		return 1;
	}
	if(me->query("ggs/started")!=1)
	{
		command("say 还没有开始就要休息……");
		command("pig " + me->query("id"));
		return 1;
	}
	if(me->query_temp("ggs/started")!=1)
	{
		command("say 你是不是没问休息就下线了？结束时间就按照你上次下线时间算吧。");
		me->set("ggs/over_time",FINGER_D->get_last_on(me->query("id")));		
	}
	else
	{	
		me->set("ggs/over_time",time());	
	}
	
	user_time=ABS((int)me->query("ggs/over_time")-(int)me->query("ggs/start_time"));
	command("say 是啊，劳逸结合，读书领悟久了，是该休息休息。");
	command("look " + me->query("id"));
	
	command("say 你的鬼谷算术开始时间是：" + CHINESE_D->chinese_date((int)me->query("ggs/start_time"),1) + "。");
	command("say             结束时间是：" + CHINESE_D->chinese_date((int)me->query("ggs/over_time"),1) + "。");
	command("say 这次你一共修炼了：" + CHINESE_D->chinese_time(user_time)+"。");
	me->set("ggs/left_time",me->query("ggs/left_time") - user_time);

	log_file( "quest/ggs",sprintf("%s(%s)在第%d周结束ggs,剩:%s,用:%s.\n",
			me->name(),
			me->query("id"),
			this_week,
			CHINESE_D->chinese_time(me->query("ggs/left_time")),
			CHINESE_D->chinese_time(user_time)
			));



	if (me->query("ggs/left_time") < 0 ) //防止bug
		me->set("ggs/left_time",0);
		
	if (me->query("ggs/left_time")) 	
		command("say 你本周还可以使用鬼谷算术"+CHINESE_D->chinese_time(me->query("ggs/left_time"))+"。");
	else
		command("say 你的鬼谷算术时间用完了，下周再来吧。");
	
	me->set_temp("ggs/started",0);
	me->set("ggs/started",0);
	me->set("ggs/start_time","");
	me->set("ggs/over_time","");	
	
	me->clear_condition("guigushu"); //清除了


return 1;	
}

//不死
int accept_fight(object ob){
        command("say 这位"+RANK_D->query_respect(ob)+"，武功是用来防身的，不是好斗滴！");
}
int hit_ob(object ob)
{
        command("say 这位"+RANK_D->query_respect(ob)+"，武功是用来防身的，不是好斗滴！");
}


void kill_ob(object ob)
{
        ob->remove_killer(this_object());
        remove_killer(ob);
        command("swear");
}

void unconcious()
{
	message_vision(YEL"$N突然运用鬼谷之术，全身发出异样色彩，有愈战愈勇之势。\n"NOR, this_object());
        reincarnate();
        add("str",10); //越来越勇，^_^
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
        clear_conditions_by_type("poison");
}

void die()
{
        unconcious();
}

//解密泥鳅功

int ask_duan()
{
	command("say 哼，跟我替他作甚？");
	command("angry ");
	command("say 四张机，鸳鸯织就欲双飞，可怜未老头先白，春波碧草，晓寒深处，相对浴红衣。\n");
	command("cry ");
	command("consider ");
	this_player()->set_temp("nqg/askying",1);
	return 1;
}
int ask_nqg()
{
	object me,ob;	
	ob = this_object();
	me = this_player();
	
	if (!me->query_temp("nqg/askying"))
	{
		return notify_fail("瑛姑不愿意搭理你，嫌你太笨了！\n");
	}
	if (me->query_skill("force",1)<450)
		return notify_fail("你的基本内功太弱，不适宜去为我完成这个任务。\n\n\n");
	command("say 这门神功乃是我在泥潭中苦修多年方才习得，端的是厉害无比。\n\n\n");
	command("say 想学这门神功可以，但你必须要替我杀一个人去。你敢么？\n\n\n");
	command("say 这个人罪大恶极，你若杀了他我就教你这门神功。\n\n\n");
	write(HIG"瑛姑想让你替他杀一个人，你愿意(yes)还是不愿意(no)？\n");
	add_action("do_huida","answer");
	return 1; 
}
int do_huida(string arg)
{
	object me=this_player();
	if (!arg) return notify_fail("你回答什么？");
	if (arg=="yes")
	{
		command("say 好吧，既然你愿意就替我到桃源县，一所石屋内杀了一个老和尚,提头来见！\n");
		command("say 一路凶险，他有四个弟子都很坏，每一个人都有自己的绝技，你要小心了。！\n");
		me->set_temp("nqg/askyingok",1);
		me->delete_temp("nqg/askying");
		return 1;
	}else if(arg=="no")
	{
		command("say 好吧，既然你不愿意去杀了段智兴，那就替我去把老顽童找来，否则休想学习我这门神功！\n");
		me->delete_temp("nqg/askying");

		return 1;
	}
	
}

int accept_object(object who, object obj)
{
	
	if (who->query_temp("nqg/killyideng")&& obj->query("id")=="shouji"&&obj->query("name")=="一灯大师的首级")
	{
		who->delete_temp("nqg/killyideng");
		//标记
		who->set("quest/shediao/nqg/over",1);
		tell_object(who,HIY"瑛姑见到这枚一灯大师的首级，即咬牙切齿，又不胜悲喜，似乎陷入疯狂状态。\n"NOR);
        command("laugh ");
		command("chat 段智兴你也有今天！");
		command("chat 我苦命的孩子啊，你的仇恨妈妈替你报答了！");
		command("chat 感谢"+who->query("name")+"替我伸冤！");

		obj->move(this_object());
		destruct(obj);
		message_vision(HIC"瑛姑顺手从口袋里掏出一个金锭给$n，说道，”拿去喝酒去吧“\n"NOR,who);
		who->add("combat_exp",random(500));
		who->add("shen",-2000000);
		new("clone/money/gold")->move(this_object());
		message_vision(HIC"$N的经验增加了！\n"NOR,who);
		command("give "+who->query("id")+" 1 gold");
		return 1;
	}

}

int ask_nqgjj()
{
	object me,ob;
	int j,i,k;
	ob = this_object();
	me = this_player();
	if (!me->query("quest/shediao/nqg/over") && !me->query("quest/shendiao/大雪风陵渡/healover"))
	{
		command("say 你太懒了，不愿意搭理你，想不劳而获的人都是可耻的。\n");
		return 1;
	}

	if (me->query_skill("force",1)<450)
	{
		command("say 你的基本内功太弱，不适宜去为我完成这个任务。\n");
		return 1;
	}
	if (me->query("quest/shediao/nqg/pass"))
	{
  		 command("nod "+me->query("id"));
		 if (me->query_skill("niqiu-gong",1)<450)
		 {
			message_vision(HIC"$N满脸谄笑向$n请教关于泥鳅功的知识。\n"NOR,me,this_object());
			me->improve_skill("niqiu-gong",me->query_int());
			return 1;
		 }else
			message_vision(HIC"$n对$N冷冷地说道，我就教到这里了，剩下的就靠你自己去练习了!\n"NOR,me,this_object());
		 command("say 你已经彻底领悟了这门绝学，在这里啰嗦什么？\m");
		 return 1;
    }
	if (time()-me->query("quest/shediao/nqg/time")<86400)
	{
  		command("nod "+me->query("id"));
		command("say 你来的也太勤快了，烦不烦！？\n");
		return 1;
    }
    j=random(me->query("kar"));
	k=random(25);
	if(me->query("m-card-vip")) k =  20;
    if(me->query("y-card-vip")) k =  18;
    if(me->query("buyvip"))     k =  15;
	
	
	i=random(k);
	if (me->query("kar")<31
		&&j>27
		&&i<2)
	{
       message_vision(HIC"\n\n$N在瑛姑的指点下，终于将这泥鳅功融会贯通，彻底领悟，威力大增。\n"NOR,me);
	 
	   log_file("quest/niqiugong",sprintf("%s(%s) 从瑛姑处领悟泥鳅功绝技。随机富源j：%d。随机数i：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("quest/shediao/nqg/fail"),me->query("combat_exp"),me));
	   me->set("quest/shediao/nqg/pass",1);
	   me->improve_skill("niqiu-gong",10);
	   command("congra "+me->query("id"));
	   command( "say 恭喜你完成了泥鳅功谜题!\n");
	   return 1;
	}
	else
	{
		message_vision(HIY"\n\n$N虽然听瑛姑讲解了这泥鳅功的奥秘，但对于如何使用的劲力法门一时之间却是难以理解。\n"NOR,me);
		message_vision(HIG"\n\n$N感觉就差一层窗户纸，仿佛就在眼前，但却咫尺天涯。\n"NOR,me);
		log_file("quest/niqiugong",sprintf("%8s%-10s笨手笨脚，资质驽钝，解密泥鳅功失败，尚须努力。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("quest/shediao/nqg/fail"),me->query("combat_exp"),me));
		me->add("quest/shediao/nqg/fail",1);
		me->set("quest/shediao/nqg/time",time());
		command( "say 真够笨的，解密泥鳅功失败!\n");
	    return 1;
	}
	
}