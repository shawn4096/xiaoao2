// Npc: wuming-laoseng
inherit NPC;
inherit F_MASTER;
#include <ansi.h>

string ask_wx();
int ask_wj();
mixed ask_ff();
int ask_wxjj(); 
void create()
{
        set_name("无相禅师", ({"wuxiang chanshi", "wuxiang", "chanshi",
        }));
        set("long",
                "他是一位身穿青袍的枯瘦僧人，身材精瘦。\n"
                "须发已然全白，也看不出多少年纪。\n"
        );


        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");
        set("no_bark",1);

        set("age", 80);
        set("shen", 32000);
        set("str", 40);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 8000);
        set("max_jing", 7000);
        set("eff_jingli", 4000);
        set("neili", 25000);
        set("max_neili", 25000);
        set("jiali", 100);
        set("combat_exp", 6000000);

        set_skill("force", 550);
        set_skill("yijin-jing", 550);
        set_skill("dodge", 550);
        set_skill("shaolin-shenfa", 550);
        set_skill("parry", 550);
        set_skill("finger", 550);
        set_skill("buddhism", 220);
        set_skill("literate", 550);
	    set_skill("wuxiang-zhi",550);
	    set_skill("cuff",550);
	    set_skill("luohan-quan",550);

        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "wuxiang-zhi");
	    map_skill("cuff","luohan-quan");

        prepare_skill("finger", "wuxiang-zhi");
	    prepare_skill("cuff", "luohan-quan");

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "finger.qiankun" :),
        }));

        create_family("少林派", 34, "弟子");
	    set("inquiry", ([
		"少林武技": (: ask_wj :),
		"无相劫指": (: ask_wx :),
		"无相绝技": (: ask_wxjj :),
		"佛法": (: ask_ff :),
	]));

        setup();
        set_temp("apply/damage", 50);
        set_temp("apply/dodge", 100);
        set_temp("apply/attack", 80);
        set_temp("apply/armor", 60);
	UPDATE_D->get_cloth(this_object());
	set("no_quest", 1);
}

void attempt_apprentice(object ob)
{
	command("say 对不起，老衲现在不收徒。");
	return;
}
/*
string ask_wj()
{
	object me=this_player();
   
	if(me->query("wxz/quest") < 4) return 0;
	
	if( me->query("wxz/quest")== 4 && random(me->query("kar"))>=27)
		me->set("wxz/quest",5);
	return RANK_D->query_respect(me)+"何苦贪恋武学小技，须知慈悲为怀，方能修成正果。\n"
		+"不过既然你能来到这里，也算我俩有缘，我这套无相劫指，便传了给你吧。\n";
}
*/
string ask_wj()
{
	object me=this_player();

	if(me->query("wxz/done"))
		return RANK_D->query_respect(me)+"不是已经学到了么？\n";

	if(me->query("wxz/quest")<5)
		return "";
	if( me->query("wxz/quest")== 5)
		me->set_temp("wxz/done",1);
        command("say 你可以尝试以指力鼓劲，拨动地上的木屑，或可有所心得。");

	   // log_file("quest/wuxiang", sprintf("%8s%-10s 在无相禅师处学到无相劫指。\n",
	//	me->query("name"), "("+me->query("id")+")" ), me);
	    
	    return "只是木片跃动，便是有相。当真要名副其实，练至无形无相，纵穷毕生之功，也不易有成。";
}

mixed ask_ff()
{
	object me=this_player();

	if (!me->query("potential")) return "你的潜能不够了。";
	if (!me->query("wxz/poison")) return RANK_D->query_respect(me)+"佛法精深，心怀慈悲，我目前实在没有什么可以教你的。";

	do if (me->add("wxz/poison",-2-random(2)) < 0) {
		me->set("wxz/poison",0);
		break;
	}
	while (me->add("potential",-4-random(2)) > 0);
	if (me->query("potential") < 0) me->set("potential",0);
	command("say 即心即佛，即佛即心，心明识佛，识佛明心，离心非佛，离佛非心……");
	command("buddhi wuxiang chanshi");
	tell_object(me,"你端坐良久，若有所悟。\n");
	return 1;
}
int ask_wxjj() 
{
	object me = this_player();
	int i;
	if(this_object()->is_fighting()) return 0;
	message_vision(HIC"$N向$n请教有关无相劫指绝技的真正奥妙。\n"NOR, me, this_object());
	
	if(!me->query("wxz/done")||!me->query("wxjz/pass"))
	{
		command("?");
		command("say 你连无相劫指是什么东西都不知道，还想妄谈绝技？"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	command("look "+me->query("id"));	
	//普通玩家三次
   if(me->query("wxjz/jueji"))
	{
	
		command("say "+me->query("id"));
		command("say 你已经解开该项绝技了，老是来烦老僧，是不是吃饱了？\n");
		me->set("title",HIR"无相"HIW"无色"HIY"禅师"NOR);
		me->set("mytitle/quest/wusewuxiangtitle",HIR"无相"HIW"无色"HIY"禅师"NOR);
		return 1;
	}
	if(me->query("wxzjj/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔50K
	if( time()-me->query("wxzjj/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到到这里吧，明天吧。");
		return 1;
	}
	if(me->query("combat_exp")<5000000)
	{
		command("look "+me->query("id"));
		command("say 以你当前的经验恐怕还是难以领悟，还是抓紧去练功去吧。");
		return 1;
	}
    
	me->set("wxzjj/time",time());
	me->set("wxzjj/combat_exp",me->query("combat_exp")); 
	i= random(20);
	command("sigh "+me->query("id"));
	command("say 无相无形。既然你想打听，我就说给你听听，看你有没有这个悟性了。");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
	if(i==3 
	  && random(me->query("kar"))>27
	  && random(me->query("int"))>35
	  && me->query("kar")<31)
	{
		tell_object(me,HIY"\n你按照无相禅师的指点，对无相劫指的真正奥妙似乎有些心得。\n"NOR);
		tell_object(me,HIW"\n你先从‘起手式’开始演练，一路演练下来，潇洒自如。\n"NOR);
       
		
		//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("buddha "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("title",HIR"无相"HIW"无色"HIY"禅师"NOR);
		me->set("mytitle/quest/wusewuxiangtitle",HIR"无相"HIW"无色"HIY"禅师"NOR);
		me->set("wxjz/jueji",1);
		log_file("quest/wxjueji", sprintf("%8s(%8s) 失败%d次彻底领悟无相劫指的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("wxzjj/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("wxzjj/fail",1);
		command("buddha");
		tell_object(me,HIY"你听了无相禅师的指点，虽然看见了无相劫指的招式，可是对无相劫指的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/wxjueji", sprintf("%8s(%8s) 无相劫指绝技解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("wxzjj/fail"),i,me->query("combat_exp")) );
	}
	return 1;
}


int ask_wx() 
{
	object me = this_player();
	int i;
	if(this_object()->is_fighting()) return 0;

	message_vision(HIG"$N向$n请教有关无相劫指的奥秘。\n"NOR, me, this_object());
	
	if(me->query("wxz/done"))
	{
		command("smile "+me->query("id"));
		me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		
		return 1;
	}
	if (!me->query_temp("wxz/done"))
	{
		command("say 你是怎么来到这里的？按照原来流程走，先问禅师少林武技，再来询问无相劫指。\n");
	    return 1;
	}
	command("look "+me->query("id"));	
	//普通玩家三次
	if(me->query("wxjz/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	//武功学习之间需要间隔一天，经验需要间隔50K
	if( time()-me->query("wxjz/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到到这里吧，明天吧。");
		return 1;
	}
	if(me->query("combat_exp")<5000000)
	{
		command("look "+me->query("id"));
		command("say 以你当前的经验恐怕还是难以领悟，还是抓紧去练功去吧。");
		return 1;
	}
    
	me->set("wxjz/time",time());
	me->set("wxjz/combat_exp",me->query("combat_exp")); 
	i= random(15);
	command("sigh "+me->query("id"));
	command("say 无相无形。既然你想打听，我就说给你听听，看你有没有这个悟性了。");
	command("whisper "+me->query("id"));
	command("smile "+me->query("id"));
	if(me->query("kar")<31 
		&& random(me->query("kar"))>=27
		&&i==2)
	{
		tell_object(me,HIY"\n你按照无相禅师的指点，对无相劫指似乎有些心得。\n"NOR);
		tell_object(me,HIW"\n你先从‘起手式’开始演练，一路演练下来，潇洒自如。\n"NOR);
		tell_object(me,HIR"\n忽然间，你食指一股劲气喷涌而出，或阴柔或刚强，变化莫测，令人防不胜防。\n"NOR);
		tell_object(me,HIC"\n恭喜你！经过千辛万苦，你终于如愿以偿，习得少林绝技无相劫指。\n"NOR);
		//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("buddha "+me->query("id"));
		command("haha "+me->query("id"));
		//me->set(QUESTDIR4+"sword",1);
		me->set("wxjz/pass",1);
		me->set("wxz/done",1); 
		me->set("title",HIR"无相劫指传人"NOR);
		me->set("mytitle/quest/wxjztitle",HIR"无相劫指传人"NOR);
		log_file("quest/wxjz", sprintf("%8s(%8s) 失败%d次彻底领悟无相劫指。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("wxjz/fail"),i,me->query("combat_exp")) );
	}
	else
	{
		me->add("wxjz/fail",1);
		//me->set("wxjz/");
		command("buddha");
		tell_object(me,HIY"你听了无相禅师的指点，虽然看见了无相劫指的招式，可是对无相劫指的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/wxjz", sprintf("%8s(%8s) 无相劫指绝技解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("wxjz/fail"),i,me->query("combat_exp")) );
	}
	return 1;
} 