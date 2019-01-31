//cheng.c 成昆
inherit NPC;
void create()
{
        set_name("成昆",({"cheng kun","cheng","kun"}));
        set("long", "他就是成昆。\n");
        set("age", 60);
        set("attitude", "aggressive");
        set("class", "bonze");
        set("str", 27);
        set("int", 28);
        set("con", 27);
        set("dex", 26);        
        set("max_qi", 45000);
        set("max_jing", 15000);
        set("neili", 30000);
        set("max_neili", 30000);
        set("eff_jingli", 15000);
        set("jiali", 200);
        set("combat_exp", 12400000);
        set("shen", -18000);
        set_skill("parry",460);
        set_skill("hunyuan-yiqi",460);
        set_skill("jingang-quan",460);
        set_skill("cuff",460);
        set_skill("tianlong-xiang",460);
        set_skill("xiuluo-dao",460);
        set_skill("dodge",460);
        set_skill("parry",460);
        set_skill("force", 460);
        set_skill("blade", 460);
        map_skill("parry", "xiuluo-dao");
        map_skill("dodge", "tianlong-xiang");
        map_skill("force", "hunyuan-yiqi");
        map_skill("blade", "xiuluo-dao");
        prepare_skill("cuff","jingang-quan");
        setup();
        carry_object(BINGQI_D("blade"))->wield();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

