// duanyu.c 段誉
// COOL@SJ,990827
// Modified by tangfeng 2004
// 这里的段誉涉及到三个场景，一个在无量玉像，一个在石屋里，一个在大伦寺暗室里
// By Spiderii@ty 加入时间限制
inherit F_MASTER;
#include <ansi.h>
inherit NPC;

#define QUESTDIR "quest/天龙八部/"
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龙八部/天龙营救篇/"
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"
#define QUESTDIR6 "quest/天龙八部/武功/"

string tianlonghelp();
string askxiaofeng();
string askjiumozhi();
string ask_name();
int ask_home();
int ask_save();
void outroom(object me);
void dest(object me,object ob);
void greeting(object me);

void create()
{
        set_name("段誉", ({"duan yu", "duan", "duayu"}));
        set("gender", "男性");
        set("age", 20);
		set("title",HIG"大理国镇南王世子"NOR);

        set("long", "这是一个青年男子，身穿一身淡蓝色长袍，面如珠玉，齿白唇红，气质高雅。\n"
                    "眼神极为清澈，一看就是久经熏陶而长成的世家浊世公子，哪怕身处暗室，却依旧风采宜人。\n");
        set("attitude", "peaceful");
        set("str", 40);
        set("per", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        //set("no_quest", 1);

        set("inquiry", ([
		"段誉" : (: ask_name :),
		"name" : (: ask_name :),
		"获救" : (: ask_save :),
		"救你" : (: ask_save :),
		"救段誉" : (: ask_save :),
		"救你们" : (: ask_save :),
		"搭救" : (: ask_save :),
		"解救" : (: ask_save :),
		"save" : (: ask_save :),
		"段延庆" : "就是他把我关进来的。\n",
		"拜师" : "嗯....，我的师傅是老子、孔子和庄子，他们的学问我还没学全呢。\n",
		"大理" : "大理是我家，我家在大理。",
		"天龙寺" : "天龙寺是大理段家武学的最高之地。",
		"天龙有难" : (: tianlonghelp :),
		"萧峰" : "我大哥萧峰啊，端得一条好汉。",
		"营救萧峰" : (: askxiaofeng :),
		"慕容复" : "慕容公子确是其江南文采，诗琴书画无所不精，武功更是冠绝天下。",
		"慕容博" : "我听说是，姑苏慕容不出的杰才，可惜英年早逝。",
		"鸠摩智" : (: askjiumozhi :),
		"六脉神剑" : "天龙寺最高绝学。",
		"段正淳" : "那是我爹爹。",
		"刀白凤" : "你找我妈妈有什么事情？",
		"段正明" : "你找我伯父有什么事情？",
		"虚竹" : "你找我三弟有什么事情？",

		"回家" : (: ask_home :),
		"go home" : (: ask_home :),

		//六脉神剑的quest好像有人做了一半，在枯荣长老身上有部分描述
        ]));

        set("jing", 10000);
        set("max_jing", 10000);
        set("jingli", 10000);
        set("eff_jingli", 10000);
        set("qi", 80000);
        set("max_qi", 80000);
        set("neili", 80000);
        set("max_neili", 80000);
        set("jiali",250);
		//要设定北冥、凌波参数
        
        set("combat_exp", 15000000);
        set_skill("buddhism", 250);            
        //set_skill("daode-jing", 250);                   
        set_skill("literate", 400);                
        set_skill("force", 550);                
        set_skill("beiming-shengong", 550);     
        set_skill("dodge", 550);                
        set_skill("lingbo-weibu", 550);         
        set_skill("parry", 500);
        set_skill("finger", 500);
        set_skill("yiyang-zhi", 550);
        set_skill("liumai-shenjian", 200);
        map_skill("parry", "yiyang-zhi");
        map_skill("finger", "yiyang-zhi");
        map_skill("force", "beiming-shengong");
        map_skill("dodge", "lingbo-weibu");


		set("env/liumai","shenjian");
        set("chat_chance_combat", 100);
        set("chat_msg_combat",({ 
                (: exert_function, "beiming" :),
				(: perform_action, "dodge.luoshen" :),

                (: perform_action, "finger.yizhisanmai" :),
                (: perform_action, "finger.ciqu" :),
				//(: perform_action, "finger.liumai" :),
				(: perform_action, "finger.ciqu" :),
        }));

        setup();        
}
void init()
{
	object me;
	me = this_player();
	::init();
	if (interactive(me) && living(me) 
		&& !me->query_condition("killer")
		&& me->query(QUESTDIR1+"start") ) {
		me->start_busy(2);
        remove_call_out("greeting"); 
		call_out("greeting",2,me);
	} 
}
/*
void greeting(object me)
{
	if(!me) return;
	if(environment(this_object())!=environment(me)) return;

	if(!me->query_condition("killer")&&me->query(QUESTDIR1+"start") 
			&& !me->query_temp(QUESTDIR1+"see_duanyu1")
			&& !me->query_temp(QUESTDIR1+"see_duanyu2")
			&& !me->query(QUESTDIR1+"wuliangover")
			&& me->query_temp(QUESTDIR1+"jianying"))
    {
		//玉像处
		  message_vision(HIC"\n$N一转身大吃一惊，却发现身旁却见一个男子站在玉像前，痴痴的呆看着，那表情竟然由爱生敬，由敬成痴。\n"NOR, me);  
		  log_file("quest/TLBB", sprintf("%s(%s) 凌波微步玉像处遇见段誉。经验：%d。\n", me->name(1),me->query("id"), me->query("combat_exp")) );
		  me->set_temp(QUESTDIR1+"see_duanyu2",1);
		  me->start_busy(1);
		  command("crazy");
		  command("say");
    }
	
	if(!me->query_condition("killer")
		&& me->query(QUESTDIR2+"start") 
		&& me->query_temp(QUESTDIR2+"pushdown") 
		&& !me->query(QUESTDIR2+"over"))
    {
		  message_vision(HIC"\n$N挤进暗室，发现一个中年男子，正炯炯有神地盯着你看，感觉不到一点被囚困的样子。\n\n"NOR, me);                      
		  command("ah "+me->query("id"));
		  command("look "+me->query("id"));
		  command("heng");
		  command("say");
		  command("say 真乃人不可貌相，这魔僧看似一代高僧，却妄为大轮明王。"); 
		  me->start_busy(1);
    }
}*/
