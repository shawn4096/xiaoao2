// 书生 by River@SJ 2002.6.5

inherit NPC;
#include <ansi.h>
inherit F_MASTER;

string ask_me();
string ask_question();
string ask_yiyangshu();
string ask_sanyinguan();
string ask_qingliang();

void create()
{
	set_name("书生", ({ "shu sheng",  "zhu ziliu", "zhu","shu", "sheng" }) );
	set("long", "见他头戴逍遥巾，手挥折叠扇，颏下一丛漆黑的长须，确是个饱学宿儒模样。\n"
	+"他是一灯大师的大弟子朱子柳，一手判官笔运用的出神入化。\n");
	//set("title",HIC"书生"NOR);
	set("gender", "男性" );
	set("age", 45);
	set("str", 25);
	set("con", 25);
	set("dex", 30);
	set("int", 40);
	set("per", 28);
	set("unique", 1);
	set("attitude", "friendly");

	set("max_qi", 25000);
	set("max_jing", 5800);
	set("eff_jingli", 5600);
	set("neili", 12000);
	set("qi", 25000);
	set("jingli", 5600);
	set("max_neili", 12000);
	set("jiali", 200);

	set("combat_exp", 6500000);
	set("score", 5000);

	set_skill("parry", 400);
	set_skill("dodge", 400);
	set_skill("force", 400);
	set_skill("brush", 450);
	set_skill("sword", 400);
	set_skill("literate", 400);
	set_skill("qiantian-yiyang", 400);
	set_skill("yingou-bifa", 450);
	set_skill("duanjia-jianfa", 400);
	set_skill("tianlong-xiang", 400);
	set_skill("finger", 400);
	set_skill("yiyang-zhi", 400);
	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "yingou-bifa");
	map_skill("force", "qiantian-yiyang");
	map_skill("finger", "yiyang-zhi");
	map_skill("sword","duanjia-jianfa");
	map_skill("brush","yingou-bifa");

	prepare_skill("finger","yiyang-zhi");
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
				(: exert_function, "yiyang" :),
                (: perform_action, "brush.caoshu" :),
				(: perform_action, "brush.kaishu" :),
				(: perform_action, "brush.yiyangshu" :),
        	    (: perform_action, "brush.shiguwen" :),        
	    }));
	set("inquiry", ([
		"一灯大师" : (: ask_me :),
		"题目" : (: ask_question :),
		"一阳书指" : (: ask_yiyangshu :),
		"三因观" : (: ask_sanyinguan :),
		"清凉扇绝技" : (: ask_qingliang :),

	]));
	create_family("天龙寺", 13, "俗家弟子");
	setup();

	carry_object(BINGQI_D("panguanbi"))->wield();
	carry_object(ARMOR_D("b_cloth"))->wear();
	carry_object(ARMOR_D("caoxie"))->wear();
}

void init()
{
	::init();
	add_action("do_answer", "answer");
	add_action("do_jiaoliang", "jiaoliang");

}

string ask_me()
{
	object me = this_player();

	if ( me->query_temp("yideng/shusheng_pass"))
		return "这位"+RANK_D->query_respect(me)+"，我师傅就在前面不远处的石屋里。";

	if ( me->query_temp("yideng/ask_shusheng"))
		return "你可回答的出我的问题？";

	me->set_temp("yideng/ask_shusheng", 1);

	return "我出三道题目考考你，若是考得出，那就引你去见我师父，倘有\n"+
		"一道不中，只好请"+RANK_D->query_respect(me)+"从原路回去了。";
}

string ask_question()
{
	object me = this_player();

	if ( me->query_temp("yideng/shusheng_pass"))
		return "这位"+RANK_D->query_respect(me)+"，我师傅就在前面不远处的石屋里。";

	if ( ! me->query_temp("yideng/ask_shusheng"))
		return "这位"+RANK_D->query_respect(me)+"问我题目作甚？";

	if ( me->query_temp("yideng/quest_wait"))
		return "这位"+RANK_D->query_respect(me)+"可能答出我的题目？";

	me->set_temp("yideng/quest_one", 1);
	me->set_temp("yideng/quest_wait", 1);
	return "这里有一首诗，说的是在下出身来历，打四个字儿，你倒猜猜看。\n\n"
		"\t\t六经蕴籍胸中久，一剑十年磨在手。\n"+
		"\t\t杏花头上一枝横，恐泄天机莫露口。\n"+
		"\t\t一点累累大如斗，却掩半床无所有。\n"+
		"\t\t完名直待挂冠归，本来面目君知否？";
}
//三因观
string ask_sanyinguan()
{
	object me = this_player();

	if ( !me->query_temp("qls/askjiuwen"))
		return "我不认识你，这位"+RANK_D->query_respect(me)+"，你无缘无故来此作甚？\n";

	command("say 既然你是昆仑弟子，受灵清居士委托而来，我就告诉你这件事！\n");
	command("say 我本是昆仑旁支三因观弟子，后来拜师一灯大师，侍奉他终身。\n");
	me->delete_temp("qls/askjiuwen");
	me->set_temp("qls/askzhu", 1);
	return "往事如烟。\n\n";
}
//清凉绝技
string ask_qingliang()
{
	object me = this_player();

	if ( !me->query_temp("qls/askzhu"))
		return "我不认识你，这位"+RANK_D->query_respect(me)+"，你无缘无故来此作甚？\n";
	
	command("say 你既然想学这清凉扇，我就先考较考较你的能力！");
	command("say 你若把我打败我就指点你一二，否则，还请原路返回！\n");
	message_vision(HIY"如果准备好了就输入"+HIR"jiaoliang"+"\n"NOR,me);

	me->delete_temp("qls/askzhu");
	me->set_temp("qls/askjueji", 1);
	return "往事如烟,愿昆仑强大。\n\n";
}

int do_jiaoliang()
{
	object me, ob, weapon, weapon1;

	me = this_player();
	ob = this_object();

	weapon1 = ob->query_temp("weapon");

	if( !me->query_temp("qls/askjueji") ) return notify_fail("你要做什么？\n");

	if( me->is_busy() || me->is_fighting() ) return notify_fail("你正忙着呢。\n");

	if( ob->is_busy() || ob->is_fighting() ) return notify_fail(ob->name()+"正忙着呢。\n");

	if (time()-me->query("quest/kl/qls/time")<86400)
	{
		command("say 你来的太频繁了，我有点累了！\n");
		return notify_fail("朱子柳不想搭理你！\n");
	}
	if( me->query("qi") < me->query("max_qi")*9/10 )
		return notify_fail("你现在状态不佳，还是等会再请教吧！\n");

	if( me->query("eff_qi") < me->query("max_qi")/2 )
		return notify_fail("你现在重伤在身，还是等会再请教吧！\n");
	

		me->start_busy(1);
		message_vision(CYN"$N对着$n鞠躬，说道：“请朱师傅指点"+RANK_D->query_self(me)+"的清凉扇要诀！”\n"NOR, me, ob);
		me->delete_temp("qls/askjueji");
		
		me->set("quest/kl/qls/time", time());
		me->set("quest/kl/qls/exp", me->query("combat_exp"));

		ob->set("neili", query("max_neili")*2 );
		ob->set("jingli", query("eff_jingli")*2 );
		message_vision(HIW"$n默念清凉扇要诀，顿时笔法纵横，辗转起合，正是清凉扇“清凉快打”绝技！将$N攻个措手不及！"NOR, me, ob);

		COMBAT_D->do_attack(ob, me, weapon, 1);
		COMBAT_D->do_attack(ob, me, weapon, 1);
		COMBAT_D->do_attack(ob, me, weapon, 1);
		
		COMBAT_D->do_attack(ob, me, 0, 1);

		 COMBAT_D->do_attack(ob, me, weapon, 1);
			COMBAT_D->do_attack(ob, me, weapon, 1);
		
		COMBAT_D->do_attack(ob, me, 0, 1);

		 COMBAT_D->do_attack(ob, me, weapon, 1);
			COMBAT_D->do_attack(ob, me, weapon, 1);

		if( me->query("qi") < me->query("max_qi")*1/20 ) {
			message_vision(CYN"$n非常失望的对$N说到：“"+me->name()+"，你武功未成，还是等你打好基础再说！”\n"NOR, me, ob);
			me->start_busy(1);
			me->set_temp("marks/失败", 1);
			return 1;
		}
		
		message_vision(CYN"\n$n将七星宝剑交还给$N，愉快的说着：“"+me->name()+"，你自己慢慢琢磨下我所使用的剑诀吧！”\n"NOR, me, ob);
		message_vision(HIY"\n$N拼命地回忆着刚才的招数，开始认真思索着.........\n", me);
		
			if( random(me->query("kar")) > 26) {	// 随机福源
			message_vision(HIW"$N突然捕捉住交手瞬间的一幕，自言自语：“一寸短，一寸险，周身灵动，进退自如。”渐渐领悟出三因观清凉扇绝技的真谛。\n", me);
			tell_object(me, BYEL"恭喜你，你于" + NATURE_D->game_time() + "领悟了三因观清凉扇要诀。\n"NOR);
			command("say 既然灵清居士派你来索要这门武功，你就替我把这门绝艺传回昆仑！\n");
			command("say 我当初拜师之前也怕昆仑这门绝技失传，就写了一本手稿存放在昆仑书房中，你去找找看，看是否能找到？\n");
			me->set("quest/kl/qls/pass", 1);

		} else {
			message_vision(HIC"$N摇了摇头，道：“好像还是很困难的。”说罢，深深地叹了口气。\n", me);
			me->set_temp("marks/失败", 1);
		}
	me->delete_temp("qls");

	return 1;
}
int do_answer(string arg)
{
	object duzi;
	object me = this_player();

	if ( ! arg ) return 0;

	if ( !me->query_temp("yideng/quest_one")
	&& !me->query_temp("yideng/quest_two")
	&& !me->query_temp("yideng/quest_three")) return 0;

	if ( me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");

	if ( me->query_temp("yideng/quest_one") && arg == "辛未状元"){
		me->delete_temp("yideng");
		message_vision(CYN"$N说道：「‘六’字下面一个‘一’一个‘十’，是个‘辛’字。‘杏’字上\n"+
			"加横、下去‘口’，是个‘未’字。半个‘床’字加‘大’加一点，是个‘状’\n"+
			"字。‘完’挂冠，是个‘元’字。辛未状元，失敬失敬，原来是位辛未科的状\n"+
			"元爷。」\n\n"NOR, me);
		command("smile "+ me->query("id"));
		command("say 好好，果然不错，下一题，我有一个上联，请"+RANK_D->query_respect(me)+"对对。\n\n"
			"\t\t风摆棕榈，千手佛摇折叠扇。");
		me->set_temp("yideng/quest_two", 1);
		me->set_temp("yideng/ask_shusheng", 1);
		me->set_temp("yideng/quest_wait", 1);
		return 1;
	}
	if ( me->query_temp("yideng/quest_two") && arg == "霜凋荷叶，独脚鬼戴逍遥巾"){
		me->delete_temp("yideng");
		message_vision(CYN"$N游目四顾，只见对面平地上有一座小小寺院，庙前有一个荷塘，此时七月将\n"+
				"尽，高山早寒，荷叶已然凋了大半，心中一动，笑道：「好，我的下联是：霜\n"+
				"凋荷叶，独脚鬼戴逍遥巾。」\n\n"NOR, me);
		command("haha");
		command("say 妙极，妙极！不但对仗工整，而且敏捷之至。");
		command("say 我还有一联，请"+RANK_D->query_respect(me)+"对个下联。\n\n"
			"\t\t琴瑟琵琶，八大王一般头面。");
		me->set_temp("yideng/quest_three", 1);
		me->set_temp("yideng/ask_shusheng", 1);
		me->set_temp("yideng/quest_wait", 1);
		return 1;
	}
	if ( me->query_temp("yideng/quest_three") && arg == "魑魅魍魉，四小鬼各自肚肠"){
		me->delete_temp("yideng");
		message_vision(CYN"$N说道：「这一联是一口气要得罪渔、樵、耕、读四位，我告罪在先，这下联\n"+
				"是：魑魅魍魉，四小鬼各自肚肠。」\n"NOR, me);
	
	//处理那个特殊事件泥鳅功
	
	if (me->query_temp("nqg/askyingok"))
    {
	    if (!objectp(duzi=present("shu sheng",environment(me))))
	    {
			duzi=new("d/dali/yideng/npc/duzi");
			duzi->move(environment(me));
	    }
		command("hehe ");
		command("hehe "+me->query("id"));
		command("say 回答的倒挺好，好像是有那么回事似的，居然是一副道貌岸然的样子！\n");
		command("say 好小子，还真不赖，居然从他们三个身边过来，真不容易！\n");
		command("say 狗杂种，纳命来吧！");
		tell_object(me,HIR"\n\n\n朱子柳不知道发了什么疯，拿起手中的判官笔向你戳去！\n"NOR);
		duzi->kill_ob(me);
		me->kill_ob(duzi);
		me->add_busy(1);
		//call_out("check_jiaozi",1,me);
		return 1;
    }
	else{
		message_vision(CYN"\n$N大惊，站起身来，长袖一挥，向$n一揖到地，说道：「在下拜服。」，转\n"+
				"身纵过小缺口，道：「请罢。」\n", this_object(), me);
		me->set_temp("yideng/shusheng_pass", 1);
		return 1;
	  }		
		
	}
	command("shake");
	return 1;
}

void attempt_apprentice(object ob)
{
	
	
	if ((string)ob->query("gender") != "男性" ){
		command ("say 我向来不收女弟子，别来烦我！");
		return;
	}
	if ((string)ob->query("class")=="bonze" ){
		command ("say 阿弥陀佛！我不收出家弟子。");
		return;
	}
	if ((int)ob->query_skill("qiantian-yiyang", 1) < 250 ){
		command("say 朱某人我不收练功不勤之人，你还是多练练你的乾天一阳到250吧。");
		return;
	}
	if ((int)ob->query_skill("force", 1) < 250 ){
		command("say 朱某人不收练功不勤之人，你还是多练练你的基本内功到250吧。");
		return;
	}
	if ((int)ob->query("shen") < 1000000){
		command("say 大理段氏乃是名门正派，你不足1m正神别来找我。");
		return;
	}

	command("say 真不错的一个苗子，本师的一身武功俱都在这支笔上，你以后可要好好用心了。\n");
	command("say 既然有缘我就收下你了！\n");
	command("haha ");
	command("recruit " + ob->query("id"));
	ob->set("title", "天龙寺第十四代俗家弟子");
}

string ask_yiyangshu()
{
	int j,i,k;
	object me = this_player();

	if ( me->query("quest/tls/yiyangshu/pass"))
		return "这位"+RANK_D->query_respect(me)+"，你已经解开一阳书指，跟我开什么玩笑。\n";

	
	
	if (!me->query("family")||me->query("family/family_name")!="天龙寺")
	{
  	      command("heng "+me->query("id"));
		  return "你不是我大理弟子，所为何来，难道是奸细不成？\n";
    }
	if (me->query_skill("qiantian-yiyang",1)<300)
	{
  	  command("sigh");
  	  command("? "+me->query("id"));
		  return "一阳书指全凭一口乾天一阳真气，你的乾天一阳功力不足300，如何施展出，赶紧努力去吧。";
    }
	if (me->query_skill("yingou-bifa",1)<300)
	{
  	  command("sigh");
  	  command("? "+me->query("id"));
		  return "你的银钩笔法功力不足300，如何施展出这一阳书指，赶紧努力去吧。。";
    }
	
	if (time()-me->query("quest/tls/yiyangshu/time")<86400)
	{
  	  command("nod "+me->query("id"));
		  return "你来的也太勤快了，烦不烦！";
    }
    k=random(me->query("kar"));
	j = 20;
      if(me->query("m-card-vip")) j =  16;
      if(me->query("y-card-vip")) j =  12;
      if(me->query("buyvip"))     j =  10;
	i=random(j);
	
	if (me->query("kar")<31
		&& k >26
		&& i<5)
	{
       message_vision(HIC"\n\n$N终于将这乾天一阳功力和书法融会贯通，彻底领悟一阳书指，银钩笔法威力大增。\n"NOR,me);
	 
	   log_file("quest/yiyangshu",sprintf("%s(%s) 从朱子柳处领悟一阳书指。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),k,i,me->query("quest/tls/yiyangshu/fail"),me->query("combat_exp"),me));
	   me->set("quest/tls/yiyangshu/pass",1);
	   command("congra "+me->query("id"));
	   return "恭喜你完成了一阳书指谜题。\n";
	}
	else
	{
		message_vision(HIY"\n\n$N虽然听朱子柳说了这一阳书指绝技，但对于如何使用的劲力法门一时之间却是难以理解。\n"NOR,me);
		log_file("quest/yiyangshu",sprintf("%8s%-10s请教一阳书指，但并没有成功，尚须努力。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),k,i,me->query("quest/tls/yiyangshu/fail"),me->query("combat_exp"),me));
		me->add("quest/tls/yiyangshu/fail",1);
		me->set("quest/tls/yiyangshu/time",time());
		return "解密一阳书指谜题失败。\n";

	}     
  
}

int prevent_learn(object ob, string skill)
{
	if (skill == "yiyang-zhi"){
		command("一阳指乃是我大理国镇国之宝，非做出巨大贡献者不得而传。\n");
		return 1;
	}
	return 0;
}
/*
int check_jiaozi(object me)
{
	object duzi;
	
	duzi=present("shu sheng",environment(me));
    if (objectp(duzi)&& me->is_fighting(duzi))
    {
		remove_call_out("check_jiaozi");
		call_out("check_jiaozi",2,me);
		return 0;
    }
	if (!objectp(me)) return 0;


	me->set_temp("yideng/shusheng_pass", 1);
	return 1;	

}*/