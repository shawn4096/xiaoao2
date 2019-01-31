#include <ansi.h>
inherit NPC;

string ask_me();
string ask_yusuo2();
string ask_ankang();

void create()
{
        set_name("掌理道长", ({ "zhangli daozhang", "zhangli", "daozhang" }));
        set("long", @LONG
这是一位年纪很轻的道人，他精明能干，是全
真教第四代弟子中出类拔瘁的人物，前辈真人
们分派他来掌理全教上下的杂务。
LONG);

        set("gender", "男性");
        set("age", 22);
        set("class", "taoist");
        set("attitude", "friendly");
        set("shen_type",1);
        set("str", 22);
        set("int", 22);
        set("con", 22);
        set("dex", 22);

        set("qi", 600);
        set("max_qi", 600);
        set("jing", 400);
        set("max_jing", 400);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 0);

        set("combat_exp", 30000);
        set("score", 20000);

        set_skill("force", 60);
        set_skill("xiantian-gong", 50);
        set_skill("sword", 60);
        set_skill("quanzhen-jianfa",60);
        set_skill("dodge", 50);
        set_skill("jinyan-gong", 50);
        set_skill("parry", 60);
        set_skill("unarmed",60);
        set_skill("strike",60);
        set_skill("haotian-zhang", 50);
        set_skill("literate",50);
        set_skill("taoism",40);

        map_skill("force", "xiantian-gong");
        map_skill("sword", "quanzhen-jianfa");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "quanzhen-jianfa");
        map_skill("strike", "haotian-zhang");
        prepare_skill("strike", "haotian-zhang");

        create_family("全真教", 4, "弟子");

        set("book_count",1);
        set("yusuo_count",1);

        set("inquiry", ([
                "身体安康" :  (: ask_ankang :),
                "道德经" : (: ask_me :),
				"金关玉锁诀秘籍" : (: ask_yusuo2 :),
        ]) );

        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/grayrobe")->wear();
}
string ask_ankang()
{
        mapping fam;
        object me;
		me=this_player();
        if (! (fam = this_player()->query("family"))
           || fam["family_name"] != "全真教")
                return "阁下与本教毫无瓜葛，你这话可叫我弄不明白了。";
		command("say 最近腰酸背痛腿抽筋，身体不太好！听说吃到龟苓膏就会大为康复！\n");
		command("say 谁要是给我弄来，我感恩不尽！\n");
		me->set_temp("book/askzhangli",1);
        return "唉，年纪大了，岁数不饶人啊!\n";

}
string ask_me()
{
        mapping fam;
        object ob,me;
		me=this_player();

        if (! (fam = this_player()->query("family"))
           || fam["family_name"] != "全真教")
                return "阁下与本教毫无瓜葛，你这话可叫我弄不明白了。";
        if (!me->query("quest/qz/dichuan"))
                return "你非核心嫡传弟子，来此作甚？。";
  
		if (!me->query_temp("book/askzhangli"))
		{
			return "你我非亲非故，干嘛呢？\n";
		}
		
		if (!me->query_temp("book/givegao"))
		{
			command("say 我的身体不太好，你若能替我找到龟苓膏，我就指点你如何得到这本书！\n");
			me->set_temp("book/askyusuo2");
			return "龟苓膏需要在采药过程中不断熬制方可练成，掌药那个老东西可珍惜的很！\n";
		}
        if (query("book_count") < 1)
                return "你来晚了，道德经已经被人取走了。";
		if (me->query("party/gongji")<1000)
		{
			return "你的门派贡献值不够1000，去努力工作去！\n";
		}
		me->add("party/gongji",-1000);
		command("say "+me->query("name")+",我已经扣除了你1000点门派贡献值！\n");

        add("book_count", -1);
        ob = new(__DIR__"obj/daodejing-ii");
        ob->move(this_player());
        return "好吧，这本「道德经」你拿去好好研读，不懂的地方可以来问我。";

}

string ask_yusuo2()
{
        mapping fam;
        object ob,me;
		me=this_player();
        if (! (fam = this_player()->query("family"))
           || fam["family_name"] != "全真教")
                return "阁下与本教毫无瓜葛，你这话可叫我弄不明白了。";
        if (!me->query("quest/qz/dichuan"))
                return "你非核心嫡传弟子，来此作甚？。";
        if (query("yusuo_count") < 1)
                return "你来晚了，玉锁诀下册已经被人取走了。";
		if (!me->query_temp("book/askzhangli"))
		{
			return "你我非亲非故，干嘛呢？\n";
		}
		if (!me->query_temp("book/givegao"))
		{
			command("say 我的身体不太好，你若能替我找到龟苓膏，我就指点你如何得到这本书！\n");
			me->set_temp("book/askyusuo2",1);
			return "龟苓膏需要在采药过程中不断熬制方可练成，掌药那个老东西可珍惜的很！\n";
		}
		
		if (me->query("party/gongji")<1000)
		{
			return "你的门派贡献值不够1000，去努力工作去！\n";
		}
		
		me->add("party/gongji",-1000);
		command("say "+me->query("name")+",我已经扣除了你1000点门派贡献值！\n");

        add("yusuo_count", -1);
        ob = new("/d/quanzhen/obj/yusuojue2");
        ob->move(this_player());
		me->delete_temp("book");
        return "好吧，这本「金关玉锁二十四诀下册」你拿去好好研读，不懂的地方可以来问我。";

}

int accept_object(object who, object ob)
{

	
	if (ob->query("id")=="guiling gao"
		&& who->query_temp("book/askyusuo2")
		&& ob->query("owner")==who->query("id"))
	{
		command("say "+who->query("name")+"好，非常不错，终于拿到这个龟苓膏了！\n");
		command("say 滋阴养颜，理顺躁气的珍品！\n");
		command("say 你如此孝敬老人家，我就给你这本秘籍，好生保管！\n");
		//who->delete_temp("book");
		who->set_temp("book/givegao",1);
		destruct(ob);
		message_vision(HIY"$N获得了掌理道长的青睐，得到请教道长核心秘籍的机会！\n"NOR,who);
		return 1;
	}
	
}