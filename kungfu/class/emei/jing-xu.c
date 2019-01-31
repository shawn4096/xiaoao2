// /kungfu/class/emei/jing-xu.c
// Make by jackie 98.2

#include "nigu.h"
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("静虚师太", ({
                "jingxu shitai",
                "jingxu",
                "shitai",
        }));
        set("long",
                "她是一位慈祥的中年师太，在华藏庵修行。\n"
		"她是灭绝师太的八大静字辈弟子之二。\n");

        set("gender", "女性");
        set("attitude", "friendly");
         set("unique", 1);
        set("class", "bonze");

        set("age", 35);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 35);
        set("max_qi", 11200);
        set("max_jing", 5200);
        set("neili", 11500);
        set("max_neili", 11500);
        set("jiali", 130);
        set("combat_exp", 4500000);
        set("score", 100);

	set_skill("dacheng-fofa", 200);
	set_skill("linji-zhuang", 400);
	set_skill("literate", 130);
	set_skill("huifeng-jian", 400);
	set_skill("sword", 400);
	set_skill("parry", 400);
	set_skill("dodge", 400);
	set_skill("force", 400);
	set_skill("hand", 400);
	set_skill("jieshou-jiushi", 400);
	set_skill("anying-fuxiang", 400);
       set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
        ]));
	map_skill("force", "linji-zhuang");
	map_skill("sword", "huifeng-jian");
	map_skill("parry", "huifeng-jian");
	map_skill("hand", "jieshou-jiushi");
	map_skill("dodge", "anying-fuxiang");

        create_family("峨嵋派", 4, "弟子");
        setup();
	carry_object("/d/emei/obj/changjian")->wield();
	carry_object("/d/emei/obj/shoes")->wear();
	carry_object("/d/emei/obj/cloth")->wear();

        
}


