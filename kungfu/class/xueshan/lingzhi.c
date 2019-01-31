// lingzhi.c 灵智上人
// by iceland

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

int ask_me_1();
int ask_me_2();
int ask_tianyin();
void create()
{
        set_name("灵智上人", ({ "lingzhi shangren", "lingzhishangren" ,"lingzhi","shangren" }));
        set("long",@LONG
他长得白白净净，身体肥胖，颈项中的肥肉叠了至少三四层。慈眉善目，老是
笑眯眯的模样，张嘴一乐就露出两颗虎牙。
LONG
        );
        set("title", HIY "大轮寺第十二代弟子" NOR);
        set("gender", "男性");
        set("age", 41);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 28);
        set("int", 20);
        set("con", 25);
        set("dex", 27);
        set("max_qi", 1800);
        set("eff_jing", 900);
	    set("max_jing",900);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 100);
        set("combat_exp", 600000);
        set("score", 25000);
    	set("unique", 1);

        set_skill("mizong-fofa", 200);
        set_skill("literate", 100);
        set_skill("force", 200);
        set_skill("longxiang-boruo", 200);
        set_skill("dodge", 200);
        set_skill("yuxue-dunxing", 200);
        set_skill("hand", 200);
	    set_skill("poison",120);
        set_skill("dashou-yin",200);
        set_skill("parry", 200 );
        set_skill("staff",200);
        set_skill("wushang-dali",200);
		set_skill("claw",200);
        set_skill("tianwang-zhua",200);
        map_skill("force", "longxiang-boruo");
        map_skill("dodge", "yuxue-dunxing");
        map_skill("hand", "dashou-yin");
        map_skill("parry", "dashou-yin");
		map_skill("claw", "tianwang-zhua");
        map_skill("staff", "wushang-dali");

        prepare_skill("hand","dashou-yin");

        create_family("大轮寺", 12, "弟子");
        set("class", "huanxi");
        set("inquiry", ([
                "俸禄" : (: ask_me_1 :),
                "供奉" : "善哉，善哉，请把酥油倒在长明灯里吧。\n",
				"反手勾腕绝技" : (: ask_tianyin :),
        ]));

        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: exert_function, "shield lingzhi shangren" :),
                (: perform_action, "hand.tianyin" :), }));

        setup();
        carry_object("/d/xueshan/npc/obj/qinxiu-jiasha")->wear();

        add_money("silver",50);
}

void attempt_apprentice(object ob)
{
       	if( (string)ob->query("gender") == "无性" ) {
               command("shake");
               command("say 我佛法还不够深湛，恐怕一个把持不住...你还是去找别人吧。");
               return;
	}
        if ((string)ob->query("family/family_name") != "大轮寺") {
                command("say"+ RANK_D->query_respect(ob) +
                        "不是本寺弟子，在这里捣什么乱？！");
                return;
	}
        if ((int)ob->query_skill("mizong-fofa", 1) < 80) {
                command("say 密宗佛法是各项武功之本，你再勤加修炼吧。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多钻研钻研本门的心法吧。");
                return;
        }

        command("say 好吧，以后你就是我的弟子了。");
        command("recruit " + ob->query("id"));
        ob->set("title",   "大轮寺第十三代弟子"  );
}

int ask_me_1()
{
	object me;
	int skill,i,j;
	mapping myfam;
	me=this_player();

        skill = me->query_skill("longxiang-boruo",1);
	myfam = (mapping)me->query("family");
        i = (int)me->query("join_age");
        j = (int)me->query("gf_ok");

	if (!myfam || myfam["family_name"] != "大轮寺") {
		command("sneer "+(string)me->query("id"));
		command("say 看"+ RANK_D->query_respect(me) +"贼眉鼠眼，面生得很呀，不知道问这个做什么？\n");
		return 1;
	}
	if((int)me->query("xs_given")>=(int)me->query("age")) {
		command("sigh "+(string)me->query("id"));
		command("say 你今年的俸禄不是已经领走了么？明年再来吧。\n");
		return 1;
	}
        if( (( i + j ) < (int)me->query("age")) && ( skill < 216 ) ) {
		if((int)me->query("xs_given")>=(int)me->query("age")) {
			command("shake "+(string)me->query("id"));
			command("say "+ RANK_D->query_respect(me) +"历年供奉有所短缺，今年不能领取俸禄，明年再来吧。\n");
			return 1;
		}
		command("shake "+(string)me->query("id"));
		command("say "+ RANK_D->query_respect(me) +"历年供奉有所短缺，今年不能领取俸禄，明年再来吧。\n");
    		me->add("gf_ok",1);
        	me->set("xs_given",(int)me->query("age"));
		return 1;
	 }

	if((int)me->query("xs_given")<(int)me->query("age")) {
		if (skill < 60){
			command("pat "+(string)me->query("id"));
			command("say 你佛法尚未小成，还是勤加修炼为是。\n");
			return 1;
		}
		if (skill >= 60 && skill < 90) {
			me->set_temp("give_gold", 30);
			remove_call_out("give_money");
			call_out("give_money", 1, me);
			return 1;
		}
		if (skill >= 90 && skill < 140)	{
			me->set_temp("give_gold", 60);
			remove_call_out("give_money");
			call_out("give_money", 1, me);
			return 1;
		}
		if (skill >= 140 && skill < 180) {
			me->set_temp("give_gold", 100);
			remove_call_out("give_money");
			call_out("give_money", 1, me);
			return 1;
		}
		if (skill >= 180){
			me->set_temp("give_gold", 150);
			remove_call_out("give_money");
			call_out("give_money", 1, me);
			return 1;
		}
	}
}

int give_money(object me)
{
	int amount;
	object n_money;
        command("buddhi lingzhi shangren");
        command("say"+ RANK_D->query_respect(me) +"请拿好俸禄，尽可去精研佛法，不必再为衣食些许俗务分心了。");
        message_vision("灵智上人拿出几锭黄金，递给了$N。\n",me);
        n_money = new(GOLD_OB);
        n_money->move(me);
        amount = me->query_temp("give_gold");
        n_money->add_amount(amount);
        me->delete_temp("give_gold");
        me->set("xs_given",(int)me->query("age"));
}

int ask_tianyin()
{
	object ob;
	object me;
	int i,j;
	me=this_player();
	ob=this_object();
	if (me->query("family/family_name")!="大轮寺")
	{
		command("say 你不是我大轮寺弟子，来此询问我派秘籍所为何来？\n");
		command("consider ");
		return 1;
	}
	if (me->query_skill("dashou-yin",1)<180) 
	{
		command("say 你的大手印不足180，修炼高了再来！\n");
		return 1;
	}
	if (me->query("quest/dls/dsy/tianyin/pass")) 
	{
		command("say 你已经完成了此谜题，来此骚扰我？！\n");
		return 1;
	}
	if (time()-me->query("quest/dls/dsy/tianyin/time")<86400) 
	{
		command("say 你来的太勤快了！\n");
		return 1;
	}
	message_vision(CYN"$N笑咪咪的看着$n，悠悠地说道：“我派的大手印讲究的是简单实用，\n"
						"金刚意与智慧心并重，你看好了，我给你演示一遍，看你自己的悟性了。\n"+
						HIY"$N左冲右突，往来奔赴，疾驰如电，迅捷无比。看的$n眼花缭乱\n"+
						HIR"$N喝道，“这是金刚印”，这是智慧印！这是无畏印！这是宝瓶气！.\n"
						HIB"忽然，$N双手不断变化，十个手指渐渐成合一之态，但威力去更加迅猛。\n"
						HIC"$n不禁看得心旌神摇，这大手印的威力竟然如此惊人！"NOR, ob, me);

    j = 15;
	if(me->query("m-card-vip")) j =  13;
	if(me->query("y-card-vip")) j =  10;
	if(me->query("buyvip"))     j =  6;
	i=random(j);
	
	command("say 本门大手印唯有和龙象般若刚猛之力相配合方能发挥最大威力，这一点你千万要记住。\n");
	command("pat "+me->query("id"));
	if(i<32 && random(me->query("kar")) >= 20 ) 
	{
		tell_object(me,HIY"\n你听了灵智上人的指点，对大手印的绝技奥妙颇有心得。\n"NOR);

		me->set("quest/dls/dsy/tianyin/pass",1);
		me->set("quest/dls/dsy/tianyin/time",time());
		log_file("quest/dsytianyin", sprintf("%8s(%8s) 失败%d次后，学到大手印更高绝技,五轮大法完全融会贯通。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/dls/dsy/tianyin/fail"),i,me->query("combat_exp")) );
		command("haha"+me->query("id"));
		command( "say 恭喜解密大手印功夫成功。\n");
		//me->add(QUESTDIR4+"shenzhao",1);//
		return 1;
	}
	else
	{
		log_file("quest/dsytianyin", sprintf("%s(%s) 解密大手印绝技失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/dls/dsy/tianyin/fail"), i,me->query("combat_exp")) );
		tell_object(me,HIY"你听了灵智上人的指点，可是对大手印的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/dls/dsy/tianyin/fail",1);
		me->set("quest/dls/dsy/tianyin/time",time());
		command( "say 非常遗憾解密大手印绝技失败"+me->query("quest/dls/dsy/tianyin/fail")+"次。\n");
		return 1;
	}

}

