#include <ansi.h>
inherit NPC;
void create()
{
        set_name("鹤笔翁", ({ "he biweng", "he", "biweng" }) );
        set("title", HBBLU"玄冥二老"NOR);
        set("long", "他就是玄冥二老中的鹤笔翁。\n");
       set("gender", "男性" );
        set("age", 55);
        set("apprentice", 1);
        set("attitude", "peaceful");
        set("str",35);
        set("int",25);
        set("con",25);
        set("dex",25);
        set("unique", 1);
        set("per", 20);
        set("no_get", 1);

        set("max_qi", 50000);
        set("max_jing", 7000);
        set("neili", 36000);
        set("max_neili", 36000);
        set("jiali", 200);
        set("combat_exp", 12500000);
        set("eff_jingli", 7000);

        set_skill("force", 500);
        set_skill("xiantian-gong", 500);
        set_skill("dodge", 500);
        set_skill("caoshang-fei", 500);
        set_skill("strike", 500);
        set_skill("xuanming-shenzhang", 550);
        set_skill("parry", 500);
        set_skill("literate", 250);

        map_skill("force", "xiantian-gong");
        map_skill("dodge", "caoshang-fei");
        map_skill("strike", "xuanming-shenzhang");
        map_skill("parry", "xuanming-shenzhang");
        prepare_skill("strike", "xuanming-shenzhang");
    	set("chat_chance", 90);
    	set("chat_msg_combat", ({
        	(: perform_action, "strike.lang" :),
        	(: perform_action, "strike.xuanming" :),
        	(: exert_function, "wuqi" :),
        }));
        setup();
        carry_object("/d/wudang/obj/white-robe")->wear();
}

