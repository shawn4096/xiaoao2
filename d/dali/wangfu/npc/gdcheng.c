// gdcheng.c
// Modify By River 98/12 
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_jueji();

void create()
{
        set_name("古笃诚", ({ "gu ducheng", "gu", "ducheng" }));
        set("title", "大理国镇南王府家将");
        set("gender", "男性");
        set("age", 33);
        set("str", 37);
        set("dex", 26);
        set("per", 20);
        set("long", "这人身穿军服，手持两柄板斧，威风凛凛。\n");
        set("combat_exp", 4500000);
        set("shen_type", 1);
        set("attitude", "friendly");
        //create_family("大理", 3 , "弟子");
		create_family("天龙寺", 15 , "俗家弟子");
        set_skill("cuff", 90);
        set_skill("qiantian-yiyang", 350);
        set_skill("tianlong-xiang", 350);
        set_skill("pangen-fu", 350);
        set_skill("duanjia-quan", 350);
        set_skill("force", 350);
        set_skill("axe", 350);
        set_skill("dodge", 350);
        set_skill("parry", 350);
        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/armor", 70);
        set_temp("apply/damage", 20);
        map_skill("force", "qiantian-yiyang");
        map_skill("cuff", "duanjia-quan");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "pangen-fu");
        map_skill("axe", "pangen-fu");
        prepare_skill("cuff","duanjia-quan");
        set("chat_chance_combat", 30);
	    set("chat_msg_combat", ({
				(: exert_function, "yiyang" :),
                (: perform_action, "axe.pangen" :),
				(: perform_action, "axe.cuojie" :),
				(: perform_action, "axe.jingtian" :),
        	       
	    }));
		set("inquiry", ([
				"盘根错节绝技" : (: ask_jueji :),
		]));
        set("max_qi", 15000);
        set("neili", 6000); 
        set("max_neili", 6000);
        set("jing", 6600);
        set("max_jing", 6060);
        set("eff_jingli", 6600);
        set("jiali", 150);

        setup();
        carry_object(__DIR__"obj/banfu")->wield();
        carry_object("/d/dali/npc/obj/zipao")->wear();
}

void attempt_apprentice(object ob)
{
	
	if ((string)ob->query("gender") != "男性" ){
		command ("say 我向来不收女弟子或公公，别来烦我！");
		return;
	}
	if ((string)ob->query("class")=="bonze" ){
		command ("say 阿弥陀佛！我不收出家弟子。");
		return;
	}
	if ((int)ob->query_skill("qiantian-yiyang", 1) < 200 ){
		command("say 古某人我不收练功不勤之人，你还是多练练你的乾天一阳到200吧。");
		return;
	}
	if ((int)ob->query_skill("duanjia-quan", 1) < 200 ){
		command("say 古某人我不收练功不勤之人，你还是多练练你的段家拳到200吧。");
		return;
	}
	if ((int)ob->query_skill("force", 1) < 200 ){
		command("say 古某人不收练功不勤之人，你还是多练练你的基本内功到200吧。");
		return;
	}
	if ((int)ob->query("shen") < 20000){
		command("say 大理段氏乃是名门正派，你不足20k正神别来找我。");
		return;
	}
    if( (int)ob->query("family/generation")<15){
		command("sigh ");
		command("say "+RANK_D->query_respect(ob)+"你已经有前辈名师教导，怎敢再收你为徒？");
		return;
	}
	command("say 真不错的一个苗子，本师的一身武功俱都在把斧头上，你以后可要好好用心了。\n");
	command("say 既然有缘我就收下你了！\n");
	command("haha ");
	command("recruit " + ob->query("id"));
	//ob->set("title", "天龙寺第十三代俗家弟子");
	return;
}

string ask_jueji()
{
	object me;
	int i,j;

	me=this_player();
	if (me->query_skill("axe",1)<200)
	{
		command("say 你的基本斧法不足200，告诉你也学不会！\n");
		return "谁的斧头狠谁就说了算！\n";
	}
	if (me->query("quest/tls/pgf/pangen/pass"))
		return "你不是已经把盘根错节绝技学完了!\n";
	if (me->query_skill("pangen-fu",1)<200)
	{
		command("say 你的盘根错节斧法不足200，告诉你也学不会！\n");
		return "谁的斧头狠谁就说了算！\n";
	}
	if (time()-me->query("quest/tls/pgf/pangen/time")<86400)
		return "你来此太频繁了，这样对武功修炼不够！\n";
	if (me->is_busy())
		return "你正在手忙脚乱中！\n";
		command("say 盘根错节斧乃是我的看家本领，全凭一口真气流转，你想学我就告诉你？\n");
		command("say 好小子，既然你有如此癖好，你听好了！\n");
		  j = 20;
		  if(me->query("m-card-vip")) j =  18;
		  if(me->query("y-card-vip")) j =  15;
		  if(me->query("buyvip"))     j =  10;
		  i=random(j);

		  if (i<5 
			 && me->query("kar")<31
			 && random(me->query("kar"))>24)
		  {       
			  tell_object(me,HIC"\n你按照古笃诚的指点将浑身真气注入手臂中，手中的斧头顿时轻了许多！\n"NOR);
			  message_vision(HIR"\n$N对如何使用这个斧头的技巧一下子豁然贯通。”\n"NOR,me); 
			  tell_object(me,HIG"恭喜您解密盘根错节斧绝技成功！\n"NOR);
			  me->set("quest/tls/pgf/pangen/pass",1);
			  log_file("quest/tlspangen", sprintf("%s(%s) 失败%d次成功解开盘根斧。富源：%d；经验：%d。\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/tls/pgf/pangen/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			  me->start_busy(1);
			}
			else
			{
			 tell_object(me,HIG"\n你沉思许久，不得要领。\n"NOR);
			 message_vision(HIC"\n$N摇了摇头，深深地叹了口气,觉得自己真实笨死了。\n"NOR,me); 
			 tell_object(me,HBBLU"\n很可惜，你本次尝试盘根绝技秘密失败！\n"NOR);
			 tell_object(me,HBBLU"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
			 tell_object(me,HBBLU"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
			 log_file("quest/tlspangen", sprintf("%s(%s) 解密盘根斧绝技失败%d次。富源：%d；经验：%d。\n",   
			  me->name(1),
			  me->query("id"), 
			  me->query("quest/tls/pgf/pangen/fail"),
			  me->query("kar"),
			  me->query("combat_exp")) );
			 me->add("quest/tls/pgf/pangen/fail",1);
			 me->set("quest/tls/pgf/pangen/exp", me->query("combat_exp") );
			 me->start_busy(1);
			 me->set("quest/tls/pgf/pangen/time",time());
			}
		me->delete_temp("quest/tls");
		return "一斧头就够了！\n";
	 
		
}