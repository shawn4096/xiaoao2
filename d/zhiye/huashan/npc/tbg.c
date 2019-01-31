// NPC: /d/huashan/npc/tbq.c
// Date: Look 99/03/25

inherit NPC;

void create()
{
	set_name("�ﲮ��", ({
		"tian boguang",
		"tian",
		"boguang",
	}));
	set("long",
		"�����ǰܻ��������Ҹ�Ů���ڵĴ�������\n"
		"���Ṧ���ѣ�һ�ֿ��쵶�������𽭺���\n"
	);

	set("nickname", "�������");
	set("gender", "����");
	set("attitude", "friendly");

	set("age", 30);
	set("shen_type", -1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);

	set("qi", 3500);
	set("max_qi", 3500);
	set("jing", 1500);
	set("max_jing", 1500);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 150);
	set("combat_exp", 1000000);
	set("score", 10000);
	set("chat_chance_combat",60);
	set("chat_msg_combat", ({
		(: perform_action, "blade.huashen" :),
		(: perform_action, "blade.jingshen" :),
		(: perform_action, "blade.kuaidao" :),
		(: exert_function, "tianmo" :),
		(: exert_function, "jieti" :),
	}));
	setup();
	carry_object(BINGQI_D("blade"))->wield();
	carry_object(ARMOR_D("cloth"))->wear();
}