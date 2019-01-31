#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string ask_guo();
string ask_jinyan();
string ask_shangtianti();
string ask_sanhua();
string ask_chongyang();
string* badman=({"彭连虎","梁子翁","沙通天","灵智上人","欧阳克","钱青健","沈青刚","马青雄","吴青烈","侯通海"});
string ask_yusuo();
string ask_wangshi();
string ask_dingyangtitle();
int do_answer(string arg);
void create()
{
        set_name("马钰", ({"ma yu", "ma"}));
        set("gender", "男性");
        set("age", 42);
        set("class", "taoist");
        set("nickname",MAG"丹阳子"NOR);
        set("long",
                "他就是王重阳的大弟子，全真七子之首，丹阳子马钰马真人。\n"
				"马真人一神功夫内外兼修，尤其是昊天掌修为在七子中最高。\n"
                "他慈眉善目，和蔼可亲，正笑着看着你。\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 28);
        set("int", 32);
        set("con", 31);
        set("dex", 30);
        set("title","全真七子之首");
        set("qi", 34500);
        set("max_qi", 34500);
		set("eff_qi",34500);
        set("jing", 5200);
        set("max_jing", 5200);
        set("neili", 24700);
        set("max_neili", 24700);
        set("jiali", 200);
        set("level", 18);
        set("combat_exp", 9400000);

        set_skill("force", 450);
        set_skill("xiantian-gong", 450);
        set_skill("sword", 450);
        set_skill("quanzhen-jianfa",450);
        set_skill("dodge", 450);
        set_skill("jinyan-gong", 450);
        set_skill("parry", 450);
        set_skill("literate",250);
        set_skill("strike", 450);
        set_skill("haotian-zhang", 450);
        set_skill("taoism",200);
	    set_skill("medicine", 200);
        set_skill("tiangang-beidouzhen", 450);
		set_skill("leg", 200);
        set_skill("yuanyang-lianhuantui", 450);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
		map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("strike","haotian-zhang");
		prepare_skill("leg", "yuanyang-lianhuantui");

        create_family("全真教", 2, "弟子");

        set("book_count",1);
        set("miji_count",1);
        set("inquiry", ([
             "郭靖" : (:ask_guo:),
			 "金雁功" : (:ask_jinyan:),
			 "上天梯" : (:ask_shangtianti:),
			"三花聚顶掌" : (:ask_sanhua:),
			"重阳连环掌绝技" : (:ask_chongyang:),
			"金关玉锁二十四诀" : (:ask_yusuo:),
			"全真教秘闻" : (:ask_wangshi:),
			"先天定阳" : (:ask_dingyangtitle:),
        ]) );
		set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: perform_action, "sword.sanqing" :),
                (: perform_action, "sword.qixing" :),
                (: perform_action, "sword.ding" :),
				(: perform_action, "sword.jianqi" :),
                (: perform_action, "sword.lian" :),
				(: exert_function, "daojue" :),
				(: exert_function, "wuqi" :),
				(: exert_function, "yusuo" :),
               
        }));
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

string ask_dingyangtitle()
{
	string new_title,title,*title1,*title2;
	object me;
	me=this_player();
	title1 =({ "承","平","定","乾","钧","清","紫","冥","烈" });	
	title2 =({ "真人","真君" });
	if (me->query("mytitle/quest/dingyangtitle")) return "你已得固定头衔。\n";
	if (me->query("quanzhen/force")=="pass") 
		{			
			title= "全真教·"+title1[random(sizeof(title1))]+"阳"+title2[random(sizeof(title2))];
			me->set("title",HIB+title+NOR);
			me->set("mytitle/quest/dingyangtitle",HIB+title+NOR);
			command("say 既然如此，赐你"+title+"！\n");
			return "不错，不错。";
		}
		return "呵呵。。。。。。\n";
}
string ask_guo()
{
	object me;
	me=this_player();
	if (me->query("family/family_name")!="全真教")
	{
		return "你不是我全真教弟子！\n";
	}
	command("say 郭靖本是江南七怪的弟子，当初为了和丘师弟打赌，这七侠远赴大漠，教导此子！\n");
	command("say 相约十八年后在嘉兴醉仙楼比武赌输赢！\n");
	command("say 我知道全真教内功越到后期威力越大，这郭靖原本非我丘师弟弟子的对手！\n");
	command("say 我心中念及这七人的侠义心肠，所以就曾远赴大漠教导了这孩子数年！\n");
	command("say 当时传授他的就是我全真教的内功和全真轻功----金雁功！\n");
	me->set_temp("jyg/askma",1);
	return "往事悠悠，这陈年往事至今提及，仍然让人对七侠敬佩有加！\n";
}
//往事启动项，获得先天功一阳指提示

string ask_wangshi()
{
	object me;
	me=this_player();
	if (me->query("family/family_name")!="全真教"
		||!me->query("quest/qz/dichuan"))
	{
		return "你不是我全真教核心弟子！\n";
	}
	if (!me->query("quest/qz/xtg/wuqi/pass"))
	{
		return "先天功打好基础很重要，你连五气朝元都没参悟透，如何能学会定阳针绝技？\n";
	}
	if (me->query("con")<40)
	{
		return "你先天根骨不足40，参悟不了定阳针绝学？\n";
	}
	if (me->query("quest/qz/xtg/dingyang/start"))
	{
		return "你已经获得了五篇另文的消息，还不赶紧去找到！\n";
	}
	if (time()-me->query("quest/qz/xtg/dingyang/time")<86400)
	{
		return "你来的太频繁了!\n";
	}

	command("say 你可知道我全真教最厉害的内功是什么招式？！\n");
	add_action("do_answer","answer");
	me->set_temp("marks/wangshi",1);
	return "往事悠悠，不提也罢！\n";
}
int do_answer(string arg)
{
	object me=this_player();
	if (!arg||arg!="先天功定阳针")
	{	
		command("kick "+me->query("id"));
		command("say 蠢材，连我大全真教的先天功定阳针神技都不知道！\n");
		return 1;
	}
	if (me->query_temp("marks/wangshi"))
	{
		me->delete_temp("marks");
		command("say 瞎点头回答什么？\n");
		return 1;
	}
	command("say 这先天功定阳针乃是我全真教第一内功！\n");
	command("say 也是天下第一等的内功心法！\n");
	command("say 此乃重阳祖师威震天下并获得华山论剑第一的根本！\n");
	command("say 当初祖师凭此神功力克天下其余四绝，东邪、西毒、南帝、北丐！\n");
	command("say 获得第一后，获得了保存《九阴真经》的权利！\n");
	command("say 后来西毒欧阳锋不服气，试图抢夺《九阴真经》，祖师当时身体不好。\n");
	command("say 为了防止欧阳锋以后作乱，就设计了一场谋划！\n");
	tell_object(me,HIY"你听得非常入神，闻听马钰的讲述，仿佛回到那个惊心动魄的夜晚！\n"NOR);
	me->set_temp("quest/qz/xtg/dingyang/start",1);
	//tell_object(me,HIG"时光一阵扭曲....！\n"NOR);

	me->move("d/quanzhen/lingtang");
	return 1;

}
string ask_yusuo()
{
	object me,ob;
	me=this_player();
	if (me->query("family/family_name")!="全真教")
	{
		command("say 你不是我全真教弟子！\n");
		return "哼！\n";
	}
	if (!me->query("quest/qz/dichuan"))
	{
		command("say 你不是我全真教核心弟子！\n");
		return "哼！\n";
	}
	if (me->query_skill("xiantian-gong",1)<350)
	{
		command("say 你的先天功不足350，修炼不了这门功夫！\n");
		return "唉!\n";
	}
	if (present("yusuo jingyao",me)||me->query_temp("yusuo/askma"))
	{
		command("say 你身上不是有玉锁诀的精要么？！\n");
		return "poor \n";
	}
	command("say 这金关玉锁二十四诀乃是先天功厉害的心法口诀！\n");
	command("say 修炼到后期全凭一口先天真气，即便说话也蕴含莫大威力！\n");
	command("say 这门神功修炼到高深境界，摘叶飞花也能伤人，此乃是我教不传之秘！\n");
	command("say 这门功夫全凭个人参悟所得，因人而异，人人不同\n");
	command("say 总共有九重境界，你能修炼到何种地步全看你的悟性和毅力了！\n");
	command("say 我全真教先天功天下第一，你要好自为之，切勿自误！\n");
	command("say 带上这本我修炼的《金关玉锁诀精要》到禅房去找个蒲团认真修炼！\n");
	ob=new("/d/quanzhen/obj/yusuojue3");
	ob->move(me);
	me->set_temp("yusuo/askma",1);

	return "";
}
string ask_jinyan()
{
	object me;
	me=this_player();
	if (me->query("family/family_name")!="全真教")
	{
		return "你不是我全真教弟子！\n";
	}
	if (!me->query_temp("jyg/askma"))
	{
		return "那是我全真教最重要的轻功身法！\n";
	}
	command("say 我当初迫于门派规矩，无法亲自传授郭靖技艺！\n");
	command("say 只是传授了他一些轻身身法和呼吸之法！\n");
	command("say 其中这金雁功最重要心法就是“上天梯”绝技！\n");
	command("say 凭此绝技，可以在大山险壑间纵横无碍！\n");
	
	me->set_temp("jyg/askjyg",1);
	return "金雁功博大精髓，外门派是不晓得其中诀窍的！\n";
}
string ask_shangtianti()
{
	object me;
	me=this_player();
	if (me->query("family/family_name")!="全真教")
	{
		return "你不是我全真教弟子！\n";
	}
	if (!me->query_temp("jyg/askjyg"))
	{
		return "那是我全真教最重要的轻功身法！\n";
	}
	 if (me->query_skill("xiantian-gong",1) < 450) {
               command("say 我全真教一身功夫全在先天功，你先天功不足450，来此作甚？。");
               return "";
       }
	   if (me->query_skill("jinyan-gong",1) < 450) {
               command("say 这金雁功不足450，来此作甚？。");
               return "";
       }	   
	   if (me->query("dex") < 35) {
               command("say 这金雁功需要先天身法，不足35，来此作甚？。");
               return "";
       }
	   	if (me->query("quest/qz/jyg/shangtianti/pass"))
		{
			return "你的金雁功上天梯的铁脚绝技已经解开了”！\n";
		}
		if (time()-me->query("quest/qz/jyg/shangtianti/time")<86400)
		{
			return "你来的太频繁了，明天再来！\n";
		}
		if (me->query("party/gongji")<100)
		{
			return "你门派贡献功绩不够100！\n";
		}
		me->add("party/gongji",-100);
	   command("say 事先声明，你向我请教需要扣除你的门派贡献值每次100点，如果不够你没资格请教我。\n\n\n\n");

       command("say 好吧，既然你如此努力，我就告诉你其中诀窍。\n");
		command("say 郭靖的上天梯绝技是当初在蒙古的一处悬崖处修习来的！\n");
		command("say 轻功功夫全靠锻炼出来，你若有心就去哪儿找找机缘，看能否有所参悟！\n");
	
	me->set_temp("jyg/askstt",1);
	return "山天梯是金雁功的精髓所在！\n";
}

//三化聚顶掌
//替马钰去杀了彭连虎

string ask_sanhua()
{
	object me;
	string bad;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="全真教")
	{
		return "你不是我全真教弟子！\n";
	}
	if (me->query("shen") < 500000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在德行方面，" + RANK_D->query_respect(me) +
                       "是否还做得不够500k？(1m)");
               return "";
       }
	   if (me->query("party/gongji") < 100) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在教派功绩方面，" + RANK_D->query_respect(me) +
                       "是否还做得不够？(需要100点门派贡献值)\n");
               return "";
       }
	   if (!me->query("quest/qz/dichuan"))
	   {
		       command("say 你非我门中嫡传弟子，来此作甚？");
              return "";

	   }
	   if (me->query_skill("xiantian-gong",1) < 350) {
               command("say 我全真教一身功夫全在先天功，你先天功不足350，来此作甚？。");
               return "";
       }
	   if (me->query_skill("haotian-zhang",1) < 350) {
               command("say 我昊天掌不足200，来此作甚？。");
               return "";
       }
	   	if (me->query("quest/qz/htz/sanhua/pass"))
		{
			return "你的昊天掌的三花聚顶掌已经解开了”！\n";
		}
		if (time()-me->query("quest/qz/htz/sanhua/time")<86400)
		{
			return "你来的太频繁了，明天再来！\n";
		}
		if (!me->query_temp("quest/qz/htz/sanhua/killed"))
		{
			command("say 这三花聚顶掌乃是我全真教顶级武功之一，你若想学，需要替我去杀几个恶人！\n");
			bad=badman[random(sizeof(badman))];
			command("say 这次你替我去杀了"HIY+bad+NOR"这个恶贼！\n");
			me->set_temp("quest/qz/htz/sanhua/askma",1);
			me->set_temp("quest/qz/htz/sanhua/killtarget",bad);
			return "这恶贼坏事干尽，居然在掌中暗藏毒针暗算与我！\n";
		}

	   command("say 事先声明，你向我请教需要扣除你的门派贡献值每次100点，如果不够你没资格请教我。\n\n\n\n");

       command("say 好吧，既然你如此努力，我就告诉你其中诀窍。\n");
       command("whisper "+me->query("id"));
	   
	   if (me->is_busy())
	   {
		  return "你正在手忙脚乱中!\n";
	   }
		me->start_busy(10);
		
		me->add("party/gongji",-100);

		message_vision(HIC"$N看着$n，慢慢说道：“我派的昊天掌威力不同凡响，你若能修成这三化聚顶掌，武林中大可去的。\n"
							"你既然到达如此程度，我就传给你这招“三花聚顶掌”的奥秘，我给你演示一遍，看你自己的悟性了。\n"+
					   HIR"\n\n\n$N缓缓站起来，然后纵身跃起，顿时化作三朵莲花聚集头顶，掌法威力明显增大不小！\n"NOR,this_object(),me);
		
	 
		i = 20;
		if(me->query("m-card-vip")) i =  18;
		if(me->query("y-card-vip")) i =  15;
		if(me->query("buyvip"))     i =  10;
		i=random(i);
		j=random(me->query("kar"));
		command("say 你看懂了么。\n");
		command("pat "+me->query("id"));
		if( i<3
			&& me->query("kar")<31
			&& j >= 25 ) 
		{
			tell_object(me,HIC"\n你听了的马钰的亲自指点，联想起早期自己所用昊天掌的种种心得，两下印照。\n"NOR);
			tell_object(me,HIR"\n忽然劳宫穴一股大力传来，你顿时感觉掌法力量大增，瞬间领悟了这三花聚顶掌的运气法门。\n"
						NOR);
			me->set("quest/qz/htz/sanhua/pass",1);
			log_file("quest/qzsanhua", sprintf("%8s(%8s) 失败%d次后，学到三花聚顶掌绝技,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
				me->name(1),me->query("id"), me->query("quest/qz/htz/sanhua/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			command("haha"+me->query("id"));		
			me->delete_temp("quest/qz/htz");
			return "恭喜解密三花聚顶掌绝技成功!\n";
			
		}	
	   else
		{
			log_file("quest/qzsanhua", sprintf("%8s(%8s) 解密三花聚顶掌掌绝技绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
				me->name(1),me->query("id"), me->query("quest/qz/htz/sanhua/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
			
			tell_object(me,HIY"你听了马钰的指点，可是对昊天掌决三花聚顶掌绝技的奥妙全然不得要领。\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			me->add("quest/qz/htz/sanhua/fail",1);
			me->set("quest/qz/htz/sanhua/time",time());
			me->start_busy(2+random(3));
			me->delete_temp("quest/qz/htz");

			return "非常遗憾解密昊天掌之三花聚顶掌绝技失败"+me->query("quest/qz/htz/sanhua/fail")+"次。\n";
		}

   
}

//接受物品

int accept_object(object who,object obj)
{
	object obb;
	
	if (obj->query("kill_by"))
	{
		obb=obj->query("kill_by");
	}
	if (who->query_temp("quest/qz/htz/sanhua/killtarget")
		&&obb->query("id")==who->query("id")
		&&obj->query("name")==who->query_temp("quest/qz/htz/sanhua/killtarget")+"的首级")
	{
		
		command("haha "+who->query("id"));
		command("say 你能将"+obj->query("victim_name")+"这个恶贼替我杀了，我很高兴！\n");
		command("pat "+who->query("id"));
		command("say 这说明你最近武功修炼不错，我很看好你！\n");
		command("say 你先下去好好休息吧！\n");

		message_vision(RED"\n\n$n甩手将"+obj->query("name")+RED"抛入身后的悬崖中！\n"NOR,who,this_object());
		destruct(obj);
		who ->set_temp("quest/qz/htz/sanhua/killed",1);
	}	

	return 1;
}

//重阳连环掌
string ask_chongyang()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="全真教")
	{
		return "你不是我全真教弟子！\n";
	}
	if (!me->query("quest/qz/htz/sanhua/pass"))
	{
		return "三花聚顶是昊天掌重阳连环的基础，你不懂三花聚顶，如何修习重阳连环？\n";
	}
	if (me->query("shen") < 2000000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在德行方面，" + RANK_D->query_respect(me) +
                       "是否还做得不够？(2m)");
               return "";
       }
	   if (me->query("party/gongji") < 100) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在教派功绩方面，" + RANK_D->query_respect(me) +
                       "是否还做得不够？(需要100点门派贡献值)\n");
               return "";
       }
	   if (!me->query("quest/qz/dichuan"))
	   {
		       command("say 你非我门中嫡传弟子，来此作甚？");
              return "";

	   }
	   if (me->query_skill("xiantian-gong",1) < 450) {
               command("say 我全真教一身功夫全在先天功，你先天功不足450，来此作甚？。");
               return "";
       }
	   if (me->query_skill("haotian-zhang",1) < 450) {
               command("say 我昊天掌不足450，来此作甚？。");
               return "";
       }
	   	if (me->query("quest/qz/hzt/chongyang/pass"))
		{
			return "你的昊天掌的重阳连环掌已经解开了”！\n";
		}
		if (time()-me->query("quest/qz/hzt/chongyang/time")<86400)
		{
			return "你来的太频繁了，明天再来！\n";
		}
	   command("say 事先声明，你向我请教需要扣除你的门派贡献值每次100点，如果不够你没资格请教我。\n\n\n\n");

       command("say 好吧，既然你如此努力，我就告诉你其中诀窍。\n");
       command("whisper "+me->query("id"));
	   if (me->is_busy())
	   {
		  return "你正在手忙脚乱中!\n";
	   }
		me->start_busy(10);
		
		me->add("party/gongji",-100);

		message_vision(HIC"$N看着$n，慢慢说道：“我派的昊天掌威力不同凡响，这重阳连环掌需要和天上北斗七星共同参悟方可有效。\n"
						"这掌法我们七子全部没有学会，但我见祖师曾经演练过，若灿烂星辰，威力不可同耳语。\n"+
					   HIR"\n\n\n$N说道，“你若想修习这门绝技，最好到祖师闭关之所，在那个独特观星台上可以参悟这门绝技”！\n"
						+"切记，切记，心要诚，祖师创建全真，着实不易。你要谦恭，去吧，可以到后山山洞祖师闭关之所看看是否有此机缘！\n"NOR,this_object(),me);
		me->set_temp("quest/qz/htz/chongyang/askma",1);
		return "观星台空气好，若机缘巧合能参悟星斗之力，领悟快！\n";
}


void attempt_apprentice(object ob)
{
       if (ob->query("gender")!="男性")
       {
		   command("say 你一个女人家来拜我为师，难道是有什么企图不成？！\n");
		   command("say 我全真一脉，最终全在内丹修为上，关于坤丹的修炼我不擅长！\n");
		   command("say 你还是去寻找下师叔清静散人孙不二，看他是否收你？\n");
		   return ;

       }

	   if ((int)ob->query("shen") < 2000000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在德行方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(2m)");
               return;
       }
	   if (ob->query("party/gongji") < 3000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在教派功绩方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(需要3000点门派贡献值)\n");
               return;
       }
	   if (!ob->query("quest/qz/dichuan"))
	   {
		       command("say 你非我门中嫡传弟子，来此作甚？");
              return;

	   }
	   if (ob->query_skill("xiantian-gong",1) < 350) {
               command("say 我全真教一身功夫全在先天功，你先天功不足350，来此作甚？。");
               return;
       }
	 
       command("say 好吧，贫道就收下你了。");
       command("recruit " + ob->query("id"));
       ob->set("title", "全真七子亲传弟子");
       ob->set("class","taoism");
	   return;
}