#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("刘处玄", ({"liu chuxuan", "liu"}));
        set("gender", "男性");
        set("age", 38);
        set("class", "taoist");
        set("nickname",WHT"长生子"NOR);
        set("long",
                "他就是全真三徒刘处玄刘真人，他身材瘦小，但顾盼间自有一\n"
                "种威严气概。\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 30);
        set("int", 30);
        set("con", 28);
        set("dex", 30);

        set("title","全真七子之三");

        set("qi", 34500);
        set("max_qi", 34500);
		set("eff_qi",34500);
        set("jing", 5200);
        set("max_jing", 5200);
        set("neili", 24700);
        set("max_neili", 24700);
        set("jiali", 200);
        set("level", 18);
        set("combat_exp", 9400000);

        set_skill("force", 450);
        set_skill("xiantian-gong", 450);
        set_skill("sword", 450);
        set_skill("quanzhen-jianfa",450);
        set_skill("dodge", 450);
        set_skill("jinyan-gong", 450);
        set_skill("parry", 450);
        set_skill("literate",250);
        set_skill("strike", 450);
        set_skill("haotian-zhang", 450);
        set_skill("taoism",200);
	    set_skill("medicine", 200);
        set_skill("tiangang-beidouzhen", 450);
		set_skill("leg", 200);
        set_skill("yuanyang-lianhuantui", 450);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
		map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("strike","haotian-zhang");
		prepare_skill("leg", "yuanyang-lianhuantui");


        create_family("全真教", 2, "弟子");

        set("inquiry", ([

        ]) );

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