// sha.c 嵩山派第三代弟子 沙天江
// Creat by Lklv 2001.10.18

#include <ansi.h>
inherit NPC;
string ask_pixie();
string ask_job();
int ask_fangqi();
inherit F_MASTER;

void create()
{
        set_name("沙天江", ({ "sha tianjiang", "sha", "tianjiang" }));
        set("nickname", WHT"秃鹰"NOR);
        set("long", "这是一个秃头老者,和卜沉是长期混迹于江河的英豪。\n");
        set("gender", "男性");
        set("unique", 1);
        set("age", 45);
        set("per", 20);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 26);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("unique", 1);

        set("max_qi", 13000);
        set("max_jing", 4000);
        set("eff_jingli", 4000);
        set("jiali", 150);
        set("combat_exp", 3600000);
        set("eff_neili", 4000);
        set("shen", -150000);
		set_skill("songyang-jue", 150);

		set_skill("literate", 100);
		set_skill("force", 250);
		set_skill("parry", 250);
		set_skill("blade", 250);
		set_skill("dodge", 250);
		set_skill("hand", 250);
		set_skill("zhongyuefeng", 250);
		set_skill("songyang-shou", 250);
		set_skill("hanbing-zhenqi", 250);
		set_skill("fenshui-daofa", 250);
		//set_skill("whip", 220);
	  //  set_skill("songyang-bian", 220);

		map_skill("force", "hanbing-zhenqi");
		map_skill("dodge", "zhongyuefeng");
		map_skill("hand", "songyang-shou");
		map_skill("parry", "songshan-jian");
		map_skill("blade", "fenshui-daofa");
		prepare_skill("hand", "songyang-shou");

		create_family("嵩山派", 4, "弟子");
		set("class", "songshan");
		set("chat_chance_combat", 10);
		set("chat_msg_combat", ({
			(: perform_action, "blade.fenshui" :),
			(: perform_action, "hand.junji" :),
			(: exert_function, "juhan" :),
		}));
		set("inquiry", ([
			"辟邪剑法" : (: ask_pixie :),
			"任务" : (: ask_job :),
			"放弃" : (: ask_fangqi :),

		]) );
			setup();
			carry_object(ARMOR_D("changpao1"))->wear();
			carry_object(BINGQI_D("blade"))->wield();
}
void attempt_apprentice(object ob)
{
	if (!ob->query("quest/ss/rumen/pass"))
	{
		command("say 你先通过狄修师弟的考验再说！\n");
		command("say 你有何德何能拜我为师？\n");
		command("say 我又何原何故收你为徒？\n");
		command("say 大嵩山需要忠诚的门徒，你还是先做给我看吧？\n");
		return;
	}
	if (ob->query("family/family_name")!="嵩山派")
	{
		command("say 一看就是鬼鬼祟祟之徒，为何到此？\n");
		return;
	}
	if(ob->query_skill("hanbing-zhenqi",1) < 120 ){
		command("say 你的寒冰真气太弱了，不足120别来找我！");
		return;
	}
	if(ob->query("party/gongji") < 1000 ){
		command("say 你的门派功绩不够1000，别来找我！");
		return;
	}
	if(ob->query("shen") > -10000 ){
		command("say 嵩山剑法以狠辣著称（<-100k），你这娘娘腔一看就不够心狠手辣，快滚！");
		return;
	}
	command("say 好吧，师傅正要我多培育一些弟子来发扬嵩山派呢。");
	command("recruit " + ob->query("id"));
}

string *names = ({
"/d/fuzhou/bank",	"/d/fuzhou/beijie",	"/d/fuzhou/beimen",
"/d/fuzhou/biaoju",	"/d/fuzhou/bridge",	"/d/fuzhou/chalou",
"/d/fuzhou/chalou2",	"/d/fuzhou/dangpu",	"/d/fuzhou/dongjie",
"/d/fuzhou/dongxiang","/d/fuzhou/dongxiang2",
"/d/fuzhou/feiyuan",	"/d/fuzhou/fenduo1",	"/d/fuzhou/haigang",
"/d/fuzhou/houyuan",		"/d/fuzhou/huadian",	"/d/fuzhou/island1",
"/d/fuzhou/island2",	"/d/fuzhou/island3",	"/d/fuzhou/island4",
"/d/fuzhou/island5",	"/d/fuzhou/jiuguan",	"/d/fuzhou/kezhan",
"/d/fuzhou/kezhan2",	"/d/fuzhou/lagoon",	"/d/fuzhou/lagoon1",
"/d/fuzhou/lagoon2",	"/d/fuzhou/laozhai",
"/d/fuzhou/midao",	"/d/fuzhou/minzhai",
"/d/fuzhou/mupeng",	"/d/fuzhou/nanjie",	"/d/fuzhou/nanmen",
"/d/fuzhou/road1",	"/d/fuzhou/road2","/d/fuzhou/road3",
"/d/fuzhou/road4",	"/d/fuzhou/road5",	"/d/fuzhou/rock",
"/d/fuzhou/wroad1",	"/d/fuzhou/wroad2","/d/fuzhou/wroad3",
"/d/fuzhou/wroad4",	"/d/fuzhou/wroad5",	"/d/fuzhou/wroad6",
"/d/fuzhou/wroad7",	"/d/fuzhou/wroad8","/d/fuzhou/wroad9",
"/d/fuzhou/wroad10",	"/d/fuzhou/xijie",	"/d/fuzhou/xijie2",
"/d/fuzhou/ximen",	"/d/fuzhou/xixiang","/d/fuzhou/xixiang3",
"/d/fuzhou/xixiang4",	"/d/fuzhou/xixiang2",	"/d/fuzhou/xyxiang",
"/d/fuzhou/xyxiang2",	"/d/fuzhou/yaopu","/d/fuzhou/yuchuan1",
"/d/fuzhou/yuchuan2",	"/d/fuzhou/yuchuan3",	"/d/fuzhou/yuchuan4",
"/d/fuzhou/yuchuan5",	"/d/fuzhou/yugang",	"/d/fuzhou/zahuopu",
"/d/fuzhou/zhangfang",	"/d/fuzhou/zhengting","/d/fuzhou/zhongxin",
"/d/fuzhou/shanpo",	"/d/fuzhou/shiqiao","/d/fuzhou/wjiuguan"
});

string ask_pixie()
{
	object me=this_player();
	if (me->query("family/family_name")!="嵩山派")
	{
		command("say 你不是我嵩山弟子，来此作甚？");
		return "哼！";
	}
	if (me->query_skill("force",1)<100)
	{
		command("say 你基本内功不足100，来此作甚？");
		return "哼！";
	}
	
	command("say 辟邪剑法是个好东西。\n");
	command("say 当初林远图凭借该剑法名震江湖，无可匹敌。\n");
	command("say 前几天正好有内部消息说华山岳不群这个伪君子蠢蠢欲动，不知道他们要干什么。\n");
	me->set_temp("ss/pixie/asksha",1);
	return "";

}


//门派嵩山抢辟邪剑谱job

string ask_job()
{
	object ob, me, ling;
	object jianxi;
	mixed objwhere;
	int i;
	string str,stw;
	me=this_player();
	ob = this_object();
	
	//ling = present("songyang ling", me);
    
	if (!me->query_temp("ss/pixie/asksha"))
	{
		command("say 你我无缘无故，凭什么要回答？\n");
		return "最近总有些不相干的人，怕有奸细！\n";
	}
	if(me->query("family/family_name")!="嵩山派") 
           return "你不是我嵩山弟子，这种门派恩怨你就不要参与了。 ";

	if (me->query_temp("ss/pixie/name"))
		return "我不是让你去福州一代寻找华山剑派中那个偷了辟邪剑谱的"+me->query_temp("ss/pixie/name")+"么？！\n";

	if ((int)me->query("combat_exp") < 100000)
		return "你武功未成，这么危险的任务还是别做了！\n";

	if (me->query("job_name") == "嵩山抢辟邪剑谱")
		return "你刚做完嵩山抢辟邪剑谱任务，你自己去修习武功去吧！";

	if(me->query_condition("job_busy"))
		return "你现在正忙着做其他任务呢！";
	if(me->query_condition("sspixie_busy"))
		return "你现在正忙着做嵩山抢辟邪剑谱任务呢！";

	if(me->query_temp("quest/busy")) //added by tangfeng 与quest冲突
		return "现在我这里没有给你的任务，你还是先处理好你其他事情再说吧。";
    
	//定义奸细属性
    jianxi=new("/d/songshan/npc/hsdizi");
	jianxi->set("long",jianxi->query("long")+"\n这是"+me->query("name")+"即将追杀的华山派捣乱分子！\n"NOR);
	jianxi->set("owner",me->query("id"));
	//赋值jianxi
	i=1;
	jianxi->do_copy(me,i);
	//定义奸细位置
	//str=names[random(sizeof(names))];
	
	objwhere = names[random(sizeof(names))];

	//objwhere =load_object(str);
	if (!objwhere) objwhere = names[random(sizeof(names))];
	jianxi->apply_condition("npc_die",30);
	jianxi->move(objwhere);
	
	command("nod "+me->query("id"));
	message_vision(HIY"$N给我听好，经内线报告，最近发现华山派伪君子岳不群门下弟子有异常活动！\n"NOR,me);
	tell_object(me,"刚得到福州门中弟子情报，确认是华山派弟子在"+objwhere->query("short")+"方圆两里左右觊觎林家辟邪剑谱！\n");
	tell_object(me,"此人的名字叫“"+jianxi->query("name")+"("+jianxi->query("id")+")”，你速去拦截，别让他目的得逞！\n");
	tell_object(me,"我算了下时辰，他刚被发现不多久，应该就在福州一带附近，你快去快回，不要耽搁！\n");
	tell_object(me,"抓到他后直接就地处决，带人头见我，以儆效尤，如果他身上有关于辟邪剑法的消息也一并带给我！\n");
	
	me->set_temp("ss/pixie/place",objwhere->query("short"));
	me->set_temp("ss/pixie/id",jianxi->query("id"));
	me->set_temp("ss/pixie/name",jianxi->query("name"));
	me->set_temp("ss/pixie/time",time());
	me->set_temp("ss/pixie/nandu",i);
	
	me->apply_condition("sspixie_busy", 30 + random(5));
	me->apply_condition("job_busy", 30);

	
	return "此事关系到掌门并派大事，事不迟疑，你要快去快回！\n";
	
}
int accept_object(object who,object obj)
{
	object obb;
	int gg;
	string msg;
	gg=1+random(3);
	obb=obj->query("kill_by");
	if (obj->query("name")==who->query("ss/pixie/name")
		||obb->query("id")==who->query("id"))
	{
		command("haha "+who->query("id"));
		command("say 你能将"+obj->query("victim_name")+"这个小伪君子给我杀了，我很高兴！\n");
		command("pat "+who->query("id"));
		command("say 这说明你最近武功修炼不错，我很看好你！\n");
		command("say 你先下去好好休息吧！\n");
		destruct(obj);
		message_vision(RED"\n\n沙天江甩手将这颗人头用石灰腌制起来，放到角落里，嘿嘿阴笑不已！\n"NOR,who);
	
	
		

		TASKREWARD_D->get_reward(who,"嵩山辟邪",-1,0,0,2,0,0,0,"沙天江");  
		who->add("party/gongji",1+random(1));
		//who->add("job_time/嵩山追杀",1);
		tell_object(who,HIG"你获得了"+chinese_number(gg)+"点门派贡献奖励！\n"NOR);
		who->set("job_name","嵩山抢辟邪剑谱");

		if (random(who->query("job_time/嵩山辟邪"))>800
			&&random(who->query("kar"))>26)
		{
			message_vision(HIG"\n沙天江冲你哈哈大笑，说道，“你这个娃娃不错，掌门让我告诉你光荣地成为我派嫡传弟子”！\n"NOR,who);
			who->set("title","嵩山派嫡传弟子");
			who->set("quest/ss/dichuan",1);
		}
		//增加判断去解密辟邪剑法的提示
		who->apply_condition("job_busy",3);
		who->apply_condition("sspixie_busy",3);
		who->delete_temp("ss/pixie");
	}	
	return 1;
}
int ask_fangqi()
{
	object me;
	mapping ob;
	string name;
	me=this_player();
	command("heng "+me->query("id"));
	command("angry "+me->query("id"));
	if (!me->query_temp("ss/pixie"))
	{
		command("say 你什么都没做，瞎放弃什么？\n");
		return 1;
	}

	command("say 既然你完不成就暂时下去歇息去了，我算是记住你了。\n");
	me->delete_temp("ss/pixie");
	me->apply_condtion("job_busy",4);

	return 1;
}