// NPC: /d/huashan/npc/cong_bq.c
// Date: Look 99/03/25
// Modify by Lklv 2001.10.18

inherit NPC;
#include <ansi.h>
void create()
{
        set_name("从不弃",({"cong buqi", "cong", "buqi" }));
        set("title","华山派第十三代剑宗弟子");
        set("nickname","恶剑客");
        set("long", "一个流里流气的市井小人，一双手格外粗大。\n");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("no_quest",1);

        set("max_qi",12500);
        set("qi", 12500);
        set("max_jing", 4400);
        set("jing",4400);
        set("eff_jingli", 4700);
        set("jingli", 4700);
        set("max_neili", 13500);
        set("neili", 13500);
        set("jiali", 200);
        set("combat_exp", 6400000);
        set("score", 30000);

        set_skill("zhengqi-jue",  200);
        set_skill("sword",  450);
        set_skill("dodge",  380);
        set_skill("force",  380);
        set_skill("parry",  380);
        set_skill("huashan-qigong", 300);
        set_skill("huashan-jianfa",  450);
        set_skill("huashan-shenfa",  380);

        map_skill("dodge", "huashan-shenfa");
        map_skill("force","huashan-qigong");
        map_skill("sword","huashan-jianfa");
        map_skill("parry","huashan-jianfa");

        prepare_skill("strike","hunyuan-zhang");

        set("chat_chance_combat",80);
	    set("chat_msg_combat", ({
		(: perform_action, "sword.lianhuan" :),
		(: perform_action, "sword.kuaijian" :),
		(: perform_action, "sword.fengyi" :),
			(: exert_function, "yujianshi" :),
			(: exert_function, "juli" :),
	}));

        create_family("华山派",13,"弟子");

	setup();
	carry_object(BINGQI_D("sword/sword"))->wield();
	carry_object(ARMOR_D("armor/cloth"))->wear();
}
void attempt_apprentice(object ob)
{
        mapping fam;
        if (mapp(fam=ob->query("family")) && (string)fam["family_name"] != "华山派"  && (int)ob->query("is/huashan")==1 ) {
                message_vision(CYN "$N！你这个华山派的叛徒还回来干什么 ？？？\n"NOR, ob );
                command("slap "+ob->query("id"));
                return;
        }
		if (!ob->query_temp("jianzong/bijian"))
			 return ;
		if ((int)ob->query_skill("huashan-jianfa",1) <= 200) {
                command("say 我华山派剑宗最重视剑法修为，你的等级太低了。");
               // command("say 在德行方面不足10k，" + RANK_D->query_respect(ob)+"是否还做得不够？");
                return;
        }
		if ((int)ob->query("shen") <= 80000) {
                command("say 我华山派乃是堂堂名门正派，对弟子要求极严。");
                command("say 在德行方面不足80k，" + RANK_D->query_respect(ob)+"是否还做得不够？");
                return;
        }
       if(ob->query("quest/huashan")=="气宗"&&!ob->query_temp("jianzong/bijian")){
              
                command("heng");
                command("say 你不是华山气宗高徒么？怎么？来我们剑宗找死？");
				return;
		}
		//只有经过解密过程才能剑盟剑宗，否则白搭，不收。。规避bug
        if (ob->query("quest/huashan")!="剑宗") {
               command("say 你是谁，我不认识你，抓紧修炼吧。");
                return;
        }
      
        command("say 好吧，我就收下你了,你可要为我们华山派剑宗争口气。");
        command("recruit " + ob->query("id"));
        ob->set("title",HIW"华山派剑宗亲传弟子"NOR);
        ob->set("quest/huashan","剑宗");
		return;

}


/*
void init()
{
        object me, ob;
        ::init();

        ob = this_player();
        me = this_object();

	if (interactive(ob) && !environment(ob)->query("no_fight")) {
		command("say 敢进入我剑宗禁地,只有死！！！\n");
		me->set_leader(ob);
		remove_call_out("kill_ob");
		call_out("kill_ob", 1, ob);
	}
}
*/