// xieyan.c
//by kingso 2010 08 侠客行系列

#include <ansi.h>

inherit NPC;



void create()
{
        object ob;
		seteuid(getuid());
        set_name("闵柔", ({ "min rou", "minrou" }));
        set("long", @LONG
白衣女子骑在白马上，若不是鬓边戴了朵红花，腰间又系着一条猩红飘带
几乎便如服丧，红带上挂了一柄白鞘长剑,她是玄素庄庄主夫人，和丈夫石
清并称“黑白双剑”，为上清观弟子,其为人文秀清雅，娴熟温柔，衣衫飘飘
人如其名。
LONG );
        set("title","上清观弟子");
		set("nickname", HIC "玄素庄庄主夫人" NOR);
        set("gender", "女性");
        set("age", 41);
        set("shen_type", 1);
        set("attitude", "friendly");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("qi", 25000);
        set("max_qi", 25000);
		set("eff_qi", 25000);

        set("jing", 6500);
        set("max_jing", 6500);
		set("eff_jing", 6500);

        set("neili", 20000);
        set("max_neili", 20000);
        set("max_jingli", 8000);
        set("jingli", 8000);
        set("eff_jingli", 8000);
        set("jiali", 200);

        set("combat_exp", 10500000);

        set_skill("force", 460);
        set_skill("sword", 500);
        set_skill("dodge", 460);
        set_skill("parry", 460);
        set_skill("strike", 460);
        set_skill("xuantian-wuji", 460);
        set_skill("taxue-wuhen", 460);
        set_skill("shangqing-jian", 460);
		set_skill("kunlun-zhang", 460);

        map_skill("force", "xuantian-wuji");
        map_skill("dodge", "taxue-wuhen");
        map_skill("strike", "kunlun-zhang");
        map_skill("parry", "shangqing-jian");
        map_skill("sword", "shangqing-jian");

        prepare_skill("strike", "kunlun-zhang");
        set("chat_chance_combat", 80);
     
		set("chat_msg_combat", ({
		(: exert_function, "wuji" :),
		(: perform_action, "dodge.taxue" :),
		(: perform_action, "sword.qingfeng" :),
		//(: perform_action, "leg.ruying" :),
	}));


        set("inquiry", ([
             //   "碧针清掌" : (: ask_me :),
               // "绝招"     : (: ask_me :),
               // "澎湃"     : (: ask_me :),
              //  "绝技"     : (: ask_me :),
             //   "玄铁令"   : "两枚玄铁令我已经收回,还有一枚失落江湖。最近匪人甚多，你可以去赵城之那里看看。",
              //  "石破天"   : "狗杂种那个白痴还没死么？",
        ]));
        setup();
  	    carry_object("/clone/weapon/changjian")->wield();
  	 //   ob=new("/clone/weapon/changjian");
		//ob->wield();

        carry_object("/clone/armor/cloth")->wear();
}
