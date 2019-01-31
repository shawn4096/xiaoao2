// xiang.c 向问天
// Finish by action@SJ 2009.1.6
//给日月加入任务体系，拉拢同伙或者击杀反对者 by renlai
#include <ansi.h>
#include <job_mul.h>
#include <get_place.h>

inherit NPC;
inherit F_MASTER;

int check(object ob);

int ask_jiuwen();
string do_ask();
string do_cancel();
string do_finish();
int is_target(object corpse, object me);

void create()
{
        set_name("向问天", ({ "xiang wentian", "xiang", "wentian"}));
        set("long", "只见他容貌清瘦，身形高大，颏下疏疏朗朗一丛花白长须，垂在胸前，\n"+
		"背上负着一个包袱，再看他腰间时，却无弯刀。\n");
        set("title",HIY"日月神教 "HIW"光明左使"NOR);
        set("gender", "男性");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);

        set("max_qi", 4000);
        set("max_jing", 5200);
        set("eff_jingli", 5500);
        set("jiali", 200);
        set("combat_exp", 10400000);

        set_skill("strike", 460);
        set_skill("blade", 220);
        set_skill("club", 460);
        set_skill("parry", 460);
        set_skill("dodge", 460);
        set_skill("force", 460);
        set_skill("literate", 160);

        set_skill("tianmo-gun",460);
        set_skill("tianmo-zhang",460);
        set_skill("tianmo-dao",200);
        set_skill("huanmo-wubu",460);
        set_skill("tianmo-gong",460);
        set_skill("tianmo-jue",200);

        map_skill("force", "tianmo-gong");
        map_skill("parry", "tianmo-gun");
        map_skill("blade", "tianmo-dao");
        map_skill("club", "tianmo-gun");
        map_skill("dodge", "huanmo-wubu");
        map_skill("strike", "tianmo-zhang");

        prepare_skill("strike", "tianmo-zhang");
        set("inquiry", ([
                 //"秘密" : (: ask_mimi :),
		         "旧闻" : (: ask_jiuwen:),
			     //"金猿神魔" : (: ask_jinyuan:),
				 "job": (: do_ask() :),
                "任务": (: do_ask() :),
				"fangqi": (: do_cancel() :),
                "cancel": (: do_cancel() :),
                "放弃": (: do_cancel() :),
				"完成": (: do_finish() :),
				"finish": (: do_finish() :),
        ]));
        set("chat_chance", 3);
        set("chat_msg", ({
		        "向问天拿起酒壶，灌了一大口，道：“好酒！”\n",
					"向问天自言自语道：哼哼，梅庄四友....哪儿究竟隐藏着什么秘密呢？”\n",
					"向问天自言自语道：令狐冲那小子有点意思。”\n",
					"向问天自言自语道：可惜，我日月十大长老围攻华山，一去不回，到底发生了何事？。”\n",
					"向问天自言自语道：我日月的核心武技遗失不少，否则焉有左老儿的横行霸道！”\n",
        }));
        create_family("日月神教", 6, "长老");
        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
                (: perform_action, "club.luanwu" :),
				(: perform_action, "club.zhenfeng" :),
                (: exert_function, "tianmo" :),
        }));
		
        setup();

        carry_object(MISC_D("cloth"))->wear();  
        carry_object(BINGQI_D("club"))->wield();      
}

void init()
{
	//object ob;
	//ob = this_player();

	::init();
	/*
	if( interactive(ob = this_player()) && !is_fighting() && !is_busy()	  
	   && ob->query_temp("ry/ry_job/请")) {
		remove_call_out("greeting");
		call_out("greeting", 2, ob);
	}*/
}

/*
void greeting(object me)
{
	object target, ob;
	mapping quest;

	if( !me || environment(me) != environment() || !living(me)) return;

	if (!me->query_temp("ry/ry_job") || !me->query_temp("ry/ry_job/请") || !stringp(me->query_temp("ry/npc/id"))) return;

	command("nod "+me->query("id"));

	ob = this_object();

	if(objectp(target=present(me->query_temp("ry/npc/id"), environment(me)))
	  && target->query_temp("riyue_job") == me
	  && living(target)){
		me->add_busy(2);
		target->set_leader(0);
		command("haha");
		command("touch "+target->query("id"));
		command("say "+target->name()+"能来，我救出任教主又多了一份把握！哈哈！");
		write("向问天顺手递给"+target->name()+"一颗药丸。\n");
		call_out("done", 2, target, me, quest, 1);
		return;
	}	
}
*/


string do_finish()
{
	object me, ob,target;
	me = this_player();
	ob = this_object();
	
	if (!me->query_temp("ry/ry_job") || !me->query_temp("ry/ry_job/请") || !stringp(me->query_temp("ry/npc/id"))) 
		return "你没有领任务，要完成什么？";
	
	if(objectp(target=present(me->query_temp("ry/npc/id"), environment(me)))
	  && target->query_temp("riyue_job") == me
	  && living(target)){
		me->add_busy(2);
		target->set_leader(0);
		command("haha");
		command("touch "+target->query("id"));
		command("say "+target->name()+"能来，我救出任教主又多了一份把握！哈哈！");
		 message_vision("\n$N顺手递给$n一颗药丸。\n",ob,target);
		//write("向问天顺手递给"+target->name()+"一颗药丸。\n");
		call_out("done", 1, target, me, 1);
		return "你做的很好。";
	}	
}


string do_ask()
{
	object me, ob,target, *living;
	string type, t;
	mapping quest;
	int i,j;
	string str;

	me = this_player();
	ob = this_object();

	if(ob->is_busy()) return "我正忙着呢，你等等。";	

	if( me->query("combat_exp") < 1000000
	 || me->query("shen") > -1000)
	return RANK_D->query_respect(ob)+"看你满脸稚气,又不够心黑手狠，怎能放心让你去办大事呢？";

	if( me->query("job_name") == "日月复兴")
		return "你刚帮过我，还是休息一下吧。";	

	if( me->query_condition("job_busy"))
		return "你正忙着呢！。";

	if(me->query_condition("riyue_job"))
		return "你上次的日月复兴任务还没有完成吧。";

	living = livings();
	for (i=0;i < sizeof(living);i++){
		j = random(sizeof(living));
		if (j <= 1 || j == sizeof(living)-1) continue;
		if(check(living[j]) ){
			target = living[j];
			str = environment(target)->query("short");
			if( str == "武僧堂"
			 || str == HIR"心禅堂"NOR
			 || str == "金刚伏魔圈"
			 || environment(target)->query("quest")
			 || str == HIB"戒律院"NOR) continue;
			if( get_place(base_name(environment(target)))!="" )
				break;
		}
	}
	
	if( !target )
		return "最近比较空闲，你过一会儿再来吧。";	
	
	me->apply_condition("job_busy", 30);
	me->apply_condition("riyue_job", 30);
	me->delete_temp("ry/qing");//避免累计
	me->set_temp("ry/ry_job",1);
	me->set_temp("ry/times", uptime());
	me->set_temp("ry/npc",1);
	me->set_temp("ry/npc_time",time());
	me->set_temp("ry/npc_place",get_place(base_name(environment(target)))+environment(target)->query("short"));
	
	ob=new(__DIR__"robber");
	
	ob->setparty(10,me->query("max_pot")-100,me->query("combat_exp"));	
	
	//这里加进去状态
	ob->copy_player(me);//先初始化npc气血，否则被玩家一下击倒	
	ob->set_temp("target", me->query("id"));
	ob->move(environment(target));
	//ob->add_temp("apply/defense", 300);
	//ob->add_temp("apply/armor", 300);
	//ob->add_temp("apply/damage", 1000);
	
	me->set_temp("ry/npc_ob",ob);
	me->set_temp("ry/npc/name",ob->query("name"));
	me->set_temp("ry/npc/id",ob->query("id"));
	
	type = random(2)?"请":"杀";
	
	if(type == "杀"){
		me->set_temp("ry/ry_job/杀",1);		
		command("grin");
		command("whisper "+me->query("id")+" 你听着，有弟子回报"HIR+ob->query("title")+ob->query("name")+CYN"这人忠于东方不败，那么……");
		return "嘿嘿，他在"HIY+me->query_temp("ry/npc_place")+CYN"一带，你去将他杀了带着他的尸体赶回来。\n";
	}
	else{
		me->set_temp("ry/ry_job/请",1);		
		command("nod");
		command("whisper "+me->query("id")+" 对了，"HIG+ob->query("title")+ob->query("name")+CYN"和我交情不错，如得他相助，救出任教主之事简直易如反掌。");
		return "你就代表我去"HIY+me->query_temp("ry/npc_place")+CYN"邀请他。";
	}
}


int accept_object(object who, object ob,object me)
{
       int type,count,exp,pot,total_job_times;
       me=this_object();
	   
	    if(ob->query("id") == "heimu ling") 
		{
			if (!who->query_temp("hssb/askxiang")) {
	                 command("say 你给我这个做什么？\n");	
		        return 0;
               }
			 if (who->query_temp("hostage/linggived"))
	    {	
		
		who->delete_temp("hostage/linggived");
		write(HIY"向问天将这块黑木令拿在手中翻来覆去的看着。\n"NOR);
        write(CYN"向问天在哪儿自言自语起来，脸上亦喜亦忧。\n"NOR);
		
		command("say 既然你替我找到了这块黑木令，那我就把这个消息告诉你。\n");
		command("say 十大长老围攻华山一去不回，我怀疑他们中了对方的奸计。\n");
		command("say 也就说，如果你去华山后山附近转悠转悠说不定有什么惊人的发现。\n");
		command("say 不过生死有命，富贵在天，我看你还是随缘的好。凡事不必强求。\n");
		who->set_temp("hssb/juejiasked",1);
		destruct(ob);
		return 1;
	         }
			 else {
               command("say 你瞎折腾什么？\n");
	     return 0;
	}			
			
		}
		else
		{
       
       type = is_target(ob, who);
       switch (type){
	    case 0: command("say 你拿个"+ob->name()+"给我干嘛？");
		    return 0;
	    case -1:command("say 耶？让请人你不去，倒杀人丢脸去了，滚开！");
		    return 0;
	    case -2:command("say 嘿嘿，谁让你去乱杀人了？简直是给我日月神教抹黑！");
		    who->apply_condition("job_busy", 9);
		    return 0;
	    case -3:command("say 嗯，这人不是你杀的！");
		    who->apply_condition("job_busy", 9);
		    return 0;
	    case -4:command("say 哦，这是个同名同性的人，算他倒霉吧！");
		    return 0;
	    default:command("haha");
		   command("say 好！好！你办事不错，是块好料子。");
		   message_vision("\n$N给$n讲解一些武学上的疑难，$n若有所思地点着头。\n",me, who);		   
		TASKREWARD_D->get_reward(who,"日月复兴",-1,0,0,10+random(6),0,0,0,"向问天"); 

    log_file("job/fuxing",sprintf("%8s%-10s完成第%4d次日月复兴杀人任务，经验：%d\n",who->name(),"("+who->query("id")+")",who->query("job_time/日月复兴"),who->query("combat_exp")),who);
	
    who->clear_condition("job_busy");
	who->clear_condition("riyue_job");
    //who->apply_condition("riyue_job", 3);
	who->delete_temp("ry");
	who->delete_temp("riyue_job");
	
	
	if (who->query("family/family_name")=="日月神教" && !who->query_temp("mz_entrance") && !who->query("quest/xxdf/pass") && who->query("combat_exp")>8000000 )	
		{
			if (QUEST_D->job_questing(who,2,"mz_entrance","日月复兴",4000,"雪山",4000,"mz_entrance"))
		     command("say "+who->query("name")+"，听说杭州梅庄四位庄主喜欢琴棋书画，你若能投其所好送去礼物，或许会有一番机缘。\n");	
		}	
	/*
	total_job_times=who->query("job_time/日月复兴")+who->query("job_time/雪山");
	
	if (wizardp(who)||
	(random(who->query("job_time/日月复兴"))>4000 
	   && random(who->query("kar"))>25 
	   && random(who->query("job_time/雪山"))>4000 
	   && who->query("family/family_name")=="日月神教"
	   && !who->query_temp("mz_entrance")
	   && !who->query("quest/xxdf/pass")
	   && who->query("combat_exp")>8000000
	   && random(10)<5
	   && total_job_times % 50 == 0 ))
	{
		who->set_temp("mz_entrance", 1);
		command("say "+who->query("name")+"，听说杭州梅庄四位庄主喜欢琴棋书画，你若能投其所好送去礼物，或许会有一番机缘。\n");
		log_file("quest/xixing",sprintf("%8s%-10s日月复兴任务时，去梅庄，日月：%4d，雪山：%4d，福：%2d。\n",who->name(),"("+who->query("id")+")",who->query("job_time/日月复兴"),who->query("job_time/雪山"), who->query("kar")),who);
	}   
*/
	
	who->set("job_name", "日月复兴");	
	call_out("destroy", 1, ob);
	return 1;
	    }
      return 1;
		}
}


int is_target(object corpse, object me)
{
	if (!me->query_temp("ry/ry_job")) return 0; // didnt get the job	

	if (!me->query_temp("ry/ry_job/杀")) return -1;  // job type is not killing

	if ( corpse->query("id") != "corpse" && corpse->query("id") != "shouji") return 0;// it's not a corpse or head.
	
	if (corpse->query("kill_by") != me) return -3;

	if ( corpse->query("victim_id") != me->query_temp("ry/npc/id") || corpse->query("victim_name") != me->query_temp("ry/npc/name"))
		return -2;      // killed wrong person.
	if ( corpse->query("victim_user")) return -4;   // killed a player.
	else return 1;
	
}


void destroy(object ob)
{
	destruct(ob);
}

string do_cancel()
{
	object me;
	int exp, i;

	me = this_player();
	exp = me->query("combat_exp");

	if(!me->query_temp("ry/ry_job"))
		return "你没有领任务，和我嚷嚷什么？";

	me->add("combat_exp",-(20+random(50)));
	if(exp > 500000){
	      me->add("combat_exp",-(30+random(40)));
	}
	i = 40 - me->query_condition("job_busy");
	if ( i >= 9 )
		me->apply_condition("job_busy", 1);
	else
		me->apply_condition("job_busy", 9 - i);
	//me->clear_condition("riyue_job");
	me->apply_condition("riyue_job", 10);
	me->delete_temp("riyue_job");
	
	if (me->query_temp("ry/npc_ob")) 
	 {
		 destruct(me->query_temp("ry/npc_ob"));  //消除job npc
		 me->delete_temp("ry/npc_ob");
	 }
	 
	me->delete_temp("ry");	
	log_file("job/fuxing",sprintf("%8s%-10s 放弃日月复兴任务，经验：%d\n",me->name(),"("+me->query("id")+")",me->query("combat_exp")),me);
	
	return "你这样偷奸耍滑，何时才能救出任教主！！！";
}


void done(object target, object me,int i)
{
       int count,exp,pot,total_job_times,qing;

       if(me && i >= 0){
		if(target){
			
			message_vision("\n$N点头道："+me->name()+"你这娃娃不赖，让我指点几招，就当是奖励吧！\n", target, me);
		    tell_room( environment(me), target->name() + "在" + me->name()+ "耳边小声地说了些话。\n", ({ me, target }) );
		
		qing=(int)me->query_temp("ry/qing");
		if (qing>10) qing=10;
		//这里获取请人次数，加入奖励计算 by renlai
			TASKREWARD_D->get_reward(me,"日月复兴",-1,0,0,18+qing,0,0,0,"向问天"); 
     log_file("job/fuxing",sprintf("%8s%-10s完成第%4d次日月复兴请人任务，经验：%d\n",me->name(),"("+me->query("id")+")",me->query("job_time/日月复兴"),me->query("combat_exp")),me);	
			//me->add("job_time/日月复兴", 1);
			me->clear_condition("job_busy");
	        me->clear_condition("riyue_job");
			//me->apply_condition("riyue_job", 3);
			
			if (me->query("family/family_name")=="日月神教" && !me->query_temp("mz_entrance") && !me->query("quest/xxdf/pass") && me->query("combat_exp")>8000000 )	
		{
			if (QUEST_D->job_questing(me,2,"mz_entrance","日月复兴",4000,"雪山",4000,"mz_entrance"))
		     command("say "+me->query("name")+"，听说杭州梅庄四位庄主喜欢琴棋书画，你若能投其所好送去礼物，或许会有一番机缘。\n");	
		}	
			
/*			
			total_job_times=me->query("job_time/日月复兴")+me->query("job_time/雪山");
	
	if (wizardp(me)||
	(random(me->query("job_time/日月复兴"))>4000 
	   && random(me->query("kar"))>25 
	   && random(me->query("job_time/雪山"))>4000 
	   && me->query("family/family_name")=="日月神教"
	   && !me->query_temp("mz_entrance")
	   && !me->query("quest/xxdf/pass")
	   && me->query("combat_exp")>8000000
	   && random(10)<5
	   && total_job_times % 50 == 0 ))
	{
		me->set_temp("mz_entrance", 1);
		command("say "+me->query("name")+"，听说杭州梅庄四位庄主喜欢琴棋书画，你若能投其所好送去礼物，或许会有一番机缘。\n");
		log_file("quest/xixing",sprintf("%8s%-10s日月复兴任务时，去梅庄，日月：%4d，雪山：%4d，福：%2d。\n",
			me->name(),"("+me->query("id")+")",me->query("job_time/日月复兴"),me->query("job_time/雪山"), me->query("kar")),me);
			}
			*/
//else  log_file("quest/xixing",sprintf("%8s%-10s日月复兴任务时，梅庄提示失败，日月：%4d，雪山：%4d，福：%2d。\n",me->name(),"("+me->query("id")+")",me->query("job_time/日月复兴"),me->query("job_time/雪山"), me->query("kar")),me);
			
			me->delete_temp("ry");
	        me->delete_temp("riyue_job");						
			me->set("job_name", "日月复兴");
			tell_room(environment(target), target->query("name")+"摇头苦笑一声，接过向问天手中药丸一口吞下。\n", ({target}));
			destruct(target);
			/*
			if(target->return_home()){
				target->delete_temp("riyue_job");
				target->delete_temp("last_lost_to");
				target->clear_condition("riyue_busy");
				target->set("chat_chance", target->query("chat_c"));
				if(!target->query_temp("location"))
				target->delete("location");
				target->set_leader(0);
				target->reincarnate();
			}
			else destruct(target);
			*/
			
		}
	}
	else if(target){
		tell_room(environment(target), target->query("name")+"摇头苦笑一声，接过向问天手中药丸一口吞下。\n", ({target}));
		destruct(target);
	}
}



void attempt_apprentice(object ob)
{
     if(ob->query_skill("tianmo-gong",1) < 350 ||
      ob->query_skill("tianmo-zhang",1) < 350 ||
        ob->query_skill("tianmo-dao",1) < 350){
        command("say 你的武功还不够娴熟，再回去练练吧。");
        return;
        }
     command("say 好，我正想招兵买马救教主出来，看来你还不错嘛，就收下你了。");
     command("recruit " + ob->query("id"));
     ob->set("title","日月神教光明左使座下堂主");
}


int ask_jiuwen()
{
     object me=this_player();
     if (me->query("family/family_name")!="日月神教")
         return notify_fail("你不是我神教弟子来此瞎打听作甚？\n");

	 if (me->query_skill("tianmo-gong",1)<449)
		 return notify_fail("你的天魔功力太弱，不足450，还是好好练功去吧。");
     
	
		
		 command("say 我曾听任教主提到，十大长老围攻华山之战役，不知为何竟然全部失踪。\n");
		 command("think ");
		 command("say 那时候我神教英雄辈出，金猿神魔张乘风、张乘云兄弟，一套天魔棍法横扫天下。\n");
		 command("say 还有大力神魔范松长老的大力神魔斧更是威震江湖。\n");
		 command("sigh ");
		 command("say 谁要是能帮我找到黑木令，我就告诉他真相。\n");
		 command("heng ");
		 me->set_temp("hssb/askxiang",1);
		 return 1;
		 //command("");
		//随即 选择需要礼物，然后满意了就告诉他去华山。。
}

int check(object ob)
{
	object room;
	string room_name;

	if(!objectp(ob)
	 || !ob->query("startroom")      // add by Yuj@SJ to void job NPC
	 || ob->query("env/invisibility")
	 || ob->query("no_quest")	 
	 || userp(ob)
	 || ob->query("attitude")=="aggressive"
	 || ob->query("have_master")
	 || !objectp(room=environment(ob))
	 || room->query("no_fight")
	 || room->query("sleep_room")     //add by renlai for no fight sleep room
	 || room->query("quest")          //add by renlai for not enter room
	 || room->query("outdoors") == "昆仑翠谷"
	 || room->query("outdoors") == "蝴蝶谷"   //add by renlai for not enter zone
	 || strsrch(room_name = file_name(room),"/d/") != 0
	 || strsrch(room_name, "/d/wizard/") == 0
	 || strsrch(room_name, "/d/wuguan/") == 0
	 || strsrch(room_name, "/d/group/") == 0
	 || strsrch(room_name, "/d/death/") == 0
	 || strsrch(room_name, "/d/mingjiao/lsd/") == 0
	 || strsrch(room_name, "/d/mingjiao/bhd/") == 0
	 || strsrch(room_name, "/d/xueshan/") == 0
	 || strsrch(room_name, "/d/shaolin/fumoquan") == 0
	 || strsrch(room_name, "/d/baituo/") == 0)
	 return 0;
	return 1;
}

void die()
{
	object ob;
	if (!query_temp("living"))
	{
		ob = new("/d/hmy/npc/xiang");
		ob->move("/d/hmy/liangting");
	}
	::die();
}




