// lisheng.c ����
// Looklove 2000/10/21

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
#include "begger.h";

void create()
{
	set_name("����", ({"li sheng", "li", "sheng"}));
	set("title", "ؤ��˴�����");
	set("gb/bags",8);
	set("nickname", HIC"��������"NOR);
	set("gender", "����");
	set("age", 58);
	set("long", "����λ���Ը�ֱ����������ؤ��˴����ӡ�\n");
	set("attitude", "peaceful");

	set("str", 32);
	set("int", 18);
	set("con", 20);
	set("dex", 23);

	set("qi", 13390);
	set("max_qi", 13390);
	set("jing", 5300);
	set("max_jing", 5300);
	set("eff_jingli", 5800);
	set("neili", 14800);
	set("max_neili", 14800);
	set("jiali", 200);

	set("combat_exp", 4200000);

	set_skill("force", 350);
	set_skill("huntian-qigong", 350);
	set_skill("strike", 350);
	set_skill("xianglong-zhang", 350);
	set_skill("lianhua-zhang", 350);
	set_skill("dodge", 350);
	set_skill("xiaoyaoyou", 350);
	set_skill("parry", 350);
	set_skill("stick", 350);
	set_skill("begging", 120);

	map_skill("force", "huntian-qigong");
	map_skill("strike", "lianhua-zhang");
	map_skill("parry", "xianglong-zhang");
	map_skill("dodge", "xiaoyaoyou");
	prepare_skill("strike", "xianglong-zhang");

    	set("chat_chance_combat", 40);
    	set("chat_msg_combat", ({
        	(: perform_action, "strike.bingdi" :),
        	(: exert_function, "huntian" :),
        }));

	create_family("ؤ��", 19, "����");

	setup();

        carry_object(ARMOR_D("bainayi"))->wear();
        carry_object(ARMOR_D("caoxie"))->wear();
	carry_object(__DIR__"obj/gb_budai8")->wear();
}

void attempt_apprentice(object ob)
{
	if( ob->query("shen") < 0 ) return;
        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "ؤ��") {
                command("say �㻹��ȥ������ɿ����ɡ�");
                return;
	}
        if ((int)ob->query("gb/bags") >= 2
        && ob->query("family/family_name") != "ؤ��" ) {
                command("say ؤ����ݲ��������ַ����޳���С�ˣ����ҹ���");
                command("kill "+ob->query("id"));
                return;
        }

        if((int)ob->query_skill("xiaoyaoyou",1) < 80 ){
		command("say ��ң����ؤ���洫�Ĺ�����Դ����в�������\n");
		return;
	}
	    command("say �ã���������һ��һ���˲�����ͽ�ܣ��һ�ϲ���������أ�");
        command("recruit " + ob->query("id"));

        if (!ob->query("gb/bags")) ob->set("gb/bags", 1);
        ob->set("title",sprintf("ؤ���ܶ�%s������",
                chinese_number(ob->query("gb/bags"))) );
        ob->set("gb/fenduo","�ܶ�");
        ob->set("class","beggar");
}