// pi.c 皮清玄
// By Lgg,1998.10
inherit NPC;

void create()
{
        set_name("皮清玄", ({"pi qingxuan", "pi"}));
        set("gender", "男性");
        set("age", 24);
        set("class", "taoist");
        set("long",
                "他是一位体格强健的壮年道士，似乎身怀武艺。\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 26);
        set("int", 25);
        set("con", 25);
        set("dex", 26);

        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 1400);
        set("max_jing", 1400);
		set("jingli", 2000);
        set("max_jingli", 2000);

        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 100);

        set("combat_exp", 500000);

        set_skill("force", 140);
        set_skill("xiantian-gong", 140);
        set_skill("dodge", 140);
        set_skill("jinyan-gong", 140);
        set_skill("parry", 140);
        set_skill("leg",140);
        set_skill("yuanyang-lianhuantui", 140);
        set_skill("literate",40);
        set_skill("taoism",40);

        map_skill("force", "xiantian-gong");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("leg", "yuanyang-lianhuantui");
        prepare_skill("leg", "yuanyang-lianhuantui");

        create_family("全真教", 4, "弟子");

        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄门正宗。\n",
        ]) );
        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: perform_action, "leg.yuanyang" :),
                (: perform_action, "leg.lianhuan" :),
             //   (: perform_action, "strike.lian" :),
               
        }));

        setup();

        //carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}
