// zhenshanzi.c (笑傲)
// By sohu
inherit NPC;
//inherit F_MASTER;
#include <ansi.h>
string ask_feihua();
string ask_xu();

void create()
{
	set_name("苦柏道人", ({ "kubai daoren", "kubai", "daoren" }));
	set("title", "昆仑派长老");
        set("nickname", HIC"昆仑长青"NOR);
	set("long",
		"他就是昆仑派长老、名扬江湖的昆仑名宿苦柏道人。\n"
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
	set_skill("dodge", 550);
	set_skill("taxue-wuhen", 550);
	set_skill("parry", 500);
	set_skill("sword", 500);
	set_skill("liangyi-jue", 200);
	set_skill("xunlei-jian", 500);
	set_skill("cuff", 500);
	set_skill("zhentian-quan", 500);
	set_skill("kunlun-zhang", 500);
	set_skill("strike", 500);

	map_skill("force", "xuantian-wuji");
	map_skill("strike", "kunlun-zhang");
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
	prepare_skill("strike", "kunlun-zhang");

    create_family("昆仑派", 2, "门中长老");
	set("class", "taoist");

	set("inquiry", ([
		"雨打飞花绝技" : (: ask_feihua :),
		"昆仑掌蓄劲绝技" : (: ask_xu :),
		//"昆仑掌叠掌" : (: ask_diezhang :),

		//"琴技入门技巧" : (: ask_qinji :),
	//	"苏习之" : (: ask_su :),
		//"追杀" : (: ask_ding :),
	]));


	setup();
	carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/kunlun/obj/pao2.c")->wear();
}

string ask_feihua()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="昆仑派")
	{
		return "你的不是昆仑派，难道不怕死么？！\n";
	}
	if (me->query_skill("liangyi-jian",1)<450)
	{
		return "你的两仪剑等级不足450，告诉你也没用！\n";
	}
	if (me->query("quest/kl/lyj/feihua/pass"))
	{
		return "你的两仪剑“雨打飞花已经解开了”！\n";
	}
	if (time()-me->query("quest/kl/lyj/feihua/time")<86400)
	{
		return "你来的太频繁了，明天再来！\n";
	}
	if (!me->query("quest/kl/dichuan"))
	{
		return "你竟然不是昆仑嫡传弟子？！\n";
	}

	message_vision(HIC"$N严肃的看着$n，慢慢说道：“我派的两仪剑讲究的剑走轻灵，和其他门派都不太相同。\n"
						"你既然到达如此程度，我就传给你这招雨打飞花的奥秘，我给你演示一遍，看你自己的悟性了。\n"+
				   HIR"\n\n\n$N缓缓抽出一柄长剑，纵身跃起，如雨打飞花泻下，看的$n心旌神摇\n"NOR,this_object(),me);
	
 
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
		tell_object(me,HIY"\n你听了的苦柏道人长老的亲自指点，联想起早期自己所用两仪剑的种种心得，两下印照。\n"NOR);
		tell_object(me,HIG"\n你剑招连连，宛如长江大河，滔滔不绝，一出手剑招即为连环招式，下意识的出招。\n"
			             +"招式看似繁复，但大多数招式你已经了然若胸，信手拈来，连绵不绝。\n"
						 +"你终于领悟了这门雨打飞花的运用法门。心中大喜。\n"NOR);
		me->set("quest/kl/lyj/feihua/pass",1);
		log_file("quest/lyjfeihua", sprintf("%8s(%8s) 失败%d次后，学到雨打飞花,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/feihua/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "恭喜解密雨打飞花绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/lyjfeihua", sprintf("%8s(%8s) 解密雨打飞花绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/feihua/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了苦柏道人长老的指点，可是对两仪剑决雨打飞花的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/lyj/feihua/fail",1);
		me->set("quest/kl/lyj/feihua/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密两仪剑之雨打飞花失败"+me->query("quest/kl/lyj/feihua/fail")+"次。\n";
	}


}

string ask_xu()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="昆仑派")
	{
		return "你的不是昆仑派，难道不怕死么？！\n";
	}
	if (me->query_skill("kunlun-zhang",1)<500)
	{
		return "你的昆仑掌等级不足500，告诉你也没用！\n";
	}
	if (me->query("quest/kl/klz/xu/pass"))
	{
		return "你的蓄劲技巧已经解开了”！\n";
	}
	if (time()-me->query("quest/kl/klz/xu/time")<86400)
	{
		return "你来的太频繁了，明天再来！\n";
	}
	if (!me->query("quest/kl/dichuan"))
	{
		return "你竟然不是昆仑嫡传弟子？！\n";
	}

	message_vision(HIC"$N严肃的看着$n，慢慢说道：“我派的昆仑掌讲究的臂力和功力深厚，和其他门派都不太相同。\n"
						"你既然到达如此程度，我就传给你这招蓄劲的奥秘，我给你演示一遍，看你自己的悟性了。\n"+
				   HIR"\n\n\n$N纵身跃起，双掌运功发力，看的$n心旌神摇！\n"NOR,this_object(),me);
	
 
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
		tell_object(me,HIY"\n你听了的苦柏道人长老的亲自指点，联想起早期自己所用昆仑掌的种种心得，两下印照。\n"NOR);
		tell_object(me,HIG"\n你终于领悟了这门昆仑掌蓄力的运用法门。心中大喜。\n"NOR);
		me->set("quest/kl/klz/xu/pass",1);
		log_file("quest/klzxu", sprintf("%8s(%8s) 失败%d次后，学到昆仑掌蓄力,彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/klz/xu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "恭喜解密昆仑掌蓄力绝技成功!\n";
		
	}	
   else
	{
		log_file("quest/klzxu", sprintf("%8s(%8s) 解密昆仑掌蓄力绝技失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/kl/klz/xu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了苦柏道人长老的指点，可是对昆仑掌蓄力的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/klz/xu/fail",1);
		me->set("quest/kl/klz/xu/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密昆仑掌蓄力失败"+me->query("quest/kl/klz/xu/fail")+"次。\n";
	}


}