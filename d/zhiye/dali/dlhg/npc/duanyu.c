// duanyu.c 段誉
// COOL@SJ,990827
// Modified by tangfeng 2004
// 这里的段誉涉及到三个场景，一个在无量玉像，一个在石屋里，一个在大伦寺暗室里
// By Spiderii@ty 加入时间限制
//inherit F_MASTER;
#include <ansi.h>
inherit NPC;

int ask_liumai();

void create()
{
        set_name("段誉", ({"duan yu", "duan", "duayu"}));
        set("gender", "男性");
        set("age", 20);
		set("title",HIC"大理国镇南王世子"NOR);

        set("long", "这是一个青年男子，身穿一身淡蓝色长袍，面如珠玉，齿白唇红，气质高雅。\n"
                    "眼神极为清澈，一看就是久经熏陶而长成的世家浊世公子，哪怕身处暗室，却依旧风采宜人。\n");
        set("attitude", "peaceful");
        set("str", 40);
        set("per", 30);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        //set("no_quest", 1);

        

        set("jing", 10000);
        set("max_jing", 10000);
        set("jingli", 10000);
        set("eff_jingli", 10000);
        set("qi", 80000);
        set("max_qi", 80000);
        set("neili", 80000);
        set("max_neili", 80000);
        set("jiali",250);
		//要设定北冥、凌波参数
        
        set("combat_exp", 15000000);
        set_skill("buddhism", 250);            
        //set_skill("daode-jing", 250);                   
        set_skill("literate", 400);                
        set_skill("force", 550);                
        set_skill("beiming-shengong", 550);     
        set_skill("dodge", 550);                
        set_skill("lingbo-weibu", 550);         
        set_skill("parry", 500);
        set_skill("finger", 550);
        set_skill("yiyang-zhi", 550);
        set_skill("liumai-shenjian", 180);
        map_skill("parry", "yiyang-zhi");
        map_skill("finger", "yiyang-zhi");
        map_skill("force", "beiming-shengong");
        map_skill("dodge", "lingbo-weibu");
		prepare_skill("finger","yiyang-zhi");
		set("quest/tls/yyz/liumai/pass",1);
		set("quest/tls/yyz/zhijian/pass",1);

		set("env/liumai","shenjian");

		set("inquiry", ([
			"六脉神剑" : (: ask_liumai :),
	

        ]));
        set("chat_chance_combat", 100);
        set("chat_msg_combat",({ 
                (: exert_function, "beiming" :),
				(: perform_action, "dodge.luoshen" :),

                (: perform_action, "finger.yizhisanmai" :),
                (: perform_action, "finger.ciqu" :),
				//(: perform_action, "finger.liumai" :),
				(: perform_action, "finger.ciqu" :),
        }));

        setup();        
}



int ask_liumai()
{
	object me=this_player();
    int time;

	if(me->query("family/family_name")!="天龙寺") 
	{
		command("say 天龙寺的六脉神剑乃是天下第一等的武功！\n");
		command("say 你非我大理天龙寺弟子，来此打听这个问题是不是心存不轨？\n");
		return 1;
	}
	
	if (me->query("yyz/degree")>1)
	{
		command("say 一阳指虽说到达四品境界就可以施展六脉神剑，但毕竟是勉强，你需达到一品境界再来找我。\n");
		return 1;
	}
	if (!me->query("quest/天龙八部/大辽救援篇/over"))
	{
		command("say 天龙八部故事你还没有做完大辽救援篇，我跟你说了你也不懂。\n");
		return 1;
	}
	if (me->query("yideng/ronghe")!="pass")
	{
		command("say 你连一阳指的绝世奥秘都不领会明白，我跟你说六脉神剑你能懂么？\n");
		return 1;
	}
	if (me->query("quest/tls/yyz/liumai/pass"))
	{
		command("say 你已经懂了六脉贯通之术，还来请教什么？\n");
		me->set("title",HIG"六脉神剑传人"NOR);
		me->set("mytitle/quest/6mtitle",HIG"六脉神剑传人"NOR);
		return 1;
	}
	if (me->query("int")<40)
	{
		command("say 六脉神剑需要绝高的悟性，你先天悟性不足40，无需来此聒噪!\n");
		return 1;
	}
	if (me->query("yideng/ronghe")!="pass")
	{
		command("say 你连一阳指的绝世奥秘都不领会明白，我跟你说六脉神剑你能懂么？\n");
		return 1;
	}
	if (!me->query("quest/tls/liumai/winzhi"))
	{
		command("say 风云际会是一件说不清的事情，天龙有难，你在哪儿？\n");
		return 1;
	}
	time=time() - me->query("quest/tls/yyz/liumai/time");
	if (me->query("quest/tls/yyz/liumai/time") && time<86400)
	{
		command("say 你来的如此频繁，不嫌累么？\n");
		return 1;
	}
	command("sigh ");
	command("say 我大理原本乃是武林世家,虽然身居大理天南王位，但从未放弃过武功修习。\n");
	command("say 并凭借我大理家传武学一阳指而名扬天下。\n");
	command("say 世人皆知我大理一阳指，但殊不知我大理最厉害的武功乃是叫做“六脉神剑”的奇技！\n");
	command("say 这六脉神剑藏在天龙寺内，乃我大理不世出的武学。\n");
	command("say 是修为到了四品以后方可施展出来的一门神妙武学。\n");
	command("say 既然你想我学，你可看好了！\n");
	message_vision(HIY"$N忽然纵身而起，瞬间施展出六脉神剑的绝技！$n只见场间剑气纵横，心旌神摇！\n"NOR,this_object(),me);
	command("say 看好了！");

	   message_vision(HIC"\n$N左手小指一伸，使出「少泽剑法」，一股劲气从$P少泽穴中激射而出，指向身前$n！\n"+
							"$n只觉得一股无形剑气向你的$l激射而来，其变化精微，快绝无比，当真是忽来忽去，变化精微\n"NOR,this_object(),me);
                   message_vision(MAG"\n$N无名指一挥，拙滞古朴的关冲剑气直射而出，端端正正地刺向$n的$l,正是「关冲剑法」\n"+
									"$n感觉到那无形剑气拙滞古朴，奇正有别，委实难以架挡,无形剑气竟然使你无从躲避\n"NOR,this_object(),me);
                   message_vision(HIG"\n$N拇指一屈，食指点出，变成了「商阳剑法」，一缕剑气向$n$l刺出，其轻灵迅速，快速无比\n"+
									"那无形的剑气巧妙灵活，难以琢磨，幻化间直奔$n而来，瞬间已逼到了$跟前\n"NOR,this_object(),me);

				   message_vision(HIR"\n$N身形一恭，双手前伸，一式「中冲剑法」,双手合使，两道凌厉无比的剑气破空刺向$n的$l\n"+
										"猛然间$n感到周身大穴都被一股大开大合，气势雄伟的无形剑气所包围\n"NOR,this_object(),me);
                   message_vision(CYN"\n$N掌托于胸前，伸出右小指，一招「少冲剑法」,缓缓地点向$n的周身大穴，弹指无声，但却嗤嗤作响\n"+
										"$n待那剑气到得近前，竟是劲气弥漫，破空之声甚厉,无形剑气似‘拙’而不缓，‘缓’而不弱，有如神剑\n"NOR,this_object(),me);
                   message_vision(HIB"\n$N大拇指向前双按，「少商剑气」便如是一幅泼墨山水相似，纵横倚斜，寥寥数笔，却是剑路雄劲\n"+
									 "$n见那无形剑气颇有石破天惊、风雨大至之势，大开大阖，气派宏伟逼得$n纵高伏低，东闪西避！\n"NOR,this_object(),me);
	me->start_busy(99);
	remove_call_out("thinking");
	call_out("thinking",1,me);
	return 1;
}

int thinking(object me)
{
	int i,j,total;
	if(!me) return 0;
	
	if(me->query_temp("liumai_ask")<(13+random(3)))
    { 
	  me->add_temp("liumai_ask",1);
      if(random(2)) tell_object(me,HIG"\n你认真回想着刚才段誉的一招一式...\n"NOR);
             else tell_object(me,HIY"\n突然间，你似乎感觉抓到了什么六脉神剑的一丝感悟...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	 // remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("liumai_ask");
      total = me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  17;
	  i= random(j);
 
 
	  if(i<2 
		&& random(total)>40
		&& random(me->query("kar"))>28)
	  {
		tell_object(me,HIG"\n你按照段誉的指点，对六脉神剑的真正奥妙似乎有些心得。\n"NOR);
        tell_object(me, HIY"你按照段誉所言，内息起自“长强穴”，随后自腰俞、阳关、命门、悬枢\n+"+
"诸穴，一路沿着脊椎上升，走的都是背上督任各个要穴，然后是脊中、中枢、筋缩、至阳、\n"+
"灵台、神道、身柱、陶道、大椎、痖门、风府、脑户、强间、后顶、而至顶门的“百会穴”。\n"NOR);
		tell_object(me,BYEL+HIW"\n你历尽千辛万苦，终于得偿所愿，将六脉神剑融汇贯通。\n"NOR);
       	//me->improve_skill("wuxiang-zhi", 10+random(me->query_int()));
		command("look "+me->query("id"));
		command("pat "+me->query("id"));
		command("haha "+me->query("id"));
		me->set("quest/tls/yyz/liumai/pass",1);
		me->set("title",HIG"六脉神剑传人"NOR);
		me->set("mytitle/quest/6mtitle",HIG"六脉神剑传人"NOR);
		me->start_busy(1);
		log_file("quest/liumaishenjian", sprintf("%8s(%8s) 失败%d次后，彻底领悟六脉神剑的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/tls/yyz/liumai/fail"),i,me->query("combat_exp")) );
	  }
	  else
	  {
		me->add("quest/tls/yyz/liumai/fail",1);
		me->set("quest/tls/yyz/liumai/time",time());
		command("hehe ");
		tell_object(me,HBGRN+HIW"\n你听了段誉的指点，虽然听见了六脉神剑的奥秘，可是对六脉神剑功的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->start_busy(1);
		log_file("quest/liumaishenjian", sprintf("%8s(%8s) 六脉神剑解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/tls/yyz/liumai/fail"),i,me->query("combat_exp")) );
	   }
    	return 1;
    }

}
