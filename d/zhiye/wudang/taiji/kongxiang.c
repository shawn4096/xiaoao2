// By Spiderii
#include <ansi.h>
inherit NPC;

void create()
{
	set_name("空相大师", ({
		"kongxiang dashi",
		"kongxiang",
		"dashi",
	}));
	set("long",
		"他是一位面色红润的中年老僧，身穿一袭银丝棕黄袈裟。他身材高大，\n"
		"两手过膝。双目半睁半闭，却不时射出一缕精光。\n"
	);


	set("nickname", "金刚掌");
	set("gender", "男性");
	set("attitude", "peaceful");
	set("class", "bonze");

	set("age", 40);
	set("shen_type", 1);
	set("str", 35);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 23000);
	set("max_jing", 8000);
	set("neili", 20000);
	set("max_neili", 20000);
	set("jiali", 200);
	set("combat_exp", 10000000);
	set("score", 500000);

	set_skill("force", 480);
	set_skill("hunyuan-yiqi", 480);
	set_skill("dodge", 480);
	set_skill("shaolin-shenfa", 480);
	set_skill("parry", 480);

	set_skill("strike", 480);

	set_skill("banruo-zhang", 480);
	//set_skill("sanhua-zhang", 480);
	set_skill("buddhism", 140);
	set_skill("literate", 140);

	map_skill("force", "yijin-jing");
	map_skill("strike", "banruo-zhang");
	map_skill("dodge", "shaolin-shenfa");

	map_skill("parry", "banruo-zhang");

    prepare_skill("strike", "banruo-zhang");
    set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
		(: perform_action, "strike.chaodu" :),
		(: perform_action, "strike.yipai" :),
		
	}));
	create_family("少林派", 36, "弟子");

	setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}
int init()
{
	 object ob;
        
        ::init();
        
        if( interactive(ob = this_player()))
        {
              if (ob->query_temp("mwd/step7") )
              {
				command("chat 我乃少林弟子空相，少林有难，为魔教凶徒围攻，危在旦夕！");

              }
			   // remove_call_out("greeting");
             //   call_out("greeting", 0, ob);
        }

}
int greeting(object ob)
{
		command("chat 弟子一路赶来，时间紧迫，来不及细说，须亲见张真人方可详细禀报！");
		command("chat 奉掌门之命来此求见张真人，还请各位师兄及时通报！！");
}
int greet2(object ob)
{
		command("cry");
		command("say 张真人，魔教这次大举来攻，少林危在旦夕，你可得救我们少林派啊！");
		command("say 我来的时候，魔教凶徒已经围困少林寺，我一路跋涉，不知现在少林还存在不存在！");
		command("cry");
		command("cry");
}