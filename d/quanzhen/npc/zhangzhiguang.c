// zhang.c 张志光

inherit NPC;

void create()
{
        set_name("张志光", ({"zhang zhiguang", "zhang"}));
        set("gender", "男性");
        set("age", 24);
        set("class", "taoist");
        set("long",
                "他就是全真教第三代弟子中的好手，谭处端的弟子。\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 26);
        set("int", 25);
        set("con", 25);
        set("dex", 26);


        set("qi", 15000);
        set("max_qi", 15000);
        set("jing", 3000);
        set("max_jing", 3000);
		set("eff_jing", 3000);

		set("jingli", 4000);
        set("max_jingli", 4000);
        set("eff_jingli", 4000);

        set("neili", 15000);
        set("max_neili", 15000);
        set("jiali", 150);

        set("combat_exp", 6600000);
		set("quest/qz/xtg/daojue/pass",1);
		set("quest/qz/jyg/shangtianti/pass",1);
		set("quest/quanzhen/sword/lianhuan",1);

        set_skill("force", 380);
        set_skill("xiantian-gong", 380);
        set_skill("sword", 380);
        set_skill("quanzhen-jianfa",380);
        set_skill("dodge", 380);
        set_skill("jinyan-gong", 380);
        set_skill("parry", 380);
        set_skill("strike",380);
        set_skill("haotian-zhang", 380);
        set_skill("literate", 160);
        set_skill("taoism", 160);      
        set_skill("tiangang-beidouzhen", 380);
        set_skill("leg", 380);      
        set_skill("yuanyang-lianhuantui", 380);
        set_skill("jinguan-yusuojue", 350);

		map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
		map_skill("leg", "yuanyang-lianhuantui");

        prepare_skill("strike", "haotian-zhang");
		prepare_skill("leg", "yuanyang-lianhuantui");
		set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: perform_action, "sword.ding" :),
			(: perform_action, "sword.sanqing" :),
			(: perform_action, "sword.lian" :),
			(: exert_function, "daojue" :),
			(: perform_action, "dodge.yanwu" :),
		}));

        create_family("全真教", 3, "弟子");

        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄门正宗。\n",
        ]) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}
