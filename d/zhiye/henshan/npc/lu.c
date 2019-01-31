// lu.c
inherit NPC;
//inherit F_MASTER;
#include <ansi.h>;
void create()
{
        set_name("Â³Á¬ÈÙ", ({ "lu lianrong", "lu", "lianrong" }) );
        set("nickname", HIY"½ðÑÛµñ"NOR);
        set("gender", "ÄÐÐÔ");
        set("class", "swordsman");
        set("age", 45);
        set("attitude", "peaceful");
        set("per", 13);
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("neili", 14000);
        set("max_neili", 14000);
        set("jiali", 130);
        set("max_qi",15000);
        set("max_jing",3800);
        set("combat_exp", 6000000);
        set("shen_type", -1);

        set_skill("sword", 450);
        set_skill("force", 450);
        set_skill("parry", 450);
        set_skill("dodge", 450);
		set_skill("hand", 450);
        set_skill("songshan-jian", 450);
        set_skill("zhongyuefeng", 450);
		set_skill("hanbing-zhenqi", 450);
		set_skill("songyang-shou", 450);
        map_skill("sword", "songshan-jian");
        map_skill("parry", "songshan-jian");
        map_skill("dodge", "zhongyuefeng");
		map_skill("force", "hanbing-zhenqi");

		map_skill("hand", "songyang-shou");
		prepare_skill("hand","songyang-shou");
        create_family("áÔÉ½ÅÉ", 2, "µÜ×Ó");
		set("chat_msg_chance",90 );
		set("chat_msg_combat", ({
                (: perform_action, "sword.feiwu" :),
				(: perform_action, "sword.songyang" :),
				(: perform_action, "sword.longfeng" :),
				(: perform_action, "hand.junji" :),
				(: exert_function, "hanbing" :),
		}) );

        setup();
		
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/armor/cloth")->wear();
}


