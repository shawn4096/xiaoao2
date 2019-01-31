// zhi.c
inherit NPC;

#include <ansi.h>;
void create()
{
        set_name("仪琳", ({ "yi lin", "yilin" , "lin"}) );
        set("gender", "女性");
        set("class", "bonze");
        set("age", 15);
        set("attitude", "peaceful");
        set("per", 24);
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("neili", 13400);
        set("max_neili", 13400);
        set("jiali", 200);
        set("max_qi", 16000);
        set("max_jing", 5800);
		set("max_jingli", 5800);

        set("combat_exp", 4500000);
        set("shen_type", 1);

        set_skill("sword", 350);
        set_skill("force", 350);
        set_skill("parry", 350);
        set_skill("dodge", 350);
        set_skill("strike", 350);
        set_skill("sixiang-zhang" ,350);
        set_skill("linji-zhuang", 350);
        set_skill("hengshan-jianfa", 350);
        //set_skill("qingmang-jianfa", 100);

        map_skill("sword", "hengshan-jianfa");
        map_skill("force", "linji-zhuang");
        map_skill("strike", "sixiang-zhang");
        map_skill("parry", "hengshan-jianfa");
        //map_skill("dodge", "qingmang-jianfa");
        prepare_skill("strike", "sixiang-zhang");

        create_family("恒山派", 14, "弟子");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/emei/obj/shoes")->wear();
        carry_object("/d/emei/obj/cloth")->wear();

}
