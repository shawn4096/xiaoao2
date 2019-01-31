// ma.c ������

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

#include "begger.h";

void create()
{
        set_name("������", ({"ma duozhu", "ma", "duozhu"}));
        set("title", YEL"ؤ����·ֶ����"NOR);
        set("gb/bags",8);
        set("gender", "����");
        set("age", 40);
        set("long","���ǰ˴��������ƹܴ��·ֶ档\n");
        set("attitude", "peaceful");
        set("unique", 1);

        set("str", 25);
        set("int", 18);
        set("con", 20);
        set("dex", 20);

        set("qi", 5200);
        set("max_qi", 5200);
        set("jing", 3800);
        set("max_jing", 3800);
        set("eff_jingli", 4440);
        set("neili", 14000);
        set("max_neili", 14000);
        set("jiali", 150);

        set("combat_exp", 4320000);

        set_skill("force", 350); // �����ڹ�
        set_skill("huntian-qigong", 350); // ��������
        set_skill("dodge", 350); // ��������
        set_skill("xiaoyaoyou", 350); // ǧ������
        set_skill("parry", 350); // �����м�
        set_skill("staff", 350);
        set_skill("fengmo-zhang",350);
        set_skill("lianhua-zhang",350);
        set_skill("strike",350);
        set_skill("begging", 150);

        map_skill("force", "huntian-qigong");
        map_skill("parry","fengmo-zhang");
        map_skill("staff","fengmo-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("strike", "lianhua-zhang");
        prepare_skill("strike", "lianhua-zhang");

        create_family("ؤ��", 19, "�˴�����");

        set("inquiry", ([
                "ؤ��" : "����ؤ�������µ�һ��\n",
                "����" : "���������Ƿ壬���ǵ�ǰ�ΰ�����\n",
                "ѧ�Ʒ�" : "�Ƕ��Ǻܶ���ǰ�����ˣ�����ʱ����������һ��С��\n"
                           "����ͷ������\n",
        ]));
        setup();

        carry_object(__DIR__"obj/gb_budai8")->wear();
        carry_object(ARMOR_D("bainayi"))->wear();
        carry_object(ARMOR_D("caoxie"))->wear();
        carry_object(BINGQI_D("gangzhang"))->wield();
}

void attempt_apprentice(object ob)
{

	if ((int)ob->query_str() <=20	) {
		command("say ���������㣬����ѧ�����ҵĹ���\n");
		return;
	}

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
        ob->set("title",sprintf("ؤ����·ֶ�%s������",
                chinese_number(ob->query("gb/bags"))) );
        ob->set("gb/fenduo","���·ֶ�");
        ob->set("class","beggar");
}