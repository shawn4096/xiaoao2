// deng.c 嵩山派第五代弟子 丁勉 2004.12.15 add ask gold
// Lklv 2001.10.18 Modified

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_jueji();
int ask_gold(object who);

void create()
{
	set_name("丁勉", ({ "ding mian", "ding", "mian" }));
	set("nickname", HIR"托塔手"NOR);
	set("long", "这是位肥胖的老者，他身材魁伟，是嵩山派掌门人的二师弟托塔手丁勉。\n");
	set("gender", "男性");
	set("age", 51);
	set("per", 18);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 33);
	set("int", 23);
	set("con", 25);
	set("dex", 25);
	set("unique", 1);
	set("env/wimpy", 70);

	set("max_qi", 23000);
	set("max_jing", 5000);
	set("eff_jingli", 5000);
	set("max_neili", 23500);
	set("jiali", 200);
	set("combat_exp", 9500000);
	set("shen", -1640000);
	set_skill("songyang-jue", 180);

	set_skill("literate", 200);
	set_skill("force", 450);
	set_skill("parry", 450);
	set_skill("sword", 450);
	set_skill("dodge", 450);
	set_skill("hand", 450);
	set_skill("zhongyuefeng", 450);
	set_skill("songyang-shou", 450);
	set_skill("hanbing-zhenqi", 450);
	set_skill("songshan-jian", 450);

	map_skill("force", "hanbing-zhenqi");
	map_skill("dodge", "zhongyuefeng");
	map_skill("hand", "songyang-shou");
	map_skill("parry", "songyang-shou");
	map_skill("sword", "songshan-jian");

	prepare_skill("hand", "songyang-shou");
	set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
		(: perform_action, "hand.junji" :),
		(: perform_action, "hand.tuota" :),
		(: exert_function, "juhan" :),
		(: exert_function, "hanbing" :),
	}));

	create_family("嵩山派", 3, "弟子");

	set("inquiry", ([
		"五岳并派" : (: ask_gold :),
	//	"托塔手绝技" : (: ask_jueji :),
		"绝技": "这绝招有个名字叫：「峻极神掌(junji)」，取自此峻极峰。",
		"大嵩阳手": "嘿嘿，想当年我两掌震伤恒山定逸老尼，用的就是这套手法的绝技。",
		"嵩山派" : "我们嵩山派是五岳剑派之首！\n",
		"五岳剑派" : "我们五岳剑派在武林之中势力巨大，可与少林、武当抗衡。\n",
		"左冷禅" : "他就是我们的掌门人，功夫深不可测。\n",
	]) );

	setup();
	carry_object(ARMOR_D("changpao1"))->wear();
	add_money("gold", 1);
}

int ask_gold(object who)
{
	object me = this_player();
	int gold = 0;

	if( me->query("family/family_name") != "嵩山派" ) {
		command("say 我们嵩山派的事，" + RANK_D->query_respect(me) + "最好是不要插手！");
		return 1;
	}

        if( (int)me->query_skill("hanbing-zhenqi", 1) < 216 ) {
		command("say " + RANK_D->query_respect(me) + "不好好学习我嵩山派武功，整天问东问西，告诉你又能如何？");
		return 1;
	}

	if( me->query("songshan_given") >= 300 ) {
		command("say " + RANK_D->query_respect(me) + "武功高强，既然有心出力，那就烦请多联系些江湖高手来我派助阵吧！");
		return 1;
	}

	if( (int)me->query("songshan_given") + 10 < (int)me->query_skill("hanbing-zhenqi", 1) ) {
		if( (int)me->query_skill("hanbing-zhenqi", 1) > 300 ) 
			gold = 300 - (int)me->query("songshan_given");
		else gold = (int)me->query_skill("hanbing-zhenqi", 1) - (int)me->query("songshan_given");
		gold *= 10000;

		if( (int)me->query_skill("literate", 1) < 100 ) gold *= 5; 
		else if( (int)me->query_skill("literate", 1) >= 150 ) gold *= 3; 
		else gold *= 4; 

		command("interest");
		me->add("balance", gold);
		me->set("songshan_given", (int)me->query_skill("hanbing-zhenqi", 1));
		command("say 多日不见，" + RANK_D->query_respect(me) + "的武学似乎增进不少啊！");
		command("say 既然" + RANK_D->query_respect(me) + "有心，我这就将" + MONEY_D->money_str(gold) + "存入你的钱庄，你定要好好招揽群雄助我派夺得盟主之位啊！");
	} else command("say " + RANK_D->query_respect(me) + "，我嵩山派以武功称霸武林，在武学方面马虎不得啊！");
	return 1;
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
	if(ob->query("party/gongji") < 5000 ){
		command("say 你的门派功绩不够5000，别来找我！");
		return;
	}
	if(ob->query_skill("hanbing-zhenqi",1) < 300 ){
		command("say 你的寒冰真气太弱了，不足300别来找我！");
		return;
	}
	if(ob->query_skill("songyang-shou",1) < 300 ){
		command("say 你的嵩阳手太弱了，不足300别来找我！");
		return;
	}
	if(ob->query("family/generation") <4){
		command("say 你已经拜我师兄为师了，我可不敢收你！");
		return;
	}
	if(ob->query("shen") > -1000000 ){
		command("say 嵩山剑法以狠辣著称（<-1m），你这娘娘腔一看就不够心狠手辣，快滚！");
		return;
	}
	command("say 好吧，师傅正要我多培育一些弟子来发扬嵩山派呢。");
	command("recruit " + ob->query("id"));
}

string ask_jueji()
{
	object me;
	int i,j;

	me=this_player();
	if (me->query_skill("hand",1)<200)
	{
		command("say 你的基本手法不足200，告诉你也学不会！\n");
		return "谁的拳头大，谁就说了算！\n";
	}
	if (me->is_busy()) return "你很忙啊！\n";
	
	if (me->query_skill("songyang-shou",1)<220)
	{
		command("say 你的大嵩阳手法不足220，告诉你也学不会！\n");
		return "谁的拳头大，谁就说了算！\n";
	}
	if (time()-me->query("quest/ss/sys/tuota/time")<86400) 
		return "你来的太勤快了，这对武功修炼是不利的！\n";
	
		command("say 大嵩阳手中托塔手绝技乃是我独创，你想学我就告诉你？\n");
		command("say 好小子，既然你想学，你听好了！\n");
		  j = 20;
		  if(me->query("m-card-vip")) j =  18;
		  if(me->query("y-card-vip")) j =  15;
		  if(me->query("buyvip"))     j =  10;
		  i=random(j);

		  if (i<4 
			 && me->query("kar")<31
			 && random(me->query("kar"))>25)
		  {       
			  tell_object(me,HIC"\n你按照丁勉的指点将浑身真气注入手臂中，手法顿时重了许多！\n"NOR);
			  message_vision(HIR"\n$N对如何使用这个托塔手的技巧一下子豁然贯通。”\n"NOR,me); 
			  tell_object(me,HIG"恭喜您解密托塔手绝技成功！\n"NOR);
			  me->set("quest/tls/sys/tuota/pass",1);
			  log_file("quest/sstuota", sprintf("%s(%s) 失败%d次成功解开托塔手。富源：%d；经验：%d。\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/tls/sys/tuota/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			  me->start_busy(1);
			}
			else
			{
			 tell_object(me,HIG"\n你沉思许久，不得要领。\n"NOR);
			 message_vision(HIC"\n$N摇了摇头，深深地叹了口气,觉得自己真实笨死了。\n"NOR,me); 
			 tell_object(me,HBBLU"\n很可惜，你本次尝试托塔手绝技秘密失败！\n"NOR);
			 tell_object(me,HBBLU"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
			 tell_object(me,HBBLU"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
			 log_file("quest/sstuota", sprintf("%s(%s) 解密托塔手绝技失败%d次。富源：%d；经验：%d。\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/tls/sys/tuota/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			 me->add("quest/tls/sys/tuota/fail",1);
			 me->set("quest/tls/sys/tuota/exp", me->query("combat_exp") );
			 me->start_busy(1);
			 me->set("quest/tls/sys/tuota/time",time());
			}
		me->add_busy(2);
		return "托塔手是大嵩阳手绝技！\n";
	 
		
}

