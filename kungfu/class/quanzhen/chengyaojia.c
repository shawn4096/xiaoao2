//程瑶迦，设定女性师傅
//chengyaojia.c 
//孙不二的弟子
#include <ansi.h>;

inherit NPC;
inherit F_MASTER;
void create()
{
        set_name("程瑶迦", ({"cheng yaojia", "cheng"}));
        set("gender", "女性");
        set("age", 24);
        set("class", "taoist");
        set("long",
                "程瑶迦，长得亭亭玉立，往哪儿一站宛如风摆荷花，出水芙蓉，是清净散人孙不二的弟子。\n一说话脸上立即红彤彤一片！\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("per", 26);
        set("str", 26);
        set("int", 25);
        set("con", 25);
        set("dex", 26);


        set("qi", 15000);
        set("max_qi", 15000);
        set("jing", 5800);
        set("max_jing", 5800);
		set("jingli", 4800);
        set("max_jingli", 4800);
        set("eff_jingli", 4800);

        set("neili", 15000);
        set("max_neili", 15000);
        set("jiali", 60);
        set("level", 8);
        set("combat_exp", 160000);
		set("quest/qz/xtg/daojue/pass",1);
		set("quest/qz/jyg/shangtianti/pass",1);

        set_skill("force", 350);
        set_skill("xiantian-gong", 350);
        set_skill("sword", 350);
        set_skill("quanzhen-jianfa",350);
        set_skill("dodge", 350);
        set_skill("jinyan-gong", 350);
        set_skill("parry", 350);
        set_skill("strike",350);
        set_skill("haotian-zhang", 350);
		set_skill("whip",350);
		set_skill("qiufeng-chenfa",350);
		set_skill("leg",350);
        set_skill("yuanyang-lianhuantui", 350);
        set_skill("tiangang-beidouzhen", 350);

        set_skill("literate",160);
        set_skill("taoism",160);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
        prepare_skill("strike", "haotian-zhang");
        map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("leg", "yuanyang-lianhuantui");

        create_family("全真教", 3, "弟子");
		set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: perform_action, "sword.ding" :),
			(: perform_action, "sword.sanqing" :),
			(: perform_action, "sword.lian" :),
			(: exert_function, "daojue" :),
		//	(: exert_function, "daojue" :),
		}));

        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄门正宗。\n",
        ]) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

void attempt_apprentice(object ob)
{
       if (ob->query("gender")!="女性")
       {
		   command("say 你一个男人家来拜我为师，难道是有什么企图不成？！\n");
		   command("say 我全真一脉，最终全在内丹修为上，关于乾丹的修炼我不擅长！\n");
		   command("say 你还是去寻找下李志常师兄或尹志平师兄，看他是否收你？\n");
		   return ;

       }

	   if ((int)ob->query("shen") < 1000000) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在德行方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(1m)");
               return;
       }
	   if (ob->query("party/gongji") < 1500) {
               command("say 我全真教乃是堂堂名门正派，对弟子要求极严。");
               command("say 在教派功绩方面，" + RANK_D->query_respect(ob) +
                       "是否还做得不够？(需要1500点门派贡献值)\n");
               return;
       }
	   if (!ob->query("quest/qz/dichuan"))
	   {
		       command("say 你非我门中嫡传弟子，来此作甚？");
              return;

	   }
	   if (ob->query_skill("xiantian-gong",1) < 200) {
               command("say 我全真教一身功夫全在先天功，你先天功不足200，来此作甚？。");
               return;
       }
	   if (ob->query_skill("yuanyang-lianhuantui",1) < 200) {
               command("say 我鸳鸯连环腿不足200，来此作甚？。");
               return;
       }		
       command("say 好吧，贫道就收下你了。");
       command("recruit " + ob->query("id"));
       ob->set("class","taoism");
	   return;
}