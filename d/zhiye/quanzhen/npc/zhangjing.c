#include <ansi.h>
inherit NPC;

string ask_me();
string ask_read();

void create()
{
        set_name("掌经道长", ({ "zhangjing daozhang", "zhangjing", "daozhang" }));
        set("long", @LONG
这位是全真教里掌管经书的道长。他以前是长
安镇上一个私塾的夫子，因为仰慕大道，才拜
到了全真门下。不过毕竟因为年岁大了，功夫
的根基扎得不牢，这也正合他意，可以安安心
心地研读经书了。
LONG);

        set("gender", "男性");
        set("age", 36);
        set("class", "taoist");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 28);
        set("int", 18);
        set("con", 20);
        set("dex", 26);

        set("qi", 25000);
        set("max_qi", 25000);
        set("jing", 3500);
        set("max_jing", 3500);
        set("neili", 15900);
        set("max_neili", 15900);
        set("jiali", 200);

        set("combat_exp", 9620000);
        set("score", 15000);

        set_skill("force", 450);
        set_skill("xiantian-gong", 450);
        set_skill("sword", 450);
        set_skill("quanzhen-jianfa",450);
        set_skill("dodge", 450);
        set_skill("jinyan-gong", 450);
        set_skill("parry", 450);
        set_skill("leg",450);
        set_skill("strike",450);
        set_skill("haotian-zhang", 450);
        set_skill("literate",200);
        set_skill("taoism",280);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
        prepare_skill("strike", "haotian-zhang");

        create_family("全真教", 4, "弟子");

        set("book_count",1);
        set("inquiry", ([
                "全真教" : "我全真教是天下道家玄门正宗。\n",
                "道德经" : (: ask_me :),
				//"借阅" : (: ask_read :),
        ]) );
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                 (: perform_action, "sword.sanqing" :),
                (: perform_action, "sword.qixing" :),
                (: perform_action, "sword.ding" :),
				(: perform_action, "sword.jianqi" :),
                (: perform_action, "sword.lian" :),
				(: exert_function, "daojue" :),
				(: exert_function, "wuqi" :),
				(: exert_function, "yusuo" :),
               
        }));
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/grayrobe")->wear();

}

string ask_me()
{
        mapping fam;
        object ob,me;
		me=this_player();
        
		if (! (fam = this_player()->query("family"))
           || fam["family_name"] != "全真教")
                return "阁下与本教毫无瓜葛，你这话可叫我弄不明白了。";
		if (me->query("party/gongji")<500)
		{
			return "你的门派贡献值不够500，去努力工作去！\n";
		}
		me->add("party/gongji",-500);
		command("say "+me->query("name")+",我已经扣除了你500点门派贡献值！\n");
        if (query("book_count") < 1)
                return "你来晚了，道德经已经被人取走了。";
        if (!me->query("quest/qz/dichuan") )
                return "你非我门中嫡传弟子，来此作甚？\n";

        add("book_count", -1);
        ob = new(__DIR__"obj/daodejing-i");
        ob->move(this_player());
        return "好吧，这本「道德经」你拿去好好研读，不懂的地方可以来问我。";

}
