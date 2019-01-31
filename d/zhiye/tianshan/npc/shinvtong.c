// Npc: /d/tianshan/npc/zhujian.c
// By Linux
#include <ansi.h>

inherit NPC;
string ask_mimi();
void create()
{
	set_name("童姥侍女", ({ "shi nu", "shi", "shinu"}));
	set("long",
	    "这是个容貌姣好的女子, 瓜子脸蛋,\n"+
	    "眼如点漆, 清秀绝俗.\n"+
	    "是伺候童姥起居的贴身侍女.\n");
		set("gender", "女性");
		set("age", 18);
		set("per",27);
        set("shen_type",1);
        set("attitude", "peaceful");

        set("str", 20);
        set("int", 25);
        set("con", 30);
        set("dex", 30);
		set("unique", 1);

        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 2500);
        set("max_jing", 2500);
        set("neili", 3500);
        set("max_neili", 3000);
        set("eff_jingli", 2500);
        set("jiali", 60);

        set("combat_exp", 1000000);
        set("score", 2000);

        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("hand",100);
        set_skill("strike", 100);
        set_skill("sword",100);

        set_skill("tianyu-qijian",100);
        set_skill("zhemei-shou",100);
        set_skill("liuyang-zhang",100);
        set_skill("yueying-wubu",100);
        set_skill("bahuang-gong", 100);
        set_skill("literate", 130);
        set_skill("yangyanshu",130);

        map_skill("force", "bahuang-gong");
        map_skill("strike","liuyang-zhang");
        map_skill("dodge", "yueying-wubu");
        map_skill("hand", "zhemei-shou");
        map_skill("parry", "liuyang-zhang");
        map_skill("sword", "tianyu-qijian");
		prepare_skill("hand", "zhemei-shou");
		prepare_skill("strike", "liuyang-zhang");
		set("inquiry", ([
			"name": "奴家叫做"+this_object()->name()+"，从十五岁起便投在这里学艺。",
			"rumors": "最近很少见到宫主。",
			"秘密"		: (: ask_mimi :),

			"here": "这里是灵鹫宫，你没事还是不要随便乱转的好。",
			//"养颜术": "tete",
		//	"秘密" : (: ask_mimi :),

		]));

        create_family("灵鹫宫",3,"弟子");
        setup();
        carry_object(__DIR__"obj/qingyi")->wear();
        carry_object(BINGQI_D("changjian"))->wield();
        add_money("silver",20+random(20));
}
string ask_mimi()
{
	object me=this_player();
	if (me->query("family/family_name")!="灵鹫宫")
	{
		command("say 别来问我，我什么都不知道，我只不过是伺候童姥起居的一个小丫鬟而已。\n");
		return "我怕~~~~~~~~~~~~~~~！\n	";
		//return 1;
	}
	if (me->query("quest/tonglao/pass"))
	{
		message_vision(HIC"小侍女垂目沉思片刻, 说道：“既然你已经深得童姥真传, 我就告诉你点小秘密。”\n"NOR,me);
        command("sigh" + me->query("id"));
		command("say 我在伺候童姥起居时见童姥临睡前从床下拿出一本书在不断翻阅，我不知道是什么书！");
		command("say 我知道肯定和武功无关，我也不知道是什么书，只是知道童姥每次看完后，都会显得非常年轻！\n");
		me->set_temp("askyangyanshu",1);
	}
	return "童姥每次修炼后越来越像小姑娘，真是神奇的很！\n";
	//return 1;
}
