// Npc: /kungfu/class/shaolin/dao-zheng.c

inherit NPC;

void create()
{
	set_name("������ʦ", ({
		"daozheng chanshi",
		"daozheng",
		"chanshi",
	}));
	set("long",
		"����һλ��ĸߴ������ɮ�ˣ����۴�׳��������Բ�����ֱֳ�\n"
		"�У���һϮ�Ҳ�������ģ��ƺ���һ�����ա�\n"
	);

	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 40);
	set("shen_type", 1);
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set("max_qi", 400);
	set("max_jing", 300);
	set("neili", 450);
	set("max_neili", 450);
	set("jiali", 40);
	set("combat_exp", 80000);
	set("score", 100);

	set_skill("force", 80);
	set_skill("yijin-jing", 80);
	set_skill("dodge", 80);
	set_skill("shaolin-shenfa", 80);
	set_skill("strike", 80);
	set_skill("weituo-zhang", 80);
        set_skill("cuff", 85);
	set_skill("luohan-quan", 85);
	set_skill("parry", 80);
        set_skill("sword", 80);
	set_skill("damo-jian", 80);
	set_skill("buddhism", 80);
	set_skill("literate", 80);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("strike", "weituo-zhang");
        map_skill("cuff", "luohan-quan");
	map_skill("parry", "weituo-zhang");

        prepare_skill("strike", "weituo-zhang");
        prepare_skill("cuff", "luohan-quan");

	create_family("������", 39, "����");

	setup();

        carry_object("/d/shaolin/obj/dao-cloth")->wear();
}

#include "/kungfu/class/shaolin/dao.h"
