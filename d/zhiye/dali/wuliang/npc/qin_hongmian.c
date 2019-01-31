// NPC qin_hongmian.c 秦红棉
// By sohu@xojh 2014
#include <ansi.h>

inherit NPC;
string ask_duan();
int qin(object me);

void create()
{
        set_name("秦红棉", ({ "qin hongmian", "qin", "hongmian"}));
        set("title",HIB"修罗刀"NOR);
        //set("nickname","俏夜叉");        
        set("gender", "女性" );
        set("age", 36);
        set("str", 17);
        set("con", 23);
        set("dex", 26);
        set("int", 25);
        set("per", 25);
   		set("attitude", "friendly");

        set("max_qi", 10000);
        set("max_jing", 8000);
        set("eff_jingli", 8000);
        set("neili", 8000);
		set("qi", 10000);	
        set("max_neili", 8000);      
        set("unique", 1);
        
        set("long","这妇人约莫三十六七岁左右年纪，容色清秀，眉目间依稀与木婉清甚是相似。\n");
        set("combat_exp", 4200000);
        set("shen", 800); 

        set_skill("parry", 380);
        set_skill("dodge", 380);
        set_skill("force", 380);
        set_skill("strike", 380);
		set_skill("blade", 400);
		set_skill("xiuluo-dao", 400);
        set_skill("qiantian-yiyang", 380);        
        set_skill("tianlong-xiang", 380);
        set_skill("qingyan-zhang", 380);

        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "xiuluo-dao");
        map_skill("strike", "qingyan-zhang");
        map_skill("force", "qiantian-yiyang");
        prepare_skill("strike","qingyan-zhang");
		set("chat_chance_combat", 60);
		set("chat_msg_combat",({
			(: perform_action, "blade.xiuluo" :),
			(: perform_action, "strike.qingyan" :),
			(: perform_action, "strike.piaomiao" :),
			(: exert_function, "qi" :)
		}));
        set("inquiry", ([            
            "段正淳" : (: ask_duan :),
        ]));

        setup();
		carry_object("/clone/weapon/blade")->wield();
        carry_object(__DIR__"obj/lvshan")->wear();
}
string ask_duan()
{
		object me=this_player();
		if (!me->query_temp("yyzhi/helpqhm")) return "哼，你跟我提这个负心人作甚？见了面我就杀一次！\n";
		
		command("angry ");
		command("shout 段正淳你个没良心的！");
	
		command("say 有什么事赶紧说，否则我喊人了！ ");
		command("say 我若死了不正好随了他的心意了么？想找谁就去找谁？");
		command("say .........、");
		command("say .........、");
		message_vision(HIY"\n\n\n\n经过长时间的紧张和絮叨，秦红棉终于确认$N是段正淳派来保护她的人。\n"NOR,me);

		message_vision(HIY"\n\n\n\n\此时再也控制不住自己的情绪，嚎啕大哭起来。\n"NOR,me);
		message_vision(HIY"\n\n\n\n\。。。。。。。。。\n"NOR,me);
		message_vision(HIY"\n\n\n\n\半个时辰以后，秦红棉情绪稳定下来，开始想你诉说故事的整个来龙去脉。\n"NOR,me);
		if (me->query_temp("yyzhi/helpgbb"))
		{		
			me->set_temp("yyzhi/askqin",1);
			message_vision(HIC"\n\n\不知觉间秦红棉宛如回到自己青春年代，面上现出无限神往的神采。。。\n"NOR,me);
			return "长叹一声，似乎有无穷的心事，又似乎心有不甘\n";
		}
		me->set_temp("yyzhi/askqin",1);
		call_out("qin",2,me);
		return "难道出什么事了？\n";

}
int qin(object me)
{
	//object me=this_player();
	command("hammer ");
	command("heng ");
	command("say 你既然是他派来了，他为什么不自己来？\n");
	message_vision(HIC"秦红棉沉吟良久，说道，“你确认"+HIR+"(answer 确认)"+HIC"是他真心来保护我的么？\n”"NOR,me);
	//add_action("do_answer","answer");
	return 1;

}