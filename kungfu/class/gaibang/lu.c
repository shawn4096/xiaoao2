// NPC: lu.c 鲁有脚
// Lklv 2001.9.28 update
// By Spiderii@ty srf,tjf不可以ask job跑tj.
#include <job_mul.h>
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_me();
string ask_job();
string ask_gift();
string ask_bangjue();


int ask_num();

#include "gb_lujob.h"

void create()
{
	set_name("鲁有脚", ({"lu youjiao", "lu", "youjiao"}));
	set("title", HIW"丐帮九袋长老"NOR);
	set("nickname", "掌棒龙头");
	set("gender", "男性");
	set("age", 45);
	set("long", "他在丐帮中有仁有义，行事光明磊落，深得洪七公的器重。\n");

        set("attitude", "friendly");
        set("str", 25);
        set("int", 12);
        set("con", 25);
        set("dex", 20);
        set("unique", 1);
        set("no_bark",1);
        set("job_npc",1);
        set("no_get","鲁有脚对你来说太重了。\n");

        set("qi", 13500);
        set("eff_jingli", 8000);
        set("max_qi", 13500);
        set("jing", 8000);
        set("max_jing", 8000);
        set("eff_jing", 8000);
        set("neili", 24200);
        set("max_neili", 24200);
        set("jiali", 200);
		set("bj_book", 1);
        set("combat_exp", 9400000);
        set("score", 20000);

        set_skill("force", 450); // 基本内功
        set_skill("huntian-qigong", 450); // 混天气功
        set_skill("strike",450); // 基本拳脚
        set_skill("xianglong-zhang", 450); // 降龙十八掌
        set_skill("dodge", 450); // 基本躲闪
        set_skill("xiaoyaoyou", 450); // 逍遥游
        set_skill("parry", 450); // 基本招架
        set_skill("literate", 100);
        set_skill("stick", 450); // 基本棍杖
        set_skill("begging", 200);

        map_skill("force", "huntian-qigong");
        map_skill("strike", "xianglong-zhang");
        map_skill("parry","xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");

        prepare_skill("strike", "xianglong-zhang");

    	set("chat_msg_combat", ({
        	(: perform_action, "strike.xiao" :),
        	(: perform_action, "strike.feilong" :),
        	(: exert_function, "huntian" :),
        }));

        create_family("丐帮", 18, "九袋长老");

        set("inquiry", ([
                "棒法图解" : (:ask_me:),
                "报效国家" : (:ask_job:),
                "功劳": (: ask_num :),
				"打狗棒诀": (: ask_bangjue :),
                //"补偿": (: ask_gift :),

                "洪七公": "我们平常都叫他“帮主”，亲近一点的叫他“七公”。\n",
        ]));
        set("count",1);

        setup();
        carry_object(ARMOR_D("bainayi"))->wear();
        carry_object(ARMOR_D("caoxie"))->wear();
        carry_object(__DIR__"obj/gb_budai9")->wear();
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
        object me = this_player();
        int exp,pot,shen;

	    ::init();
        if( me->query_temp("gb_job2")
         && me->query_temp("gb_job2_finish")>=5 ){
                me->delete_temp("gb_job2");
                me->delete_temp("gb_job2_finish");
                exp = 400 + random(300);
                
                exp = me->add_exp_combat(exp,this_object(),"草料场");
                
                pot = exp/5+random(exp/10);
                shen = exp*3;
                command("thumb "+me->query("id"));
                
                me->add("job_time/报效国家", 1);                
                write( sprintf(HIW"\n好，任务完成了，你得到了"
	                 + CHINESE_D->chinese_number( exp )
        	         + "点实战经验，"
                	 + CHINESE_D->chinese_number( pot )
           	      	+ "点潜能和"
               		+ CHINESE_D->chinese_number( shen )
                 	+ "点正神。\n" NOR));
        	
        	me->add( "potential", pot );
        	if( me->query("potential") > me->query("max_pot") )
                	me->set("potential", me->query("max_pot") );
            	me->add( "shen", shen );
		        me->set("job_name","火烧草料场");
		
            	log_file("job/caoliao", sprintf("%8s%-10s火烧草料场任务，经验：%3d，潜能：%3d，目前经验：%d。\n",
	           me->query("name"), "("+me->query("id")+")", exp, pot,me->query("combat_exp")),me );
        }
        add_action("qingjiao", "qingjiao");
}

string ask_me()
{
        object me = this_player();

        if ( me->query("family/family_name") != "丐帮" ){
                command("laugh " + me->query("id"));
                return RANK_D->query_respect(me) + "与本派素无来往，不知此话从何谈起？";
        }
        if (random(4)) {
                command("hehe");
                return "我不知道。";
        }
        if (query("count")){
                new(__DIR__"obj/stick-book")->move(me);
                add("count", -1);
                command(":(");
                message_vision("$N给$n一张纸片。\n", this_object(), me);
                return "好吧，这本图解你拿去研究，不懂的来问我。";
        }
        command("sigh " + me->query("id"));
        return "你来迟了一步，图解已经被人拿走了。";
}
/*
string ask_gift()
{
        object me = this_player();
        mapping fam;

        fam = me->query("family");
        if (!fam || fam["family_name"] !="丐帮")
           return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起?。\n";
        if( me->query("gb/gift") )
           return RANK_D->query_respect(me)+"还想要补偿？这个一人只能要一次。\n";

           me->set("job_time/抓蛇",1000);
           me->set("job_time/丐帮",1000);
           me->set("job_time/刺杀",1000);
           me->set("job_time/颂摩崖",1000);
           me->set("gb/gift", 1);

        return  "好了，你的告急、颂摩崖、刺杀都给你足够补偿了.\n" ;
}
*/
string ask_job()
{
        object me = this_player();
        int exp = me->query("combat_exp");

        if( (int)me->query("shen") < 0 )
               return "我看你獐头鼠目，不象个好人，如何能放心把军机大事托付给你。\n";

        if( exp < 100000 )
                return RANK_D->query_respect(me) + "纵有此心，奈何武功修为太差。\n";

        if( !wizardp(me) && me->query_condition("job_busy"))
                return "我这里现在没有什么任务，你等会再来吧。\n";

		if(me->query_temp("quest/busy")) //added by tangfeng 与quest冲突
			    return "现在我这里没有给你的任务，你还是先处理好你其他事情再说吧。";

        if ( me->query_condition("killer"))
                 return "你现在是官府捉拿的要犯，还是先处理好你自己的事情吧!"; // By Spiderii@ty加入限制
        if( me->query("menggu") )
                return "哼，你这汉奸，还想要任务？\n";

        if( exp < 100000 ){
                return gb_job1();  //100k
				//江湖告急
        }
        else if( exp < 500000 ){  //500k
                return gb_job2();
				//火烧
        }
        else if(exp < 2000000 ){  //2m
			    return gb_job3();
				//刺杀
        }
        else if(exp > 2000000 ){ //2m
                return smy_job();
				//颂摩崖
        }
        return "我这里没有什么可以给你做的任务了。\n";
}

int ask_num()
{
        object me = this_player();
        //old
        //int num = me->query("job_time/报效国家");
        //old end
        int num = me->query("job_time/告急") + me->query("job_time/刺杀") + me->query("job_time/颂摩崖");

        command( "say "
        	+ RANK_D->query_respect(me) + "已经为国家做了"
        	+ CHINESE_D->chinese_number( num )
        	+ "次贡献。" );
        command("addoil " + me->query("id"));
        return 1;
}

int qingjiao(string arg)
{
        object me = this_player();
        int lvl = me->query_skill("stick", 1);

        if (!living(me)) return 0;
        if (arg != "stick" || !present("stick book", me)) return notify_fail("你要请教什么？\n");
        if (!living(this_object())) return notify_fail("你先把他弄醒再说吧！\n");
        if (this_object()->is_busy() || this_object()->is_fighting())
        	return notify_fail(this_object()->query("name")+"正忙着呢。\n");
        if (lvl < 30) return notify_fail("你的基本棒法修为不够，对鲁有脚的讲解似懂非懂。\n");
        if (lvl < 101) {
                write("你拿着棒法图解向鲁有脚请教。\n");
                me->receive_damage("jing", 30);
                write("你的「基本棒法」进步了。\n");
                me->improve_skill("stick", me->query("int"));
                return 1;
        }
        command("blush " + me->query("id"));
        return notify_fail("");
}

string ask_bangjue()
{
	object me=this_player();
    
	if ( me->query("family/family_name") != "丐帮" ){
                command("laugh " + me->query("id"));
                return "你与本派素无来往，不知此话从何谈起？";
    }
	if ( me->query("family/master_name") != "洪七公" ){
                command("laugh " + me->query("id"));
                return "你非洪老帮主亲传弟子，打听这个作甚？";
    }
	if ( me->query("gb/bags")<9) {
		command("say 你在帮中职位太低，先积累功劳升到九袋吧。\n");
		return "";
    }
	if ( me->query_skill("dagou-bang",1)<450) {
		command("say 你的打狗棒等级太低，不足450，无法修习打狗棒诀。\n");
		return "";
    }
	if (me->query_skill("bangjue",1) < 150)
	{
       command("say 打狗棒乃是我丐帮不传之谜，乃是武林至高武技之一。\n");
	   command("say 好，看在你如此为我大丐帮出力的份上，我就把这本[打狗棒口诀]送给你学习。\n");
	   command("say 你要好好学习，若机缘巧合能习得无上武技，可以为我大宋出力了。\n");
	   if (this_object()->query("bj_book")<1)
	   {
		    command("say 我刚把这本书送人了，你待会再来。\n");
			return "嘿嘿。。";
	   }
	   new("kungfu/class/gaibang/obj/bangjue-book.c")->move(me);
	   this_object()->add("bj_book",-1);
	   command("say 喏，这本棒诀你千万要收好了。");
	   return "";
	}
	command("say 我丐帮打狗棒真正的口诀全部在黄帮主之处，她正在襄阳助郭大侠守城。\n");
	command("say 前几天还嘱咐我要我招募天下英雄豪杰，过去一起守城。\n");
	command("say 你就先替我跑一趟，能为我大宋子民做点恭喜也是我丐帮份内之事。\n");
	command("say 你先去，我过几天也过去。\n");
	me->set_temp("bangjue/asklu",1);
	return "这襄阳战局越来越凶险了，这仗真不知道要打到什么时候？";
}