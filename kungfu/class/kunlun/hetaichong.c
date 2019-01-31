// hetaichong.c (kunlun)
// By Spiderii 暂时关闭，不收徒
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string ask_me();
string ask_fail();
string ask_qinji();
string ask_job();
int accept_object(object who,object obj);
string ask_feipu();

#include <job_mul.h>
//#include "d/kunlun/npc/jianxi.h"

string *names = ({
"/d/fairyland/shanlu1",	"/d/fairyland/shanlu2",	"/d/fairyland/hmzhuang",
"/d/fairyland/dating",	"/d/fairyland/nuange",	"/d/fairyland/houyuan",
"/d/fairyland/lggong",	"/d/fairyland/shanxi",	"/d/fairyland/xuanya",
"/d/group/entry/klclin1",
"/d/kunlun/klshanlu","/d/kunlun/shanmen",
"/d/kunlun/shanlu01",	"/d/kunlun/shanlu02",	"/d/kunlun/shanlu03",
"/d/kunlun/shanlu04",		"/d/kunlun/guangchangw",	"/d/kunlun/guangchang",
"/d/kunlun/guangchange",	"/d/kunlun/pingfeng",	"/d/kunlun/qianting",
"/d/kunlun/keting2",	"/d/kunlun/elang01",	"/d/kunlun/wlang01",
"/d/kunlun/keting1",	"/d/kunlun/shilu1",	"/d/kunlun/shufang",
"/d/kunlun/jingxiushi",	"/d/kunlun/huayuan1",	"/d/kunlun/lang",
"/d/kunlun/lang2",	"/d/kunlun/liangong",	"/d/kunlun/lang1",
"/d/kunlun/sanshengtang",	"/d/kunlun/gate",	"/d/kunlun/shilu2",
"/d/kunlun/jiuqulang2",	"/d/kunlun/shanlin1","/d/kunlun/shanlin2",
"/d/kunlun/shanlin3",	"/d/kunlun/houyuan",	"/d/kunlun/fufengshan",
"/d/kunlun/jiuqulang1",	"/d/kunlun/tieqinju","/d/kunlun/shiqiao"
});


void create()
{
	set_name("何太冲", ({ "he taichong", "he" }));
	set("title", "昆仑派掌门");
        set("nickname", MAG"铁琴先生"NOR);
	set("long",
		"他就是昆仑派掌门、名扬江湖的铁琴先生何太冲。\n"
		"虽然年纪已大，但仍然看得出他年轻时英俊潇洒。\n");
	set("gender", "男性");
	set("age", 40);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);

	set("max_qi", 13500);
	set("max_jing", 6000);
	set("neili", 29000);
	set("max_neili", 29000);
	set("eff_jingli", 6000);
	set("jiali", 200);
	set("combat_exp", 12500000);
	set("score", 4000);
	set("qinji-book",1);
	set_skill("art", 200);
    set_skill("literate", 250);
	set_skill("force", 460);
	set_skill("xuantian-wuji", 460);
	set_skill("dodge", 460);
	set_skill("taxue-wuhen", 460);
	set_skill("parry", 460);
	set_skill("sword", 480);
	set_skill("liangyi-jue", 160);
	set_skill("liangyi-jian", 480);
	set_skill("cuff", 460);
	set_skill("zhentian-quan", 460);
	set_skill("strike", 460);
	set_skill("kunlun-zhang", 460);
	map_skill("strike", "kunlun-zhang");
	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("cuff", "zhentian-quan");
	map_skill("parry", "liangyi-jian");
	map_skill("sword", "liangyi-jian");
	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
  		(: perform_action, "sword.feipu" :),
		(: perform_action, "sword.jinzhen" :),

  		(: perform_action, "sword.feihua" :),
		(: perform_action, "sword.duanyun" :),
		(: exert_function, "wuji" :),			
  		(: perform_action, "dodge.taxue" :),
	}));
	prepare_skill("cuff", "zhentian-quan");
	prepare_skill("strike", "kunlun-zhang");

    create_family("昆仑派", 3, "掌门人");
	set("class", "taoist");

	set("inquiry", ([
		"心法" : (: ask_me :),
		"琴技入门技巧" : (: ask_qinji :),
		"放弃" : (: ask_fail :),
		"fail" : (: ask_fail :),
		"百丈飞瀑绝技" : (: ask_feipu :),

		"工作" : (: ask_job :),
		"job" : (: ask_job :),

	]));

	set("book_count", 1);
	set("ding_count", 18);

	setup();
	carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/kunlun/obj/pao2.c")->wear();
}
void attempt_apprentice(object ob)
{
        if(ob->query("gender")=="女性"){
 	    command("haha");
	    command("say "+RANK_D->query_respect(ob)+"老夫可不敢收女弟子，你去找我夫人去吧。");
	    return;
	}
        if(ob->query("appren_hezudao", 1) == 1) {
  	   command("say "+RANK_D->query_respect(ob)+"怎敢开这等玩笑，真是折杀我了。");
	   return;
	}
	if(ob->query_skill("xuantian-wuji",1) < 300){
  	   command("hmm");
	   command("say "+RANK_D->query_respect(ob)+"你的玄天无极功太差，不足300，我可不想收你。");
 	   return;
	}
	if(ob->query_skill("zhentian-quan",1) < 300){
  	   command("hmm");
	   command("say "+RANK_D->query_respect(ob)+"你的震天拳太差，不足300，我可不想收你。");
 	   return;
	}

	if(ob->query_skill("taixue-wuhen",1) < 300){
  	   command("hmm");
	   command("say "+RANK_D->query_respect(ob)+"你的踏雪无痕太差，不足300，我可不想收你。");
 	   return;
	}
	command("say 好吧，我便收下你，只是你投入我门下之后，须得安心学艺。");
	command("recruit " + ob->query("id"));
	ob->set("title","昆仑派第四代弟子");

}
string ask_me()
{
	mapping fam;
	object ob;

	if (!(fam = this_player()->query("family"))
	 || fam["family_name"] != "昆仑派")
	   return RANK_D->query_respect(this_player())+ "与本派素无来往，不知此话从何谈起？";

        if(this_player()->query("gender")!="女性" && this_player()->query("per") < 23)
   	   return "本派心经不在我这里。";

		ob = unew("/d/kunlun/obj/force-book.c");
        if(!clonep(ob)) return "你来晚了，本派心经已被你师兄拿走了。";
        if(clonep(ob) && ob->violate_unique()){
               destruct(ob);
  	       return "你来晚了，本派心经已被你师兄拿走了。";
        }
		ob->move(this_player());
		return "我这里有本「心法」，是有关吐呐吸气的，你拿回去好好钻研，有空多来找我哦";
}
string ask_qinji()
{
	mapping fam;
	object ob;

	if (!(fam = this_player()->query("family"))
	 || fam["family_name"] != "昆仑派")
	   return RANK_D->query_respect(this_player())+ "与本派素无来往，不知此话从何谈起？";  
		
		if (this_object()->query("qinji-book")<1)
		{
			 return "你来晚了，本派心经已被你师兄拿走了。";
		}
		if (this_player()->query_skill("xuantian-wuji",1)<200)
		{
			return RANK_D->query_respect(this_player())+ "你的玄天无极不足200，功力不够无法运气！\n";  
		}
		this_object()->add("qinji-book",-1);
		ob = unew("/d/kunlun/obj/string-book3.c");     
		ob->move(this_player());

		return "我这里有本「琴技入门技巧」，你拿回去好好钻研，有空多来找我哦";
}
//门派追杀奸细任务

string ask_ding()
{
        mapping fam;
	object ob;

	if (!(fam = this_player()->query("family"))
	 || fam["family_name"] != "昆仑派")
	    return RANK_D->query_respect(this_player())+ "与本派素无来往，不知此话从何谈起？";
		
	if(this_player()->query_skill("mantian-huayu",1) < 60)
            return "你如此自愿为师门效力，不枉我平时一番栽培，速速去吧";
		   
	if(present("sangmen ding", this_player()) )
	    return RANK_D->query_respect(this_player())+"你现在身上不是有吗，怎么又来要了？";

    if (query("ding_count") < 1)
	    return "丧门钉已给了我派去追杀苏习之的人，你就不用去了。";
	add("ding_count", -1);
	this_player()->set_temp("kunlun/ding",1);
	ob = new(BINGQI_D("sm_ding"));
	ob->move(this_player());
	return "你如此自愿为师门效力，不枉我平时一番栽培，这把丧门钉你就拿去吧。";
}

string ask_su()
{
        mapping fam;

	if (!(fam = this_player()->query("family"))
	 || fam["family_name"] != "昆仑派")
	    return RANK_D->query_respect(this_player())+ "与本派素无来往，不知此话从何谈起？";
		
	if(this_player()->query_temp("kunlun/ding",1))
            return "你还待在这里做什么，还不快去追苏习之";
	    return "苏习之这家伙竟然敢偷看本派的两仪神剑，我派弟子必当将其追杀。";
}

//门派追杀奸细job

string ask_job()
{
	object ob, me, ling;
	object jianxi;
	mixed objwhere;
	string str,stw;
	me=this_player();
	ob = this_object();
	
	ling = present("zhusha ling", me);
    
	if(me->query("family/family_name")!="昆仑派") 
           return "你不是我昆仑弟子，这种门派恩怨你就不要参与了。 ";

	if (me->query_temp("kl/zhuisha"))
		return "我不是让你去追杀一名偷学我昆仑武技的奸细"+me->query_temp("kl/zhuisha/name")+"了么？！\n";

	if ((int)me->query("combat_exp") < 100000)
		return "你武功未成，这么危险的任务还是别做了！\n";

	if (me->query("job_name") == "昆仑追杀奸细")
		return "你刚做完追杀奸细任务，你自己去修习武功去吧！";

	if(me->query_condition("job_busy"))
		return "你现在正忙着做其他任务呢！";
	if(me->query_condition("klzsjob_busy"))
		return "你现在正忙着做追杀奸细任务呢！";

	if(me->query_temp("quest/busy")) //added by tangfeng 与quest冲突
		return "现在我这里没有给你的任务，你还是先处理好你其他事情再说吧。";
    
	//定义奸细属性
    jianxi=new("/d/kunlun/npc/jianxi");
	jianxi->set("long",jianxi->query("long")+"\n这是"+me->query("name")+"即将追杀的昆仑派奸细！\n"NOR);
	jianxi->set("owner",me->query("id"));
	//赋值jianxi
	
	jianxi->do_clone(jianxi, me);
	//定义奸细位置
	//str=names[random(sizeof(names))];
	
	objwhere = names[random(sizeof(names))];

	//objwhere =load_object(str);
	if (!objwhere) objwhere = names[random(sizeof(names))];
	
	jianxi->move(objwhere);
	
	command("nod "+me->query("id"));
	message_vision(HIY"$N你给我听好，最近发现有些门派门下弟子进入我派中偷学我大昆仑武功，此事决不能罢休！\n"NOR,me);
	command("say 刚得到门中弟子情报，有人在"+objwhere->query("short")+"一带发现一名奸细！\n");
	command("say 你听好了，此奸细的名字叫“"+jianxi->query("name")+"("+jianxi->query("id")+")”，可别让他给跑了！\n");
	command("say 我算了下时辰，他刚被发现不多久，应该就在昆仑山附近，你快去快回，不要耽搁！\n");
	command("say 不管什么门派的，抓到他后直接就地处决，带人头见我，以儆效尤！\n");
	
	me->set_temp("kl/zhuisha/place",objwhere->query("short"));
	me->set_temp("kl/zhuisha/id",jianxi->query("id"));
	me->set_temp("kl/zhuisha/name",jianxi->query("name"));
	me->set_temp("kl/zhuisha/time",time());

	me->apply_condition("hs_job", 30 + random(5));
	me->apply_condition("job_busy", 30);

	
	return "因不知此人功力情况，你千万要小心，快去快回！\n";
	
}
int accept_object(object who,object obj)
{
	object obb;
	int exp,pot,exprelife,expdb;
	string msg;
	exp=100+random(20);
	pot=50+random(10);
	exprelife=0;
	expdb=0;
//如果身份不同奖励不同
	
	if(who->query("buyvip") )
       exp = exp + exp* 20/ 100;
	else if(who->query("y-card-vip"))
       exp = exp + exp * 10 / 100;
	else if(who->query("m-card-vip"))
       exp = exp + exp * 5 / 100;
	


	obb=obj->query("kill_by");
	if (obj->query("name")==who->query("kl/zhuisha/name")
		||obb->query("id")==who->query("id"))
	{
		command("haha "+who->query("id"));
		command("say 你能将"+obj->query("victim_name")+"这个奸细给我杀了，我很高兴！\n");
		command("pat "+who->query("id"));
		command("say 这说明你最近武功修炼不错，我很看好你！\n");
		command("say 你先下去好好休息吧！\n");
		destruct(obj);
		message_vision(RED"\n\n何太冲甩手将这颗人头从铁琴局二楼窗户中甩出，落入深涧！\n"NOR,who);
	
		msg=YEL"何太冲回头对你竖起大拇指，随手给了$N"+exp+"点经验值和"+pot+"点潜能！\n"NOR;
		//参悟exp
		if(who->query("relife/exp_ext"))
		{
           exprelife=exp*(int)who->query("relife/exp_ext",1) / 20;
		   msg+=YEL"经验参悟期间，$N又额外获得"+chinese_number(exprelife)+"点经验值！\n"NOR;

        }

        if(who->query_condition("db_exp")){  
            expdb=exp;
            msg += HIY + "双倍经验奖励期间，你额外地得到了" + HIW + chinese_number(expdb) + HIC + "点" + HIM + "经验！\n"NOR;
        }		
		//上限
		exp=exp+exprelife+expdb;

		if(who->query("combat_exp") > 75000000){
            exp =  exp * 5 /100;
            tell_object(obj,"你觉得自己最近心神不宁，对武学的研究已经进入了举步惟艰的程度，似乎就是江湖传说的『"+HIG+"武学障"+NOR+"』。\n");
        }
	//奖励
		who->add("combat_exp",exp);
		who->add("potential",pot);
		who->add("job_time/昆仑追杀",1);
		who->set("job_name","昆仑追杀奸细");
		message_vision(msg,who);

		if (random(who->query("job_time/昆仑追杀"))>800
			&&random(who->query("kar"))>25)
		{
			message_vision(HIG"\n何太冲冲你哈哈大笑，说道，“你这个娃娃不错，本掌门宣布你成为我派嫡传弟子”！\n"NOR,who);
			who->set("title","昆仑派嫡传弟子");
			who->set("quest/kl/dichuan",1);
		}
		who->apply_condition("job_busy",3);
		who->apply_condition("klzsjob_busy",3);
		who->delete_temp("kl/zhuisha");
	}	

	return 1;
}
int ask_fail()
{
	object me;
	mapping ob;
	string name;
	me=this_player();
	command("heng "+me->query("id"));
	command("angry "+me->query("id"));
	if (!me->query_temp("kl/zhuisha"))
	{
		command("say 你什么都没做，瞎放弃什么？\n");
		return 1;
	}

	command("say 既然你完不成就暂时下去歇息去了，我算是记住你了。\n");
	me->delete_temp("kl/zhuisha");
	me->apply_condtion("job_busy",4);

	return 1;
}

string ask_feipu()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="昆仑派")
	{
		return "你的不是昆仑派，难道不怕死么？！\n";
	}
	if (me->query_skill("liangyi-jian",1)<250)
	{
		return "你的两仪剑等级不足250，告诉你也没用！\n";
	}
	if (me->query("quest/kl/lyj/feipu/pass"))
	{
		return "你的两仪剑“百丈飞瀑已经解开了”！\n";
	}
	if (time()-me->query("quest/kl/lyj/feipu/time")<86400)
	{
		return "你来的太频繁了，明天再来！\n";
	}

	message_vision(HIC"$N严肃的看着$n，慢慢说道：“我派的两仪剑讲究的剑走轻灵，和其他门派都不太相同。\n"
						"你既然到达如此程度，我就传给你这招百丈飞瀑的奥秘，我给你演示一遍，看你自己的悟性了。\n"+
				   HIR"\n\n\n$N缓缓抽出一柄长剑，纵身跃起，如瀑布泻下，看的$n心旌神摇\n"NOR,this_object(),me);
	
 
    i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	j=random(me->query("kar"));
	command("say 你看懂了么。\n");
	command("pat "+me->query("id"));
	if( i<5
		&& me->query("kar")<31
		&& j >= 25 ) 
	{
		tell_object(me,HIY"\n你听了的何太冲的亲自指点，联想起早期自己所用两仪剑的种种心得，两下印照。\n"NOR);
		tell_object(me,HIG"\n你剑招连连，宛如长江大河，滔滔不绝，一出手剑招即为连环招式，下意识的出招。\n"
			             +"招式看似繁复，但大多数招式你已经了然若胸，信手拈来，连绵不绝。\n"
						 +"你终于领悟了这门百丈飞瀑的运用法门。心中大喜。\n"NOR);
		me->set("quest/kl/lyj/feipu/pass",1);
		log_file("quest/lyjfeipu", sprintf("%8s(%8s) 失败%d次后，学到百丈飞瀑,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/feipu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "恭喜解密百丈飞瀑绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/lyjfeipu", sprintf("%8s(%8s) 解密百丈飞瀑绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/feipu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了何太冲的指点，可是对两仪剑决百丈飞瀑的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/lyj/feipu/fail",1);
		me->set("quest/kl/lyj/feipu/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密两仪剑之百丈飞瀑失败"+me->query("quest/kl/lyj/feipu/fail")+"次。\n";
	}


}