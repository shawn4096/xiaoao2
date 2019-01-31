// qu.c 曲洋
// Finish by action@SJ 2009.1.6
// edit by sohu@xojhu add quest
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

int ask_zhen();
string ask_huayu();
string ask_book();
string ask_tmsbook();

void create()
{
	  object wt;
	  set_name("曲洋", ({ "qu yang", "qu", "yang"}));
        set("long", "此人乃日月神教十大长老之一，武功深不可测。\n"+
		    "而他更痴迷于琴曲之道，琴艺可以称得上是当世第一人.\n");
        set("title",HIY"日月神教  "HIW"光明右使"NOR);
        set("gender", "男性");
        set("age", 60);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);

        set("max_qi", 33000);
        set("max_jing", 5200);
        set("eff_jingli", 5200);
        set("jiali", 250);
        set("combat_exp", 9000000);
        set("shen", -1000);
        set("hxshenzhen",1);
		set("hmy/quest/huayu","pass");
		set("book_count",1);
		set("tbook_count",1);
		set("tmsbook_count",1);

        set_skill("strike", 450);
		set_skill("hand", 450);
        set_skill("poison", 100);
        //set_skill("blade", 450);
        set_skill("parry", 450);
        set_skill("dodge", 450);
        set_skill("force", 450);
		set_skill("throwing", 450);
        set_skill("literate", 200);

        set_skill("tianmo-dao",450);
        set_skill("tianmo-zhang",450);
        set_skill("tianmo-shou",450);
		set_skill("mantian-huayu",450);
        set_skill("huanmo-wubu",450);
        set_skill("tianmo-gong",450);
        set_skill("tianmo-jue",200);
        
        map_skill("force", "tianmo-gong");
        map_skill("strike", "tianmo-zhang");
        map_skill("parry", "mantian-huayu");
        map_skill("hand", "tianmo-shou");
        //map_skill("blade", "tianmo-dao");
        map_skill("dodge", "huanmo-wubu");
        map_skill("throwing", "mantian-huayu");
        prepare_skill("hand", "tianmo-shou");
        
		set("inquiry", ([
                 "黑血神针" : (: ask_zhen :),
		         "漫天花雨绝技" : (: ask_huayu :),
				 "暗器手法精要" : (: ask_book :),
				  "天魔手法精要" : (: ask_tmsbook :),

        ]));
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "throwing.huayu" :),
			    //(: perform_action, "blade.jingshen" :),
                (: exert_function, "tianmo" :),
				(: exert_function, "jieti" :),
        }));
	    create_family("日月神教", 6, "长老");
        setup();
         
	    carry_object(MISC_D("cloth"))->wear();  
		carry_object(BINGQI_D("feizhen"))->wield();
		
		//carry_object("/d/hmy/npc/obj/heixuezhen")->wield(); 
}

void attempt_apprentice(object ob)
{
     if(ob->query_skill("tianmo-gong",1) < 350 ||
        ob->query_skill("tianmo-shou",1) < 350)
	 {
        command("say 你的日月神教武功还不够娴熟，再回去练练吧。");
        return;
     }
     if (ob->query_skill("poison",1)<100)
     {
		 command("say 你一点毒计都不懂，居然还有脸跑我这儿来拜师。先把毒计学到120再说。\n");
		 return;
     }
     command("say 好，我正想招兵买马救教主出来，看来你还不错嘛，就收下你了。");
     command("recruit " + ob->query("id"));
     ob->set("title","日月神教光明右使座下堂主");
}

int ask_zhen() 
{
  object me=this_player();
  object hxzhen;
  hxzhen=new("/d/hmy/npc/obj/heixuezhen");
  if (me->query("family/family_name")!="日月神教")
     return notify_fail("你不是我神教弟子，来打听这个干什么？");
  if (objectp(present("heixue shenzhen",me)))
     return notify_fail("你身上不是带有神针么？");
  if (me->query_skill("throwing",1)<350
	  ||me->query_skill("tianmo-shou",1)<350
	  ||me->query_skill("hand",1)<350
	  ||me->query_skill("mantian-huayu",1)<350||me->query_skill("force",1)<350)
     return notify_fail("你手法或暗器功力不够，如何能用的了黑血神针绝技？");
 
  if ((int)query("hxshenzhen")>0)
  { 
	  command("say 黑血神针乃是我日月神教至宝，要小心使用为上,以免遭受江湖同道围攻。\n");
	  command("say 这是一袋神针，你收好了\n");
	  hxzhen->move(me);
	  tell_object(me,HIC"曲洋递给你一袋黑血神针。\n");
      add("hxshenzhen",-1);
	  return 1;
  }
  else {
	  command("say 我手头只有一袋神针，已经被人领走了。你待会再来\n");
	  return 0;

  }

}



string ask_huayu()
{
     object me=this_player();
     if (me->query("family/family_name")!="日月神教")
		return "你并非我神教的弟子，打听这个作甚？\n";
     if (time()-me->query("quest/hmy/mthy/huayu/time")<86400)
		return "你来的也太勤快了。\n";

	 if (me->query_skill("mantian-huayu",1)<350
		 //||me->query_skill("hand",1)<350
		 //||me->query_skill("tianmo-shou",1)<350
		 ||me->query_skill("throwing",1)<350)
	    return "你的漫天花雨所需武技不足350，无法领悟我说的这个诀窍，回去继续努力。\n";
	 if (me->query("quest/hmy/mthy/huayu/pass"))
		return "你已经解开这个谜题，还浪费啥时间？\n";
	 command("say 漫天花雨暗器手法，乃是我多年的心得，倘若使用的好。一切敌人都将伤在这招之下。\n");
	 command("say 若再配合黑血神针，威力更上一层楼！\n");
	 command("whisper "+me->query("id")+" 是这样子的，你听好了。。。。。\n");
	 if (random(8)==5&&me->query("kar")>20) {
		
        command("chat* laugh "+me->query("id"));
        command("say 你真聪明，不错，好苗子，我大日月神教又增添一名新秀高手。\n");
		command("congra "+me->query("id"));
	
		log_file("quest/mthyhuayu",sprintf("%s(%s) 受曲洋长老的指点，成功领悟漫天花雨绝技。富源：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("quest/hmy/mthy/huayu/fail"),me->query("combat_exp"),me));
	   
	    me->set("quest/hmy/mthy/huayu/pass","pass");	  	   
		return "恭喜你解开漫天花雨秘密！\n";
      }
	  else {
       
		log_file("quest/mthyhuayu",sprintf("%s(%s) 领悟漫天花雨绝技失败。富源：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("quest/hmy/mthy/huayu/fail"),me->query("combat_exp"),me));
	   
	    me->add("quest/hmy/mthy/huayu/fail",1);
		me->set("quest/hmy/mthy/huayu/time",time());
		return "解密漫天花雨绝技失败!\n";

	  }

}
string ask_book()
{
	object me=this_player();
	object book;
	book=new("d/hmy/obj/throwing-book.c");
	if (me->query("family/family_name") !="日月神教")
	{
		command("say 你不是我大日月神教弟子，来当间隙的么？\n");
		return "这岁月真是人心不古啊！";
	}
	if (me->query("generation")>10)
	{
		command("say 你的辈分太低了，加紧努力！\n");
		command("pat "+me->query("id"));
		return "真是不错的苗子！\n";
	}
	if (query("book_count")<0)
	{
		command("say 暗器秘籍已经为门中弟子拿走了，你待会再来!\n");
		return "嘿嘿，很多人不知道我大日月暗器的厉害，尤其是黑血神针更是教中之宝！\n";
	}
	book->move(me);
	add("book_count",-1);
	message_vision(HIY"$N递给$n一本秘籍！\n"NOR,this_object(),me);
	return "暗器需要好的手法和身法，你越练越会明白的！\n";
}

string ask_tmsbook()
{
	object me=this_player();
	object book;
	book=new("d/hmy/obj/hand-book.c");
	if (me->query("family/family_name") !="日月神教")
	{
		command("say 你不是我大日月神教弟子，来当间隙的么？\n");
		return "这岁月真是人心不古啊！";
	}
	if (me->query("generation")>10)
	{
		command("say 你的辈分太低了，加紧努力！\n");
		command("pat "+me->query("id"));
		return "真是不错的苗子！\n";
	}
	if (query("tmsbook_count")<1)
	{
		command("say 手法秘籍已经为门中弟子拿走了，你待会再来!\n");
		return "嘿嘿，很多人不知道我大日月漫天花雨暗器的厉害，尤其是天魔手也算是一门绝技了！\n";
	}
	book->move(me);
	add("tmsbook_count",-1);
	message_vision(HIY"$N递给$n一本秘籍！\n"NOR,this_object(),me);
	return "天魔手配合暗器是一门不错的绝技，你越练越会明白的！\n";
}