//xiao-tong2.c С��
inherit NPC;
#include <ansi.h>
void create()
{
	
	set_name("��ҩ����",({"shishi lama", "lama", "shishi"}));
       	set("long","������ר�ŷ�������ʦ����ҩ��С�������ü��Ŀ�㡣\n");
	set("gender", "����");
	set("age", 16);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);	
	set("max_qi", 300);
	set("max_jing", 300);
	set("neili", 100);
	set("max_neili", 100);
	set("jiali", 1);
	set("combat_exp", 1000);
	set("score", 50000);
        set_skill("unarmed",20);
        set_skill("parry",20);
        set_skill("dodge",20);
	set_skill("force", 20);
	set_skill("sword", 20);
	/*
	set("inquiry", ([
            "���Ͳ�" : (: ask_tea :),
			"����" : (:ask_food:),
			"������" : (:ask_jiu:),
            "ʳ��" : (:ask_food:),
        ]));*/
		setup();
        carry_object("/d/mingjiao/obj/green-cloth")->wear();
}
