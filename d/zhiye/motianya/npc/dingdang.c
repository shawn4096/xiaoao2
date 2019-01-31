// dingdang.c 丁当
//by kingso 2010 08 侠客行系列

#include <ansi.h>
inherit NPC;
string inquiry_yu();
string ask_yu();
string ask_jiejiu();
#define XKX_QUEST1 "quest/侠客行/摩天崖/"

void create()
{
        set_name("丁当", ({ "ding dang","ding"}) );
        set("gender", "女性" );
        set("age", 18);
        set("long", "一个十七八岁的少女，身穿淡绿衫子，一张瓜子脸，秀丽美艳。\n");
        set("shen_type", 1);
        set("combat_exp", 4500000);
        set("str", 28);
        set("dex", 22);
        set("con", 25);
        set("int", 35);
        set("per",30);
        set("attitude", "friendly");

        set("qi", 12000);
        set("max_qi", 12000);
        set("jing", 2000);
        set("max_jing", 2000);
		set("max_jingli", 4000);
        set("neili", 12000);
        set("max_neili", 12000);
        set("jiali", 150);

        set_skill("force", 350);
        set_skill("unarmed", 350);
        set_skill("parry", 350);
        set_skill("dodge", 350);
        set_skill("taiji-shengong", 350);
        set_skill("taiji-quan", 350);
        set_skill("tiyunzong", 350);

        map_skill("force","taiji-shengong");
        map_skill("cuff","taiji-quan");
        map_skill("parry","taiji-quan");
        map_skill("dodge","tiyunzong");
        prepare_skill("cuff","taiji-quan");

		set("chat_chance", 10);
        set("chat_msg", ({

                CYN"丁当念叨着: 也不知道我的玉哥哥现在怎么样了。\n"NOR,
                CYN"丁当暗暗抹了把眼泪。\n"NOR,
                CYN"丁当一跺脚，说道: 不行，我要上摩天崖把我的玉哥哥救回来。\n"NOR,
                CYN"丁当叹了口气，说道: 要是有玄铁令就好了。\n"NOR,
        }));
        set("inquiry",([
                "石中玉" :  (: ask_yu :),
                "解救" : (: ask_jiejiu :),
                "摩天崖" : "前面这座山就是了，你要小心呀，那个老头的武功好强呀。",
                "玄铁令" : "据说是在石破天手里，真假我就不知道了。",
        ]));
        setup();
        carry_object(ARMOR_D("changqun"))->wear();

        add_money("gold", 2);
}

string ask_yu()
{
		object me;
		me=this_player();
   
   
	   if (!me->query(XKX_QUEST1+"start"))
	   {
			command("say 我很想我的玉哥哥!\n");
			return "呜呜。。。我的玉哥哥。。。我好想他。。。！\n";
	   }
	   if (me->query_temp(XKX_QUEST1+"jiejiu"))
			return "呜呜。。。我不是跟你说了吗？还问？你烦不烦啊！\n";

	   if ((int)me->query_skill("force",1) < 500)
			return "就你这三脚猫的功夫省省吧！\n";

        command("say  呜呜呜~~~！玉哥哥被那个臭老头抓到摩天崖上面关起来了。。。呜呜呜~~~！");
        command("cry " + me->query("id"));
        command("say  怎么办啊要想个办法救救玉哥哥啊！可是那个臭老头，死老头武功那么高，摩天崖我又上不去~！");
		command("say 要是我三爷爷，四爷爷在我就不怕了，可是怎么救玉哥哥呢？");
        me->set_temp(XKX_QUEST1+"askyu", 1);
        return "谁要是帮我救了我的玉哥哥，我就一定好好报答他！\n";
}

string ask_jiejiu()
{
    object me;
    object ob;
    me=this_player();
   
   
   if (!me->query_temp(XKX_QUEST1+"askyu"))
       return "你能有什么办法啊？就算你能上得去摩天崖，你也打不过那个臭老头啊！\n";

   if (me->query_temp(XKX_QUEST1+"jiejiu"))
       return "我不是告诉你了吗？只有这个办法了！\n";

   if ((int)me->query("combat_exp") < 1200000)
       return "就你这三脚猫的功夫省省吧！\n";

   command("say  嘿对了。。我有办法了！");
   command("grin " + me->query("id"));
   command("whisper "+ me->query("id") +" 我跟你说吧，咱们这样子。。。既然打不过那个臭老头我们就要智取，对吧？\n");
   command("whisper "+ me->query("id") +" 既然打不过，我就先去把那老头引走，你去救玉哥哥好不好？!!\n");
   command("whisper "+ me->query("id") +" 你来帮我好不好？求求你了!!\n");
   command("cry ");

 //  command("whisper "+ me->query("id") +" 我这里有一包迷魂散，是先前，不四爷爷给我防身用的，药力十分强劲，只要吸进去一点点，都要昏睡一整天呢!!\n");
 //  command("whisper "+ me->query("id") +" 你上去后，看见了谢烟客，等靠近点就撒一点点在附近的空气中，一会他就会晕过去的。\n");
   command("beg1 " + me->query("id"));
 //  ob = unew("/d/motianya/obj/mhs");
  // ob ->move(me);
 //  command("rumor 听说"+ me->name(1)+ "从叮当那里获得了一包"+ ob->name(1)+ "。");  
   me->set_temp(XKX_QUEST1+"jiejiu", 1);
   add_action("do_answer","answer");
   return "求求你了！\n";   
}

int do_answer(string arg)
{
	object me=this_player();
	if (!me->query_temp(XKX_QUEST1+"jiejiu"))
	{
		return notify_fail("你得不得不,瞎答应什么？");
	}

	if (!arg||arg!="yes")
	{
		
		return notify_fail("你冷冷地拒绝了叮铛的请求！叮铛嚎啕大哭，转身而去\n");
	}
	command("jump ");
	command("say 真是太好了，有你这么相助，我一定回把玉哥哥就出来的！\n");
	command("say 我先去吧那老头引走，你直接去救玉哥哥！然后我们在长乐帮见？\n");
	me->set_temp(XKX_QUEST1+"agree", 1);

	command("");
}
