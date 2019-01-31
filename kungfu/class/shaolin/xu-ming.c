// Npc: /kungfu/class/shaolin/xu-ming.c
// Date: YZC 96/01/19

inherit NPC;


void create()
{

	set_name("虚明", ({
		"xu ming",
		"xu",
		"ming",
	}));
	set("long",
		"他是一位身穿黄布袈裟的青年僧人。脸上稚气未脱，身手却已相\n"
		"当矫捷，看来似乎学过一点武功。\n"
	);

	set("nickname", "知客僧");
	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 20);
	set("shen_type", 1);
	set("str", 20);
	set("int", 20);
	set("con", 35);
	set("dex", 20);
	set("max_qi", 550);
	set("max_jing", 400);
	set("neili", 500);
	set("max_neili", 500);
	set("jiali", 20);
	set("combat_exp", 15000);
	
	set_skill("force", 50);
	set_skill("yijin-jing", 50);
	set_skill("dodge", 50);
	set_skill("shaolin-shenfa", 50);
	set_skill("strike", 50);
	set_skill("banruo-zhang", 50);
	set_skill("parry", 50);
	set_skill("sword", 50);
	set_skill("damo-jian", 50);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("strike", "banruo-zhang");
	map_skill("parry", "damo-jian");
	map_skill("sword", "damo-jian");

	prepare_skill("strike", "banruo-zhang");

	create_family("少林派", 41, "弟子");

	setup();

        carry_object("/d/shaolin/obj/changjian")->wield();
        carry_object("/d/shaolin/obj/xu-cloth")->wear();

}
int accept_object(object who, object ob,object me)
{
        mapping fam; 
        me=this_object();

        if (ob->query("owner")!=who->query("id")
			||!ob->query_temp("sljob/qingwu/yingke"))
		{
                command("hehe "+who->query("id"));
                command("say 你给我东西有什么企图？！");
        		return 0;
        }
		if(!who->query_temp("sljob/qingwu/yingke"))
		{
			command("say 你的令牌是那来的，轮值必须得到清无大师的允许！");
			return 0;
		}
		if(!userp(ob) && ob->query("id") == "yingke ling")
		{
			command("say 好吧，你既然有清无大师的令牌，你就在这和我在这里帮我忙吧，可忙死我了。");
			who->apply_condition("sl_yingke",random(4)+7);
			who->set_temp("sljob/qingwu/yingking",1);
			call_out("dest", 1, ob);
			return 1;
		}
	return 1;
}