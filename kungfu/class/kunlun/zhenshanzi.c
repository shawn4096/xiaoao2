// zhenshanzi.c (笑傲)
// By sohu
inherit NPC;
//inherit F_MASTER;
#include <ansi.h>
string ask_duanyun();
string ask_zhenshen();

void create()
{
	set_name("震山子", ({ "zhen shanzi", "zhen" }));
	set("title", "昆仑派长老");
        set("nickname", HIC"乾坤一剑"NOR);
	set("long",
		"他就是昆仑派长老、名扬江湖的乾坤一剑震山子。\n"
		"虽然年纪已大，但仍然看得出他年轻时英俊潇洒。\n");
	set("gender", "男性");
	set("age", 40);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);

	set("max_qi", 23500);
	set("max_jing", 7000);
	set("neili", 29000);
	set("max_neili", 29000);
	set("eff_jingli", 7000);
	set("jiali", 200);
	set("combat_exp", 12500000);
	set("score", 4000);
	set_skill("art", 200);
    set_skill("literate", 250);
	set_skill("force", 500);
	set_skill("xuantian-wuji", 500);
	set_skill("dodge", 500);
	set_skill("taxue-wuhen", 500);
	set_skill("parry", 500);
	set_skill("sword", 500);
	set_skill("liangyi-jue", 200);
	set_skill("xunlei-jian", 500);
	set_skill("cuff", 500);
	set_skill("zhentian-quan", 500);
	set_skill("leg", 500);
	set_skill("chuanyun-tui", 500);

	map_skill("force", "xuantian-wuji");
	map_skill("leg", "chuanyun-tui");
	map_skill("dodge", "taxue-wuhen");
	map_skill("cuff", "zhentian-quan");
	map_skill("parry", "xunlei-jian");
	map_skill("sword", "xunlei-jian");
	set("chat_chance_combat", 70);
	set("chat_msg_combat", ({
  		(: perform_action, "sword.podi" :),
  		(: perform_action, "sword.benlei" :),
		(: perform_action, "sword.sanqiu" :),
		(: exert_function, "wuji" :),			
  		(: perform_action, "dodge.taxue" :),
	}));
	prepare_skill("cuff", "zhentian-quan");
	prepare_skill("leg", "chuanyun-tui");

    create_family("昆仑派", 2, "门中长老");
	set("class", "taoist");

	set("inquiry", ([
		"峭壁断云" : (: ask_duanyun :),
	//	"震山拳技巧" : (: ask_zhenshan :),
		
	]));


	setup();
	carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/kunlun/obj/pao2.c")->wear();
}

string ask_duanyun()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="昆仑派")
	{
		return "你的不是昆仑派，难道不怕死么？！\n";
	}
	if (me->query_skill("liangyi-jian",1)<350)
	{
		return "你的两仪剑等级不足350，告诉你也没用！\n";
	}
	if (me->query("quest/kl/lyj/duanyun/pass"))
	{
		return "你的两仪剑“峭壁断云已经解开了”！\n";
	}
	if (time()-me->query("quest/kl/lyj/duanyun/time")<86400)
	{
		return "你来的太频繁了，明天再来！\n";
	}
	if (!me->query("quest/kl/dichuan"))
	{
		return "你竟然不是昆仑嫡传弟子？！\n";
	}

	message_vision(HIC"$N严肃的看着$n，慢慢说道：“我派的两仪剑讲究的剑走轻灵，和其他门派都不太相同。\n"
						"你既然到达如此程度，我就传给你这招峭壁断云的奥秘，我给你演示一遍，看你自己的悟性了。\n"+
				   HIR"\n\n\n$N缓缓抽出一柄长剑，纵身跃起，如峭壁断云泻下，看的$n心旌神摇\n"NOR,this_object(),me);
	
 
    i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	j=random(me->query("kar"));
	command("say 你看懂了么。\n");
	command("pat "+me->query("id"));
	if( i<5
		&& me->query("kar")<31
		&& j >= 26 ) 
	{
		tell_object(me,HIY"\n你听了的震山子长老的亲自指点，联想起早期自己所用两仪剑的种种心得，两下印照。\n"NOR);
		tell_object(me,HIG"\n你剑招连连，宛如长江大河，滔滔不绝，一出手剑招即为连环招式，下意识的出招。\n"
			             +"招式看似繁复，但大多数招式你已经了然若胸，信手拈来，连绵不绝。\n"
						 +"你终于领悟了这门峭壁断云的运用法门。心中大喜。\n"NOR);
		me->set("quest/kl/lyj/duanyun/pass",1);
		log_file("quest/lyjduanyun", sprintf("%8s(%8s) 失败%d次后，学到峭壁断云,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/duanyun/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "恭喜解密峭壁断云绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/lyjduanyun", sprintf("%8s(%8s) 解密峭壁断云绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/duanyun/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了震山子长老的指点，可是对两仪剑决峭壁断云的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/lyj/duanyun/fail",1);
		me->set("quest/kl/lyj/duanyun/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密两仪剑之峭壁断云失败"+me->query("quest/kl/lyj/duanyun/fail")+"次。\n";
	}


}
/*
string ask_zhenshan()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="昆仑派")
	{
		return "你的不是昆仑派，难道不怕死么？！\n";
	}
	if (me->query_skill("zhenshan-quan",1)<200)
	{
		return "你的镇山拳等级不足200，告诉你也没用！\n";
	}
	if (me->query("quest/kl/zsq/zhenshan/pass"))
	{
		return "你的镇山拳的奥秘已经解开了”！\n";
	}
	if (time()-me->query("quest/kl/zsq/zhenshan/time")<86400)
	{
		return "你来的太频繁了，明天再来！\n";
	}

	message_vision(HIC"$N严肃的看着$n，慢慢说道：“我派的两仪剑讲究的剑走轻灵，和其他门派都不太相同。\n"
						"你既然到达如此程度，我就传给你这招峭壁断云的奥秘，我给你演示一遍，看你自己的悟性了。\n"+
				   HIR"\n\n\n$N缓缓抽出一柄长剑，纵身跃起，如峭壁断云泻下，看的$n心旌神摇\n"NOR,this_object(),me);
	
 
    i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	j=random(me->query("kar"));
	command("say 你看懂了么。\n");
	command("pat "+me->query("id"));
	if( i<5
		&& me->query("kar")<31
		&& j >= 26 ) 
	{
		tell_object(me,HIY"\n你听了的震山子长老的亲自指点，联想起早期自己所用两仪剑的种种心得，两下印照。\n"NOR);
		tell_object(me,HIG"\n你剑招连连，宛如长江大河，滔滔不绝，一出手剑招即为连环招式，下意识的出招。\n"
			             +"招式看似繁复，但大多数招式你已经了然若胸，信手拈来，连绵不绝。\n"
						 +"你终于领悟了这门峭壁断云的运用法门。心中大喜。\n"NOR);
		me->set("quest/kl/lyj/duanyun/pass",1);
		log_file("quest/lyjduanyun", sprintf("%8s(%8s) 失败%d次后，学到峭壁断云,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/duanyun/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "恭喜解密峭壁断云绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/lyjduanyun", sprintf("%8s(%8s) 解密峭壁断云绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/duanyun/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了震山子长老的指点，可是对两仪剑决峭壁断云的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/lyj/duanyun/fail",1);
		me->set("quest/kl/lyj/duanyun/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密两仪剑之峭壁断云失败"+me->query("quest/kl/lyj/duanyun/fail")+"次。\n";
	}


}*/