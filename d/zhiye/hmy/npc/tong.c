// Finish by Numa@SJ 2000.8
// edit by sohu,add quest

#include <ansi.h>
inherit F_MASTER;
inherit NPC;
string ask_tmd();
void create()
{
        set_name("童百熊", ({ "tong baixiong", "tong", "baixiong"}));
        set("long", "一名须法俱白的老者，身材魁梧，双目炯炯有神，\n"+
        	"他掌管着日月教风雷堂，负责着教中所有对外的事务。\n");
        set("title",HIY"日月神教 "HIC"风雷堂主"NOR);
        set("gender", "男性");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 28);
        set("int", 28);
        set("con", 28);
        set("dex", 38);

        set("max_qi", 13500);
        set("max_jing", 2200);
        set("eff_jingli", 2200);
        set("jiali", 200);
        set("combat_exp", 4800000);
        set("shen", -1);

        set_skill("parry", 450);
        set_skill("dodge", 450);
        set_skill("force", 450);
        set_skill("blade", 450);
		set_skill("tianmo-jue", 200);
        set_skill("huanmo-wubu", 450);
        set_skill("tianmo-dao", 450);
        set_skill("tianmo-gong", 450);
        set_skill("strike", 450);
        set_skill("tianmo-zhang", 450);
        map_skill("dodge", "huanmo-wubu");
        map_skill("force", "tianmo-gong");
        map_skill("blade", "tianmo-dao");
        map_skill("parry", "tianmo-dao");
        map_skill("strike", "tianmo-zhang");
        prepare_skill("strike", "tianmo-zhang");
        create_family("日月神教",8,"弟子");

        
        set("inquiry", ([
                 "天魔绝刀" : (: ask_tmd :),
		        // "玄铁剑法" : (: ask_sword :),
        ]));
        
        setup();
		carry_object(BINGQI_D("blade"))->wield();
 
        carry_object(MISC_D("cloth"))->wear();
}

void attempt_apprentice(object ob)
{
     if(ob->query("shen") >-50000){
        command("say 你不够心狠手辣，且心地不纯，我不收你！");
        return;
        }
	 if(ob->query_skill("tianmo-gong",1)<250){
        command("say 你的天魔功功力不够，你要继续努力！");
        return;
	 }
     if(ob->query_skill("tianmo-jue",1)<180){
        command("say 你的天魔诀不够，你要继续努力！");
        return;
	 }
	 
     command("haha");
	 command("say 好吧，为了光大日月神教，我就收下你了。");
     command("recruit " + ob->query("id"));
}

string ask_tmd()
{
     object me=this_player();
     if (me->query("family/family_name")!="日月神教")
		return "你并非我神教的弟子，打听这个作甚？\n";
     if (time()-me->query("quest/hmy/tmd/time")<86400)
		return "你来的也太勤快了。\n";
	 if (me->query_skill("tianmo-dao",1)<250)
	    return "你的天魔刀武技不足250，无法领悟我说的这个诀窍，回去继续努力。\n";
	 if (me->query("quest/hmy/tmd/pass"))
		return "你已经解开这个谜题，还浪费啥时间？\n";
	 command("say 天魔刀法有两个使用的小技巧，乃是我多年的心得，倘若使用的好\n");
	 command("say 天魔刀的威力将大增，千万不可小觑了这门刀法。来来来，你听好了！\n");
	 command("whisper "+me->query("id")+" 是这样子的，你听好了“乱刀困敌”和“快刀破敌”\n");

	 if (random(me->query("kar"))>27) {
		command("chat* laugh "+me->query("id"));
        command("say 你真聪明，不错，好苗子，我大日月神教又增添一名新秀高手。\n");
		command("congra "+me->query("id"));
		//command("say 你解开");
		//message_vision(HIC"$N终于解开天魔绝刀秘密。！\n"NOR,me);
		log_file("quest/tianmd",sprintf("%s(%s) 受童百熊的指点，成功领悟天魔绝刀秘籍。富源：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("tmd/fail"),me->query("combat_exp"),me));
	   
	    me->set("quest/hmy/tmd/pass",1);	  	   
		return "恭喜你解开天魔绝刀秘密！\n";
      }else {
        //message_vision(HIC"$N解密天魔绝刀秘密失败！\n"NOR,me);
		log_file("quest/tianmd",sprintf("%s(%s) 领悟天魔绝刀秘籍失败。富源：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("tmd/fail"),me->query("combat_exp"),me));
	   
	    me->add("quest/hmy/tmd/fail",1);
		me->set("quest/hmy/tmd/time",time());
		return "解密天魔刀绝技失败!\n";

	  }

}


