// shengdi.c 胜谛
// by iceland

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("胜象", ({ "sheng xiang", "shengxiang" ,"sheng","xiang"}));
        set("long",@LONG
他是血刀老祖座下的亲传弟子之一，在几个弟子中武功以力大著称，擅长红砂掌。
他身材甚高，有些微胖，显得极为魁梧。
LONG
        );
        set("title", HIR "血刀老祖座下弟子" NOR);
        set("gender", "男性");
	set("class", "huanxi");
        set("age", 45);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 21000);
        set("eff_jing", 6400);
        set("max_jing",6400);
		set("neili", 21300);
        set("max_neili", 21300);
        set("jiali", 180);
        set("combat_exp", 9400000);
        set("score", 40000);
		set("unique", 1);

        set_skill("huanxi-chan", 180);
        set_skill("literate", 180);
        set_skill("force", 450);
        set_skill("xuedao-jing", 450);
        set_skill("dodge", 450);
        set_skill("xueying-dunxing", 100);
        set_skill("strike", 100);
        set_skill("hongsha-zhang", 450);
        set_skill("parry", 450 );
        set_skill("xuedao-daofa", 450);
        set_skill("blade", 450 );

        map_skill("force", "xuedao-jing");
        map_skill("dodge", "xueying-dunxing");
        map_skill("parry", "xuedao-daofa");
        map_skill("strike", "hongsha-zhang");

        prepare_skill("strike","hongsha-zhang");
		set("chat_chance_combat", 65);
		set("chat_msg_combat", ({
			(: perform_action, "blade.chuanxin" :),
			(: perform_action, "blade.liuxing" :),
			(: perform_action, "blade.bafang" :),
			(: perform_action, "blade.chilian" :),
			(: exert_function, "yuxue" :),			
			(: perform_action, "dodge.xueying" :),
		}));

        create_family("血刀门", 5, "弟子");
        setup();
        carry_object("/d/xueshan/npc/obj/gongde-jiasha")->wear();
        carry_object(BINGQI_D("miandao"))->wield();        

        add_money("gold",1);
}

void attempt_apprentice(object ob)
{
        if ((string)ob->query("family/family_name") != "血刀门") {
               command("say"+ RANK_D->query_respect(ob) +
                        "不是本门弟子，在这里捣什么乱？！");
                return;
        }

        if ((int)ob->query_skill("huanxi-chan", 1) < 150) {
                command("say 欢喜禅是各项武功之本，不足150，你再勤加修炼吧。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多钻研钻研本门的心法吧。");
                return;
        }
        if ((int)ob->query_skill("jingang-liantishu", 1) < 200) {
                command("say 金刚炼体术是各项武功之本，不足200，你再勤加修炼吧。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多练习吧。");
                return;
        }

        if ((int)ob->query_skill("xuedao-jing", 1) < 200) {
                command("say 血刀经是各项武功之本，不足200，你再勤加修炼吧。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多练习吧。");
                return;
        }
            if (!ob->query("quest/xd/dichuan")) {
                command("say 你没有嫡传身份，我不敢收你。");
                return;
        }

        command("say 好吧，以后你就好好侍奉佛爷我吧。");
        command("recruit " + ob->query("id"));

       // ob->set("title", HIR "血刀门第六代弟子" NOR);
}
