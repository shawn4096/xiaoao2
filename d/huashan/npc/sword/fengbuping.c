// NPC: /d/huashan/npc/feng_bp.c
// Date: Look 99/03/25
// Modify by Lklv 2001.10.18

inherit NPC;
#include <ansi.h>

void create()
{
	set_name("封不平",({"feng buping", "feng", "buping" }));
	set("title",HIW"华山派第十三代剑宗掌门"NOR);
	set("nickname",HIR"狂风快剑"NOR);
	set("long", "这就是在江湖中默默无闻，但身手着实不凡的华山剑宗传人。\n");
	set("age", 40);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("no_quest",1);

        set("max_qi",18000);
        set("qi", 18000);
        set("max_jing", 5400);
        set("jing",5400);
        set("eff_jingli", 5700);
        set("jingli", 5700);
        set("max_neili", 23500);
        set("neili", 23500);
        set("jiali", 200);
        set("combat_exp", 9500000);
        set("score", 30000);

        set_skill("zhengqi-jue",  200);
        set_skill("sword",  450);
        set_skill("dodge",  400);
        set_skill("force",  380);
        set_skill("parry",  400);
        set_skill("literate",200);
        set_skill("huashan-qigong", 380);
        set_skill("huashan-jianfa",  450);
        set_skill("huashan-shenfa",  400);
        set_skill("cuff",  350);

		set_skill("poyu-quan",  350);

		map_skill("dodge", "huashan-shenfa");
        map_skill("force","huashan-qigong");
        map_skill("sword","huashan-jianfa");
        map_skill("parry","huashan-jianfa");

        prepare_skill("strike","hunyuan-zhang");

        set("chat_chance_combat",60);
        set("chat_msg_combat", ({
		(: perform_action, "strike.yujianshi" :),
		(: perform_action, "sword.kuaijian" :),
		(: perform_action, "sword.lianhuan" :),
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
		
	
		if ((int)ob->query_skill("huashan-jianfa",1) <= 350) {
                command("say 我华山派剑宗最重视剑法修为，你的等级太低了。");
               // command("say 在德行方面不足10k，" + RANK_D->query_respect(ob)+"是否还做得不够？");
                return;
        }
		if ((int)ob->query("shen") <= 1000000) {
                command("say 我华山派乃是堂堂名门正派，对弟子要求极严。");
                command("say 在德行方面不足1M，" + RANK_D->query_respect(ob)+"是否还做得不够？");
                return;
        }
       if(ob->query("quest/huashan")=="气宗"&&!ob->query_temp("jianzong/bijian")){
              
                command("heng");
                command("say 你不是华山气宗高徒么？怎么？来我们剑宗找死？");
				return;
		}
		//只有经过解密过程才能剑盟剑宗，否则白搭，不收。。规避bug
        if (ob->query("quest/huashan")!="剑宗" && !ob->query_temp("jianzong/bijian")) {
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

        if (interactive(ob) && !environment(ob)->query("no_fight")){
		command("say 敢进入我剑宗禁地,只有死！！！\n");
		me->set_leader(ob);
		remove_call_out("kill_ob");
		call_out("kill_ob", 1, ob);
	}
}
*/
