//update by cool 98.2.18
//added by tangfeng 2004
inherit F_MASTER;
inherit NPC;
#include <ansi.h>

#define QUESTDIR "quest/天龙八部/"
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
#define QUESTDIR2 "quest/天龙八部/天龙营救篇/"
#define QUESTDIR3 "quest/天龙八部/萧峰身世篇/"
#define QUESTDIR4 "quest/天龙八部/大辽救援篇/"
#define QUESTDIR5 "quest/天龙八部/复兴天下篇/"
#define QUESTDIR6 "quest/天龙八部/武功/"

string askduanyu();
string tianlonghelp();
string asksave();
string askxiaofeng();
string askjiumozhi();

int ask_xingyue(object who);
string ask_liumai1();
string ask_liumai2();
string ask_krcg();
string ask_lmjj();

int ask_dudan(object who);   

void create()
{
		object ob;
        set_name("枯荣长老", ({ "kurong zhanglao","kurong","zhanglao"}) );
        set("nickname", "天龙寺长老");
		set("long", 
" 枯荣长老面容奇特之极，左边的一半脸色红润，
皮光肉滑，有如婴儿，右边的一半却如枯骨，除了
一张焦黄的面皮之外全无肌肉，骨头突了出来，宛
然便是半个骷髅骨头。他在天龙寺中辈份最高，在
这里独参枯禅已数十年，天龙寺诸僧众，谁也没见
过他真面目。\n");
        set("gender", "男性" );
        set("class","bonze");   
        set("unique", 1);
        set("age", 99);
        set("str", 30);
        set("con", 27);
        set("dex", 32);
        set("int", 35);
        set("per",23);

        set("max_jing",8000);
        set("eff_jingli", 8500);
        set("max_qi", 40500);
        set("jiali",200);
        set("neili",45000);
        set("max_neili",45000); 
        set("rank_info/respect", "高僧");
        create_family("天龙寺", 12, "僧侣");
        set("combat_exp", 16350000);
        set("score", 1000);
		set("liumai-shenjian/shaoshang",1);
		 	 
		set("env/liumai","shaoshang");
        set("chat_chance_combat", 80);
        set("chat_msg_combat",({ 
                (: exert_function, "kurong" :),
				(: exert_function, "ku" :),
				(: exert_function, "rong" :),
                (: perform_action, "finger.yizhisanmai" :),
                (: perform_action, "finger.sandie" :),
        }));
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 550);
        set_skill("finger", 550);
        set_skill("whip", 500);
        set_skill("liumai-jianzhen",500);
        set_skill("cihang-bian", 500);
     
        
		set_skill("strike", 500);
        set_skill("buddhism", 200);
        set_skill("literate", 200);
        set_skill("liumai-shenjian", 150);
        set_skill("kurong-changong", 550);
        set_skill("yiyang-zhi", 550);
        set_skill("tianlong-xiang", 500);
 
        map_skill("whip", "cihang-bian");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "kurong-changong");
        map_skill("finger", "yiyang-zhi");
        map_skill("strike","kurong-changong");
        map_skill("force", "kurong-changong");
        prepare_skill("finger","yiyang-zhi"); 

        set_temp("apply/armor", 200);
        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);

        set("inquiry", ([
		"name": "贫僧就是枯荣",
		"菩提" : (: ask_xingyue :),
		"毒丹" : (: ask_dudan :),
		"枯荣禅功" : (: ask_krcg :),
		//"普云洞" : (: ask_liumai2 :), liumai/fightzhiok
		"鸠摩智拜寺" : (: ask_liumai1 :),
            		"段誉" : (: askduanyu :),
		            "大理" : "这里便是大理。",
		            "天龙寺" : "这里正是天龙寺，大理段家武学的最高之地。",
		            "天龙有难" : (: tianlonghelp :),
		            "营救" : (: asksave :),
		            "搭救" : (: asksave :),
		            "萧峰" : "江湖人称南慕容、北萧峰，端得一条好汉。",
		            "营救段誉" : (: asksave :),
		            "营救萧峰" : (: askxiaofeng :),
		            "慕容复" : "江湖人称南慕容、北萧峰，听说慕容公子年级轻轻，却无所不精。",
		            "慕容博" : "我听说是，姑苏慕容不出的杰才，可惜英年早逝。",
		            "鸠摩智" : (: askjiumozhi :),
		            "六脉神剑" : (: ask_liumai2 :),
					"参悟六脉绝技" : (: ask_lmjj :),
		]));
     
        set("env/一阳指",3);
        setup();
        /*
        if (clonep(this_object())) {
		   if (ob = carry_object("/clone/weapon/xingyue"))
		   ob->wield(); 
	    }*/
		carry_object("/d/tls/obj/jiasha")->wear();
		carry_object("/d/tls/obj/sengxie")->wear();
}

void reset()
{
	object ob;
	if (clonep() && (ob = unew(BINGQI_D("xingyue")))) {
		ob->move(this_object());
		//command("wield xingyue puti");
    }
}

#include "kurong.h"
string askjiumozhi()
{
	object me;
	me = this_player();
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "听说，大轮寺第一高僧鸠摩智将来我天龙寺佛法交流，真是我大理之幸啊。";
	}
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh");
  	  command("? "+me->query("id"));
		  return "这魔僧竟然如此欺负我大理无人，妄为吐蕃国第一佛法高僧。";
	}
	if (me->query(QUESTDIR2+"start")&& me->query(QUESTDIR2+"over"))
	{
  	  command("nod "+me->query("id"));
		return "鸠摩智妄为西域第一佛法高僧，所谓口生莲花，全是一派胡言。";
	}

	command("nod");
	return "大轮明王鸠摩智是吐蕃国的护国法王，但听说他具大智慧，精通佛法，想来武功也是惊人。";
}

string ask_krcg()
{
	object me;
	int i,j;
	me = this_player();
	if (!me->query("family")||me->query("family/master_id")!="kurong zhanglao")
	{
  		  command("? "+me->query("id"));
		  return "听说，你同我非亲非故，所为何来？";
	}
	if (me->query_skill("kurong-changong",1)<500)
	{
  		  command("kick");
  		  command("? "+me->query("id"));
		  return "你的枯荣禅功连500级都不到，还来凑什么热闹？";
	}
	if (me->query("quest/tls/kurong/pass"))
	{
  		  command("kick");
  		  command("? "+me->query("id"));
		  return "你不是已经开了么，还来啰嗦什么？";
	}
	if (time()-me->query("quest/tls/kurong/time")<86400)
	{
  		  command("sigh "+me->query("id"));
		  return "你总是这么勤快？";
    }
	i=random(10);
	j=random(me->query("kar"));
	command("say 本门枯荣禅功乃是注重防御的无上法门，若全部参悟的通，那么也能发挥最大威力，这一点你千万要记住。\n");
	command("pat "+me->query("id"));
	if( i==2 
		&& me->query("kar")<31
		&& j > 27 ) 
	{
		tell_object(me,HIY"\n你听了枯荣大师的指点，对枯荣禅功奥妙颇有心得。\n"NOR);
		tell_object(me,HIG"\n你试图将内息流转任督二脉，似乎卡在一个重要的关口，堵在哪儿。\n"
			           HIR+"\n你只觉左边一片冰凉，右侧热如烘炉，全身真气似乎要控制不住。\n"
					   HIC+"正在你不知所措之际，一旁的枯荣禅师忽然伸出手指点了你印堂穴。\n"
						 +"和膻中二穴，这股被蓄积已久的劲力宛如泄洪的潮流一样宣泄而行。\n"
						HIG +"顷刻之间，你领悟了这枯荣禅功的亦枯亦荣的最高境界。\n"NOR);
		me->set("quest/tls/kurong/pass",1);
		log_file("quest/kurong", sprintf("%8s(%8s) 失败%d次后，参悟透枯荣禅功最高境界。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n",
			me->name(1),me->query("id"), me->query("quest/tls/kurong/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));
		me->set("title",HIY"枯荣禅功传人"NOR);
		
		return "恭喜解密枯荣禅功成功!\n";
		//me->add(QUESTDIR4+"shenzhao",1);//
	}
	
   else
	{
		log_file("quest/kurong", sprintf("%8s(%8s) 解密枯荣禅功最高境界失败%d次！。随机数i取值：%d|随机富源j取值：%d|当前富源取值：%d|经验：%d。\n", 
			me->name(1),me->query("id"), me->query("quest/tls/kurong/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"你听了枯荣长老的指点，可是对枯荣禅功的奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/tls/kurong/fail",1);
		me->set("quest/tls/kurong/time",time());
		me->start_busy(1+random(3));
		
		return "非常遗憾解密枯荣禅功最高境界亦枯亦荣失败"+me->query("quest/tls/kurong/fail")+"次。\n";
	}

}
string askxiaofeng()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR3+"start"))
  {
  	  command("hoho");
  		return "江湖人称南慕容、北萧峰，端得一条好汉，何来援救之说。";
  }
	if (me->query(QUESTDIR3+"start") && !me->query(QUESTDIR3+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }

	if (me->query(QUESTDIR3+"bad"))
	{
  	  command("heng");
  	  command("? "+me->query("id"));
		  return "乔峰，难不是你所迫出中原，今日所谓搭救不知何意！";
  }
	if (me->query(QUESTDIR3+"start") && me->query(QUESTDIR3+"over")&& !me->query(QUESTDIR4+"start"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }
	if (me->query(QUESTDIR4+"start")&& !me->query(QUESTDIR4+"over"))
	{
  	  command("nod "+me->query("id"));
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }
	if (me->query(QUESTDIR4+"start") && me->query(QUESTDIR4+"over"))
	{
  	  command("haha "+me->query("id"));
		  return "听说那一战，"+me->query("name")+"更是威震武林，端得厉害啊。";
  }
  command("hoho");
	return "江湖人称南慕容、北萧峰，端得一条好汉，何来援救之说。";
}
string asksave()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"start") &&!me->query(QUESTDIR2+"start"))
  {
  	  command("hoho");
  		return "小王子素来不喜武学，只爱佛法易经，平易近人，何来援救之说？";
  }
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说，前段时间小王子和镇南王又是吵架一番，至今未有回家，不知"+RANK_D->query_respect(me) +"可否帮助打听一下。";
  }
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
  }
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "我佛慈悲。只是自从万劫谷回来，小王子精神恍惚，不知所中何毒还是受何种内伤。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "我佛慈悲。小王子自万劫谷回来，总是气血不定，内力怪异，才被送往我天龙寺求救来了。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "我佛慈悲。竟然惹出鸠摩智这等高手，但愿王子吉人天相啊。";
	}
	command("hoho");
	return "小王子素来不喜武学，只爱佛法易经，平易近人，何来援救之说？";
}
string askduanyu()
{
	object me;
	me = this_player();
	if(!me->query(QUESTDIR1+"start" )&&!me->query(QUESTDIR2+"start"))
	{
  	  command("hoho");
  		return "你问誉儿啊，他是镇南王正淳的公子，听说天资聪明，生性淳厚，只是素来不喜武学，只爱佛法易经。";
	}
	if (me->query(QUESTDIR1+"start") && !me->query(QUESTDIR1+"wuliangover")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说，前段时间小王子和镇南王又是吵架一番，至今未有回家。";
	}
	if (me->query(QUESTDIR1+"start") && me->query_temp(QUESTDIR1+"yingjiu")&& !me->query(QUESTDIR1+"over"))
	{
  	  command("sigh");
  	  command("shrug "+me->query("id"));
		  return "听说这件事情，只是天龙寺向来不涉及武林之争。";
	}
	if (me->query(QUESTDIR1+"start") && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"start"))
	{
  	  command("thank "+me->query("id"));
		  return "我佛慈悲。多谢"+RANK_D->query_respect(me) +"搭救小王子。";
	}
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over")&& !me->query_temp(QUESTDIR2+"caught"))
	{
  	  command("sigh "+me->query("id"));
		  return "我佛慈悲。小王子自万劫谷回来，总是气血不定，内力怪异，才被送往天龙求救来了。";
	}
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("sigh "+me->query("id"));
		  return "我佛慈悲。竟然惹出鸠摩智这等高手，但愿王子吉人天相啊。";
	}
	command("hoho");
	return "你问誉儿啊，他是镇南王正淳的公子，听说天资聪明，生性淳厚。";
}
string tianlonghelp()
{
	object me;
	me = this_player();
  if(!me->query(QUESTDIR1+"over"))
  {
  	  command("haha");
  		return "天龙寺是我段家武学的最高之地，高手众云，请不要危言耸听。";
  }
	if (me->query(QUESTDIR1+"over") && !me->query(QUESTDIR2+"start"))
	{
  	  command("nod "+me->query("id"));
		  return "听说，大轮寺高僧鸠摩智不日将来我天龙寺，不知是喜是祸。";
  }
	if (me->query(QUESTDIR2+"start") && !me->query(QUESTDIR2+"over"))
	{
  	  command("heng");
		  return "我佛慈悲。这魔僧竟然如此欺负我大理无人，妄为吐蕃国第一佛法高僧。";
  }
	if (me->query(QUESTDIR2+"over"))
	{
  	  command("thank "+me->query("id"));
		  return "我佛慈悲。多谢"+RANK_D->query_respect(me) +"化解这场天龙危机，还将我大理小王子得以解救。";
  }
  command("hoho");
	return "我佛慈悲。天龙寺是我段家武学的最高之地，高手众云，请不要危言耸听。";
}
//六脉起步阶段

string ask_liumai1()
{
    object ob;
    
	ob=this_player();
	
	if(!ob->query("quest/天龙八部/天龙营救篇/over"))
		return "你需要先把段誉救回来再说,完成天龙营救篇。\n";
    if (ob->query("family/family_name")!="天龙寺" || ob->query("family/master_id")!="kurong zhanglao")
		return "你不是我的弟子，所为何来？\n";
	
	
	if (ob->query("yyz/degree")>3)
	{
		command("say 只有一阳指达到四品以上方可修一阳指，你还差的远呢。\n");			

	}
		
	if ((time()-ob->query("quest/tls/liumai_1/time"))<86400)
	{
		command("say 今天的机会已经没了，明天再来。\n");
		return "";
	}

	if (ob->query("quest/tls/liumai_1/pass"))
	{
		command("say 你不是解开一脉了额么？。\n");
		return "";
	}		
		
	command("say 正好，大轮寺掌门鸠摩智来访，我看他来者不善，你与我一起去到牟尼堂看看。\n");
	ob->set_temp("tls/fight1",1);
	return "阿弥陀佛！ \n";	
	
}

int prevent_learn(object ob, string skill)
{
	if (skill == "yiyang-zhi"){
		command("一阳指乃是我大理国镇国之宝，非做出巨大贡献者不得而传。\n");
		return 1;
	}
	return 0;
}