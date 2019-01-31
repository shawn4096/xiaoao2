// shengdi.c 胜谛
// by iceland

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("圣象", ({ "sheng xiang", "shengxiang" ,"sheng","xiang"}));
        set("long",@LONG
他是血刀老祖座下的弟子，在几个弟子中武功颇为精深。
他身材甚高，形貌枯槁，脸上带有一股难以言述的神秘微笑。
LONG
        );
        set("title", HIR "血刀老祖座下弟子" NOR);
        set("gender", "男性");
        set("age", 45);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 3200);
        set("eff_jing", 1500);
		set("max_jing",1500);
		set("eff_jingli", 2000);
        set("neili", 3500);
        set("max_neili", 3500);
        set("jiali", 50);
        set("combat_exp", 1700000);
        set("score", 5000);
		set("unique", 1);

        set_skill("huanxi-chan", 200);
        set_skill("literate", 100);
        set_skill("force", 200);
        set_skill("xuedao-dafa", 200);
        set_skill("dodge", 200);
        set_skill("yuxue-dunxing", 200);
        set_skill("tianwang-zhua", 200);
        set_skill("parry", 200);
        set_skill("xuedao-jing", 200);
        set_skill("blade", 200);
        set_skill("claw", 200 );

        map_skill("force", "xuedao-dafa");
        map_skill("dodge", "yuxue-dunxing");
        map_skill("claw", "tianwang-zhua");
        map_skill("parry", "xuedao-jing");
        map_skill("blade", "xuedao-jing");

        prepare_skill("claw","tianwang-zhua");

        create_family("血刀门",2, "弟子");
        set("class", "huanxi");

        setup();
        carry_object("/d/xueshan/npc/obj/gongde-jiasha")->wear();
        carry_object(BINGQI_D("xinyuedao"))->wield();        

        add_money("gold",1);
}
/*
void attempt_apprentice(object ob)
{
        if ((string)ob->query("family/family_name") != "大轮寺") {
                command("say"+ RANK_D->query_respect(ob) +
                        "不是本寺弟子，在这里捣什么乱？！");
                return;
        }

        if ((int)ob->query_skill("huanxi-chan", 1) < 100) {
                command("say 欢喜禅是各项武功之本，你再勤加修炼吧。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多钻研钻研本门的心法吧。");
                return;
        }
	if( ob->query_skill("longxiang-boruo", 1) < 100) {
                command("say 我大轮寺各种武功均和内功相辅相成。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多钻研钻研本门的内功吧。");
                return;

        }
        command("say 好吧，以后你就好好侍奉佛爷我吧。");
        command("recruit " + ob->query("id"));

        ob->set("title", HIR "大轮寺血刀门第六代弟子" NOR);
}
*/