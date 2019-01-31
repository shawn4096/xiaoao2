 // by Xiaoyao

inherit NPC;
#include <ansi.h>
void destroying(object, object);
#include "/d/suzhou/npc/lchj.h";
string ask_diyun();
int ask_skills();
string ask_qiyu();

void create()
{
        set_name("丁典", ({ "ding dian", "ding" }));
        set("long", "这人满脸虬髯，头发长长的直垂至颈，衣衫破烂不堪，简直如同荒山中的野人。\n");
        set("gender", "男性");
        set("age", 35);
        set("unique", 1);

        set_skill("cuff", 520);
        set_skill("dodge", 520);
        set_skill("parry", 530);
        set_skill("force", 550);
		set_skill("sword", 550);

        set_skill("tangshi-jianfa", 550);
        set_skill("wuying-shenquan", 500);
        set_skill("shenzhao-jing", 550);
		set_skill("caoshang-fei", 520);
        
		map_skill("sword","tangshi-jianfa");

        map_skill("dodge","caoshang-fei");
        map_skill("force","shenzhao-jing");
        map_skill("parry", "wuying-shenquan");
        map_skill("cuff","wuying-shenquan");
        prepare_skill("cuff","wuying-shenquan");
        
		set("max_jing",8000);
        set("jing",8000);
        set("eff_jing",8000);

		set("max_neili",55000);
        set("neili",55000);
        set("max_qi",51680);
        set("qi",51680);
        set("eff_jingli",8000);
        set("jingli",8000);
        set("jiali",250);
		set("inquiry", ([
		"狄云" : (: ask_diyun :),
		"name": "你问这干嘛，我就是丁典，你有什么事情？",
		"here": "这里便是苏州监狱，嘿嘿。",
		"神照经" : (: ask_skills :),
		"人生奇遇": (: ask_qiyu :),
		"苏州" : "这里便是苏州。",
		"连城诀" : "你问这个干什么？哼......",
		"连城剑法" : "你问这个干什么？哼......",
		"万震山" : "梅念笙老先生收的三个不肖弟子啊，怎么有这样的江湖败类。",
		"言达平" : "梅念笙老先生收的三个不肖弟子啊，怎么有这样的江湖败类。",
		"戚长发" : "梅念笙老先生收的三个不肖弟子啊，怎么有这样的江湖败类。",
		"梅念笙" : "铁骨墨萼梅念笙老先生，可惜死得冤枉啊。",
		"菊友" : "她是霜华的贴身丫鬟。",
		"凌退思" : "他就是霜华的爹爹，真是苍天弄人啊。",
		"凌霜华" : "她就是翰林府大小姐，也是我最心爱的人。",
	])); 
		set("shenzhao/diyun",1);
		set("shenzhao",4);
		set("chat_chance_combat", 100);
		set("chat_msg_combat", ({
			(: exert_function, "shenzhao" :),
			(: perform_action, "cuff.wuying" :),
			(: perform_action, "cuff.shenquan" :),
		
		}));

	set("combat_exp", 15600000);
        set("shen_type", 1);
        setup();
        carry_object("/clone/armor/cloth")->wear();

}
void heart_beat()
{
	::heart_beat();
	clear_conditions_by_type("poison");
}
int accept_object(object me, object obj)
{
        object key;
        if ((string)obj->query("id")=="lu juhua") {
			message("vision",me->name()+"给丁典一盆绿菊花。\n",environment(me),({me}));
			key = unew("/clone/armor/wucanyi");
			if(!clonep(key)) return notify_fail (CYN"丁典说道：我已经托人给霜华捎话了，不劳您大驾了。\n"NOR);  
			if(clonep(key) && key->violate_unique()){
				destruct(key);
				return notify_fail (CYN"丁典说道：我已经托人给霜华捎话了，不劳您大驾了。\n"NOR);
			} 
			command("touch "+me->query("id"));
			command("say 这位"+RANK_D->query_respect(me)+"是霜华派你来捎话的吧,嗨！我们可是苦命的鸳鸯。");
			key->set("owner",me->query("id"));//
			key->move(me);        
			message_vision("$n递给$N一件乌蚕衣。\n", me, this_object() );
			if(!me->query(QUESTDIR1+"start"))
						me->set(QUESTDIR1+"start",1);//开始了哦
			command("say 这位"+RANK_D->query_respect(me)+"真是太感谢你了,这件宝衣你拿去用吧。");
			me->start_busy(1);
			remove_call_out("destroying");
			call_out("destroying", 1, this_object(), obj);
			return 1;
		}
        return 0;
}
//人生奇遇
string ask_qiyu()
{
	object me,ob;
	object *obj;
	int x;
	me = this_player();
	ob = this_object();
	if(!me->query_temp(QUESTDIR3+"start"))
	{
	   command("en");
	   command("say 我很忙，你没事别来烦我！\n");
	   return "癞蛤蟆想吃天鹅肉！";
	}
	if(me->query("shen")<0)
	{
	   command("heng "+me->query("id"));
	   return "你满身戾气，居然想替我帮忙，真是天大笑话，你给我走吧！";
	}


	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
	   return "我已经身陷官府之中，"+RANK_D->query_respect(me) +"还是自己小心通缉吧！";
	}
    
	command("say");
	command("look "+me->query("id"));
	//增加时间和经验间隔限制
	//时间一天，经验500K
	message_vision(HIY"$N对$n一脸的不屑，说道“既然你想体验这段奇遇，那咱们就开始好了！”。\n", ob,me);
	   command("say 我最近神照经武功即将大乘，有一些觊觎这门神功的人将陆续到来抢夺我手中秘籍，你若有心就替我警戒一阵！\n");
       command("say 遇到有人偷袭我,就将他们全部杀死，我一会将进入武功最后关头，能否成功就看你的了！\n ");
	//add_action("do_guard","kanshou");
	//add_action("do_guard","jingjie");

	//设定标志
	//me->set(QUESTDIR+"time",time());
	me->set(QUESTDIR+"combat_exp",me->query("combat_exp")); 	
	me->set_temp(QUESTDIR3+"kanshou",1);

	return "你要仔细体味我给你说的话，从中看能否领悟出啥内容来？\n切记切记，没有得到提示不要轻易离开,否则后果自负！\n";
}

string ask_diyun()
{
	object me,ob;
	object *obj;
	int x;
	me = this_player();
	ob = this_object();
	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
	   return "我已经身陷官府之中，"+RANK_D->query_respect(me) +"还是自己小心通缉吧！";
	}
	if(me->query(QUESTDIR1+"over"))
	{
	   command("en");
	   message_vision(HIY"$N脸上露出怀念的神色。\n", ob);
	   return "原来狄兄弟现在在雪山雪谷一带！恩，所谓吉人天相啊！";
	}
	if(!me->query(QUESTDIR1+"start" ))
	{
	   command("sneer "+me->query("id"));
	   command("say");
	   return "不知道你找狄兄弟干什么？！";
	}
	if(me->query(QUESTDIR1+"start" ) && (me->query_temp(QUESTDIR1+"start")|| me->query(QUESTDIR1+"over")))
	{
	   command("sigh");
	   message_vision(HIY"$N脸上露出怀念的神色。\n", ob);
	   return "我也不知道狄兄弟现在在哪里！也许吉人天相，但愿无碍！";
	}
    
	command("say");
	message_vision(HIY"$N脸上露出怀念的神色。\n", ob);
	command("look "+me->query("id"));
	//增加时间和经验间隔限制
	//时间一天，经验500K
	if(me->query(QUESTDIR+"time")&&time()-me->query(QUESTDIR+"time")<86400)
	{
		command("shake "+me->query("id"));
		if(random(2)) return "今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！";
		else return "寻找狄兄弟也不用急在一时，"+RANK_D->query_respect(me) +"先行休息去吧！";
	}
    if (!me->query("cw_exp"))

	   if(me->query(QUESTDIR+"combat_exp")&&me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<500000)
	{
		command("sigh "+me->query("id"));
		return "以"+RANK_D->query_respect(me) +"目前的经验就算去找，也帮不上什么忙，还是抓紧练功吧！";
	}
	obj = users();
	x = sizeof(obj);
	while(x--)
	{
		if ( obj[x]->query_temp(QUESTDIR1+"start")&& obj[x]!=me) 
			return ""+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"已经去雪山寻找狄兄弟了，"+RANK_D->query_respect(me) +"不用那么着急！";		  
	}
	command("say 恩，"+RANK_D->query_respect(me) +"能送来绿菊花真的很感谢了。");
	command("thank");
	command("say 当年我的确认识一个叫狄云的好兄弟，只是出狱后听说被雪山派血刀老祖抓走了。");
	command("yumen");
	command("shout");
	//设定标志
	me->set(QUESTDIR+"time",time());
	me->set(QUESTDIR+"combat_exp",me->query("combat_exp")); 	
	me->set_temp(QUESTDIR1+"start",1);
	me->set_temp("quest/busy",1);
	log_file("quest/LCHJ", sprintf("%8s(%8s)获得乌蚕衣，并开始执行Quest。\n", me->name(1),me->query("id")) );	
	return "";
}
int ask_skills() 
{
	object me = this_player();
	int i;
	if(me->query(QUESTDIR1+"start") && me->query(QUESTDIR4+"shenzhao"))
	{
		if(me->query("potential")>4)
		{
			message_vision("$N向$n请教有关神照经的奥妙。\n", me, this_object());
			me->receive_damage("jing", 10);
			tell_object(me,HIY"你听了丁典的指点，对神照经的奥妙似乎有些心得。\n"NOR);
			me->add("potential",-(random(3)+1));
			if( me->query("potential")<0)
				me->set("potential",0);
			if(me->query(QUESTDIR4+"shenzhao") < 2 && me->query_skill("shenzhao-jing")>=300)
			{
				if(random(6)==1) tell_object(me,HIR"丁典突然很神秘地指点道：你现在神照经已经到这等地步，可以寻找狄云兄也许有更深地了解。\n"NOR);			
				me->improve_skill("shenzhao-jing", 10+random(me->query_int()));//学习速度变化
			}
			else
			{
				if(me->query_skill("shenzhao-jing")>=300 || me->query_skill("shenzhao-jing")<=250)//学习速度控制
				{
				   me->improve_skill("shenzhao-jing", 25+random(me->query_int()*2));
			       me->improve_skill("force", random(me->query_int())/2);
			  }
			  else
			  {
				   me->improve_skill("shenzhao-jing", 25+random(me->query_int()));
			       me->improve_skill("force", random(me->query_int())/2);
			  }
			}
			

		}
		else 
		{
			message_vision("$N向$n请教有关神照经的奥妙。\n", me, this_object());
			tell_object(me,HIY"你听了丁典的指点，可是还是不能理解。\n"NOR);
		}
		return 1;
	}
	if(me->query(QUESTDIR1+"start"))
	{
		command("look "+me->query("id"));
		//普通玩家三次
		if(me->query(QUESTDIR4+"shenzhao_fail")>=3 && me->query("registered")<3)
		{
			command("papaya "+me->query("id"));
			command("say 已经多次传授，这位"+RANK_D->query_respect(me) +"怎么都还没有领悟！");
			command("puke "+me->query("id"));
			return 1;
		}
	   //武功学习之间需要间隔一天，经验需要间隔50K
	   if(me->query(QUESTDIR4+"time") && time()-me->query(QUESTDIR4+"time")<86400)
	   {
		   command("shake "+me->query("id"));
		   command("say 今天先教到到这里吧，明天吧。");
		   return 1;
        }
		
if (!me->query("cw_exp"))
			if(me->query(QUESTDIR4+"combat_exp") && me->query("combat_exp")-me->query(QUESTDIR4+"combat_exp")<50000)
	     {
		   command("look "+me->query("id"));
		   command("say 以"+RANK_D->query_respect(me) +"当前的经验恐怕还是难以领悟，还是抓紧去练功去吧。");
		   return 1;
	     }

	   me->set(QUESTDIR4+"time",time());
	   me->set(QUESTDIR4+"combat_exp",me->query("combat_exp")); 
	   i= random(15);
	   if(i==2 
	   && me->query("kar")<31  
	   && random(me->query("kar"))>27)
	   {
		   command("say 这是铁骨墨萼梅念笙老先生曾经教我的一套内功的秘经。我就传授给"+RANK_D->query_respect(me) +"吧。");
		   command("say ‘神照经’功夫，是天下内功中威力最强、最奥妙的法门。");		   
		   command("pat "+me->query("id"));
		   tell_object(me,HIY"你听了丁典的指点，对神照经的奥妙似乎有些心得。\n\n"NOR);
		   me->improve_skill("shenzhao-jing", 5+random(me->query_int()));
		   me->improve_skill("force", random(me->query_int())/2);
		   command("haha "+me->query("id"));	
		   command("gao");
		   command("u&me "+me->query("id"));
		   me->set(QUESTDIR4+"shenzhao",1);
		   me->set("quest/shenzhao/ding",1);//丁典标识
		   log_file("quest/LCHJ", sprintf("%s(%s) 失败%d次学到神照经绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query(QUESTDIR4+"shenzhao_fail"),i,me->query("combat_exp")) );
	   }
	   else
	   {
		   command("say 这是铁骨墨萼梅念笙老先生曾经教我的一套内功的秘经。我就传授给"+RANK_D->query_respect(me) +"吧。");
		   if(random(2)) command("say 如果你留心，当年在武馆之内就刻有神照经内功心法。嘿嘿。");
		   command("say ‘神照经’功夫，是天下内功中威力最强、最奥妙的法门。");		
		   command("ah "+me->query("id"));
		   tell_object(me,HIY"你听了丁典的指点，可是对神照经的奥妙全然不得要领。\n\n"NOR);
		   command("sigh "+me->query("id"));
		   me->add(QUESTDIR4+"shenzhao_fail",1);//
		   command("courage");   		   
		   log_file("quest/LCHJ", sprintf("%s(%s) 学习神照经失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query(QUESTDIR4+"shenzhao_fail"),i,me->query("combat_exp")) );
	   }
	   return 1;
	} 
	command("hehe");
	command("say 你问这个干嘛。神照经是铁骨墨萼梅念笙老先生曾经教我的一套内功的秘经。");
	command("smash");
	return 1;
}
void destroying(object me,object obj)
{
        destruct(obj);
        return;
}

