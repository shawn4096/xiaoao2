// shuisheng.c

inherit NPC;
#include <ansi.h>;
string ask_diyun();
string ask_laozu();
string ask_dachang();
#include "/d/suzhou/npc/lchj.h"

void create()
{
       set_name("水笙", ({ "shui sheng", "shui", "sheng" }));
       set("long", 
       "她二十岁上下年纪，白衫飘飘，样貌清秀俏丽，左肩上悬着一朵红绸制的大花，相貌却极为俏丽。\n");
       set("gender", "女性");
       set("nickname", HIW"铃剑双侠"NOR);
       set("age", 20);
       set("attitude", "peaceful");
       set("shen_type", 0);
       set("str", 30);
       set("int", 30);
       set("con", 30);
       set("dex", 30);
       set("per", 35);

       set("max_qi", 12000);
       set("max_jing", 4500);
       set("neili", 12000);
       set("max_neili", 12000);
       set("jiali", 150);
       set("combat_exp", 6500000);
       set("shen_type", 1);

       set_skill("force", 400);
       set_skill("huashan-qigong", 400);
       set_skill("dodge", 400);
       set_skill("huashan-shenfa", 400);
       set_skill("strike", 400);
       set_skill("hunyuan-zhang", 400);
       set_skill("parry", 400);
       set_skill("sword", 400);
       set_skill("huashan-jianfa", 400);
       set_skill("literate", 400);

       map_skill("force", "huashan-qigong");
       map_skill("dodge", "huashan-shenfa");
       map_skill("strike", "hunyuan-zhang");
       map_skill("parry", "huashan-jianfa");
       map_skill("sword", "huashan-jianfa");
	   prepare_skill("strike","hunyuan-zhang");

       set("inquiry", ([
              "落花流水": "你不会不知道江南四侠的大号吧？冷月剑水岱就是我的父亲。",
              "血刀恶僧": "这个家伙自称血刀老祖，其实无恶不作，我看到他一定一剑刺死他。",
		   	  "狄云" : (: ask_diyun :),
			 "血刀老祖" : (: ask_laozu :),
			 "鸟羽大氅" : (: ask_dachang :),

       ]));
		set("chat_chance_combat", 40);

        set("chat_msg_combat", ({
			(: perform_action, "sword.jianzhang" :),
			(: perform_action, "sword.fengyi" :),
			(: perform_action, "sword.lianhuan" :),
			(: exert_function, "juli" :),
			(: exert_function, "yujianshi" :),

		}));

       setup();
       carry_object("/clone/weapon/changjian")->wield();
}
void init( )
{
        call_out("hunting",300);
}

void hunting()
{
   object ob=this_object();
   if (this_player())
    {
      message("vision", HIW"只听得叮玲玲，叮玲玲一阵铃声，一骑马向远处跑走了。\n"NOR, this_player());
     }
    destruct(ob);
}

string ask_diyun()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR3+"tofindshui"))
	{
		command("say 我与你非亲非故，真是莫名其妙，来此作甚？\n");
		return "哼，我可是鼎鼎大名的岭南双侠，少来惹我！\n";
	}
	command("say 你们都错了，他不是淫贼，他是一位好人！\n");
	command("say 我用我亲身故事告诉你他是一位很优秀的男子！\n");
	command("say 前一阵子，我就是被血刀淫贼没抓住了，要不是他，我根本就活不了！\n");

	me->set_temp(QUESTDIR3+"shuisay1",1);

	return "那是一场惊心动魄的大战，血刀老祖是一位非常邪恶的淫贼！\n";
}
string ask_laozu()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR3+"shuisay1"))
	{
		command("say 我与你非亲非故，真是莫名其妙，来此作甚？\n");
		return "哼，我可是鼎鼎大名的岭南双侠，少来惹我！\n";
	}
	command("cry ");
	command("cry "+me->query("id"));

	command("say 血刀老祖把我的父亲和其他三位伯伯全杀了！\n");
	command("say 太凶狠了！\n");
	command("say 都亏了狄云一直保护我，否则我根本就活不了！\n");
	command("say 他一直保护我的名节和生命，我一直都和感激他！\n");
	command("say 后来我为他走了一件鸟羽大氅，也不知道他穿上了没有？！\n");

	me->set_temp(QUESTDIR3+"shuisay2",1);

	return "那雪谷天寒地冻，有这件大氅也许他能暖和点！\n";
}
string ask_dachang()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR3+"shuisay2"))
	{
		command("say 我与你非亲非故，真是莫名其妙，来此作甚？\n");
		return "哼，我可是鼎鼎大名的岭南双侠，少来惹我！\n";
	}
	command("blush ");
	command("blush "+me->query("id"));
	command("say 我当时用雪谷中动物羽毛为他编制了一件鸟羽大氅！\n");
	command("say 走时匆忙放到一个山洞处，不知道他收到了没有！\n");
	command("say 我记得那个山洞在大雪山附近，后来一场大战，匆忙间想不起来放哪儿去了！\n");
	command("say 你若在五分钟内找到那件大氅并送给我就谢谢你！\n");
	command("say 不知道是一场缘份还是仇恨！\n");

	me->set_temp(QUESTDIR3+"tofinddachang",1);
	//if (present("shui sheng",environment(me)))
		//call_out("hunting",10+random(10));
	return "也不知道他在那雪谷山洞中冷不冷？！\n";
}



int accept_object(object me, object obj)
{
		int i;
        if ((string)obj->query("id")=="niaoyu dachang"
			&&me->query_temp(QUESTDIR3+"tofinddachang")) 
		{
			message("vision",me->name()+"给水笙一件鸟羽大氅。\n",environment(me),({me}));
			
			//if(obj->query("owner")!=me->query("id")) return notify_fail (CYN"水笙似乎被如此大礼吓了一跳。\n水笙对"+me->name()+"表示衷心感谢。\n"NOR);  
			
			command("ah "+me->query("id"));
			command("say 这位"+RANK_D->query_respect(me)+"应该是狄云大哥的朋友吧。");
			command("smile "+me->query("id"));
			command("say 既然是狄云大哥的朋友，那么我就告诉你一个小秘密。\n");
			command("say 这整个连城诀的恩怨除了宝藏外，还牵扯到一门叫做神照经的绝世神功。\n");
			command("say 世俗众人争夺的是宝藏，而武林豪客争夺的却是那神照经神功。\n");
			command("say 这门神功我在你发现大氅的那个地方亲眼见到狄云大哥如何大展神威打败敌人的。\n");
			command("say 你如果愿意，我就带你一起去看看狄云大哥在现场有所重大突破的地方。\n");
			command("say 你这么好心肠且有缘，说不定到哪儿去看看有你自己的机缘。\n");
			command("say 你先去哪儿等我，我随后就到。\n");

			me->set_temp(QUESTDIR3+"shuitellstory",1);
			if (present("shui sheng",environment(me)))
				call_out("hunting",5+random(4));

			command("rumor "+"机缘巧合之下，"+me->query("name")+"知晓了神照经神功最后破镜的小道消息！\n");
			return 1;
		}
      
		return 0;
}