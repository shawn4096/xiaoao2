// qi.c 祁志诚

#include <ansi.h>

inherit NPC;
string ask_yanlian();
string ask_me();

void create()
{
        set_name("祁志诚", ({"qi zhicheng", "qi"}));
        set("gender", "男性");
        set("age", 24);
        set("class", "taoist");
        set("long",
                "他就是全真教第三代弟子中的好手，谭处端的大弟子祁志诚。\n"
                "他相貌英俊，精明能干，深受长辈的信任，派遣他去掌管教中\n"
                "的经书典籍。\n");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 25);
        set("int", 25);
        set("con", 24);
        set("dex", 24);

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

		set("quest/qz/xtg/daojue/pass",1);
		set("quest/qz/jyg/shangtianti/pass",1);
		set("quest/quanzhen/sword/lianhuan",1);

        set_skill("force", 350);
        set_skill("xiantian-gong", 350);
        set_skill("sword", 360);
        set_skill("quanzhen-jianfa", 360);
        set_skill("dodge", 350);
        set_skill("jinyan-gong", 350);
        set_skill("parry", 350);
        set_skill("leg", 350);
        set_skill("yuanyang-lianhuantui", 350);
        set_skill("literate",160);
        set_skill("taoism",200);
        set_skill("tiangang-beidouzhen",350);
        set_skill("strike",350);
        set_skill("haotian-zhang", 350);
        set_skill("tiangang-beidouzhen", 350);
        set_skill("jinguan-yusuojue", 350);

		map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("leg", "yuanyang-lianhuantui");
        map_skill("strike", "haotian-zhang");

		prepare_skill("strike", "haotian-zhang");
		prepare_skill("leg", "yuanyang-lianhuantui");
        create_family("全真教", 3, "弟子");
		set("chat_chance_combat", 40);
		set("chat_msg_combat", ({
			(: perform_action, "sword.ding" :),
			(: perform_action, "sword.sanqing" :),
			(: perform_action, "sword.lian" :),
			(: exert_function, "daojue" :),
			(: perform_action, "dodge.yanwu" :),
		}));
        create_family("全真教", 3, "弟子");

        set("book_count",1);
        set("inquiry", ([
                "全真教" :  "我全真教是天下道家玄门正宗。\n",
                "道德经" : (: ask_me :),
				"演练天罡北斗大阵" :  (:ask_yanlian:),  
        ]) );

        setup();
		set("chat_chance_combat", 40);
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
        carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

string ask_yanlian()
{
	object me;
	me=this_player();
	if (!me->query_temp("lianzhen/zhao"))
	{
		return "没事不要来打扰我！\n";
	}
	if (me->query_temp("lianzhen/qi"))
	{
		return "你不是喊过我一次了?";
	}
	command("say 好的，既然赵师兄邀请一起演练大阵，我随后就到！\n");
	me->set_temp("lianzhen/qi",1);
	call_out("go_jiaochang",2+random(3));
	return "天罡北斗阵乃是全真精华所在！\n";
}
int go_jiaochang()
{
	object room;
	room=load_object("/d/quanzhen/dajiaochang");
	
	command("say 又要去大校场演练阵法了,真心累！\n");
	if (!present("qi zhicheng",room))
		this_object()->move("/d/quanzhen/dajiaochang");
	return 1;
}
string ask_me()
{
        mapping fam;
        object ob;

        if (!(fam = this_player()->query("family")) || fam["family_name"] != "全真教")
                return RANK_D->query_respect(this_player()) +
                "与本教毫无瓜葛，你这话可叫我弄不明白了。";
        if (query("book_count") < 1)
                return "你来晚了，道德经已经被人取走了。";
        add("book_count", -1);
        ob = new("/d/quanzhen/npc/obj/daodejing-ii");
        ob->move(this_player());
        return "好吧，这本「道德经」你拿回去好好研读。";
}

void reset()
{
	set("book_count", 1);
}

