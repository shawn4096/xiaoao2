//xiao-tong2.c 小僮
inherit NPC;
#include <ansi.h>
void create()
{
	
	set_name("炼药喇嘛",({"shishi lama", "lama", "shishi"}));
       	set("long","他就是专门服侍门中师傅炼药的小喇嘛。长得眉清目秀。\n");
	set("gender", "男性");
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
            "酥油茶" : (: ask_tea :),
			"糌粑" : (:ask_food:),
			"青稞酒" : (:ask_jiu:),
            "食物" : (:ask_food:),
        ]));*/
		setup();
        carry_object("/d/mingjiao/obj/green-cloth")->wear();
}
