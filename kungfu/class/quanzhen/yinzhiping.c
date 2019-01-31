#include <ansi.h>;
#include <job_mul.h>

inherit NPC;
inherit F_MASTER;
int ask_shouwei();
int ask_over();
int ask_fangqi();
int ask_lilian();
int check(object ob);
int ask_qingjiao();
int do_copyy(object me,object ob);

//"马光佐"
string* zhuxiong=({"马光佐","霍都","达尔巴","尼摩星","潇湘子","尹克西","公孙止"});
string* name=({"/d/quanzhen/shijie1","/d/quanzhen/shijie2","/d/quanzhen/shijie3",
"/d/quanzhen/shijie4","/d/quanzhen/shijie5","/d/quanzhen/shijianyan","/d/quanzhen/banshanting",
"/d/quanzhen/shijie8","/d/quanzhen/shijie9","/d/quanzhen/guanritai","/d/quanzhen/jiaobei",
"/d/quanzhen/shijie6","/d/quanzhen/shijie7","/d/quanzhen/dajiaochang","/d/quanzhen/fangzhenqiao",
"/d/quanzhen/damen","/d/quanzhen/datang1","/d/quanzhen/datang2","/d/quanzhen/datang3",
"/d/quanzhen/baihuagu","/d/quanzhen/baihuagurukou","/d/quanzhen/cetang","/d/quanzhen/chanfang1",
"/d/quanzhen/chanfang2","/d/quanzhen/chanfang3","/d/quanzhen/chufang","/d/quanzhen/cundaota1",
"/d/quanzhen/cundaota2","/d/quanzhen/cundaota3","/d/quanzhen/cundaota4","/d/quanzhen/diziju",
"/d/quanzhen/guangning","/d/quanzhen/guozhendian","/d/quanzhen/houshan","/d/quanzhen/houtang1",
"/d/quanzhen/houtang2","/d/quanzhen/houtang3","/d/quanzhen/huajing1","/d/quanzhen/huajing2",
"/d/quanzhen/huajing3","/d/quanzhen/huizhentang","/d/quanzhen/jingxiushi","/d/quanzhen/laojundian",
"/d/quanzhen/liangong","/d/quanzhen/maocaowu","/d/quanzhen/nairongdian","/d/quanzhen/piandian",
"/d/quanzhen/pingdi","/d/quanzhen/qingjing","/d/quanzhen/rongwutang","/d/quanzhen/shandong",
"/d/quanzhen/shantang","/d/quanzhen/shiweishi","/d/quanzhen/tongtiandian","/d/quanzhen/wanwutang",
"/d/quanzhen/wuchang1","/d/quanzhen/wuchang2","/d/quanzhen/shulin1","/d/quanzhen/shulin2",
"/d/quanzhen/shulin3","/d/quanzhen/shulin4","/d/quanzhen/shulin5","/d/quanzhen/shulin6",
"/d/quanzhen/xianzhentang","/d/quanzhen/xiaohuayuan1","/d/quanzhen/xiaohuayuan2","/d/quanzhen/xiaohuayuan3",
"/d/quanzhen/xiaolu1","/d/quanzhen/xiaolu2","/d/quanzhen/xiaolu3","/d/quanzhen/yaojishi",
"/d/quanzhen/yuanshidian","/d/quanzhen/yuzhengong"});
void create()
{
        set_name("尹志平", ({"yin zhiping", "yin"}));
        set("gender", "男性");
        set("class", "taoist");
        set("nickname", HIM"清和真人"NOR);
        set("age", 24);
        set("long",
                "他是丘处机的得意大弟子尹志平，他粗眉大眼，长的有些英雄气\n"
                "概，在全真教第三代弟子中算得上年轻有为。身材不高，眉宇间\n"
		"似乎有一股忧郁之色。长的倒是长眉俊目，容貌秀雅，面白无须，\n"
		"可惜朱雀和玄武稍有不和。\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 28);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
		set("no_get","尹志平对你而言太重了。");
	    set("no_bark",1);
		set("job_npc", 1);


        set("qi", 15000);
        set("max_qi", 15000);
        set("jing", 6000);
        set("max_jing", 6000);
        set("neili", 20000);
        set("max_neili", 20000);
        set("jiali", 200);
		set("jingli",6000);
		set("max_jingli",6000);
        set("eff_jingli", 6000);

        set("combat_exp", 8200000);
		set("quest/qz/xtg/daojue/pass",1);
		set("quest/qz/jyg/shangtianti/pass",1);

        set_skill("force", 420);
        set_skill("xiantian-gong", 420);
        set_skill("sword", 400);
        set_skill("quanzhen-jianfa", 400);
        set_skill("dodge", 400);
        set_skill("jinyan-gong", 400);
        set_skill("parry", 400);
        set_skill("leg", 400);
        set_skill("yuanyang-lianhuantui", 400);
        set_skill("literate",160);
        set_skill("taoism",200);
        set_skill("tiangang-beidouzhen",400);
        set_skill("strike",400);
        set_skill("haotian-zhang", 400);
        set_skill("tiangang-beidouzhen", 400);
        set_skill("jinguan-yusuojue", 400);

		map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("leg", "yuanyang-lianhuantui");
        map_skill("strike", "haotian-zhang");

		prepare_skill("strike", "haotian-zhang");
		prepare_skill("leg", "yuanyang-lianhuantui");

        create_family("全真教", 3, "弟子");
		
		set("chat_chance_combat", 65);
		set("chat_msg_combat", ({
			(: perform_action, "sword.ding" :),
			(: perform_action, "sword.sanqing" :),
			(: perform_action, "sword.lian" :),
			(: exert_function, "daojue" :),
		//	(: exert_function, "daojue" :),
		}));

        set("inquiry", ([
                "全真教"   :  "我全真教是天下道家玄门正宗。\n",
				"小龙女"   :  "惊鸿一瞥，惊为仙人，古墓花丛，旖旎仙境。\n",

				"守卫古墓" : (: ask_shouwei :),
				
				"放弃" : (: ask_fangqi :),
				"下山历练" : (: ask_lilian :),
				//"清剿主凶" : (: ask_qingjiao :),
        ]) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

void attempt_apprentice(object ob)
{
      if (ob->query("gender")!="男性")
       {
		   command("say 你一个女人家来拜我为师，难道是有什么企图不成？！\n");
		   command("say 我全真一脉，最终全在内丹修为上，关于坤丹的修炼我不擅长！\n");
		   command("say 你还是去寻找下师叔清静散人孙不二门下弟子程瑶迦师妹，看他是否收你？\n");
		   return ;

       }
	   if ((int)ob->query("shen") < 1200000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在德行方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(1.2m)");
               return;
       }
	   if (ob->query("party/gongji") < 1500) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在教派功绩方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(需要1500点门派贡献值)\n");
               return;
       }
	   if (!ob->query("quest/qz/dichuan"))
	   {
		       command("say 你非我门中嫡传弟子，来此作甚？");
              return;

	   }
 	   if (ob->query_skill("xiantian-gong",1) < 250) {
               command("say 我全真教一身功夫全在先天功，你先天功不足250，来此作甚？。");
               return;
       }
	   if (ob->query_skill("yuanyang-lianhuantui",1) < 250) {
               command("say 你的鸳鸯连环腿不足250，来此作甚？。");
               return;
       }
	   if (ob->query_skill("haotian-zhang",1) < 250) {
               command("say 你的昊天掌不足250，来此作甚？。");
               return;
       }		
       command("say 好吧，贫道就收下你了。");
       command("recruit " + ob->query("id"));
       ob->set("class","taoism");
	   return;

}
int ask_shouwei()
{
	object me=this_player();
	//object ob=this_object();
	if (me->query("family/family_name")!="全真教")
	{
		command("say "+me->query("name")+",你不是我教中弟子，来此作甚？\n");
		return 1;
	}
	if (me->query_skill("xiantian-gong",1)<100)
	{
		command("say "+me->query("name")+",你的先天功太弱了，来此作甚？\n\n");
		return 1;
	}
	
	if (me->query("combat_exp") < 150000)
	{
		command("say "+me->query("name")+",你的实战经验不足150k，还是先去奋斗吧！\n\n");
		return 1;
	}
	
	if(me->query("job_name") == "守卫古墓") 
	{
        command("say "+me->query("name")+",你刚结束守卫古墓，还是先休息一会吧。");
	    return 1;

	}
	if(me->query("shen") <0) 
	{
        command("say "+me->query("name")+",你是邪魔外道之辈，胆敢来全真教撒野，难道是嫌弃自己命太硬了么？");
	    return 1;

	}
	if (me->query_temp("qz/shouwei/target")&&me->query_temp("qz/shouwei/answeryes"))
	{
		command("say 我不是让你去杀"+me->query_temp("qz/shouwei/target")+"了么？你怎么还不去？!\n");
		return 1;
	}
	if (me->query_temp("qz/shouwei"))
	{
		command("say "+me->query("name")+",你上一次任务还没完成呢。\n");
	    return 1;
	}
	if (me->query_condition("job_busy"))
	{
		command("say "+me->query("name")+",你正在任务繁忙中，还是先休息一会吧。\n");
	    return 1;
	}
	command("say "+me->query("name")+",今日闻听消息，有一批不明人士正在终南山脚下集结。\n");
	command("say 据可靠消息，是有人企图向古墓派龙姑娘求婚。\n");
	command("blush ");
	command("say 祖师曾有严令，令我弟子要保护古墓不得侵犯。\n");
	command("say 我看中天门乃是去往古墓的必经之路，"+me->query("name")+"，你守卫在哪儿，以防有人来此捣乱。\n");
	command("say "+me->query("name")+"，这次任务比较艰巨，阻击完成后提他人头见我！\n");

	me->apply_condition("job_busy",20);
	me->apply_condition("qzsw_job_busy",20);
	
	//删除标记 否则会出bug
	me->delete_temp("qz/shouwei/twice");

	me->set_temp("qz/shouwei/askyin",1);
	return 1;

}

int accept_object(object who, object ob)
{
	object sil;
	string arg;
	int gold,getshen,jobs;
	arg=zhuxiong[random(sizeof(zhuxiong))];
	
	jobs=who->query("job_time/守卫古墓");

	gold=30+random(20);
	//霍都的人头
	if (ob->query("kill_by")==who
		&&ob->query("id")=="shouji"
		&& who->query_temp("askyin/xiashan")
		&& ob->query("victim_id")=="huo du")
	{
		command("say "+who->query("name")+"好，非常不错，你替我杀了霍都这个奸贼！\n");
		command("say 这下龙姑娘就可以安心弹琴了！\n");
		command("say 你看来着实不错，既然如此，我就提醒你到存道塔去寻找下那本《同归剑法》入门篇武技\n");
		command("say 那本秘籍是七位师傅所创，本来为了预防本门厉害的对头欧阳锋所创！\n");
		command("say 这们功夫在短期内可以大幅提升威力，但缺点是防守不足，切记切记！\n");
		command("say 后期的飞跃可以和全真剑法结合在一起，其中关键和诀窍你还需向丘真人请教！\n");
		who->set("quest/qz/tgjf/pass",1);
		who->delete_temp("askyin");
		message_vision(HIY"$N获得了在存道塔观看同归剑法的机会！\n"NOR,who);
		return 1;
	}
	if (ob->query("kill_by")==who
		&& who->query_temp("qz/shouwei/guard")
		&& ob->query("id")=="shouji")
	{
	
		getshen=1;
		//奖励
	//	TASKREWARD_D->get_reward(me,"全真采药",getshen,0,0,random(2)-1,0,0,0,this_object());
		if (ob->query("name")==who->query_temp("qz/shouwei/target")+"的首级"
			&&who->query_temp("qz/shouwei/answeryes"))
		{
			command("hoho ");
			
			who->set_temp("qz/shouwei/twice",1);
		}

		sil=new("clone/money/silver");
		sil->set("set_amount",gold);
		sil->move(who);
		
		who->set("job_name","守卫古墓");
	//	who->add("job_time/全真采药",1);
		
		who->apply_condition("job_busy",3);

		who->add("party/gongji",1+random(1));
		
		
		tell_object(who,RED"\n尹志平随手将"+ob->query("name")+RED+"甩入身后的万丈深渊！\n"NOR);
		destruct(ob);

		command("say 很好，"+who->query("name")+"，既然你把这批淫贼给杀了，我就给你点下酒钱！\n");

		tell_object(who,HIY"\n尹志平丢给"+who->query("name")+HIY+chinese_number(gold)+"两白银的奖励！\n"NOR);

		//预留入门提示接口
		if (random(who->query("job_time/守卫古墓"))>1000
			&&random(who->query("kar"))>26 
			&& !who->query("quest/qz/dichuan"))
		{
			
				message_vision(HIC"尹志平在远处对$N竖起了大拇指，说道，“经过考验，我接受$N为大全真核心嫡传弟子”\n"NOR,who);
				who->set("title","全真教嫡传弟子");
				who->set("quest/qz/dichuan",1);
		}
		who->set("job_name", "守卫古墓");

		//随机去杀一些核心骨干
		if (!who->query_temp("qz/shouwei/target")
			&&who->query("combat_exp")>4500000
			//&&!random(6))
			&&who->query("quest/qz/dichuan"))
		{
			message_vision(HIY"尹志平在$N耳边小声说道，“事情已经明了，此次主持袭扰龙姑娘的主凶是"HIR+arg+HIY"这恶贼！”\n"NOR,who);
			
			
			who->set_temp("qz/shouwei/target",arg);
			message_vision("尹志平要你去杀"+arg+",你如果愿意就输入(answer yes ),不愿意就输入(answer no)！\n",who);
			add_action("do_answer","answer");
			return 1;
		}
				//做俩次首先奖励exp

		if (who->query_temp("qz/shouwei/twice") && who->query("quest/qz/dichuan") && !QUEST_D->queryquest(who,"qz/qzjf/lianhuan/start"))
		{
			command("say "+who->query("name")+"好，非常不错，你做的很好！\n");
			TASKREWARD_D->get_reward(who,"守卫古墓",getshen,0,0,3+random(2),0,0,0,this_object());
			//会带出三连环提示
			
			if (QUEST_D->job_questing(who,1,"qz/qzjf/lianhuan/start","守卫古墓",4000,"不计算",-1,""))	               			
			{
				message_vision(HIY"尹志平对$n说道，“我前几日遗漏了一本全真剑法秘籍，上面记载了关于三连环的法门”\n"NOR,who);
				message_vision(HIR"尹志平对$n说道，“你替我到山下密林花丛一带去找找，看能否找到？”\n"NOR,who);
				//who->set("quest/qz/qzjf/lianhuan/start",1);
			}

		}
		else TASKREWARD_D->get_reward(who,"守卫古墓",getshen,0,0,1+random(2),0,0,0,this_object());
		
		who->delete_temp("qz/shouwei");
		who->delete_temp("qz");
		return 1;
	}
}

int do_answer(string arg)
{
	object me,ob;
	object objwhere;
	string pos;
	me=this_player();
	
	pos=name[random(sizeof(name))];
	if (pos="")
	{
		pos=name[1];
	}
	if (!objectp(objwhere=find_object(pos)))
	{
		objwhere=load_object(pos);
	}
	if (!me->query_temp("qz/shouwei/target"))
	{
		command("say 你又没有接任务，回答什么？\n");
		return 1;
	}
	if (arg=="yes")
	{
		me->set_temp("qz/shouwei/answeryes",1);
		message_vision(HIY"$N对尹志平点了点头，说道，“既然是"+me->query_temp("qz/shouwei/target")+"这狗贼做的，那就杀了他好了！”\n"NOR,me);
		
		
		switch (me->query_temp("qz/shouwei/target"))
		{
			case "马光佐":
				ob=new("/d/xingxiu/npc/maguangzuo");				
				tell_object(me,"尹志平对"+me->query("name")+"悄声说道，“马光佐尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!”\n");				
				break;
			case "尼摩星":
				ob=new("/d/xueshan/npc/nimoxing");				
				//tell_object(me,"尹志平对"+me->query("name")+"悄声说道，“尼摩星尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!”\n");				
				command("tell "+ me->query("id")+" 尼摩星尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!\n");
				break;				
			case "霍都":
				ob=new("/kungfu/class/xueshan/huodu");				
				//tell_object(me,"尹志平对"+me->query("name")+"悄声说道，“霍都尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!”\n");				
				command("tell "+ me->query("id")+" 霍都尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!\n");
				break;				

			case "潇湘子":
				ob=new("/d/kunlun/npc/xiaoxiangzi");				
				//tell_object(me,"尹志平对"+me->query("name")+"悄声说道，“潇湘子尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!”\n");				
				command("tell "+ me->query("id")+" 潇湘子尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!\n");
				break;				

			case "尹克西":
				ob=new("/d/kunlun/npc/yinkexi");				
				//tell_object(me,"尹志平对"+me->query("name")+"悄声说道，“尹克西尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!”\n");				
				command("tell "+ me->query("id")+" 尹克西尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!\n");
				break;				

			case "达尔巴":
				ob=new("/d/xueshan/npc/daerba");				
				//tell_object(me,"尹志平对"+me->query("name")+"悄声说道，“达尔巴尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!”\n");				;
				command("tell "+ me->query("id")+" 达尔巴尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!\n");
				break;				
			case "公孙止":
				ob=new("/d/gumu/jqg/npc/gsz");				
				//tell_object(me,"尹志平对"+me->query("name")+"悄声说道，“公孙止尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!”\n");				
				command("tell "+ me->query("id")+" 公孙止尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!\n");
				break;
			default :
			    ob=new("/d/gumu/jqg/npc/gsz");				
				//tell_object(me,"尹志平对"+me->query("name")+"悄声说道，“公孙止尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!”\n");				
				command("tell "+ me->query("id")+" 公孙止尚未离开全真区域，正在"+objwhere->query("short")+"附近一带活动!\n");
				break;           				
		}		
		
								
				message_vision(HIY"尹志平道，“只有把这批人杀了才能彻底阻止他们对龙姑娘的骚扰！”\n"NOR,me);
				tell_object(me,"尹志平对"+me->query("name")+"悄声说道，“你去把他杀了，提人头见我!”\n");
				ob->apply_condition("npcdie_job",120);
				ob->set("owner",me->query("id"));
				ob->set("long",ob->query("long")+"\n这是玩家"+me->query("name")+"("+me->query("id")+")"+"要追杀的淫贼头子！\n");
				do_copyy(me,ob);
				ob->move(objwhere);		
			//remove_action("do_answer","answer");
		return 1;
	}
	if (arg=="no")
	{
		

		message_vision(HIY"$N对尹志平摇了摇头，说道，“"+me->query_temp("qz/shouwei/target")+"这狗贼我杀不过，让别人做好了！”\n"NOR,me);
		command("sigh "+me->query("id"));
		command("say 你做不了就这样吧，也不难为你了，去吧！\n");
		me->delete_temp("qz/shouwei/target");
		me->delete_temp("qz");
		TASKREWARD_D->get_reward(me,"守卫古墓",1,0,0,1+random(2),0,0,0,this_object());
		//remove_action("do_answer","answer");
		return 1;
	}

}
int ask_fangqi()
{
	object me=this_player();
	
	if (me->query_temp("qz/shouwei"))
	{
		
	    message_vision(HIC"尹志平对"+me->query("name")+"长叹一声道，“既然完不成也没关系，下次再来吧。”\n"NOR,me);
		me->delete_temp("qz");
		me->clear_conditions_by_type("qzsw_job_busy");
		me->add_condition("job_busy",4+random(2));

		return 1;
	}
	
	command("say "+me->query("name")+",你到处瞎跑，什么都没干成，要放弃啥呢。\n");
	
	return 1;

}

void die()
{
	object ob;
	ob=this_object();
//	room=find_object("d/quanzhen/jiaobei");
	
	if (!query_temp("living"))
	{
		
			ob = new("/kungfu/class/quanzhen/yinzhiping");
			
			ob->move("/d/quanzhen/jiaobei");
		
	}
	::die();
}
//下山历练获得

int ask_lilian()
{
	object me=this_player();
	//object ob=this_object();
	if (me->query("family/family_name")!="全真教")
	{
		command("say "+me->query("name")+",你不是我教中弟子，来此作甚？\n");
		return 1;
	}
	if (me->query_skill("xiantian-gong",1)<200)
	{
		command("say "+me->query("name")+",你的先天功太弱了,不足200，来此作甚？\n\n");
		return 1;
	}
	if(random(me->query("job_time/守卫古墓"))<500) 
	{
        command("say "+me->query("name")+",你守卫古墓次数不足，我不信你。");
	    return 1;

	}
	if(me->query("shen") <0) 
	{
        command("say "+me->query("name")+",你是邪魔外道之辈，胆敢来全真教撒野，难道是嫌弃自己命太硬了么？");
	    return 1;

	}
	
	if (me->query_temp("askyin/xiashan"))
	{
		command("say "+me->query("name")+",我不是刚给你说了么，还不赶紧去?\n\n");
	    return 1;
	}
	
	command("say "+me->query("name")+",今日闻听消息，有一批不明人士正在终南山脚下集结。\n");
	command("say 我打探清楚了，那个带头的人叫霍都。\n");
	command("angry ");
	command("say 这两个坏蛋居然敢来古墓打扰龙姑娘的清修，真是活得不耐烦了。\n");
	command("say 你替我去把霍都杀了，人头给我拿来。需要提醒的是这霍都武功很高。\n");
	command("say 我本想传你一套在短期内提升威力的剑法，就看你是不是这块料了。\n");

	command("say "+me->query("name")+"，这次任务比较艰巨，提他人头见我！\n");

	me->set_temp("askyin/xiashan",1);
	return 1;

}

//清缴残匪
// 马光佐、霍都、达尔巴、尹克西、潇湘子、尼摩星
int do_copyy(object me,object ob)
{
	int i;
	if(!me) destruct(ob);
    i = me->query("max_pot") - (70 + random(10));
    
	if(i < 350) i = 350;
    ob->set("combat_exp", me->query("combat_exp")/5*4);
	ob->set("max_qi", me->query("max_qi")/3*2); 
    ob->set("max_jing", me->query("max_jing")/3*2); 
    ob->set("max_neili", me->query("max_neili")/3*2);
    ob->set("jiali", ob->query_skill("force",1)/3);
    ob->reincarnate(); 
    ob->set("eff_jing", me->query("eff_jing")/3*2);
    ob->set("jingli", me->query("jingli")/3*2);
    ob->set("neili", me->query("max_neili")/3*2);
    ob->set("qi", me->query("max_qi")/3*2);

	ob->set_skill("force",i);
	ob->set_skill("parry",i);
	ob->set_skill("dodge",i);
	ob->set_skill("strike",i);
	ob->set_skill("hand",i);
	ob->set_skill("finger",i);
	ob->set_skill("cuff",i);
	ob->set_skill("leg",i);
	ob->set_skill("claw",i);
	//没特殊技能会出错，这里加个判断 by renlai
	if (ob->query_skill_mapped("strike")) ob->set_skill(ob->query_skill_mapped("strike"),i);
	if (ob->query_skill_mapped("hand")) ob->set_skill(ob->query_skill_mapped("hand"),i);
	if (ob->query_skill_mapped("leg")) ob->set_skill(ob->query_skill_mapped("leg"),i);
	if (ob->query_skill_mapped("finger")) ob->set_skill(ob->query_skill_mapped("finger"),i);
	if (ob->query_skill_mapped("cuff")) ob->set_skill(ob->query_skill_mapped("cuff"),i);
	if (ob->query_skill_mapped("claw")) ob->set_skill(ob->query_skill_mapped("claw"),i);

	if (ob->query_skill_mapped("sword")) ob->set_skill(ob->query_skill_mapped("sword"),i);
	if (ob->query_skill_mapped("blade")) ob->set_skill(ob->query_skill_mapped("blade"),i);
	if (ob->query_skill_mapped("brush")) ob->set_skill(ob->query_skill_mapped("brush"),i);
	if (ob->query_skill_mapped("club")) ob->set_skill(ob->query_skill_mapped("club"),i);
	if (ob->query_skill_mapped("whip")) ob->set_skill(ob->query_skill_mapped("whip"),i);
	if (ob->query_skill_mapped("hammer")) ob->set_skill(ob->query_skill_mapped("hammer"),i);
	if (ob->query_skill_mapped("staff")) ob->set_skill(ob->query_skill_mapped("staff"),i);

	ob->set_skill(ob->query_skill_mapped("dodge"),i);
	ob->set_skill(ob->query_skill_mapped("parry"),i);
	ob->set_skill(ob->query_skill_mapped("force"),i);
	/*
	ob->set("chat_chance", 10);
	ob->set("chat_msg", ({
		(: random_move :)
	}) );
	*/
	return 1;
}
