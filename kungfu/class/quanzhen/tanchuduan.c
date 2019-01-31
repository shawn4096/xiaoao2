// tan.c 谭处端

#include <ansi.h>
//#include "/kungfu/class/quanzhen/qz_perform.h"

inherit NPC;
inherit F_MASTER;

string ask_sanhua();

void create()
{
        set_name("谭处端", ({"tan chuduan", "tan"}));
        set("gender", "男性");
        set("age", 40);
        set("class", "taoist");
        set("nickname",HIY"长真子"NOR);
        set("long",
                "他就是全真次徒谭处端谭真人，他身材魁梧，浓眉大眼，嗓音\n"
                "洪亮，拜重阳真人为师前本是铁匠出身，掌法精研，有独特专长。\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 34);
        set("int", 28);
        set("con", 28);
        set("dex", 28);

        set("title","全真七子之二");

        set("qi", 24000);
        set("max_qi", 24000);
        set("jing", 6000);
        set("max_jing", 6000);
        set("neili", 20200);
        set("max_neili", 20200);
        set("jiali", 200);

        set("level", 20);
        
		set("combat_exp", 10500000);

        set_skill("force", 470);
        set_skill("xiantian-gong", 470);
        set_skill("sword", 470);
        set_skill("quanzhen-jianfa",470);
        set_skill("dodge", 470);
        set_skill("jinyan-gong", 470);
        set_skill("parry", 470);
        set_skill("strike", 470);
        set_skill("haotian-zhang", 470);
        set_skill("literate",180);
        set_skill("taoism",200);
	    set_skill("leg",470);
		set_skill("yuanyang-lianhuantui",470);
	    set_skill("tiangang-beidouzhen", 470);
	
        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
        prepare_skill("strike","haotian-zhang");
        map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("leg", "yuanyang-lianhuantui");

        create_family("全真教", 2, "弟子");
	    set("inquiry", ([               
                //"三花聚顶掌绝技" : (: ask_sanhua :),
			   
           ]));		       

        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                 (: perform_action, "sword.sanqing" :),
                (: perform_action, "sword.qixing" :),
                (: perform_action, "sword.ding" :),
				(: perform_action, "sword.jianqi" :),
                (: perform_action, "sword.lian" :),
				(: exert_function, "daojue" :),
				(: exert_function, "wuqi" :),
				(: exert_function, "yusuo" :),
               
        }));
        set("book_count",1);

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}


void attempt_apprentice(object ob)
{
       if (ob->query("gender")!="男性")
       {
		   command("say 你一个女人家来拜我为师，难道是有什么企图不成？！\n");
		   command("say 我全真一脉，最终全在内丹修为上，关于坤丹的修炼我不擅长！\n");
		   command("say 你还是去寻找下师叔清静散人孙不二，看他是否收你？\n");
		   return ;

       }

	   if ((int)ob->query("shen") < 1500000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在德行方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(1.5m)");
               return;
       }
	   if (ob->query("party/gongji") < 3000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在教派功绩方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(需要3000点门派贡献值)\n");
               return;
       }
	   if (!ob->query("quest/qz/dichuan"))
	   {
		       command("say 你非我门中嫡传弟子，来此作甚？");
              return;

	   }
	   if (ob->query_skill("xiantian-gong",1) < 300) {
               command("say 我全真教一身功夫全在先天功，你先天功不足300，来此作甚？。");
               return;
       }
	 
       command("say 好吧，贫道就收下你了。");
       command("recruit " + ob->query("id"));
       ob->set("title", "全真七子亲传弟子");
       ob->set("class","taoism");
	   return;
}