// /kungfu/class/emei/jing-xian.c
// Update by Lklv 2001.10.18

#include "nigu.h"
inherit F_MASTER;
inherit NPC;

void create()
{
	set_name("����ʦ̫", ({"jingxian shitai", "jingxian", "shitai"}));
	set("long",
		"����һλ���������ʦ̫�������������С�\n"
		"�������ʦ̫�İ˴��ֱ�����֮�ߡ�\n"
	);

	set("gender", "Ů��");
	set("attitude", "friendly");
	set("unique", 1);
	set("class", "bonze");

	set("age", 35);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 32);
	set("max_qi", 12000);
	set("max_jing", 6000);
	set("neili", 15000);
	set("max_neili",15000);
	set("jiali", 200);
	set("combat_exp", 4700000);
	set("score", 10000);

	set_skill("dacheng-fofa", 280);
	set_skill("linji-zhuang", 280);
	set_skill("literate", 130);
	set_skill("huifeng-jian", 280);
	set_skill("sword", 280);
	set_skill("parry", 280);
	set_skill("blade", 280);
	set_skill("yanxing-daofa", 280);
	set_skill("sixiang-zhang", 280);
	set_skill("dodge", 280);
	set_skill("strike", 280);
	set_skill("force", 280);
	set_skill("anying-fuxiang", 280);
	set("inquiry",([
                "���"  : (: ask_for_join :),
                "����"  : (: ask_for_join :),
        ]));

	map_skill("strike", "sixiang-zhang");
	map_skill("force", "linji-zhuang");
	map_skill("sword", "huifeng-jian");
	map_skill("parry", "huifeng-jian");
	map_skill("dodge", "anying-fuxiang");

	prepare_skill("strike", "sixiang-zhang");

	create_family("������", 4, "����");
	setup();

	carry_object("/d/emei/obj/shoes")->wear();
	carry_object("/d/emei/obj/cloth")->wear();
}
