#include <skill.h> 
#include <ansi.h>

inherit NPC;
int do_learn(string arg);

void create()
{
        set_name("¹�ȿ�", ({ "lu zhangke", "lu", "zhangke" }) );
        set("title", HBBLU"��ڤ����"NOR);
        set("long", "��������ڤ�����е�¹�ȿ͡�\n");
        set("gender", "����" );
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
        set("jiali", 220);
        set("combat_exp", 13500000);
        set("eff_jingli", 17000);

        set_skill("force", 500);
        set_skill("xiantian-gong", 500);
        set_skill("dodge", 500);
        set_skill("caoshang-fei", 500);
        set_skill("strike", 500);
        set_skill("xuanming-shenzhang", 550);
        set_skill("parry", 500);
        set_skill("literate", 250);

        map_skill("force", "xiantian-gong");
        map_skill("dodge", "caishang-fei");
        map_skill("strike", "xuanming-shenzhang");
        map_skill("parry", "xuanming-shenzhang");
        prepare_skill("strike", "xuanming-shenzhang");
       	set("chat_chance_combat", 90);
    	set("chat_msg_combat", ({
        	(: perform_action, "strike.lang" :),
        	(: perform_action, "strike.xuanming" :),
        	(: exert_function, "wuqi" :),
        }));
        setup();
        carry_object("/d/wudang/obj/white-robe")->wear();
}


int prevent_learn(object ob, string skill)
{
	if (skill == "xuanming-shenzhang")
		return 0;
	return 1;
}

int is_apprentice_of(object ob)
{
	return 1;
}

int recognize_apprentice(object ob)
{
	return 1;
}
