// fangtianlao.c 方天劳

inherit NPC;
#include <ansi.h>
string ask_wei();
void create()
{
	set_name("方天劳", ({ "fang tianlao","tianlao","fang" }) );
	set("gender", "男性" );
	set("age", 52);
	set("long", "这个老者脸若朱砂，一个酒糟鼻子火也般红，笑眯眯的颇为
和蔼可亲。只是身材略为矮小。\n");
	set("attitude", "peaceful");
        set("nickname", "西域少林长老");
	set("class", "bonze");
	set("str", 35);
	set("con", 35);
	set("int", 25);
	set("dex", 35);

	set("unique", 1);
	set("max_qi", 23000);
	set("max_jing", 4500);
	set("neili", 13000);
	set("max_neili", 13000);
	set("jiali", 170);
	set("shen_type", 1);
	set("startroom","/d/shaolin/shijie8");
	set("combat_exp", 6900000);
	set("chat_chance_combat", 50);
		set("chat_msg_combat", ({
		//(: perform_action, "sword.sanjue" :),
			(: perform_action, "sword.sanjue" :)
        }));
	set_skill("force", 400);
	set_skill("finger", 400);
	set_skill("sword", 400);
	set_skill("dodge", 400);
	set_skill("parry", 400);
	set_skill("shaolin-shenfa", 400);
	set_skill("literate", 120);
	set_skill("yizhi-chan", 400);
    set_skill("damo-jian", 400);
	set_skill("yijin-jing", 400);
	set_skill("buddhism", 150);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "yizhi-chan");
        map_skill("parry", "damo-jian");
        map_skill("sword", "damo-jian");
        prepare_skill("finger", "yizhi-chan");
        
		

	create_family("西域少林", 19, "弟子");

	set("chat_chance", 20);
	set("inquiry", ([
		"昆仑三圣": (: ask_wei :),
	
	]));
	setup();
	carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void init()
{
	object me=this_player();
	if (me->query_temp("klbs/askhe")&& present("fang tianlao",environment(me)))
	{
		message_vision(HIC"方天劳看了你一眼，神情肃然，自言自语道，“昆仑三圣欲不利于少林，我在此防守，不知他何时能来？”\n"NOR,me);
		command("chat 据说昆仑三圣要对少林不利，请少林弟子时刻防守！");
		
	}
}

string ask_wei()
{
	object me=this_player();
	if (!me->query_temp("klbs/askhe"))
		return "你瞎打听什么，和你没关系！\n";
    message_vision(HIC"$N向$n打了个手势贴近$n小声说道，“昆仑三圣....”\n"NOR,me,this_object());
	this_object()->kill_ob(me);
	me->set_temp("kl/baihe/fightfang",1);
	
	return "奸贼，纳命来吧！";
}