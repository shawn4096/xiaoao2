// NPC: /d/huashan/npc/yuebuqun.c
// Date: Look 99/03/25
// Modify by Looklove 2000,12,15
// By Spdierii@ty 重要npc.杀不死
// by lsxk@hsbbs  统一奖励算法 2007/1/10

inherit NPC;
inherit F_MASTER;

#include <job_mul.h>
#include <ansi.h>
string ask_zhengqi();
string ask_zixia();
string ask_me1();
string ask_me2();
string ask_pay();
string ask_fail();
string ask_qizong();
string ask_jianzong();
string ask_fengyi();
string ask_hssb();
string ask_ziyin();
int ask_jianzong();
int do_huida(string arg);
void create()
{
	set_name("岳不群",({"yue buqun", "yue", "buqun" }));
	set("title","华山派第十三代掌门人");
	set("nickname",HIG"君子剑"NOR);
	set("long", "这就是在江湖中侠名远播，疾恶如仇，华山派掌门人。\n");
	set("age", 40);
	set("attitude", "friendly");
	set("no_bark",1);
	set("shen_type", 1);
	set("job_npc", 1);
	set("no_get", 1);

	set("per", 25);
	set("pur", 10);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);

	set("max_qi",23800);
	set("qi", 23800);
	set("max_jing", 6400);
	set("jing",6400);
	set("eff_jingli", 5700);
	set("jingli", 5700);
	set("max_neili", 15500);
	set("neili", 15500);
	set("jiali", 200);
	set("combat_exp", 9800000);
	set("score", 30000);
	set("chat_chance_combat",60);
	set("chat_msg_combat", ({
		(: perform_action, "sword.jianzhang" :),
		//(: perform_action, "sword.kuaijian" :),
		(: perform_action, "sword.fengyi" :),
		(: exert_function, "zixia" :),
		//(: perform_action, "sword.kuaijian" :),
		(: perform_action, "sword.lianhuan" :),
		(: perform_action, "sword.cangsong" :),
		(: perform_action, "sword.shijiushi" :),
		(: exert_function, "zixia" :),
		(: exert_function, "jianyi" :),
		(: exert_function, "jianqi" :),
	}));

	set_skill("poyu-quan", 400);
	set_skill("cuff", 400);
	set_skill("sword",  460);
	set_skill("dodge",  400);
	set_skill("force",  480);
	set_skill("parry",  400);
	set_skill("literate",400);
	set_skill("zixia-gong", 480);
    set_skill("huashan-qigong", 450);
	set_skill("huashan-jianfa",  460);
	set_skill("huashan-shenfa",  400);
	set_skill("zhengqi-jue", 200);
	set_skill("ziyin-yin", 200);
    set_skill("hunyuan-zhang", 400);
    set_skill("strike", 400);
    map_skill("strike", "hunyuan-zhang");
	map_skill("dodge", "huashan-shenfa");
	map_skill("force","zixia-gong");
	map_skill("sword","huashan-jianfa");
	map_skill("parry","huashan-jianfa");
	map_skill("cuff","poyu-quan");
	prepare_skill("strike","hunyuan-zhang");
	create_family("华山派",13,"掌门");

	set("inquiry", ([
		"紫霞秘籍"	: (: ask_zixia :),
		"紫氤吟"	: (: ask_ziyin :),
		"失败"		: (: ask_fail :),
		"fail"		: (: ask_fail :),
		"惩恶扬善"	: (: ask_me1 :),
		"job"		: (: ask_me1 :),
		"复命"		: (: ask_me2 :),
		"完成"		: (: ask_me2 :),
		"finish"	: (: ask_me2 :),
		"正气诀"	: (: ask_zhengqi :),
		"有凤来仪"	: (: ask_fengyi :),
        "剑气之争"      : (: ask_qizong :),
        "华山剑宗"      : (: ask_jianzong :),
		"华山石壁"      : (: ask_hssb :),
	]));

	setup();
	carry_object(BINGQI_D("sword"))->wield();
	carry_object(ARMOR_D("cloth"))->wear();
}

void heart_beat()
{
	::heart_beat();

	clear_conditions_by_type("poison");
	if( !is_fighting() && living(this_object()))
		reincarnate();
}

void init()
{
	object ob;
	//add_action("do_huidai","answer");
	add_action("do_huida","answer");
	::init();
	ob = this_player();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object me)
{
	int shen;
	if(!me) return;

	if ( file_name(environment(this_object())) != this_object()->query("startroom")) return;

	shen = me->query("shen");
    if(shen <= -200000 
		&& me->query("family/family_name") == "华山派" 
		//&& me->query("quest/huashan")=="气宗"
		){
		command("disapp "+me->query("id"));
		command("say 你满眼瘴气，身带邪气，从今天起你不再是华山弟子了！");
        command("expell " + me->query("id"));
		command("say 好，我算记住你了，你已经被我开除了"+me->query("expells")+"次!\n");

		if (!me->query("expells"))
		{			
			me->set("expells",1);
		}else me->add("expells",1);
       // me->delete("quest/huashan");
	}
	//警告！
	if(shen <0 && shen > -200000 && me->query("family/family_name") == "华山派"){
		command("sigh "+me->query("id"));
		command("say 我看你满眼瘴气，身带邪气，最近是不是在外面做了什么坏事？");
		command("say 如果被我查到你做过有辱我华山声名的事，我定不饶你！");
	}
}

void attempt_apprentice(object ob)
{
	mapping fam;
	if ( mapp(fam=ob->query("family"))
	 && (string)fam["family_name"] != "华山派"
	 && (int)ob->query("is/huashan")==1 ) {
		message_vision(CYN "$N！你这个华山派的叛徒还回来干什么 ？？？\n"NOR, ob );
		command("kick "+ob->query("id"));
		return;
	}
	if ( ob->query("fengset")) {
		command("say 你不是已经拜了剑宗的前辈为师了么？");
		return;
	}
	if(ob->query("quest/huashan")=="剑宗"){
    command("heng");
    command("say 哼哼！剑宗弟子早已离开华山，不再是华山派弟子，你又来这里，难道是想争夺这掌门之位？");
    return;
    }
	if (!ob->query("quest/hs/dichuan"))
	{
		command("consider");
		command("look "+ob->query("id"));
		command("say 你并非我华山的嫡传弟子，拜我为师好早呢。有机会你多去为华山砍点柴。");
		return ;
	}
	if ( ob->query("gender") != "男性" ){
		command("say 我只收男徒，" + RANK_D->query_respect(ob) + "请回吧。");
		return;
	}
	if ( ob->query_skill("huashan-qigong",1) <300 ){
		command("say 我只收男徒，" + RANK_D->query_respect(ob) + "你的华山气功不足300，还是请回吧。");
		return;
	}
	if ((int)ob->query("shen") < 1000000) {
		command("say 我华山派乃是堂堂名门正派，对弟子要求极严，不足1M正气来此作甚？。");
		command("say 在德行方面，" + RANK_D->query_respect(ob) + "是否还做得不够？");
		return;
	}
	command("say 好吧，我就收下你了,你可要为我们华山派争口气。");
	command("recruit " + ob->query("id"));
	ob->set("title","华山派气宗亲传弟子");
    ob->set("quest/huashan","气宗");
}

string ask_ziyin()
{
    object me;
    mapping fam;
	string msg,arg;
    me=this_player();

    if ( mapp(fam=me->query("family"))
    && (string)fam["family_name"] != "华山派"){
    command("? "+me->query("id"));
    return "这位" + RANK_D->query_respect(me) + "哪里听来的谣传？\n";
    }
    if (me->query("quest/huashan")=="剑宗")
       return "哼哼！剑宗弟子早已离开华山，不再是华山派弟子，你又来这里，难道是想争夺这掌门之位？\n";

   //if ((int)me->query("combat_exp")<4500000)
       //return "哎。。你这点经验值，我看还是算了吧。华山派不幸啊，这些陈年旧事跟你还提他做甚？\n";
   if ((int)me->query_skill("force")<350)
       return "哎。你这点内功基础太弱了,不足350。领悟不了这紫氤吟的真意？\n";
   
   if(me->query_temp("zyy/askyue")){
       
       return "刚才不是都告诉你了么？还想让我重复说一便？你当听童话故事啊？";
   }
   command("say 我华山派气宗完全靠内功致胜，初期还不明显，但越到后期，你才能体味为师这句话的真意！");
   command("cry "+me->query("id"));
   command("say 前一阶段，我曾将华山气宗的炼精化气之法稍作总结，偶有心得！");
   command("say 你若感兴趣，就去我寝室看看，是否有这机缘！");

   me->set_temp("zyy/askyue",1);
   return me->name(1)+"，你可要从本门气功开始修炼，循序而进才行啊！";

}

string ask_qizong()
{
    object me;
    mapping fam;
	string msg,arg;
    me=this_player();

    if ( mapp(fam=me->query("family"))
    && (string)fam["family_name"] != "华山派"){
    command("? "+me->query("id"));
    return "这位" + RANK_D->query_respect(me) + "哪里听来的谣传？\n";
    }
/*
   if (me->query("quest/huashan")=="气宗")
       return "当年剑气之争，牺牲了数名华山好手，你可要好好修炼，光大华山派啊！\n";
*/
   if (me->query("quest/huashan")=="剑宗")
       return "哼哼！剑宗弟子早已离开华山，不再是华山派弟子，你又来这里，难道是想争夺这掌门之位？\n";

   if ((int)me->query("combat_exp")<4500000)
       return "哎。。你这点经验值，我看还是算了吧。华山派不幸啊，这些陈年旧事跟你还提他做甚？\n";
   if ((int)me->query_skill("force")<350)
       return "哎。你这点内功基础太弱了。华山派不幸啊，这些陈年旧事你还提他做甚？\n";
   if ((int)me->query("int")<35)
       return "华山派最讲究就是悟性，你先天悟性不足35，跟你说了也白搭？\n";

   if (me->query("fengget"))
    {
		command("consider");
		return "既然你已经得到剑宗传承，还想偷学我气宗的紫霞功";
	}
   if(me->query_temp("quest/huashan/xiangzheng")){
       add_action("do_huida","answer");
       return "怎么？还想让我重复说一便？你当听童话故事啊？";
   }
   command("say 我华山派的确有剑气之分，当年华山玉女峰一战，同门兄弟却相互撕杀，惨不忍睹啊！");
   command("cry "+me->query("id"));
   msg="我气宗弟子乃讲究“以气驭剑”，正所谓真气所至，草木皆为利剑。气为重，剑为辅！\n"
   +"内功一旦有成，剑招威力自然非同一日而语。再加上本派享誉江湖的“紫霞神功”，\n"
   +"练剑数十载，岂是那些只会花俏剑招，内功平平的剑宗弟子可比的？\n";
   command("say "+msg);
  
   add_action("do_huida","answer");
   me->set_temp("quest/huashan/xiangzheng",1);
   return me->name(1)+"，你可要从本门气功开始修炼，循序而进才行啊！";

}

//紫霞功第一步开始 标记为quest/huashan/zixia1,玩家去思过崖面壁，寻求领悟
int do_huida(string arg)
{
    object me=this_player();
	if(!me->query_temp("quest/huashan/xiangzheng")) return 0;

    if(!arg) return notify_fail("你想回答什么？\n");
    
    if(arg!="是" && arg !="yes") return notify_fail("请回答“是”来表示赞同看法！否则岳不群很生气。\n");
    if(arg == "是" || arg == "yes" ){
        me->set("quest/huashan","气宗");
		message_vision(HIM"$N点了点头，连声称“是，师傅！”\n"NOR,me);
		if (random(me->query("job_time/华山")) > 1000 && me->query_temp("hs/askzixia"))
	    {   
		command("pat "+me->query("id"));
	    command("say [华山九功，紫霞第一]，紫霞功最讲究心平气静，我看你还是先到思过崖去面壁静坐吧，看能否有所领悟。\n");
		me->delete_temp("quest/huashan/xiangzheng");
		me->delete_temp("hs/askzixia");
		me->set_temp("quest/huashan/zixia1",1);
		return 1;
	    }
		message_vision(HIC"岳不群面露赞许之色，似乎对$N的回答甚是满意。\n"NOR,me);
       // return 0;
    }
	return 0;
}

string ask_me1()
{
	int i;
	object ob, me, name1, ling;
	me=this_player();
	ob = this_object();
	ling = present("ling pai", me);
	name1 = me->query("id");
	i = me->query("shen");
    if(me->query_temp("mb")) 
           return "你还是先去思过崖面壁思过去吧。 ";
	if (!wizardp(me) && me->query("shen") < 1)
		return "你眼露凶光, 还想去惩恶扬善? ";

	if (!wizardp(me) && me->query_temp("hs/jobji"))
		return "你不能光说呀，倒是做出点成绩给我看看！\n";

	if (!wizardp(me) && (int)me->query("combat_exp") < 100000)
		return "你武功未成，这么危险的任务还是别做了！\n";

	if (me->query("job_name") == "惩恶扬善" && !wizardp(me))
		return "现在没有听说有恶人为害百姓，你自己去修习武功去吧！";

	if(!wizardp(me) && me->query_condition("job_busy"))
		return "你现在正忙着做其他任务呢！";

	if(me->query_temp("quest/busy")) //added by tangfeng 与quest冲突
		return "现在我这里没有给你的任务，你还是先处理好你其他事情再说吧。";
    if ( me->query_condition("job_busy")){
                if (me->query("job_name")=="惩恶扬善")
                  return "现在暂时还没有工作让你去做。";
                if( me->query("job_name"))
                  return "你刚做完"+me->query("job_name")+"任务，还是先休息一会吧。";
               return "你正忙着别的事情呢，等会再来。";
        }

	ob = new(__DIR__"obj/ling");
	ob->set("ever_owner",getuid(me));
	me->set_temp("hs/jobji",1);
	command("nod "+me->query("id"));
	ob->move(me);
	ob->set_temp("hsjob", name1);
	me->apply_condition("hs_job", 30 + random(5));
	me->apply_condition("job_busy", 30);
	me->set_temp("hs_time", uptime());
	tell_object(me, "岳不群给了你一块令牌。\n");
	return "听说现在华山附近经常出现一些恶贼，骚扰百姓，你去巡视一下，遇到恶人不可手软。\n";
}

string ask_zhengqi()
{
	mapping fam;
	object me, ob;
	int shen, exp, i;
	me = this_player();
	ob = this_object();
	shen = (int)me->query("shen", 1);
	exp = (int)me->query("combat_exp", 1);
	i = (shen - exp);
	fam = me->query("family");

	if (!fam || fam["family_name"] !="华山派")
		return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？\n";
	if( i < 1000 )
		return "你的侠义之气不够，如何叫我指点你的正气诀？\n";
	if( (int)me->query_skill("zhengqi-jue", 1) < 150 )
		return "你的正气诀未到火候，恐怕我无法指点你。\n";
	if( (int)me->query_skill("zhengqi-jue", 1) >= 200 )
		return "你的正气诀已到火候，恐怕我无法指点你。";
	if( (int)me->query("jing", 1) < 100 )
		return "你现在身体状况太差了，你无法领悟正气诀的绝妙之处。\n";
	if( (int)me->query("potential", 1) < 2 )
		return "你现在潜能不足，我无法指点你关于正气诀。\n";
	me->improve_skill("zhengqi-jue", 100 + random(100));
	me->add("shen", -1000);
	me->add("potential", -1);
	me->receive_damage("jing", random(100));
	tell_object(me, HIC"你感到心中激荡着侠义正气。\n"NOR);
	return  "好吧，既然你问起我正气诀，我就指点你一下。\n" ;
}

string ask_me2()
{
	return "你的令牌呢？";
}

int accept_object(object me, object ling)
{
	object name1;
	int getshen, total_job_times, done,gold,gold2,total_job_times2, tb ;
	int i,j;
	name1 = me->query("id");

	if( ling->query("id") != "ling pai")
		return notify_fail("岳不群说道：惭愧呀，华山派居然出了你这样的骗子！\n");
	if( ling->query_temp("mmr") != name1 && !wizardp(me)){
		command("hmm "+ me->query("id"));
		me->add("shen", -(int)me->query("job_time/华山",1));
		me->delete_temp("hs/jobji");
		me->delete_temp("hs/have");
		me->delete_temp("hs/power");
		me->delete_temp("hs/robot");
		call_out("destroying", 1, ling);
		return notify_fail("岳不群说道：你怎么这么没用？没敢去找到恶贼？\n");
	}
	if( ling->query_temp("hsjob") != name1 && !wizardp(me)) {
		command("hmm "+ me->query("id"));
		me->add("shen", -(int)me->query("job_time/华山",1) * 5);
		me->delete_temp("hs/jobji");
		me->delete_temp("hs/have");
		me->delete_temp("hs/power");
		me->delete_temp("hs/robot");
		call_out("destroying", 1, ling);
		return notify_fail("岳不群说道：这是你的令牌么？\n");
	}
	done = (int)ling->query_temp("done", 1);
	if( done < 2 && !(done==1 && me->query_temp("hs/robot")) )
		return notify_fail("岳不群说道：你还没完成师傅的任务呢。\n");
	if ( !me->query_temp("hs/jobji") && !wizardp(me)){
		command("hmm "+ me->query("id"));
		me->add("shen", -(int)me->query("job_time/华山",1) * 5);
		me->delete_temp("hs/jobji");
		me->delete_temp("hs/have");
		me->delete_temp("hs/power");
		me->delete_temp("hs/robot");
		call_out("destroying", 1, ling);
		return notify_fail("岳不群说道：你的令牌从哪里偷来的？\n");
	}
	if ( !me->query_condition("hs_job") && !wizardp(me)){
		command("hmm "+ me->query("id"));
		me->add("shen", -(int)me->query("job_time/华山",1) * 5);
		me->delete_temp("hs/jobji");
		me->delete_temp("hs/have");
		me->delete_temp("hs/power");
		me->delete_temp("hs/robot");
		call_out("destroying", 1, ling);
		return notify_fail("岳不群说道：你怎么去了这么长时间？\n");
	}
	write("岳不群看了看你的令牌。\n", me);
	command("thumb "+ me->query("id"));
	command("say 还望" + RANK_D->query_respect(me) + "日后多行善事，必有好报。\n");
    getshen = 1;
	if( me->query("family") && me->query("family/family_name") =="桃花岛") getshen = 0;


   if(done!=2)
       TASKREWARD_D->get_reward(me,"华山",getshen,0,0,random(2)-1,0,0,0,this_object());
   
   else
   {
       command("wa2 "+ me->query("id"));	   
       TASKREWARD_D->get_reward(me,"华山",getshen,0,0,2+random(2),0,0,0,this_object());	
   }

	me->delete_temp("hs_time");
	me->clear_condition("hs_job");
	me->clear_condition("job_busy");
	me->set("job_name","惩恶扬善");
              gold= 2000+random(1000);
      
        gold2=gold/5000+random(gold/5000);
              me->add("balance", gold);

	me->delete_temp("hs/jobji");
	me->delete_temp("hs/have");
	me->delete_temp("hs/power");
	me->delete_temp("hs/robot");
	me->delete_temp("mb");
	call_out("destroying", 1, ling);
//增加身份标记
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  18;


//edit by sohu
	// 风清扬 quest 控制
	// 经验值大于 10M 或 华山，送信，丐帮的随机数都大于 4000
	// 华山，送信，丐帮次数之和为 50 的倍数
	// 福缘随机数大于= 28
	// me->query("mianbi") < me->query("mianbi")/100000 + 1
	// by mxzhao 2004/05/07
	total_job_times = me->query("job_time/华山") + me->query("job_time/送信") + me->query("job_time/丐帮");
	total_job_times2 = me->query("job_time/华山") + me->query("job_time/武当");
	if (random(me->query("job_time/华山")) >40000
		&& random(me->query("job_time/送信")) >40000
		&& random(j)==7
		&& me->query("int")>40 //增加先天属性int以上方可有提示
        &&( (me->query_temp("sj_credit/quest/hs/jiujian")&& random(me->query("kar")) >= 28 )|| random(me->query("kar")) > 28) //修改之处
		&&( random(me->query("job_time/丐帮")) >1000 || random(me->query("combat_exp"))>12000000 )
		&& random(me->query("combat_exp"))>10000000
		&& !me->query("fengset")
		&& !me->query_temp("mb")
       // && !me->query("quest/hsjf/fengyi4_time")
		&& (me->query("mianbi") < me->query("combat_exp")/1000 + 1)
		&& me->query("family/family_name")=="华山派"
		&& total_job_times % 50 == 0 ) 
    	{
		    me->set_temp("mb", time());
		    me->add("mianbi", 1);
		    log_file("quest/jiujian",sprintf("%8s%-10s第%4d次华山任务时，上思过崖面壁，送信：%4d，丐：%4d，福：%2d，次：%d。\n",
			me->name(1),"("+capitalize(me->query("id"))+")",me->query("job_time/华山"), me->query("job_time/送信"),
			me->query("job_time/丐帮"), me->query("kar"), me->query("mianbi")),me);
		    command("say "+me->query("name")+"你杀了不少恶人，未免杀气过重不如上思过崖面壁忏悔吧。\n");
     	}
     /*      
	  else if (wizardp(me)||random(me->query("job_time/华山")) >4000
		&&( random(me->query("job_time/武当")) >4000 && random(me->query("combat_exp"))>8000000 )
        && random(me->query("kar")) >= 25

		&& !me->query_temp("mz_entrance")
		&& !me->query("quest/xxdf/pass")
		&& random(10)<5
		&& me->query("family/family_name")=="日月神教"
		&& total_job_times2 % 50 == 0 ) 
	{
		me->set_temp("mz_entrance", 1);
		command("say "+me->query("name")+"，听说魔教教主被关在杭州西湖湖底，你去把他杀了，我就让你入五岳剑派。\n");
		log_file("quest/xixing",sprintf("%8s%-10s华山任务时，去梅庄，华山：%4d，武当：%4d，福：%2d。\n",
			me->name(1),"("+capitalize(me->query("id"))+")",me->query("job_time/华山"), 
			me->query("job_time/武当"), me->query("kar")),me);
	}
	*/
	
	return 1;
}

string ask_zixia()
{
	mapping fam;
	object me;
	me = this_player();
	fam = me->query("family");

	if (!fam || fam["family_name"] !="华山派")
		return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？";
	if((int)me->query_skill("zhengqi-jue", 1) < 200 )
		return "你的正气诀未到火候，现在就来问紫霞秘籍，未免为时过早。";
	if((int)me->query_skill("huashan-qigong", 1) < 350 )
		return "你的华山气功未到火候，现在就来问紫霞秘籍，未免为时过早。";

	if(me->query_temp("quest/huashan/zixia4"))
	{
	  me->delete_temp("quest/huashan/zixia4");
	  me->set_temp("quest/huashan/zixia5",1);   
	  return "岳不群脸色阴沉，下意识地说道，”都是灵珊那丫头...!哼！一定华山内部出了内鬼！到底是谁呢？";
	  }

	me->set_temp("hs/askzixia",1);
	return  "紫霞秘籍乃我华山至宝，前段时间不知为何下落不明，唉，难道我堂堂华山派出了内贼不成？" ;
}

string ask_fengyi()
{
	mapping fam;
	object me;
	me = this_player();
	fam = me->query("family");

	if (!fam || fam["family_name"] !="华山派")
		return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？";
	if((int)me->query_skill("zhengqi-jue", 1) < 200 )
		return "你的正气诀未到火候，现在就来问有凤来仪，未免为时过早。";
	if((int)me->query_skill("huashan-qigong", 1) < 350 )
		return "你的华山气功未到火候，现在就来问有凤来仪，未免为时过早。";
	if((int)me->query_skill("huashan-jianfa", 1) < 350 )
		return "你的华山剑法未到火候，现在就来问【有凤来仪】，未免为时过早。";
	if (me->query("quest/hsjf/fengyi4/time")=="pass") return "你已经解开了有凤来仪。\n";
	if( (time() - (int)me->query("quest/hsjf/fengyi4/time"))<86400)		
     	  return "你来的也太勤快了耶，还是去休息一下吧。\n";
	if(me->query("quest/hsjf/fengyi4")=="pass")
	{
	  command("consider "+me->query("id"));
	  return "岳不群脸色阴沉，说道，你这剑法是从那里听说来的？我怎么从来没看见过？\n";
      }
	me->set_temp("hs/askyuefy4",1);
	me->set_temp("hssb/juejiasked",1);
	message_vision(HIC"岳不群长叹一声，自言自语道，当年魔教十长老围攻华山，一场大战使得我无数前辈俱都阵亡，很多武技失传，甚是可惜。\n"NOR,me);
	return  "有凤来仪乃是我华山派有数的杀招之一，可惜后来却失传了，你若真想领会这招，可以到思过崖去好好参悟一番。\n若真能参悟出来，为师也甚是高兴。我华山又将添一英才。\n" ;
}
string ask_fail()
{
	object me,ling;
	me = this_player();
	ling = present("ling pai", me);
	if(! me->query_temp("hs/jobji"))
		return "你又没领过任务，何谓失败啊？";
	if( ling && ling->query_temp("hsjob") == me->query("id"))
		destruct(ling);
	me->delete_temp("hs/jobji");
	me->delete_temp("hs/have");
	me->delete_temp("hs/power");
	me->delete_temp("hs/robot");
	me->clear_condition("hs_job");
	me->apply_condition("job_busy", 3+random(4));
	me->add("combat_exp", -(20+random(10)));
	return "既然如此，也不能勉强，你就先退下吧。";
}

void destroying(object ling)
{
	if (ling) destruct(ling);
}
void die()
{
	object ob;
	if (!query_temp("living"))
	{
		ob = new("/d/huashan/npc/yuebuqun");
		ob->move("/d/huashan/zhengqi");
	}
	::die();
}

int prevent_learn(object ob, string skill)
{
	if (skill == "zixia-gong")
		return 1;
	if (skill=="ziyin-yin"||skill=="zhengqi-jue")
	{
		write("这种功夫只能靠个人从书中参悟所得，你从师父这儿能学到什么?\n");
		return 1;
	}
	return 0;
}

string ask_jianzong()
{
	  object me=this_player();
      if (me->query("family/family_name")!="华山派" )
         return "你不是华山弟子，来打听这个问题，想要何为？";
      if (me->query("quest/huashan")=="剑宗" )
         return "你已经是剑宗弟子，早已被开除出华山，来此何为？";
      if (!me->query_temp("jianzong/askning"))
         return "你是从何处听说剑宗这件事的？";
      command("sigh "+me->query("id"));
      command("say 当初剑宗和气宗本是一家，后来因为所见不和，导致本门内剑气之分。\n");
      command("say 后来这种分歧越来越大，最终形成两派大比之势，以至于当年玉女峰一战。\n");
      command("say 双方一场比剑，好手彼此死伤不少，剑宗落败，但华山派实力也大损，\n");
      command("say 祖师爷爷凭借紫霞功力克剑宗数位长老，一战定乾坤，才有了我们现在的华山派，\n");
      message_vision(HIR"岳不群一面说着往事，神情肃然，忽然将自己的衣襟掀开，对$N喝道，"NOR,me);
      command("say 这就是为师当时留下的伤口，要不是当时为师年纪幼小，中剑后昏迷，嘿嘿...、\n");
      command("say 我华山门派最重事这剑宗和气宗之分，气功乃是纲，剑招乃是目，刚举方能目张。");
      command("look "+me->query("id"));
      command("say 你若是混淆了这纲目之分，便已经入了魔道，休怪为师不客气。\n");
      me->delete_temp("jianzong/askning");
      me->set_temp("jianzong/askyue",1);
      return "岳不群似乎想起了一种伤心往事，陷入沉思之中。\n\n\n随后，他悠悠地叹道，”当年玉女峰一战真是惨烈，至今还留有遗迹，“\n";
}

string ask_hssb()
{
	  object me=this_player();
	  if (me->query("family/family_name")!="华山派" )
         return "你不是华山弟子，来打听这个问题，想要何为？";
      if (me->query("quest/huashan")=="剑宗" )
         return "你已经是剑宗弟子，早已被开除出华山，来此何为？";
      if (me->query("quest/hs/hssb/pass"))
         return "你不是已经彻底领悟华山石壁的奥秘了么？还在这里啰嗦什么？\n";
	  if (me->query_skill("huashan-jianfa",1)<450)
	     return "你华山剑法不足450，去了也领悟不了。\n";

	  if (time()-me->query("quest/hs/hssb/time")<86400)
         return "你来的太勤快了点了！？\n";
	  
	  if (me->query_skill("huashan-jianfa",1)<450)
         return "你华山剑法不足450，去了华山石壁也是领悟不了。\n";
	  command("sigh ");
	  command("say 说起这件事，不得不说下陈年往事了。\n");
	  command("say 你既然问这个问题，应该是已经听说过十大长老围攻华山之役。\n");
	  command("say 这件事我也是听师傅说起过，双方战斗的极为灿烈。\n");
	  command("say 华山、嵩山、衡山、恒山、泰山诸位高手齐集华山，和魔教十大长老进行一场大战。\n");
	  command("say 最终以我们五岳联合胜利而告终，至此，我华山派等五岳剑派扬名江湖，而魔教却一蹶不振。\n");
	  command("say 地点就在华山附近，听师傅说好像在后山附近，但我当时幼小，尚不知详情。\n");
	  command("say 你既然问起来这段往事，师傅我就把这故事给你说说，我辈当继承祖师遗训，誓灭魔教。\n");
	  me->set_temp("hssb/juejiasked",1);
	  return "";

}