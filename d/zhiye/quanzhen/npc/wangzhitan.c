// wangzhi.c ��־̹

inherit NPC;

void create()
{
        set_name("��־̹", ({"wang zhitan", "wang"}));
        set("gender", "����");
        set("age", 24);
        set("class", "taoist");
        set("long",
                "������ȫ��̵����������еĺ��֣��������ĵ��ӡ�\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 26);
        set("int", 25);
        set("con", 25);
        set("dex", 26);

        set("qi", 4500);
        set("max_qi", 4500);
        set("jing", 3000);
        set("max_jing", 3000);
		set("jingli", 4000);
        set("max_jingli", 4000);


        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 160);
        set("level", 8);
        set("combat_exp", 4800000);
       
		set("eff_jingli", 4000);
		set("eff_jing", 3000);

        set("combat_exp", 160000);

        set_skill("force", 380);
        set_skill("xiantian-gong", 380);
        set_skill("sword", 380);
        set_skill("quanzhen-jianfa",370);
        set_skill("dodge", 370);
        set_skill("jinyan-gong", 370);
        set_skill("parry", 380);
        set_skill("strike",380);
        set_skill("haotian-zhang", 370);
        set_skill("literate",160);
        set_skill("taoism",160);
        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
        prepare_skill("strike", "haotian-zhang");
		set("quest/qz/xtg/daojue/pass",1);
		set("quest/qz/jyg/shangtianti/pass",1);
		set("quest/quanzhen/sword/lianhuan",1);


        create_family("ȫ���", 3, "����");

        set("inquiry", ([
                "ȫ���" :  "��ȫ��������µ����������ڡ�\n",
        ]) );
		set("chat_chance_combat", 60);
		set("chat_msg_combat", ({
			(: perform_action, "sword.ding" :),
			(: perform_action, "sword.sanqing" :),
			(: perform_action, "sword.lian" :),
			(: exert_function, "daojue" :),
			(: perform_action, "dodge.yanwu" :),
		}));

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}
