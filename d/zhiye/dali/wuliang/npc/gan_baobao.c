// NPC :gan_baobao.c 甘宝宝 
// By River 98/12
#include <ansi.h>

inherit NPC;
string ask_duan();
int yun_come(object me);
int zhong_come(object me);

void create()
{
        set_name("甘宝宝", ({ "gan baobao", "gan", "baobao"}));
        set("title","万劫谷谷主夫人");
        set("nickname",HIC"俏夜叉"NOR);        
        set("gender", "女性" );
        set("age", 36);
        set("str", 17);
        set("con", 23);
        set("dex", 26);
        set("int", 25);
        set("per", 25);
   		set("attitude", "friendly");

        set("max_qi", 15000);
        set("max_jing", 8000);
        set("eff_jingli", 8000);
        set("neili", 8000);
		set("qi", 15000);	
        set("max_neili", 8000);      
        set("unique", 1);
        
        set("long","这妇人约莫三十六七岁左右年纪，容色清秀，眉目间依稀与钟灵甚是相似。\n");
        set("combat_exp", 4200000);
        set("shen", 800); 

        set_skill("parry", 380);
        set_skill("dodge", 380);
        set_skill("force", 380);
        set_skill("strike", 380);
        set_skill("qiantian-yiyang", 380);        
        set_skill("tianlong-xiang", 380);
        set_skill("zhongjia-zhang", 380);
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "zhongjia-zhang");
        map_skill("strike", "zhongjia-zhang");
        map_skill("force", "qiantian-yiyang");
        prepare_skill("strike","zhongjia-zhang");

        set("inquiry", ([            
            "段正淳" : (: ask_duan :),
        ]));

        setup();
        carry_object(__DIR__"obj/lvshan")->wear();
}

string ask_duan()
{
		object me=this_player();
		if (!me->query_temp("yyzhi/helpgbb")) return "哼，你跟我提这个负心人作甚？\n";
		
		command("blush ");
		command("blush ");
		command("say 你到底是谁？为何跟我替他？ ");
		command("say 他是一位王爷，我怎么可能认识他！");
		command("say 你认错人了吧？ ");
		command("say 我是万劫谷谷主夫人，你来问我此事所为何来？！");
		command("say 他是他，我是我。 ");
		command("say 你不要在我的面前提到他的名字。");
		command("say 你看到灵儿了么？ ");
		command("say 她是个苦命的孩子！");
		command("say 她爹是万劫谷谷主！这你知道的，她姓钟。 ");
		command("say 万劫谷古主钟万仇是我丈夫！");
		command("say 有什么事赶紧说，否则我喊人了！ ");
		command("say .........、");
		command("say .........、");
		command("say .........、");
		message_vision(HIY"\n\n\n\n经过长时间的紧张和絮叨，甘宝宝终于确认$N是段正淳派来保护她的人。\n"NOR,me);

		message_vision(HIY"\n\n\n\n\此时再也控制不住自己的情绪，嚎啕大哭起来。\n"NOR,me);
		message_vision(HIY"\n\n\n\n\。。。。。。。。。\n"NOR,me);
		message_vision(HIY"\n\n\n\n\半个时辰以后，甘宝宝情绪稳定下来，开始想你诉说故事的整个来龙去脉。\n"NOR,me);
		if (me->query_temp("yyzhi/helpgbb"))
		{		
			me->set_temp("yyzhi/askgan",1);
			message_vision(HIC"\n\n\不知觉间甘宝宝宛如回到自己青春年代，面上现出无限神往的神采。。。\n"NOR,me);
			call_out("zhong",2+random(3),me);
			return "长叹一声，似乎有无穷的心事，又似乎心有不甘\n";
		}
		return "";

}

int zhong(object me)
{
	message_vision(HIR"忽听门外有一个粗暴的声音喊道，“谁？谁他妈的又钻到我老婆的房间里去了？”\n"NOR,me);
	command("say 快点躲起来，我丈夫很是多疑，一会就来了，那麻烦可就大了!\n");
	command("blush ");

	message_vision(HIC"$N说道，“甘夫人不要害怕，王爷派我来保护"HIR"(baohu 甘宝宝)"HIC"你的！”？”\n"NOR,me);

}