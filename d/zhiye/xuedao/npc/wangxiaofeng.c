// wangxiaofeng.c

inherit NPC;
#include <ansi.h>;
#include "/d/suzhou/npc/lchj.h"
string ask_diyun();
string ask_shuisheng();
string ask_qiangjie();
int shui_go(object me,object shui);

void create()
{
       set_name("汪啸风", ({ "wang xiaofeng", "wang", }));
       set("long", 
       "二十上下，英俊雅致，一身黄衫，修长俊拔，骑一匹高头长身遍身深为金黄色毛发的骏马。\n");
       set("gender", "男性");
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
              "落花流水": "你不会不知道江南四侠的大号吧？冷月剑水岱就是我女朋友的父亲。",
              "血刀恶僧": "这个家伙自称血刀老祖，其实无恶不作，我看到他一定一剑刺死他。",
			"狄云" : (: ask_diyun :),
			"师妹" : (: ask_shuisheng :),
			"吵架" : (: ask_qiangjie :),


       ]));
		set("chat_chance_combat", 50);

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

int init()
{
	object shui;
	object me=this_player();
	if (me->query_temp(QUESTDIR3+"askshui"))
	{
		message_vision(HIC"$N远远看去，见前方似乎有一对青年男女正在吵架，那女子一怒之下，似乎拍马而去!\n"NOR,me);
		message_vision(HIM"而那男的却似乎犹豫不决，他见$N正在向此处走来，也装作若无其事的样子!\n"NOR,me);
		if (!objectp(shui=present("shui sheng",this_object())))
		{
			shui=new("d/xuedao/npc/shuisheng");
			shui->move(environment(me));
		}
		call_out("shui_go",2+random(3),me,shui);

		me->set_temp(QUESTDIR3+"findstory",1);
		me->delete_temp(QUESTDIR3+"askshui");
	}

}
int shui_go(object me,object shui)
{
	
	if (!me) return 0;
	message_vision(YEL"一位面色略显黑色的俊俏小姑娘似乎怒气冲冲的样子，从$N身边扬鞭向南狂奔而去.......！\n"NOR,me);
	if (objectp(shui=present("shui sheng",environment(me))))
	{
		destruct(shui);
	}

	return 1;
}

void hunting()
{
   object ob=this_object();
   if (this_player()->query_temp(QUESTDIR3+"wangyouyu"))
    {
      message("vision", HIW"师妹，等等我！！，只听得叮玲玲，叮玲玲一阵铃声，一骑马向远处跑走了。\n"NOR, this_player());
	  this_player()->set_temp(QUESTDIR3+"tofindshui",1);
     }
    destruct(ob);
	return;
}
string ask_diyun()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR3+"findstory"))
	{
		command("say 我与你非亲非故，真是莫名其妙，来此作甚？\n");
		return "哼，我可是鼎鼎大名的岭南双侠，少来惹我！\n";
	}
	command("say 你说的是那个秃头小瘪三啊，我正想找这小淫贼呢，一双眼睛光看我师妹了，一看就不是好东西！\n");
	command("say 尤其是他旁边还有个淫贼，肯定是一路货色！\n");
	command("say 你打听他，一看也不是好货色！\n");

	me->set_temp(QUESTDIR3+"askwang",1);

	return "你看起来贼腻兮兮的，也不是什么好鸟！\n";
}
string ask_shuisheng()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR3+"askwang"))
	{
		command("say 我与你非亲非故，真是莫名其妙，来此作甚？\n");
		return "哼，我可是鼎鼎大名的岭南双侠，少来惹我！\n";
	}
	command("say 我师妹是天下第一美人！\n");
	command("say 我和他人称岭南双侠，我们可不是好惹的！\n");
	command("say 我方才还和我师妹在一起！\n");

	me->set_temp(QUESTDIR3+"askwangshui",1);

	return "我的师妹真漂亮！\n";
}
string ask_qiangjie()
{
	object me;
	me=this_player();
	if (!me->query_temp(QUESTDIR3+"askwangshui"))
	{
		command("say 我与你非亲非故，真是莫名其妙，来此作甚？\n");
		return "哼，我可是鼎鼎大名的岭南双侠，少来惹我！\n";
	}
	command("cry ");
	command("cry "+me->query("id"));
	command("fear ");
	command("say 既然你什么都知道了，我就跟你说实话吧！\n");
	command("say 就在方才我和我师妹吵了一架，她一怒之下就离开我独自走了！\n");
	command("say 就是方才向南去了！\n");
	command("say 我想追她，可又咽不下这口气，谁叫她来气我来！\n");
	command("say 这次我就好好教训她下，省的以后嫁给我我还要受气！\n");
	command("say 不过我心中也甚是担心，你要是找到她也一定要告诉我啊！\n");

	me->set_temp(QUESTDIR3+"wangyouyu",1);
	call_out("hunting",10+random(10));
	return "我现在去找她还是不找呢？！\n";
}
