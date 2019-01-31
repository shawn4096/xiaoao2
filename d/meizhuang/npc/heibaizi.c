// NPC: /d/meizhuang/npc/huangzhonggong.c
// By action@SJ 2009/1/11

#include <ansi.h>
inherit NPC;
string ask_xingluo();
void create()
{
	set_name("黑白子", ({ "heibai zi", "zi" }));
	set("nickname", HIW"梅庄二庄主"NOR);

	set("gender", "男性");
	set("age", 54);
	//set("no_quest", 1);
	set("no_bark", 1);
	set("long",
      "他就是梅庄四位庄主排行第二的黑白子。\n"
      "身穿一件干干净净的黑白相间的长袍。\n"
      "他已年愈五旬，身材高大，双眼神光内敛, 一望便知是一位内家的高手。\n");
	set("qi", 34000);
	set("max_qi", 34000);
	set("jing", 4000);
	set("max_jing", 4000);
	set("jingli", 4000);
	set("max_jingli", 4000);
	set("max_neili", 15000);
	set("neili", 15000);
	set("combat_exp", 9200000);
	set("attitude", "peaceful");
	//set_skill("xuantian-zhi", 180);
	set_skill("art", 180);
	set_skill("medicine", 180);
	set_skill("literate", 180);
	set_skill("force", 450);
	set_skill("parry", 450);
	set_skill("huanmo-wubu", 450);
	set_skill("finger", 450);
	set_skill("tianmo-gong", 450);
	set_skill("throwing", 450);
	set_skill("mantian-huayu", 450);
	set_skill("hand", 450);
	set_skill("tianmo-shou", 450);

	map_skill("force", "tianmo-gong");
	map_skill("dodge", "huanmo-wubu");
	map_skill("hand", "tianmo-shou");
	map_skill("throwing", "mantian-huayu");
	map_skill("parry", "mantian-huayu");
	prepare_skill("hand", "tianmo-shou");

	set_temp("apply/damage", 40);
	set("chat_chance", 1);
	set("chat_msg", ({
		"黑白子喃喃道：“呕血谱”可是天下第一棋谱，如果我能……”\n",
	}));
	set("inquiry", ([
                 "星罗棋布绝技" : (: ask_xingluo :),
		        // "神针绝技" : (: ask_huayu :),
        ]));
	setup();
	carry_object(ARMOR_D("cloth"))->wear();
	carry_object(BINGQI_D("weiqizi"))->wield();
}      

int accept_object(object who, object ob)
{
        object me;
        mapping fam;
        me = this_object();
     
	 if (!(fam = this_player()->query("family")) || fam["family_name"] !="日月神教"){
             command("thank "+ (string)who->query("id"));
             command("say 你与本派素无来往，不知为何送如此厚礼？");
             return 0;
        }
     
       /*
        if (!this_player()->query_temp("meizhuangguangling")){
             command("say 你还是先去找我大哥黄钟公去问问吧！");
             return 0;
        } */ 
        
        //if (fam["generation"] == 3)
        if ((string)ob->query("id") == "ouxue pu"&& this_player()->query_temp("meizhuangguangling")){
            command("haha "+(string)who->query("id"));
            call_out("destroying", 1, ob);
            command("say 你帮我办成了这件事，我很高兴，你去找我的三弟秃笔翁试试吧，或许他能给你一些提示！");
            who->set_temp("meizhuangouxuepu",1);
			
            who->delete_temp("meizhuangguangling");
			command("say 喏，既然你替我找到这个棋谱，我就把这盒棋子送给你了。\n");
			new("clone/weapon/weiqizi")->move(who);
            return 1;
            }
		else if ((string)ob->query("id") == "ouxue pu")
		{
			command("say 这，，，这竟然是传说中的呕血谱？\n");
			command("say 你给我这么一份大礼，我无以为报,就把我这么多年以来的星罗棋布绝技告诉你吧。\n");
            who->set_temp("qipugived",1);
			destruct(ob);
			return 1;
		}
        command("? "+ (string)who->query("id"));
        return 0;
}

void destroying(object obj)
{
        if(! obj) return;
        destruct(obj);
}

string ask_xingluo()
{
     int i,j;
	 object me=this_player();
	
	if (!me->query_temp("qipugived"))
	    return "你是怎么进来的？和我又有什么关系？我为何要告诉你？\n"+"我的呕血谱啊,到底在哪儿呢？\n";
     if (me->query("family/family_name")!="日月神教")
		return "你并非我神教的弟子，打听这个作甚？\n";
	
     if (time()-me->query("quest/hmy/mthy/xingluo/time")<86400)
		return "你来的也太勤快了。\n";

	 if (me->query_skill("mantian-huayu",1)<350
		// ||me->query_skill("hand",1)<350
		// ||me->query_skill("tianmo-shou",1)<350
		 ||me->query_skill("throwing",1)<350)
	    return "你的漫天花雨所需武技不足350，无法领悟我说的这个诀窍，回去继续努力。\n";
		
	 if (me->query("quest/hmy/mthy/xingluo/pass"))
		return "你已经解开这个谜题，还浪费啥时间？\n";
	 command("say 这手【星罗棋布】暗器手法，乃是我多年的心得，倘若使用的好。一切敌人都将伤在这招之下。\n");
	 command("say 若再配合我的围棋子，威力更上一层楼！\n");
	 command("whisper "+me->query("id")+" 是这样子的，你听好了。。。。。\n");
	 j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	  i=random(j);
	 if (i<5&&me->query("kar")>22) {
		
        command("chat* laugh "+me->query("id"));
        command("say 你真聪明，不错，好苗子，我大日月神教又增添一名暗器高手。\n");
		command("chat* congra "+me->query("id"));
	
		log_file("quest/xingluoqibu",sprintf("%s(%s) 受黑白子的指点，成功领悟星罗棋布绝技。富源：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("quest/hmy/mthy/xingluo/fail"),me->query("combat_exp"),me));
	   
	    me->set("quest/hmy/mthy/xingluo/pass",1);	  	   
		return "恭喜你解开漫天花雨之【星罗棋布】秘密！\n";
      }
	  else {
       
		log_file("quest/xingluoqibu",sprintf("%s(%s) 领悟星罗棋布绝技失败。富源：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("quest/hmy/mthy/xingluo/fail"),me->query("combat_exp"),me));
	   
	    me->add("quest/hmy/mthy/xingluo/fail",1);
		me->set("quest/hmy/mthy/xingluo/time",time());
		return "解密漫天花雨之【星罗棋布】绝技失败!\n";

	  }

}

