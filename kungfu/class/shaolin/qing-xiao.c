// Npc: /kungfu/class/shaolin/qing-xiao.c
// Date: YZC 96/01/19

inherit NPC;


void create()
{
	set_name("��������", ({
		"qingxiao biqiu",
		"qingxiao",
		"biqiu",
	}));
	set("long",
		"����һλ���ǿ����׳��ɮ�ˣ�����û���������ȫ���ƺ��̺�\n"
		"�������������һϮ�ײ��ڱ����ģ��ƺ������ա�\n"
	);


	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 30);
	set("shen_type", 1);
	set("str", 23);
	set("int", 21);
	set("con", 18);
	set("dex", 22);
	set("max_qi", 350);
	set("max_jing", 200);
	set("neili", 350);
	set("max_neili", 350);
	set("jiali", 30);
	set("combat_exp", 50000);
	set("score", 100);

	set_skill("force", 60);
	set_skill("yijin-jing", 60);
	set_skill("dodge", 60);
	set_skill("shaolin-shenfa", 60);
	set_skill("leg", 65);
	set_skill("shaolin-tantui", 65);
	set_skill("parry", 60);
	set_skill("buddhism", 60);
	set_skill("literate", 60);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("leg", "shaolin-tantui");
	map_skill("parry", "shaolin-tantui");

	prepare_skill("leg", "shaolin-tantui");

	create_family("������", 40, "����");

	setup();

        carry_object("/d/shaolin/obj/qing-cloth")->wear();
}


#include "/kungfu/class/shaolin/qing.h"

