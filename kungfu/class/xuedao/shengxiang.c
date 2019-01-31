// shengdi.c ʤ��
// by iceland

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("ʤ��", ({ "sheng xiang", "shengxiang" ,"sheng","xiang"}));
        set("long",@LONG
����Ѫ���������µ��״�����֮һ���ڼ����������书���������ƣ��ó���ɰ�ơ�
��������ߣ���Щ΢�֣��Եü�Ϊ���ࡣ
LONG
        );
        set("title", HIR "Ѫ���������µ���" NOR);
        set("gender", "����");
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

        create_family("Ѫ����", 5, "����");
        setup();
        carry_object("/d/xueshan/npc/obj/gongde-jiasha")->wear();
        carry_object(BINGQI_D("miandao"))->wield();        

        add_money("gold",1);
}

void attempt_apprentice(object ob)
{
        if ((string)ob->query("family/family_name") != "Ѫ����") {
               command("say"+ RANK_D->query_respect(ob) +
                        "���Ǳ��ŵ��ӣ������ﵷʲô�ң���");
                return;
        }

        if ((int)ob->query_skill("huanxi-chan", 1) < 150) {
                command("say ��ϲ���Ǹ����书֮��������150�������ڼ������ɡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ��������������б��ŵ��ķ��ɡ�");
                return;
        }
        if ((int)ob->query_skill("jingang-liantishu", 1) < 200) {
                command("say ����������Ǹ����书֮��������200�������ڼ������ɡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ���������ϰ�ɡ�");
                return;
        }

        if ((int)ob->query_skill("xuedao-jing", 1) < 200) {
                command("say Ѫ�����Ǹ����书֮��������200�������ڼ������ɡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ���������ϰ�ɡ�");
                return;
        }
            if (!ob->query("quest/xd/dichuan")) {
                command("say ��û�еմ���ݣ��Ҳ������㡣");
                return;
        }

        command("say �ðɣ��Ժ���ͺú��̷��ү�Ұɡ�");
        command("recruit " + ob->query("id"));

       // ob->set("title", HIR "Ѫ���ŵ���������" NOR);
}
