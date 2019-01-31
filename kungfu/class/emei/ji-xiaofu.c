// /kungfu/class/emei/ji-xiaofu.c
// Make by jackie 98.2

#include "sujia.h"
inherit F_MASTER;
inherit NPC;

void create()
{
        set_name("纪晓芙", ({
                "ji xiaofu",
                "ji",
                }));
        set("long",
                "她是一位美貌的女子，使得一手上好的回风拂柳剑。\n"
        );


        set("gender", "女性");
        set("attitude", "friendly");
         set("unique", 1);

        set("age", 25);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 12800);
        set("max_jing", 5800);
        set("neili", 18000);
        set("max_neili", 18000);
        set("jiali", 180);
        set("combat_exp", 4800000);
        set("score", 100);


        create_family("峨嵋派", 4, "弟子");

        setup();

}

