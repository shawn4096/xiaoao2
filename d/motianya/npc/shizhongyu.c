// shizhongyu.c 石中玉
//by kingso 2010 08 侠客行系列

#include <ansi.h>
inherit NPC;

string ask_name();
string ask_dingdang();

string ask_jiuyuan();
string ask_changle();
string ask_huigui();
string ask_weihe();

#define XKX_QUEST1 "quest/侠客行/摩天崖/"


void create()
{
        set_name("石中玉", ({ "shi zhongyu", "shi", "zhongyu" }));
        set("gender", "男性");
        set("age", 20);
        set("str", 15);
        set("int", 45);
        set("con", 18);
        set("dex", 20);
        set("per", 30);
        set("long", "这是一个年轻公子，大约二十左右岁，面若中秋之月，色如春晓
之花，鬓若刀裁，眉如墨画，鼻如悬胆，情若秋波，虽怒而时笑，即视而有情。\n");
        set("combat_exp", 5400000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_skill("unarmed", 350);
        set_skill("force", 350);
        set_skill("blade", 350);
        set_skill("dodge", 350);
        set_skill("parry", 350);
        set_skill("literate",100);

        set_skill("wuhu-duanmendao", 350);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/armor", 5);
        set_temp("apply/damage", 10);
        map_skill("blade", "wuhu-duanmendao");
		map_skill("parry", "wuhu-duanmendao");

        set("neili", 200);
        set("max_neili", 200);
        set("jiali", 20);
        set("inquiry", ([
                "名字" :  (: ask_name :),
                "叮当"   : (: ask_dingdang :),  
                "救援" :  (: ask_jiuyuan :),

                "长乐帮" :  (: ask_changle :), 

                "回归" :  (: ask_huigui :),  
 
                "原因" :  (: ask_weihe :),  

                "侠客岛" : "在泉州附近的一个小岛。\n",
 
                "石破天" : "我哪里知道谁是石破天，他是谁？.\n",


        ]) );
        set("chat_chance", 8);
        set("chat_msg", ({
                "\n石中玉说道: 叮当，你在哪呀，我好想你呀。\n",
                "\n石中玉叹道: 也不知道我的叮当怎么样了。\n",
                "\n石中玉说道: 腊八粥可是好东西...\n",
                "\n石中玉说道: 唉，谁能帮我杀了外面的老头，兄弟我谢谢你了！\n",

        }));
        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 10);
}

void die()
{
        say("\n石中玉说道：我还有个心愿没了，希望你能帮我照顾叮当！\n");

        message_vision("石中玉喊着叮当的名字，死了！\n", this_object());
        ::die();
}

string ask_name()
{
    object me;
    me=this_player();
   
   
   if (!me->query_temp(XKX_QUEST1+"agree"))
       return "你是哪根葱啊？凭你也想知道我的名字？！\n";

   if (me->query_temp(XKX_QUEST1+"name"))
       return "你不是已经问过我名字了么！\n";

   if ((int)me->query("combat_exp") < 1200000)
       return "就你这三脚猫的功夫省省吧！\n";

        command("say  是啊，我就是石中玉！");
        command("noshame " + me->query("id"));
      //  command("say  你是来救我的吗？！要不你跟那个死老头是一伙的？");
      me->delete_temp(XKX_QUEST1+"agree");

	  me->set_temp(XKX_QUEST1+"name", 1);
        
}
string ask_dingdang()
{
    object me;
    me=this_player();
   
   
   if (!me->query_temp(XKX_QUEST1+"name"))
       return "你是哪根葱啊？凭你也配提及叮铛的名字？！\n";

   if (me->query_temp(XKX_QUEST1+"dingdang"))
       return "你不是已经问过我名字了么,叮当又岂是你能随便叫的！\n";


        command("say 既然是叮铛派你来的，找我做什么呢？！");
        command("say  你是来救我的吗？！要不你跟那个死老头是一伙的？");
        me->delete_temp(XKX_QUEST1+"name");
		me->set_temp(XKX_QUEST1+"dingdang", 1);
        return "";
}

string ask_jiuyuan()
{
    object me;
    me=this_player();
   
   message_vision(HIY"$N说道，“石帮主好，我是受叮铛姑娘的委托过来救援你的！”\n"NOR,me);
   if (!me->query_temp(XKX_QUEST1+"dingdang"))
       return "石中玉敷衍的嗯了一声，转过身去！\n";

   if (me->query_temp(XKX_QUEST1+"jiuyuan"))
       return "唉~你这人老年痴呆啊，怎么又问我一遍？~~！\n";


        command("say  你真的是来救我的？是叮叮当当叫你来的吧？！太好了，我终于可以离开这个鸟不拉屎的地方了！");
        command("touch " + me->query("id"));
        
        me->set_temp(XKX_QUEST1+"jiuyuan", 1);
	return "居然是救我来的，是不是又是一场阴谋呢？\n";        
}
//
string ask_changle()
{
    object me;
    me=this_player();
   
   
   if (!me->query_temp(XKX_QUEST1+"jiuyuan"))
       return "我不相信你，你是如何找到叮铛的？！\n";

   if (me->query_temp(XKX_QUEST1+"changlebang"))
       return "唉~~老年痴呆啊~~~~！\n";


   command("say  什么！长。。。乐。。。帮。。。");
   command("!!! " );
   command("say  谢。。谢。。谢伯伯，救命啊~！有人要杀我啊。。");
   me->set_temp(XKX_QUEST1+"changlebang", 1);
        
}

int accept_object(object who, object obj)
{
	
	if (obj->query("id")=="bangzhu ling" 
		//&& obj->query("name")=="帮主令" 
	   // && who->query_temp(XKX_QUEST1+"start")
	    && who->query_temp(XKX_QUEST1+"changlebang")
	//	&& obj->query_temp(XKX_QUEST1+"start")
		&&obj->query("owner")==who->query("id"))
	{
		command("say 嗯，这枚令牌到是真的？\n");
		command("say 看来还真是长乐帮派你来的，是不是贝海石派你来的？ ");
		who->set_temp(XKX_QUEST1+"renke",1);
		destruct(obj);
		return 1;
	}
	
}

string ask_huigui()
{
    object me;
    me=this_player();
   
   
   if (!me->query_temp(XKX_QUEST1+"renke"))
       return "石中玉心中对你很是不信，敷衍的嗯了一声，转过身去！\n";

   if (me->query_temp(XKX_QUEST1+"huigui"))
       return "唉~你怎么又方忘记了~~~~~！\n";


        command("say  唉。。。。你既受叮当所托，应该是她朋友，是她的朋友就不会害我了。");
        command("sigh " );
        command("say  我真的不想回长乐帮，我好不容易才逃出来的。");
        command("say  可是没想到，摆脱了那么多长乐帮的追兵，跑到半路上被谢烟客当成那个什么“狗杂种”给抓上了这鸟不拉屎的地方。");
        command("say  我只想跟叮叮当当一起，我不想呆在这里啊。");
		 me->set_temp(XKX_QUEST1+"huigui", 1);
        
}

string ask_weihe()
{
    object me;
    me=this_player();
   
   
   if (!me->query_temp(XKX_QUEST1+"huigui"))
       return "我不相信你，敷衍的嗯了一声，转过身去！\n";

   if (me->query_temp(XKX_QUEST1+"weihe"))
       return "唉~~你老年痴呆啊~~~~！\n";

   if ((int)me->query("combat_exp") < 1000000)
       return "就你这三脚猫的功夫省省吧！\n";

        command("say  实话告诉你吧。");
        command("sigh " );
        command("say  长乐帮之所以要我当帮主，都是贝海石那个奸贼的阴谋。");
        command("say  你想啊，我有什么能耐？我武功那么差，也没贝老贼那些阴谋诡计，他们凭什么要我当他们的帮主？");
        command("say  刚开始，我还以为这世界上还真有天上掉馅饼这种好事呢！贝老贼放着帮主不当，要我来当？");
        command("say  后来我才知道，贝老贼他们，其实是要我到时候去接那个什么赏善罚恶令！");
        command("say  那赏善罚恶令是什么东西？后来我才知道，据说每十年有个叫侠客岛的地方，会派来两位赏善罚恶二使。");
        command("say  这两个人啊，专门到一些大门派大帮派，发这个令牌，说什么邀请去侠客岛做客，如果不接令的就要灭门。");
        command("say  三十年啦。。去的人没有一个回来的。凡没有接令的也都被灭门了。");
        command("say  你说，这不是把我当成个“顶雷”的角在利用吗？。");
        command("say  所以说，我是绝对不会跟你回去的！！！");
        me->set_temp(XKX_QUEST1+"weihe", 1);
	call_out("do_mingbai",4+random(5),me);        
}

int do_mingbai(object me)
{
	message_vision(HIR"$N认真听了石中玉的解说，明白了不少事情，但同时也陷入更大的迷惑中！\n"NOR,me);
	message_vision(HIG"谁是石破天？谁又是狗杂种？这有待于去确认！\n"NOR,me);
	message_vision(HIM"既然想不明白，就先不去想，先完成解救帮主任务再说！\n"NOR,me);
	message_vision(HIC"\n\n当下，$N不再犹豫，对石中玉说，“帮主，咱们先离开这个地方再说”！\n"NOR,me);

	me->set_temp(XKX_QUEST1+"yihuo",1);
	return 1;
}
