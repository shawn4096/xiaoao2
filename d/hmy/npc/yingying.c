// yingying.c
// Finish by action@SJ 2009.1.6
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_chong();
string ask_ling();
int do_answer(string arg);
string ask_sanshi();
string ask_qingxinzhou();
void create()
{
        
        set_name("任盈盈", ({ "ren yingying","ren","yingying" }));
        set("long", "她容貌秀丽绝伦，不过十七八岁年纪，娇羞之态，娇美不可方物。\n");
        set("nickname", HIC"小妖女"NOR);
        set("title", HIY"日月神教  圣姑"NOR);
        set("gender", "女性");
        set("attitude", "peaceful");
        set("age", 18);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 30);
        set("unique", 1);
        set("location", 1);
        set_temp("no_return", 1);

        set("max_qi", 15000);
        set("qi", 15000);
        set("jing", 6300);
        set("max_jing", 6300);
        set("neili", 19000);
        set("max_neili",19000);
        set("eff_jingli", 5700);
        set("jingli", 5700);
        set("jiali", 200);
        set("combat_exp", 9800000);
        set("shen", -1200);

        set_temp("apply/attack", 40);
        set_temp("apply/defence", 40);

        set_skill("tianmo-zhang",400);
        set_skill("mantian-huayu",400);
        set_skill("qingxin-jian",450);
        set_skill("strike", 400);
		set_skill("hand", 400);
        set_skill("parry", 400);
        set_skill("dodge",400);
        set_skill("huanmo-wubu", 400);
        set_skill("tianmo-shou", 400);
        set_skill("force", 400);
        set_skill("sword",450);
        set_skill("throwing",400);
        set_skill("tianmo-gong", 400);
        set_skill("tianmo-jue", 200);
        set_skill("art", 200);

        map_skill("strike", "tianmo-zhang");
        map_skill("hand", "tianmo-shou");
        map_skill("throwing", "mantian-huayu");
        map_skill("sword", "qingxin-jian");
        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
        map_skill("parry", "qingxin-jian");
        prepare_skill("hand", "tianmo-shou");
        set("inquiry", ([
			 "令狐冲": (: ask_chong :),
		     "黑木令": (: ask_ling :),
			 "三尸脑神丹": (: ask_sanshi :),
		     "清心普善咒": (: ask_qingxinzhou :),

        ]));

        create_family("日月神教", 8, "长老");
        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chaofeng" :),
				(: perform_action, "sword.qingxin" :),

                (: exert_function, "tianmo" :),
        }));

        setup();

        carry_object("/clone/misc/cloth")->wear();     
        carry_object(("clone/weapon/duanjian"))->wield();    
}

void init()
{
	object ob;
	::init();
	ob = this_player();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object me)
{
	
	object chong;
	me=this_player();
	if(!me) return;
    if (present("heimu ling",me)) 
    {
		command("angry "+me->query("id"));
        return;
    }

	if (!me->query_temp("hostage/passed_l")) return;

	//hmling->move(this_object());

	if ( file_name(environment(this_object())) != "/d/changan/xiaoshe") return;
    
	
    if(objectp(chong=present("linghu chong",environment(me)))){
		command("chat* blush");
		command("chat 冲哥，我没想到居然又见到你了！\n");
		message_vision(HIY"令狐冲和盈盈在一起有说有笑，甚是开心。\n"NOR,me);
        command("thank " + me->query("id"));
		command("say 既然这位" + RANK_D->query_respect(me)+"让我见到了冲哥，我就把这块黑木令送给你当做心意了。\n");
		//command("give "+me->query("id")+" heimu ling");
        new("/d/hmy/npc/obj/heimuling")->move(me);
		me->set_temp("hostage/linggived",1);
		me->delete_temp("hostage/passed_l");
		
		if (me->query_temp("qxj/askren"))
		{
			message_vision(HIC"任盈盈对$N笑道，“既然你如此用心，我就把这清心普善咒的道理说给你听听，你听好了。”\n"NOR,me);
			me->set("quest/hmy/qxj/qingxin/pass",1);

		}
		message_vision(CYN"令狐冲见已经处理完当前事宜，就和盈盈携手离开而去,真是一对神仙眷侣。\n"NOR,me);
		destruct(chong);
		return ;
	}
	

}


void attempt_apprentice(object ob)
{
     if(ob->query_skill("force",1) < 200 ||
      ob->query_skill("qingxin-jian",1) < 200 ||
        ob->query_skill("tianmo-shou",1) < 200){
        command("say 你的武功还不够娴熟，再回去练练吧。");
        return;
        }
	 if (ob->query("family/family_name")!="日月神教")
	    return notify_fail("我虽说不经常居住黑木崖，但也不胡乱收弟子！\n");

     command("say 好，我正想招兵买马救教主出来，看来你还不错嘛，就收下你了。");
     command("recruit " + ob->query("id"));
     ob->set("title",HIW"日月神教圣姑座下弟子"NOR);
}

int ask_chong()
{
     object me=this_player();
  
     command("say 自上次一别，再也没有见到冲哥，不知道他现在正在做什么。\n");
	 command("blush "+me->query("id"));
	 command("say 你是否愿意替我跑一趟华山，替我送一封信？(answer 是/否)");
	 
	 me->set_temp("askyy/songxin",1);
	 add_action("do_answer","answer");
	 return 1;

}
int do_answer(string arg)
{
	 object me=this_player();
     object ob=this_object();
     if (!me->query_temp("askyy/songxin"))
       return notify_fail("你想做什么？\n");
	 if (!arg||arg!="愿意")
	   return notify_fail("你在这胡说八道，做什么？\n");
     if(arg == "是" || arg == "愿意" ){
        me->delete_temp("askyy/songxin");
		me->set_temp("yy/songxin",1);
		me->set_temp("qxj/askren",1);
		message_vision(HIG"$N点了点头，连声称“好的，圣姑，我愿意替你去送信！”\n"NOR,me,ob);
		
		message_vision(HIC"$n见$N如此爽快答应，不禁面露赞许之色。\n"NOR,me,ob);
		command("say 我把这封信就交给你了！\n");
	    new("/d/hmy/npc/obj/letter")->move(me);
       return 1;
    }
    return 0;

}


string ask_ling()
{
     object me=this_player();
     object ling;
	 command("jump");
	 if (me->query("family/family_name")!="日月神教")
            { command("?");
	    return "你不是我神教弟子，黑木令岂能是你所拥有的？\n";
            }
	 if ((int)me->query_skill("tianmo-gong",1)<450)
		return "你天魔功力太浅，黑木令岂能是你所拥有的？\n";
     command("say 黑木令乃是神教极其神圣之物，乃教主信物，见令如见教主。\n");
	 //ling=new("/d/hmy/npc/obj/heimuling");
     return "";

}
string ask_sanshi()
{
     object me=this_player();
     object dan;
	 if (me->query("family/family_name")!="日月神教")
	    return "你不是我神教弟子，三尸脑神丹岂能是你所拥有的？\n";
	 if (me->query_skill("tianmo-gong",1)<450)
		return "你天魔功力太浅，给你三尸脑神丹也是浪费？\n";
     if (!me->query_temp("hostage/linggived"))
        return "三尸脑神丹乃是神教贵重之物，凭什么要给你？\n";
	
	 command("say 多谢你替我冲哥送信，无以为报，这枚三尸脑神丹就给你吧。\n");
	 command("xixi");
	 message_vision(HIG"$n递给$N三粒三尸脑神丹.\n"NOR,me,this_object());
	 me->delete_temp("hostage/linggived");
	 new("/d/hmy/obj/sanshidan")->move(me);
     new("/d/hmy/obj/sanshidan")->move(me);
     new("/d/hmy/obj/sanshidan")->move(me);
     return "";

}

string ask_qingxinzhou()
{
     object me=this_player();
     object dan;
	 if (me->query("family/family_name")!="日月神教")
	    return "你不是我神教弟子，我不会教给你的？\n";
	 if (me->query_skill("force",1)<200)
		return "你基本功力太浅，传给你也是浪费？\n";
     if (me->query("quest/hmy/qxj/qingxin/pass"))
        return "你不是已经解开这清心普善咒的奥秘了么？\n";
	 command("say 这清心普善咒乃是一门奇异的武学，你若感兴趣，就替我跑趟腿！\n");
	 command("say 你去替我给冲哥送信，把他请来，我就告诉你。\n");
	 command("xixi");
     me->set_temp("qxj/askren",1);	 
	 return "";

}
