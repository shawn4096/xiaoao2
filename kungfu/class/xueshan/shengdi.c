// shengdi.c ʤ��
// by iceland

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("ʥ��", ({ "sheng xiang", "shengxiang" ,"sheng","xiang"}));
        set("long",@LONG
����Ѫ���������µĵ��ӣ��ڼ����������书��Ϊ���
��������ߣ���ò���£����ϴ���һ����������������΢Ц��
LONG
        );
        set("title", HIR "Ѫ���������µ���" NOR);
        set("gender", "����");
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

        create_family("Ѫ����",2, "����");
        set("class", "huanxi");

        setup();
        carry_object("/d/xueshan/npc/obj/gongde-jiasha")->wear();
        carry_object(BINGQI_D("xinyuedao"))->wield();        

        add_money("gold",1);
}
/*
void attempt_apprentice(object ob)
{
        if ((string)ob->query("family/family_name") != "������") {
                command("say"+ RANK_D->query_respect(ob) +
                        "���Ǳ��µ��ӣ������ﵷʲô�ң���");
                return;
        }

        if ((int)ob->query_skill("huanxi-chan", 1) < 100) {
                command("say ��ϲ���Ǹ����书֮���������ڼ������ɡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ��������������б��ŵ��ķ��ɡ�");
                return;
        }
	if( ob->query_skill("longxiang-boruo", 1) < 100) {
                command("say �Ҵ����¸����书�����ڹ��ศ��ɡ�");
                command("say"+ RANK_D->query_respect(ob) +
                        "�ٰ�����ͨ��������������б��ŵ��ڹ��ɡ�");
                return;

        }
        command("say �ðɣ��Ժ���ͺú��̷��ү�Ұɡ�");
        command("recruit " + ob->query("id"));

        ob->set("title", HIR "������Ѫ���ŵ���������" NOR);
}
*/