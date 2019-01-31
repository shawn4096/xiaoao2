// jiang.c ������
// update by looklove 2000,7,3
// Modify By Looklove 2000/10/21
// Modified by looklove 2001/5/24 for xlz quest

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

#include "begger.h";

void create()
{
        set_name("������", ({"jiang duozhu", "jiang" }));
        set("title", YEL"ؤ�����ֶ����"NOR);
        set("gb/bags",8);
        set("gender", "����");
        set("age", 47);
        set("long", "���ǰ˴��������ƹܴ���ֶ档\n");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 20);
        set("con", 25);
        set("dex", 25);
        set("unique", 1);

        set("qi", 5200);
        set("max_qi", 5200);
        set("jing", 4800);
        set("max_jing", 4800);
        set("eff_jingli", 4940);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 100);

        set("combat_exp", 3200000);

        set_skill("force", 200); // �����ڹ�
        set_skill("huntian-qigong", 200); // ��������
        set_skill("strike", 200); // ����ȭ��
        set_skill("blade",200);
        set_skill("liuhe-daofa",200);
        set_skill("dodge", 200); // ��������
        set_skill("xiaoyaoyou", 200); // ǧ������
        set_skill("parry", 200); // �����м�
        set_skill("lianhua-zhang",90);
        map_skill("parry","liuhe-daofa");
        map_skill("strike","lianhua-zhang");
        map_skill("blade","liuhe-daofa");
        map_skill("force", "huntian-qigong");
        map_skill("dodge", "xiaoyaoyou");

        create_family("ؤ��", 19, "�˴�����");
        set("chat_chance", 1);
        set("chat_msg", ({
                "������̾��:�滳����ǰ���ǰ���һ�����Ƶ����Ӱ���\n",
        }) );
        set("inquiry", ([
                "ؤ��" : "����ؤ�������µ�һ��\n",
                "�ǰ���" : "��������������Զ���ҵ��ǰ�����\n",
                "�Ⱦ�" : "��Ҳϲ���Ⱦƣ���̫���ˣ�\n",
                "С��" : "�ڶ����⣬���۶��Ϸ��򣬿����ι�ȥ��\n",
                "����" : "��������������Զ���ҵ��ǰ�����\n",
        ]));
        setup();
        carry_object(__DIR__"obj/gb_budai8")->wear();
        carry_object(ARMOR_D("bainayi"))->wear();
        carry_object(ARMOR_D("caoxie"))->wear();
        carry_object(BINGQI_D("blade"))->wield();
}

void attempt_apprentice(object ob)
{
        if( ob->query("shen") < 1000 ) return;
        if ((int)ob->query("gb/bags") >= 2
        && ob->query("family/family_name") != "ؤ��" ) {
                command("say ؤ����ݲ��������ֱ��������С�ˣ�");
                command("kill "+ob->query("id"));
                return;
        }

        command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
        "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
        command("recruit " + ob->query("id"));
        if (!ob->query("gb/bags")) ob->set("gb/bags", 1);
        ob->set("title",sprintf("ؤ�����ֶ�%s������",
                chinese_number(ob->query("gb/bags"))) );
        ob->set("gb/fenduo","����ֶ�");
        ob->set("class","beggar");
}