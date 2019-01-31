// yang.c 杨过
// By River 98.8

#include <ansi.h>
#include "yang.h"
inherit NPC;
//inherit F_MASTER;
string ask_sword();
int pfm_haichao();
int pfm_anran();
string ask_skill();
string ask_skill1();
string ask_skill2();
string ask_guojing();
string ask_huangrong();
string ask_guofu();
string ask_shunv();
int do_learn(string arg);
int ask_anranzhang();
int ask_liaoshang();
int ask_zhou();
int ask_yinggu();

void create()
{
	set_name("杨过",({"yang guo","yang","guo"}));
	set("title",HIW"古墓侠侣"NOR);
	set("nickname",HIY"神雕大侠"NOR);
	set("long", "他就是名满天下的杨过。虽断一臂但仍遮不去一脸的英雄豪气。\n");
	set("age", 39);
	set("attitude", "friendly");
	set("gender", "男性");
	set("shen", 10000);
	set("per", 36);
	set("str", 40);
	set("int", 35);
	set("con", 40);
	set("dex", 35);

        set("max_qi", 50000);
        set("max_jing", 7000);
        set("neili", 58500);
        set("eff_jingli", 7500);
        set("max_neili", 58500);
        set("jiali", 250);
        set("combat_exp", 15800000);
        set("unique", 1);

        set_skill("sword",550);

		set_skill("qimen-bagua",150);
		
set_skill("dodge",500);
        set_skill("strike",550);
        set_skill("force", 550);
        set_skill("hand", 500);
        set_skill("cuff", 500);
        set_skill("parry", 500);

		set_skill("yunu-jianfa", 500);
		//
set_skill("finger",140);
        set_skill("literate", 350);
        set_skill("xiantian-gong", 150);
		//
set_skill("hamagong",300);
        set_skill("medicine",120);
        //set_skill("jingmai-xue", 80);
        set_skill("yunu-shenfa", 500);
        set_skill("xuantie-jianfa", 550);
        set_skill("anran-zhang", 550);
        set_skill("quanzhen-jianfa",500);
        set_skill("tianluo-diwang", 500);
        set_skill("yunu-xinjing",550);
        set_skill("jiuyin-zhengong",220);
        set_skill("meinu-quanfa",500);

		map_skill("force", "yunu-xinjing");        
        map_skill("sword","xuantie-jianfa");
        map_skill("dodge", "yunu-shenfa");
        map_skill("parry", "anran-zhang");        
        map_skill("hand", "tianluo-diwang");
        map_skill("strike", "anran-zhang");        
        prepare_skill("strike","anran-zhang");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
		(: exert_function, "xinjing" :),
		(: pfm_haichao :),
		(: perform_action, "strike.xiaohun":),
		(: pfm_anran :),
	}));

	create_family("古墓派",3,"男主人");

	set_temp("apply/damage", 70);
	set_temp("apply/dodge", 60);
	set_temp("apply/attack", 60);
	set_temp("apply/armor", 70);

	if (random(3))
		set("env/玄铁剑法", "汹涌");
        set("inquiry", ([
		"古墓" : "那日华山与众英雄诀别后和龙儿隐居于此已有数年，不闻世事，能与\n"+
			"龙儿在此长伴一世，此身足矣！",
		"小龙女" : "龙儿乃我爱妻，你问她做甚？",
		////"玄铁剑" : (: ask_sword :),
		//"玄铁剑法" : (: ask_sword :),
       /// "武功"  : (: ask_skill :),
		//"郭靖"  : (: ask_guojing :),
		//"黄蓉"  : (: ask_huangrong :),
		//"郭芙"  : (: ask_guofu :),
		//"淑女剑"  : (: ask_shunv :),
		"黯然销魂掌"  : (: ask_anranzhang :),
		"史家兄弟疗伤"  : (: ask_liaoshang :),
		"瑛姑"  : (: ask_yinggu :),
		"周伯通"  : (: ask_zhou :),
		//"蒙哥"  : (: ask_mengge :),
		////"剑法"  : (: ask_skill1 :),
		////"内功"  : (: ask_skill2 :),

	]));

    setup();
	carry_object(BINGQI_D("sword/gangjian"));
	carry_object("/d/gumu/obj/buxue1")->wear();
	carry_object("/d/gumu/obj/pao1")->wear();
}

void init()
{
	object ob = this_player();
	if (ob->query("quest/anran/pass"))
	{
	   add_action("do_learn","learn");
	   add_action("do_learn","xue");
	}
	::init();
}


//黯然掌开始

int ask_anranzhang()
{
	object me=this_player();
	
	if (me->is_busy()) return 0;
	if (this_object()->is_busy())
	{
		command("say 没见我很忙么，过一阵子再问？\n");
		return 1;

	}
	if (!me->query("quest/shendiao/大雪风陵渡/healover"))
	{
		
		command("say 这是我自创的一门掌法，共有一十七招。是我自从与龙儿在绝情谷逼不得已分手后，便闯荡江湖，\n");
		command("say 游历四海，行侠仗义，从而武功日长，数年之后，除了内功循序渐进外，别的无可再练，心中思念小龙女，\n");
		command("say 渐渐形销骨立。一日在海边悄立良久，百无聊赖之中随意拳打脚踢，轻轻一掌便将岩石打得粉碎。他由此深思，\n");
		command("say 创出一套完整的掌法，出手与寻常武功大异，厉害之处，全在内力。我就将这套掌法定名为“黯然销魂掌”，\n");
		command("say 取的是江淹别赋中那一句“黯然销魂者，唯别而已矣”之意。");
		if (me->query_skill("force",1)<500)
		{
			command("say 这门武功全靠雄浑的内力发动，你基本内功太弱，不足500，学了也是丢我的人。\n");
			return 1;
		}
		if (me->query("max_neili")<20000)
		{
			command("say 这门武功全靠雄浑的内力发动，你最大内力不足20000，学了也是丢我的人。\n");
			return 1;
		}
		command("say 你若想学这门绝技，就先替我去办几件事，近日得到消息，说襄阳城南的史家兄弟有难。\n");
		command("say 史家兄弟一项跟我关系很好，你带我去看看，哪儿发生什么事了。\n");
		me->set("shendiao/大雪风陵渡/askanran",1);
		me->set_temp("quest/shendiao/大雪风陵渡/askanran",1);
		return 1;
	}
	if (me->query("quest/anran/pass"))
	{ 
		command("say 这位"+RANK_D->query_respect(me) +"，我已经把黯然掌的口诀告诉你了，你难道在逗我玩么？。");
		return 1;
	}	
	
	if ((time()-me->query("quest/anran/time"))<86400)
	{ 
		command("say 这位"+RANK_D->query_respect(me) +"，你来的太频繁了？。");
		return 1;

	}
	if (me->query("gender")!="男性")
	{
			command("say 黯然销魂掌乃是纯阳的武功，非男人体质不得修习！\n");
			return 1;
	}
	if(me->query("divorce"))
	{
		command("say 你如此滥情，如何使用「黯然销魂之意」！\n");
        return 1;
		
	}	
	command("haha "+me->query("id"));
	command("say 小兄弟行侠仗义，真是不错，既然你与这门武功如此有缘，那就听好了。\n");
	me->start_busy(999);
	this_object()->start_busy(30);
    //remove_call_out("anran_think");
	call_out("anran_think",1,me);
	return 1;
}
// 瑛姑 疗伤

int ask_liaoshang()
{
	object me=this_player();
	if (!me->query_temp("quest/shendiao/大雪风陵渡/askyingfox"))
	{
		return notify_fail("你乱打听什么？\n");
	}
	command("say 史家兄弟的伤势原来必须要灵狐的血做药引子。\n");
	command("say 此事的确有些难办。\n");
	me->set_temp("quest/shendiao/大雪风陵渡/askyangshang",1);
	return 1;
	
}
int ask_yinggu()
{
	object me=this_player();

	if (!me->query_temp("quest/shendiao/大雪风陵渡/askyangshang"))
	{
		return notify_fail("瑛姑乃是段皇爷的贵妃，你乱打听什么？\n");
	}
	command("say 原来是这么回事！\n");
	command("say 既然你从瑛姑哪儿来,说明你已经找到令狐了。\n");
	command("say 只不过老顽童和瑛姑这段冤孽确实有些令人难以办理！\n");
	command("think");
	command("consider");
	me->set_temp("quest/shendiao/大雪风陵渡/askyangying",1);
	return 1;
}
int ask_zhou()
{
	object me=this_player();

	if (!me->query_temp("quest/shendiao/大雪风陵渡/askyangying"))
	{
		return notify_fail("周伯通乃是王重阳的师弟，你乱打听什么？\n");
	}
	command("say 那老顽童武功极为了得，我怕你一个人不是他的对手。\n");
	command("say 也罢，只有我和你去一趟百花谷，逼迫老顽童答应此事方可。\n");
	command("say 你先去全真教附近的百花谷去找找老顽童，我随后就到。\n");
	me->set_temp("quest/shendiao/大雪风陵渡/askyangzhou",1);
	return 1;
}

void attempt_apprentice(object ob)
{
	mapping fam = ob->query("family");
	if(!fam || fam["family_name"] != "古墓派"){
		command("say "+RANK_D->query_respect(ob)+"与本派素无来往，不知此话从何谈起？");
		return;
	}
	if(ob->query("gender") != "男性") {
		command("bow "+ ob->query("id"));
		command("say 我可只收男徒，你去找吾妻龙儿试试吧。");
		return;
	} 
	if(ob->query("divorce"))
	{
		command("你如此滥情，如何懂得「玉女心经」的精髓！\n");
        return;
	}	
	if((int)ob->query_skill("yunu-xinjing", 1) < 350) {
		command("say 玉女心经内功是古墓武功之基础。"); 
		command("say " + RANK_D->query_respect(ob)+"是否还应该先在内功上多下点功夫（350）？");
		return;
	}   
	if((int)ob->query_int() < 50 ) {
		command("say 我的武功都要极高的悟性才能学会（50）。");
		command("say 要能达到炉火纯青之境，体质什么的倒是无关紧要，悟性却是半点也马虎不得。");
		command("say "+RANK_D->query_respect(ob)+"的悟性还大有潜力可挖，还是请回吧。");
		return;
	}
	if((int)ob->query("shen") < 2000000){
		command("say 我古墓弟子行走江湖中，一向行侠仗义。");
		command("say 这位" + RANK_D->query_respect(ob)+"正气不够2m，去做几件侠义的事后再来吧？");
		return;
	}
	command("say 嗯，看你还是个学武的料，我就收下你吧！");         
    command("chat 古墓武功重现江湖，"+ ob->name() +"可别让为师看走眼了！");
    command("chat* pat " + ob->query("id"));
	command("recruit " + ob->query("id"));
	ob->set("title","古墓派神雕侠侣传人");
}

//玄铁剑开始

string ask_guojing()
{
	object me=this_player();
	command("say 郭伯父是我父亲的义兄，待我很好，他和郭伯母一向相敬如宾。\n");
	command("say 我从小受他们照顾和教导，郭伯父待我如亲子。\n");
	command("say 后来发生一些事情，使得我以为害死我父亲的凶手是郭伯父\n");
	command("say 我差点为此犯下大错！\n");
	command("sigh ");
	command("consider ");
	command("say 郭伯母待我并没郭伯父待我好。\n");
	me->set_temp("xtjf/askguo",1);
	return "其实从小时候我就知道，但为了不让郭伯父伤心，我一直没说出来。\n";
}
string ask_huangrong()
{
	object me=this_player();
	if (!me->query_temp("xtjf/askguo"))
		return "你问这个做什么？难道有什么不良企图不成？\n";
	me->delete_temp("xtjf/askguo");
	command("say 郭伯母是郭伯父的妻子，他和郭伯夫一向相敬如宾。\n");
	command("say 我从小受他们照顾和教导，郭伯父待我如亲子。\n");
	command("say 虽然小时候郭伯母待我不是太好，甚至有些讨厌我，但我想都是我年轻不懂事导致的。\n");
	command("say 后来当我知道我爹的真相时，我才明白，她原来是讨厌我父亲！\n");
	command("sigh ");
	command("consider ");
	command("say 他们有个女儿叫郭芙，小时候我们一起在桃花岛玩耍,经常打架，哈哈。\n");
	command("laugh ");
	command("say 不过后来发生了一件意外事件，从而使得我的整个人生都发生逆转,这全都拜郭芙所赐！\n");
	
	me->set_temp("xtjf/askhuang",1);
	return "我心中一直对此难以释怀，放不下，唉，冤孽啊。\n";
}
string ask_guofu()
{
	object me=this_player();
	if (!me->query_temp("xtjf/askhuang"))
		return "你问这个做什么？难道有什么不良企图不成？\n";
	me->delete_temp("xtjf/askhuang");
	command("say 芙妹是郭伯父和郭伯母的女儿。\n");
	command("say 她长得很漂亮，但我并不喜欢她，主要因为她从小就蛮不讲理，任性的很。\n");
	command("say 后来在襄阳城中她竟然一剑将我的左臂给断掉，害的我差点成为废人。\n");
	command("say 我当时昏死在地，醒后在半梦半醒之间迷迷糊糊地走入到一处人迹罕至之所！\n");
	command("say 在雕兄的帮助下，我才最终养好伤，原本我以为自己从此将成为废人。\n");
	command("say 哪知道，天不亡我，在雕兄的帮助下我竟然习得了剑魔独孤前辈的玄铁剑法。\n ");
	command("say 从此我走向了一条完全不同的练剑之路，这门剑法就叫做玄铁剑法。\n");
	
	command("say 不过后来发生了一件意外事件，从而使得我的整个人生都发生逆转,这全都拜郭芙所赐！\n");
	
	me->set_temp("xtjf/askfu",1);
	return "这把剑叫淑女剑，想起来我就心理不舒服。\n";
}
string ask_shunv()
{
	object me=this_player();
	if (!me->query_temp("xtjf/askfu"))
		
		return "你问这个做什么？难道有什么不良企图不成？\n";
	me->delete_temp("xtjf/askfu");
	command("say 淑女剑极其锋利，削铁如泥，寻常地方不容易寻找到，我记得是在绝情谷中。\n");
	command("say 淑女剑乃是断我一臂之物，至今思来不胜唏嘘。\n");

	me->set_temp("xtjf/askshunv",1);
	return "你若有心就替我先去把它找来。\n";
}

//寻找淑女剑
int accept_object(object me, object obj,object ob)
{
	ob = this_object();
	if (!me->query_temp("xtjf/askshunv")) return 0;
	
	if (obj->query("id")=="shunu jian")
	//&& obj->query("name")=="淑女剑"
	{
		message_vision(HIC"$N将这柄淑女剑拿在手中，翻来覆去的观看，面上脸色变幻不定。\n"NOR,ob);
		command("say 这把剑真是大凶之物，这么多年了，竟然还是如此的锋利。\n");
		command("say 嗯，既然你这么有心，我就收下这小礼物了。\n");
		message_vision(HIC"$N将这柄淑女剑插入剑鞘，顺手扔到一旁，不再理会，但对你的态度明显有所好转。\n"NOR,ob);
		command("sigh ");
		command("say 你既然有心就替我办第二件事吧，去把襄阳郊外的蒙哥给我杀了，也算是我帮郭伯父的一个忙了。\n");
		//me->delete_temp("xtjf/askshunv");
		me->set_temp("xtjf/shunvok",1);
		destruct(obj);
		return 1;

	}
	if (obj->query("id")=="shouji" &&obj->query("name")=="蒙哥的首级" )
	{
		if (!me->query_temp("xtjf/shunvok"))
		{
			command( "say 你连我交给你的第一件事情都办不好，还来此作甚？\n");
			return 1;
		}
		message_vision("$N将一颗蒙哥的首级递给$n观看。\n",me,ob);
		command("laugh ");
		command("say 好，这位侠士真是不错，能在万军丛中斩上将首级，真乃英雄也！\n");
		command("say 既然你如此有诚意，那么在替我去把我的一位大仇人给我杀了。\n");
		command("say 他是蒙古国第一国师，金轮法王，他的龙象波若功乃是大成境界，你要当心。\n");
		command("say 若实在打不过也不用逞强。这奸贼早晚要死于我手！\n");
		me->delete_temp("xtjf/shunvok");
		me->set_temp("xtjf/killmg",1);
		return 1;
	}
	if (obj->query("id")=="shouji"&& obj->query("name")=="金轮法王的首级")
	{
		if (!me->query_temp("xtjf/killmg"))
		{
			command( "你连我交给你的第二件事情都办不好，还来此作甚？\n");
			return 1;
		}
		message_vision("$N将一颗金轮法王的首级递给$n观看。\n",me,ob);
		command("laugh ");
		command("say 好，这位侠士真是不错，居然能将金轮法王这臭贼都杀死！\n");
		command("say 嗯，真心不错。那第四件事情是替我把那枚世上仅存的绝情丹给我找来\n");
		command("say 这枚绝情丹是我留给龙儿消除体内情花毒的。\n");
		me->delete_temp("xtjf/killmg");
		
		me->set_temp("xtjf/killfawang",1);
		return 1;
	}
	//&& obj->query("name")=="绝情丹"
	if ( obj->query("id")=="jueqing dan" )
	{
		if (!me->query_temp("xtjf/killfawang"))
		{
			command( "你连我交给你的第三件事情都办不好，还来此作甚？\n");
			return 1;
		}
		message_vision("$N将一颗绝情丹递给杨过。\n",me);
		command("laugh ");
		command("say 好，有了这枚绝情丹，龙儿的情花之毒必将解了！\n");
		command("say 既然如此，那你就替我将那柄玄铁剑替我拿来。\n");
		command("say 我告诉你运气的法门，能否领悟就看你个人的悟性了。\n");
		command("say 你一定要去剑冢哪儿看看，早去早回，若去晚了，说不定会被人拿走了！\n");
		me->delete_temp("xtjf/killfawang");
		me->set_temp("xtjf/getjqd",1);
		return 1;
	}
//&&obj->query("name")=="玄铁剑"
	if (obj->query("id")=="xuantie jian")
	{
		if (!me->query_temp("xtjf/getjqd"))
		{
			command( "你连我交给你的第四件事情都办不好，还来此作甚？\n");
			return 1;
		}
		message_vision(HIY"$N将这柄玄铁剑拿在手中，翻来覆去的观看，用手轻轻的抚摸，神情间弥漫着温柔。\n"NOR,ob);
		command("say 重剑无锋，大巧不工。\n");
		command("say 你明白这其中的道理了么？。\n");
		message_vision(HIM"$N将这柄玄铁重剑轻轻放在身边，举重若轻，坐在那儿，神情漠然,仿佛在想什么。\n"NOR,ob);
		command("sigh ");
		command("say 你既然有心就替我办第第五件事吧，我无以为报，只得把玄铁剑法的奥秘告诉你了。\n能否领悟就看你自己的悟性了，这玄铁剑法并非靠蛮力，悟性很重要。\n");
		me->delete_temp("xtjf/getjqd");
		me->set_temp("xtjf/getxtjok",1);

		me->set("xtjf/getxtjok",1);
		obj->destruct();
		return 1;
	}

    return 1;
	
}

string ask_sword()
{
	object ob=this_player();
	mapping fam = ob->query("family");
	if (this_object()->is_busy())
	{
		return RANK_D->query_respect(ob) +"没见我很忙么，过一阵子再问？\n";

	}
	if (!ob->query("xtjf/getxtjok"))
	{
		return RANK_D->query_respect(ob) +"连我交给你的任务都做不好，还想学玄铁剑法？\n";
	}	

	if ( ob->query("shen") < 0)
		return RANK_D->query_respect(ob) +"邪气太重，想必独孤前辈也不愿他的剑法被用来做恶。";

	
	if ( ob->query("max_neili")<15000)
		return "你当前的最大内力不足15000，去了也把握不了那把玄铁剑，你还是把内力提高了再去吧？";
	if ( ob->query_skill("force",1)<450)
		return "你当前的基本内功修为不足450，抗衡不了那瀑布的威力，还是修炼后再去吧？";
	//屏蔽掉女性
	if ( ob->query("gender") == "女性"){
		return "这位"+RANK_D->query_respect(ob) +"，玄铁剑法需要阳刚之力，你一个女孩子还是别练成肌肉男了。";
	}
	if ( ob->query("gender") == "无性"){
		return "这位"+RANK_D->query_respect(ob) +"，玄铁剑法需要阳刚之力，你阴阳不调，练不成的。";
	}
	//添加解密环节
	if (ob->query("quest/xtj/pass"))
	{ 
		return "这位"+RANK_D->query_respect(ob) +"，我已经把口诀告诉你了，你难道在逗我玩么？。";
	}	
	if (time()-ob->query("quest/xtj/time")<86400)
	{ 
		return "这位"+RANK_D->query_respect(ob) +"，你来的太频繁了？。";

	}
	//判断是否完成任务。
	//寻找淑女剑、杀蒙哥，杀金轮法王，拿玄铁剑	
	this_object()->start_busy(30);

	if ( ob->query("gender")=="男性") {
		command("pat "+ ob->query("id"));
		command("say 当年我在襄阳城南，得遇神雕的相助，于独孤大侠墓前练成玄铁剑法。");
		command("say");
		//ob->set("ygpass", 1);
		ob->start_busy(999);
		remove_call_out("thinking");
		call_out("thinking",1,ob);
		
		return "屏气具息，凝气守中，意守丹田，你好好领悟一下吧,若想明白了再去瀑布哪儿试试。\n";
	}	
	
}

int pfm_haichao()
{
	object me,weapon;
	me = this_object();
	weapon = present("gangjian",me);
	if( me->is_busy()) return 0;
	if( objectp(weapon)){
		set("jiali", 50);
		command("wield jian");
		command("perform haichao");
		if(random(10) > 5){
			set("jiali", 150);
			command("unwield jian");
		}
		return 1;
	}
	else {
		new(BINGQI_D("sword/gangjian"))->move(me);
		set("jiali", 50);
		command("wield jian");
		command("perform haichao");
		if(random(10) > 5){
			set("jiali", 150);
			command("unwield jian");
		}
		return 1;
	}
	return 1;
}

int pfm_anran()
{
	object me,weapon;
	me = this_object();
	weapon = me->query_temp("weapon");

	if(me->is_busy()) return 0;
	if( me->query("eff_qi") < 1 ) return 0;
	if( me->query("max_qi") / me->query("eff_qi") < 2 ) return 0;
	if(objectp(weapon)) weapon->unequip();
	this_object()->set("jiali", 150);
	command("perform anran");
	return 1;
}

string ask_skill()
{
	mapping fam;

	if( !(fam = this_player()->query("family")) || fam["family_name"] != "古墓派" )
		return "我与"+RANK_D->query_respect(this_player())+"素无瓜葛，不知此话从何谈起？";

	if( this_player()->query_temp("gumu_skill") )
		return RANK_D->query_respect(this_player()) + "，你可以向我请教‘剑法’或‘内功’方面的问题！";

	if( this_player()->query_skill("sword") < 150 )
		return RANK_D->query_respect(this_player()) + "的剑法似乎还不够精进啊！";

	if( this_player()->query("gumu_given") >= 300 )
		return RANK_D->query_respect(this_player()) + "，你的武功已经不弱了，我已经没什么可以指教的了。";

	if( this_player()->query_skill("yunu-xinjing", 1) > this_player()->query("gumu_given") + 30 ) {
		this_player()->set_temp("gumu_skill", 1);
		return RANK_D->query_respect(this_player()) + "的内功大有精进，我就指点你几下吧，你可以请教我关于‘"HIY"剑法"CYN"’或‘"HIY"内功"CYN"’的疑问！";
	} else {
		return "我近期不是刚指教过你吗？武学的关键靠的还是自己努力练习啊！\n";
	}
}

int prevent_learn(object ob, string skill)
{
	if (skill == "anran-zhang")
		return 0;
	return 1;
}

int is_apprentice_of(object ob)
{
	return 1;
}
 
int recognize_apprentice(object ob)
{
	return 1;
}


//特殊的封掉
/*
string ask_skill1()
{
	object me, ob;
	int skill, pot;
	mapping fam;

	me = this_player();
	ob = this_object();

	if( !(fam = this_player()->query("family")) || fam["family_name"] != "古墓派" )
		return "我与"+RANK_D->query_respect(this_player())+"素无瓜葛，不知此话从何谈起？";

	if( this_player()->query_skill("sword") < 150 )
		return RANK_D->query_respect(this_player()) + "的剑法似乎还不够精进啊！";

	if( !me->query_temp("gumu_skill") )
		return "当年我在襄阳城南，得遇神雕的相助，于独孤大侠墓前练成玄铁剑法！";

	if( (int)me->query_skill("yunu-xinjing", 1) > 300 ) 
		skill = 300 - (int)me->query("gumu_given");
	else skill = (int)me->query_skill("yunu-xinjing", 1) - (int)me->query("gumu_given");

	pot = skill * 10;
	pot += random(pot/2);

	skill /= 30;
	if( skill < 1 ) skill = 1;

	message_vision(HIB"$n微笑不语，将手中的剑从轻而响，从响而轻，忽寂然无声，忽轰轰之声，反复演练着。\n"NOR,me,ob);
	message_vision(HIW"$N照着$n所展示的方法练习，果然武功大有长进。\n"NOR,me,ob);

	me->delete_temp("gumu_skill");
	me->set("gumu_given", (int)me->query_skill("yunu-xinjing", 1));

	me->set_skill("xuantie-jianfa", me->query_skill("xuantie-jianfa", 1) + skill );
	me->set_skill("quanzhen-jianfa", me->query_skill("quanzhen-jianfa", 1) + skill );
	me->set_skill("yunu-jianfa", me->query_skill("yunu-jianfa", 1) + skill );
	me->set_skill("sword", me->query_skill("sword", 1) + skill );
	me->add("potential", pot );

	tell_object(me, HIC"你的「玄铁剑法」进步了！\n"NOR);
	tell_object(me, HIC"你的「全真剑法」进步了！\n"NOR);
	tell_object(me, HIC"你的「玉女素心剑」进步了！\n"NOR);
	tell_object(me, WHT"你的增加了" + chinese_number(pot) + "点潜能。\n"NOR);

	return RANK_D->query_respect(me) + "天资过人，真是个可造之才啊！哈哈哈！";
}

string ask_skill2()
{
	mapping fam;
	object me, ob;
	int skill, neili;

	me = this_player();
	ob = this_object();

	if( !(fam = this_player()->query("family")) || fam["family_name"] != "古墓派" )
		return "我与"+RANK_D->query_respect(this_player())+"素无瓜葛，不知此话从何谈起？";

	if( this_player()->query_skill("sword") < 150 )
		return RANK_D->query_respect(this_player()) + "的剑法似乎还不够精进啊！";

	if( !me->query_temp("gumu_skill") )
		return "屏气具息，凝气守中，意守丹田，这就是在洪水中运气的诀窍，你好好去领悟一下吧。";

	if( (int)me->query_skill("yunu-xinjing", 1) > 300 ) 
		skill = 300 - (int)me->query("gumu_given");
	else skill = (int)me->query_skill("yunu-xinjing", 1) - (int)me->query("gumu_given");

	neili = skill/2;
	neili += random(neili/4);

	skill = random(skill)/30;
	if( skill < 1 ) skill = 1;

	message_vision(HBYEL"$n屏气具息，凝气守中，意守丹田，周身真气聚集，正反运行玉女心经。\n"NOR,me,ob);
	message_vision(HIW"$N受了$n的启悟，心中疑团顿时解开，对内功的领悟又更进了一层。\n"NOR,me,ob);

	me->delete_temp("gumu_skill");
	me->set("gumu_given", (int)me->query_skill("yunu-xinjing", 1));

	me->set_skill("yunu-xinjing", me->query_skill("yunu-xinjing", 1) + skill );
	me->set_skill("force", me->query_skill("force", 1) + skill );
	tell_object(me, HIC"你的「玉女心经」进步了！\n"NOR);
	tell_object(me, HIC"你的「基本内功」进步了！\n"NOR);

	me->add("max_neili", neili );
	tell_object(me, WHT"你的内力修为增加了" + chinese_number(neili) + "点。\n"NOR);

	return RANK_D->query_respect(me) + "天资过人，真是个可造之才啊！哈哈哈！";
}
*/

