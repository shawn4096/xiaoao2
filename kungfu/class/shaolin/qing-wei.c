// Npc: /kungfu/class/shaolin/qing-wei.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;


void create()
{
	set_name("��Ϊ����", ({
		"qingwei biqiu",
		"qingwei",
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
	set("int", 19);
	set("con", 22);
	set("dex", 20);
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
	set_skill("mohe-zhi", 60);
	set_skill("strike", 60);
	set_skill("finger", 60);
	set_skill("parry", 60);
	set_skill("buddhism", 60);
	set_skill("literate", 60);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("finger", "mohe-zhi");
	map_skill("parry", "mohe-zhi");

	prepare_skill("finger", "mohe-zhi");

	create_family("������", 40, "����");

	setup();

        carry_object("/d/shaolin/obj/qing-cloth")->wear();
}


#include "/kungfu/class/shaolin/qing.h"

