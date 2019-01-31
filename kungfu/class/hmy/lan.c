// lan.c

#include <ansi.h>
inherit F_MASTER;
inherit NPC;
string ask_book();
string ask_dan();
string ask_xiezifen();
void create()
{
        set_name(HIB"蓝凤凰"NOR, ({ "lan fenghuang", "lan", "fenghuang"}));
        set("long", "这女子肌肤微黄，双眼极大，黑如点漆。\n"+
        	    "她掌管日月教在苗疆的下属“五毒教”，使毒手法诡秘奇特，令人防不胜防。\n");
        set("title",HIY"日月神教  "HIB"五毒教教主"NOR);
        set("gender", "女性");
        set("age", 23);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("per", 25);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);

        set("max_qi", 9800);
        set("max_jing", 5600);
        set("eff_jingli", 5600);
        set("jiali", 150);
        set("combat_exp", 5500000);
		set("book_count",1);
		set("dan_count",3);

        set_skill("parry", 380);
        set_skill("poison", 200);
        set_skill("dodge", 380);
        set_skill("force", 380);
        set_skill("hand", 380);
		set_skill("whip", 380);
        set_skill("literate", 100);
        set_skill("huanmo-wubu", 380);        
        set_skill("tianmo-shou", 380);
		set_skill("tianmo-gong", 380);
        set_skill("wudu-bian", 380);
		set_skill("poison", 180);

        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
        map_skill("parry", "wudu-bian");
        map_skill("hand", "tianmo-shou");
		map_skill("whip", "wudu-bian");
        prepare_skill("hand", "tianmo-shou");
        
		set("chat_chance_combat", 40);
		set("chat_msg_combat", ({
  		(: perform_action, "whip.shuaichou" :),
  		(: perform_action, "whip.wudu" :),
		
		}));
		set("inquiry", ([
			"五毒教" : "五毒教乃是苗疆重要的门派，以五毒作为立教之根基！",
			"五毒教毒物详解"  : (: ask_book :),
			"五毒解毒丹"  : (: ask_dan :),
			"冯锡范"  : (: ask_xiezifen :),

	]));
	    create_family("日月神教",9,"弟子");
       	setup();
		carry_object(MISC_D("cloth"))->wear();
		carry_object("clone/weapon/whip")->wield(); 
}
void attempt_apprentice(object ob)
{
     if(ob->query("str") < 25 ){
        command("say 练习天魔手需要高的臂力，你臂力不足25，我不收你！");
        return;
        }
	 if(!ob->query("family") || ob->query("family/family_name")!="日月神教" ){
        command("say 你已有名师，来此何干！");
        return;
        }
	 if(ob->query("gender") =="男性" ){
        command("say 女弟子很是麻烦，我看你还是去寻找下蓝凤凰看看，听说她正在招收女弟子？！");
        return;
        }
	 if(ob->query("gender") =="无性" ){
        command("say 你这种不男不女的货色来拜我为师？！");
        return;
        }
     command("haha");
	 command("say 好吧，为了光大日月神教，我就收下你了。");
     command("recruit " + ob->query("id"));
}

string ask_book()
{
	object me=this_player();
	object book;
	book=new("d/hmy/obj/poison-book.c");
	if (me->query("family/family_name") !="日月神教")
	{
		command("say 你不是我大日月神教弟子，来当间隙的么？\n");
		return "人心不古啊！";
	}
	if (me->query("generation")>10)
	{
		command("say 你的辈分太低了，加紧努力！\n");
		return "不错的苗子！\n";
	}
	if (query("book_count")<0)
	{
		command("say 秘籍已经为门中弟子拿走了，你待会再来!\n");
		return "我大日月的毒物必将独步武林！\n";
	}
	book->move(me);
	add("book_count",-1);
	message_vision(HIY"$N递给$n一本秘籍！\n"NOR,this_object(),me);
	return "我日月神教的五毒极为厉害，若学好了纵横天下未尝不可！\n";
}
string ask_dan()
{
	object me=this_player();
	object dan;
	dan=new("d/hmy/obj/wududan.c");
	if (me->query("family/family_name") !="日月神教")
	{
		command("say 你不是我大日月神教弟子，来当间隙的么？\n");
		command("smile "+me->query("id"));
		return "小心我一颗毒药毒死你！";
	}

	if (query("dan_count")<0)
	{
		command("say 我身上的毒丹刚好发完了，你待会再来!\n");
		return "";
	}
	dan->set("owner",me->query("id"));
	dan->move(me);
	add("dan_count",-1);
	message_vision(HIY"$N递给$n一颗五毒丹！\n"NOR,this_object(),me);
	return "我日月神教的五毒丹可以有效的防止五毒蔓延！\n";
}

                                                                                 
string ask_xiezifen()
{
	object me,ob;
	me=this_player();
	
	if (!me->query_temp("quest/kl/klz/hongsha/asklan"))
	{
		command("say 你我无缘无故，来找我何事？？\n");
		return "";
	}
	command("say 好吧，原来是修炼红砂掌之用。\n");
	command("say 既然如此，我就给你一份，但此物剧毒，不要随意涂抹(tumo)！\n");
	me->delete_temp("quest/kl/klz/hongsha/asklan");

 //   me->set_temp("quest/kl/klz/hongsha/kegive",1);
	ob=new("d/miaojiang/obj/xiezifen");
	ob->move(me);
	return "有些不舍！\n";
}

