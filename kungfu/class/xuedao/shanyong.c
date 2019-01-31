// shanyong.c 善勇
// by iceland

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string ask_hongsha();

void create()
{
        set_name("善勇", ({ "shan yong", "shanyong" ,"shan","yong"}));
        set("long",@LONG
他是血刀老祖座下二弟子，身材瘦高，脸色灰仆仆的，加上一对死鱼眼睛
看起来有些吓人。
LONG
        );
        set("title", HIR "血刀老祖座下弟子" NOR);
        set("gender", "男性");
		set("class", "huanxi");
        set("age", 42);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 28);
        set("int", 15);
        set("con", 28);
        set("dex", 28);
        set("max_qi", 21000);
        set("eff_jing", 6400);
        set("max_jing",6400);
		set("neili", 21300);
        set("max_neili", 21300);
        set("jiali", 180);
        set("combat_exp", 9400000);
        set("score", 40000);
		set("unique", 1);

        set_skill("huanxi-chan", 180);
        set_skill("literate", 180);
        set_skill("force", 450);
        set_skill("xuedao-jing", 450);
        set_skill("dodge", 450);
        set_skill("xueying-dunxing", 100);
      //  set_skill("hand", 450);
       //set_skill("hongsha-shou", 450);
        set_skill("strike", 100);
        set_skill("hongsha-zhang", 450);
        set_skill("parry", 450 );
        set_skill("xuedao-daofa", 450);
        set_skill("blade", 450 );

        map_skill("force", "xuedao-jing");
        map_skill("dodge", "xueying-dunxing");
      //  map_skill("hand", "hongsha-shou");
        map_skill("parry", "xuedao-daofa");
        map_skill("strike", "hongsha-zhang");

       // prepare_skill("hand","hongsha-shou");
        prepare_skill("strike","hongsha-zhang");
		set("inquiry",([
		"红砂掌绝技"	: (: ask_hongsha :),
		//"test"	: (: ask_test :),
	

		]));

        create_family("血刀门", 5, "弟子");
        set("class", "huanxi");

        setup();
        carry_object("/d/xueshan/npc/obj/gongde-jiasha")->wear();
        carry_object(BINGQI_D("miandao"))->wield();      

        add_money("silver",50);
}
string ask_test()
{
	command("say teset");
	//return notify_fail("tete");
	return "111";
}
void attempt_apprentice(object ob)
{
        if ((string)ob->query("family/family_name") != "血刀门") {
               command("say"+ RANK_D->query_respect(ob) +
                        "不是本门弟子，在这里捣什么乱？！");
                return;
        }

        if ((int)ob->query_skill("huanxi-chan", 1) < 150) {
                command("say 欢喜禅是各项武功之本，不足150，你再勤加修炼吧。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多钻研钻研本门的心法吧。");
                return;
        }
        if ((int)ob->query_skill("jingang-liantishu", 1) < 200) {
                command("say 金刚炼体术是各项武功之本，不足200，你再勤加修炼吧。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多练习吧。");
                return;
        }

        if ((int)ob->query_skill("xuedao-jing", 1) < 200) {
                command("say 血刀经是各项武功之本，不足200，你再勤加修炼吧。");
                command("say"+ RANK_D->query_respect(ob) +
                        "再熬几个通宵，多多练习吧。");
                return;
        }
        if (!ob->query("quest/xd/dichuan")) {
                command("say 你没有嫡传身份，我不敢收你。");
                return;
        }

        command("say 好吧，以后你就好好侍奉佛爷我吧。");
        command("recruit " + ob->query("id"));

       // ob->set("title", HIR "血刀门第六代弟子" NOR);
}


string ask_hongsha()
{

	object me;

	int i,j; 
	me = this_player();

	if(!me) return 0;
	
	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	j=random(j);
	
	if (me->query("family/family_name")!="血刀门")
	{
		return "你不是血刀门弟子，来此消遣我么？\n";
	}

	if (me->query("quest/xd/hongsha/pass"))
	{
		
		return "你已经解开了红砂血气劲这个谜题，你无缘无故来找我作甚？？\n";
	}


	if (time()-me->query("quest/xd/hongsha/time")<86400)
	{
		return "你来的太频繁了，武功最忌讳心气浮躁？？\n";
	}
	if (!me->query("quest/xd/dichuan"))
	{
		return "血刀需要的是始终如一的忠诚弟子，你非嫡传，焉能传授你高级武功？？\n";
	}
	if (me->query_skill("force",1)<200)
	{
		return "练习基本内功需要到200才能修习红砂掌绝技，还是好好修炼去吧？？\n";
	}
	if (me->query_skill("hongsha-zhang",1)<250)
	{
		return "练习红砂掌法需要到250才能修习红砂掌绝技，还是好好修炼去吧？？\n";
	}

	if (i>25
	  && j<6
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIB"\n$N磨了半天，手腕寸关穴忽然一痛，这红砂血气劲经络豁然打通。”\n"NOR,me); 
         message_vision(HIY"\n$N心中大喜，「哈哈哈」仰天大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N经过不断研磨练习领悟，终于领悟了老僧所传授的红砂血气劲的奥秘！”\n"NOR,me); 
         log_file("quest/xdhongsha", sprintf("%s(%s) 红砂血气劲解密成功！第%d次参悟，机缘巧合下，成功参悟红砂血气劲技的奥秘，随机幸运值：%d,当前随机值：%d,当前经验：%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/hongsha/fail"),
		 i,
		 j,
         me->query("combat_exp"),
		 ));

		 me->set("quest/xd/hongsha/time",time());
		 me->set("quest/xd/hongsha/pass",1);
		 return "恭喜恭喜！我大血刀前途无量\n";
     }
	 else {
	     message_vision(HIG"\n$N神情沮丧，自言自语地说道：“看来这红砂血气劲真是不好解啊，继续努力吧。”\n"NOR,me); 
		 message_vision(HIY"\n参悟红砂血气劲绝技解密失败！\n"NOR,me); 
         log_file("quest/xdhongsha", sprintf("%s(%s) 失败！参悟红砂血气劲第%d次失败，随机幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/hongsha/fail",1),
		 i,
		 j,
         me->query("combat_exp"),));        
		 me->add("quest/xd/hongsha/fail",1);
		 me->set("quest/xd/hongsha/time",time());
		 me->start_busy(2);
		 me->delete_temp("quest/xd/hongsha/modao");
		 me->delete_temp("quest/xd");
		 return "真是废物！\n";
   }
	

}