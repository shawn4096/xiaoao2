// Npc : beijinyi.c ������
// Made by Jackie
// 12345...��ɽ���ϻ�....


#include "sujia.h"
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("������", ({ "bei jinyi", "bei", "jinyi" }));
        set("long", 
                "���Ƕ������׼ҵ��ӱ����ǡ�\n"
                "������һ��������ĸ�����������˳��\n"
        );
        set("gender", "Ů��");
        set("age", 30);
        set("attitude", "friendly");
         set("unique", 1);
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);     
        set("max_qi", 3000);
        set("max_jing", 3000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 120);
        set("combat_exp", 3400000);

	set_skill("dacheng-fofa", 280);
        set_skill("linji-zhuang", 280);
	set_skill("huifeng-jian", 285);
	set_skill("sword", 290);
	set_skill("literate", 290);
	set_skill("parry", 290);
	set_skill("dodge", 280);
	set_skill("force", 280);
	set_skill("anying-fuxiang", 290);

	map_skill("force", "linji-zhuang");
	map_skill("sword", "huifeng-jian");
	map_skill("parry", "huifeng-jian");
	map_skill("dodge", "anying-fuxiang");
        create_family("������", 4, "����");
        setup();
	carry_object("/d/emei/obj/changjian")->wield();
	carry_object("/d/emei/obj/shoes")->wear();
	carry_object("/d/emei/obj/cloth")->wear();

}

