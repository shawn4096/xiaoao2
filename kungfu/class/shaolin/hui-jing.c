// Npc: /kungfu/class/shaolin/hui-xiu.c

#include <ansi.h>
inherit NPC;
string ask_me();

void create()
{
	set_name("慧净尊者", ({
		"huijing zunzhe",
		"huijing",
		"zunzhe",
	}));
	set("long",
		"和尚肥胖已极，身材即又矮，宛然是个大肉球，\n"
		"太阳穴微凸，双目炯炯有神。\n"
	);

	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

        set("age", 50);
        set("shen_type", 1);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 450);
        set("max_jing", 300);
        set("neili", 600);
        set("max_neili", 600);
 
		set("jiali", 50);
		set("combat_exp", 120000);
		set("score", 100);

        set_skill("force", 100);
        set_skill("yijin-jing", 100);
        set_skill("dodge", 100);
        set_skill("shaolin-shenfa", 100);
        set_skill("cuff", 100);
        set_skill("jingang-quan", 100);
        set_skill("staff", 100);
        set_skill("pudu-zhang", 100);
        set_skill("parry", 100);
        set_skill("buddhism", 100);
        set_skill("literate", 100);
   		map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("staff", "pudu-zhang");
        map_skill("parry", "pudu-zhang");

        prepare_skill("cuff", "jingang-quan");

		create_family("少林派", 38, "弟子");
        set("inquiry",  ([
			"冰蚕" : (: ask_me :),
		]));
	setup();

        carry_object("/d/shaolin/obj/chanzhang")->wield();
        carry_object("/d/shaolin/obj/hui-cloth")->wear();
}


string ask_me()
{
        object me=this_player();
        
		if (!me->query_temp("bingcan/askbingcan"))
		{
			return "冰蚕是我可爱的小宝宝，谁都别想给我偷走!\n";
		}
		
		command("say 冰蚕乃是毒中之王，那可是我的小宝贝儿。\n");
		command("say 这冰蚕本是我从天山后山一个山洞中所发现。\n");
		command("say 这冰蚕不仅奇毒无比，而且冰寒入骨，稍有不慎将为其冰毒所害。\n");
		command("say 我前一阵子曾发现过它，可惜被人给偷走了。\n");
		command("say 你若愿意替我去找回来我就告诉你那个所在。\n");
		command("say 切记，那是星宿毒虫谷的一条小路径，走到一个冰洞处。\n");
		command("say 去之前要准备好一个葫芦和相应的硫磺等物，否则你根本就抓不到。\n");
		me->set_temp("bingcan/askxiu",1);
		return "好吧，去哪儿应当小心防范，防止被冰蚕给冻死。\n";
}
