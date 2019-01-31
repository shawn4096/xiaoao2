inherit NPC;
#include <ansi.h>

//ob->query("birthday")< =1305041966


int ask_bagua();
int ask_liwu();
int ask_chunjie();
int ask_quanfa();
int ask_jiangli();
int ask_vip();
int ask_down();
int ask_down1();

int ask_qingming();
int ask_51();
int ask_zhongqiu();
int ask_nianka();
int ask_guoqing();
int ask_xiaonian();
int ask_yuanxiao();
int ask_yueka();
int ask_downji();
int ask_title();
int ask_duanwu();
int do_answer(string arg);
void create()
{
        set_name("巫师",({  "wizard", "wushi" }) );
        set("gender", "男性" );
        set("age", 30);
        set("long", "这是一个笑傲江湖巫师组召唤出来的巫师，偶尔协助巫师做点事，大部分的时间都是无所事事。\n");

        set("str", 17);
        set("dex", 16);
        set("con", 15);
        set("int", 17);
        set("shen_type", 1);
        set("combat_exp", 100);
        set("attitude", "peaceful");
        setup();

        set("inquiry", ([
            //  "2018元旦礼物":   (: ask_liwu  :),
		  //"小年礼物":   (: ask_xiaonian  :),
		//	"元宵节大团圆闹元宵稳定祥和过完团圆年":   (: ask_yuanxiao  :),

			  //"祝福2018年狗年旺运大吉大利":   (: ask_chunjie  :),
	//			   "清明节敬祖和第二波宕机补偿":   (: ask_qingming  :),
         //     "向五一劳动节坚持挂机的兄弟姐们致敬":   (: ask_51  :),
			//   "年卡贵宾":   (: ask_nianka  :),
			  "月卡贵宾":   (: ask_yueka  :),
             // "奇门八卦":   (: ask_bagua   :),
             // "新手拳法":   (: ask_quanfa  :),
		//	  "中秋月饼":   (: ask_zhongqiu  :),
              //"高手进阶":   (: ask_jiangli :),
              //"贵宾专享":   (: ask_vip :),
			   "国庆节中秋开心":   (: ask_guoqing :),
			//	"端午节粽子":   (: ask_duanwu :),
    //          "当机补偿第一波":   (: ask_down1 :),
			//"恢复名誉":   (: ask_title :),
		//	"当机补偿":   (: ask_downji :),
        ]) );

        carry_object("/clone/misc/cloth")->wear();
}
int ask_title()
{
	object me=this_player();
	message_vision(HIM"$N只能获得你已经解密后的title,想恢复什么title?如果想好了可以输入"HIC"(answer xxxx)"HIM"就可以了!\n"+
					"当前可以选项为如下内容:\n"+
					HIC"\t\t\t九阴真经上册----answer 九阴真经\n"+
					HIC"\t\t\t凌波微步--------answer 凌波微步\n"+
					HIC"\t\t\t星宿追魂夺命--------answer 星宿追魂夺命\n"+
					HIC"\t\t\t吸星大法融合--------answer 吸星大法融合\n"+
					HIC"\t\t\t全真掌教--------answer 全真掌教\n"NOR,me);
	add_action("do_answer","answer");
	return 1;

	

}
int do_answer(string arg)
{
	object me=this_player();

	if (!arg) return notify_fail("你在哪儿呓语什么呢？\n");
	switch (arg)
	   
	{
		case "凌波微步":
			if ( me->query("quest/天龙八部/武功/pass")&& me->query("quest/天龙八部/武功/read"))
			{
				  me->set("title",HIC"凌波"HIW"微步"HIG"传人"NOR);
				  message_vision(HIC"$n对$N满脸仰慕之色，做了个万福后，轻笑道，“真是恭喜你了！”，这么难的谜题都能解开，你真是神勇无敌\n"NOR,me,this_object());
				  return 1;
			}else {
			   message_vision(HIY"$n对于$N的骚扰不堪烦忧，轻嗔薄怒，不满之色呈现脸上，说道，“你真无聊，讨厌啦！”\n"NOR,me,this_object());
			   me->add_temp("asktitle/count",1);
			   if (me->query_temp("asktitle/count")>10)
			   {
				   message_vision(HIC"$n非常生气的对$N说道，我看你就是诚心来骚扰我的，你给我下线去吧！\n"NOR,me,this_object());
				   command("kick "+me->query("id"));
				   me->receive_wound("qi",1000,this_object());
			   }
			   return 1;
			}
			break;
		case "降龙十八掌":
			if (me->query("xlz/sanzhao","pass"))
			{
				  me->set("title",HIC"北丐"HIY"萧峰挚友"NOR);
				  message_vision(HIC"$n对$N满脸仰慕之色，做了个万福后，轻笑道，“真是恭喜你了！”，这么难的谜题都能解开，你真是神勇无敌\n"NOR,me,this_object());
				  return 1;
				  
			}else {
			   message_vision(HIY"$n对于$N的骚扰不堪烦忧，轻嗔薄怒，不满之色呈现脸上，说道，“你真无聊，讨厌啦！”\n"NOR,me,this_object());
			   me->add_temp("asktitle/count",1);
			   if (me->query_temp("asktitle/count")>10)
			   {
				   message_vision(HIC"$n非常生气的对$N说道，我看你就是诚心来骚扰我的，你给我下线去吧！\n"NOR,me,this_object());
				   command("kick "+me->query("id"));
				   me->receive_wound("qi",1000,this_object());
			   }
			   return 1;
			}
			break;
			case "全真掌教":
			if (me->query("quanzhen/force","pass"))
			{
				  me->set("title",HIB"全真教 掌教真人"NOR);
				  message_vision(HIC"$n对$N满脸仰慕之色，做了个万福后，轻笑道，“见过掌教真人。\n"NOR,me,this_object());
				  return 1;
				  
			}else {
			   message_vision(HIY"$n对于$N的骚扰不堪烦忧，轻嗔薄怒，不满之色呈现脸上，说道，“你真无聊，讨厌啦！”\n"NOR,me,this_object());
			   me->add_temp("asktitle/count",1);
			   if (me->query_temp("asktitle/count")>10)
			   {
				   message_vision(HIC"$n非常生气的对$N说道，我看你就是诚心来骚扰我的，你给我下线去吧！\n"NOR,me,this_object());
				   command("kick "+me->query("id"));
				   me->receive_wound("qi",1000,this_object());
			   }
			   return 1;
			}
			
			case "星宿追魂夺命":
			if (me->query("quest/xx/tsz/zhuihun/pass"))
			{
				   me->set("title",HIB"星宿派 追魂夺命客"NOR);
				  message_vision(HIC"$n对$N一脸鄙夷之色，啐了一口嫌弃的说道，“快滚，快滚。\n"NOR,me,this_object());
				  return 1;
				  
			}else {
			   message_vision(HIY"$n对于$N的骚扰不堪烦忧，轻嗔薄怒，不满之色呈现脸上，说道，“你真无聊，讨厌啦！”\n"NOR,me,this_object());
			   me->add_temp("asktitle/count",1);
			   if (me->query_temp("asktitle/count")>10)
			   {
				   message_vision(HIC"$n非常生气的对$N说道，我看你就是诚心来骚扰我的，你给我下线去吧！\n"NOR,me,this_object());
				   command("kick "+me->query("id"));
				   me->receive_wound("qi",1000,this_object());
			   }
			   return 1;
			}
			case "吸星大法融合":
			if (me->query("quest/xxdf/pass")==2)
			{
				  me->set("title",HIC"日月神教"HIB"吸星大法传人"NOR);
				  message_vision(HIC"$n对$N一脸嫌弃之色，鄙夷的说道，“快走，快走。\n"NOR,me,this_object());
				  return 1;
				  
			}else {
			   message_vision(HIY"$n对于$N的骚扰不堪烦忧，轻嗔薄怒，不满之色呈现脸上，说道，“你真无聊，讨厌啦！”\n"NOR,me,this_object());
			   me->add_temp("asktitle/count",1);
			   if (me->query_temp("asktitle/count")>10)
			   {
				   message_vision(HIC"$n非常生气的对$N说道，我看你就是诚心来骚扰我的，你给我下线去吧！\n"NOR,me,this_object());
				   command("kick "+me->query("id"));
				   me->receive_wound("qi",1000,this_object());
			   }
			   return 1;
			}
			break;

	}
	return 1;



}

int ask_downji()
{      
       object me = this_player();
       if ((me->query("m-card-vip") ||me->query("registered")<3 )&&me->query("combat_exp")<1500000)
       {
		   command("say 月卡以及以下身份玩家经验值不够1.5m，请继续努力爬，爬到就拿到了。！\n");
		   return 1;
       }
	   if( !me->query("liwu/downji")  )
		{ 
                 command("giggle");
				 command("say 前阵子频繁down机造成了您不少损失，这是wiz组的一点心意。");
				//me->add("combat_exp",80000);
                 me->add("SJ_Credit",1000); 
				 me->add("potential",250000);
				 me->add("balance",10000000);
                 tell_object(me, HIG"你是贵宾玩家，你获得"+ HIR + chinese_number(250000) + CYN +"点「"+HIG+"潜能"+CYN+"」！\n"NOR);
                 tell_object(me, HIG"你获得了"+ HIR + chinese_number(1000) + CYN +"个「"+HIG+"通宝"+CYN+"」！\n"NOR);
				 tell_object(me, HIG"你获得了"+ HIC + chinese_number(1000) + HIC +"两「"+HIG+"黄金"+CYN+"」！\n"NOR);

				 tell_object(me, HIM"你得到了书剑笑傲江湖的祝福，你获得了相当相当长的鬼谷算术时间！\n"NOR);    
				// me->add("ggs/left_time",1080000);
                                            
				me->set("liwu/downji",1);         
                CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) + "从会客室的巫师处获得了一份宕机补偿礼物！\n"NOR);
                         
               return 1;
       }
       else {
                 command("kick "+me->query("id"));
                 command("say 你不是已经领过了？");
                 return 1;
       }
      

}
int ask_down1()
{      
       object me = this_player();
       if (me->query("id")=="missyou" ||me->query("id")=="tiandi")
       {
		   command("say "+me->query("name")+"，真抱歉，你已经领过了。\n");
		   return 1;	 
	   }
	   if( !me->query("liwu/down1")  )
		{ 
                 command("giggle");
				 command("say 前阵子频繁down机造成了您不少损失，这是wiz组的一点心意。");
				//me->add("combat_exp",80000);
                 me->add("SJ_Credit",500); 
				 me->add("potential",250000);
                 tell_object(me, HIG"你是贵宾玩家，你获得"+ HIR + chinese_number(250000) + CYN +"点「"+HIG+"潜能"+CYN+"」！\n"NOR);
                 tell_object(me, HIG"你获得了"+ HIR + chinese_number(500) + CYN +"个「"+HIG+"通宝"+CYN+"」！\n"NOR);
				 tell_object(me, HIM"你得到了书剑笑傲江湖的祝福，你获得了相当相当长的鬼谷算术时间！\n"NOR);    
				 me->add("ggs/left_time",1080000);
                                            
				me->set("liwu/down1",1);         
                CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) + "从会客室的巫师处获得了一份宕机补偿第一波礼物！\n"NOR);
                         
               return 1;
       }
       else {
                 command("kick "+me->query("id"));
                 command("say 你不是已经领过了？");
                 return 1;
       }
      

}
/*
int ask_down()
{      
       object me = this_player();
       
        if(me->query("birthday",1) <= 1305377084 ){   
        if( !me->query("down_ext1") )  { 
                                  command("say 前阵子频繁down机造成了您不少损失，这是wiz组的一点心意。");

                 if(me->query("buyvip")) { me->add("combat_exp",150000);
                                           me->add("SJ_Credit",500); 

                                       tell_object(me, HIG"你是荣誉贵宾玩家，你获得"+ HIR + chinese_number(150000) + CYN +"点「"+HIG+"实战经验"+CYN+"」！\n"NOR);
                                       tell_object(me, HIG"你获得了"+ HIR + chinese_number(500) + CYN +"个「"+HIG+"通宝"+CYN+"」！\n"NOR);
                                          }
            else if(me->query("y-card-vip"))
                                         { me->add("combat_exp",100000);
                                           me->add("SJ_Credit",450); 

                                      tell_object(me, HIG"你是年卡玩家，你获得"+ HIR + chinese_number(100000) + CYN +"点「"+HIG+"实战经验"+CYN+"」！\n"NOR);
                                      tell_object(me, HIG"你获得了"+ HIR + chinese_number(450) + CYN +"个「"+HIG+"通宝"+CYN+"」！\n"NOR);
                                          }

           else if(me->query("registered")==3 ){ me->add("combat_exp",80000);
                                                 me->add("SJ_Credit",400); 

                                     tell_object(me, HIG"你是贵宾玩家，你获得"+ HIR + chinese_number(80000) + CYN +"点「"+HIG+"实战经验"+CYN+"」！\n"NOR);
                                     tell_object(me, HIG"你获得了"+ HIR + chinese_number(400) + CYN +"个「"+HIG+"通宝"+CYN+"」！\n"NOR);
                                                }
               me->set("down_ext1",1);         
                             me->delete("down_ext",1);            
               return 1;
                                           }
 


       else {
                 command("kick "+me->query("id"));
                 command("say 你不是已经领过了？");
                                              me->delete("down_ext",1);            
                 return 1;
            }
         }
       else 
         {    command("kick "+me->query("id"));
              command("say 乌鸦嘴！down什么机？");
                                           me->delete("down_ext",1);            
               return 1; }

}

int ask_bagua()
{      
       mapping myfam;    
       object me = this_player();
       myfam = (mapping)me->query("family");

       if(!myfam || myfam["family_name"] != "桃花岛")
        {   
           if( !me->query_skill("qimen-bagua") || me->query_skill("qimen-bagua",1) < 30 )         
             { 
               command("say 好吧，我可以教你一点奇门八卦的学问。");
               me->set_skill("qimen-bagua", 50);
               return 1;
              }
           else {
                command("say 你已经够?素缘牧耍∥铱山滩涣四闶裁炊鳌?);  
                 return 1; 
                  }
         }
         else 
         {    command("kick "+me->query("id"));
              command("say 你不去找你师傅好好学习，想投机取巧啊？");
               return 1; }

}*/
int ask_xiaonian()
{
  
    object me = this_player(); 
   //if( me->query("start_liwu") ) 
	 if( me->query("liwu/xiaonian") ) 
     {
          command("say 你不是已经领过了？");
          return 1;
     }

     if( me->query("combat_exp") < 150000 ) 
     {
          command("say 150k后才有奖励，你的实战经验不足，还是抓紧时间去练功吧，到了就可以来了。");
          return 1;
     }

     command("say 为了庆贺书剑笑傲江湖站2015年小年的到来，巫师组决定给兄弟姐们发奖励！");
	 command("say 恭贺兄弟姐妹小年快乐，身体健康，全家幸福！少撸，多干。");
     command("say 感谢您的支持，希望你玩的开心，玩的长久！");
	 command("say 小！");
	 command("say 年！");
	 command("say 快！");
	 command("say 乐！");
     me->set("liwu/xiaonian",1);
     me->add("SJ_Credit",500);
     me->add("balance", 1000000);
	 //me->add("balance", 10000000);
     tell_object(me, HIR"\n\n\n新的一年特别感谢那些为笑傲江湖提供帮助的玩家，你们是最可爱的人！\n\n\n"NOR);
     tell_object(me, HIC"\n\n\n远离quest,多多运动！照顾家人，关爱自己。\n\n\n"NOR);

     tell_object(me, HIG"你得到了书剑笑傲江湖的祝福，获得"+ HIR + chinese_number(500) + CYN +"个「"+HIG+"通宝"+CYN+"」！\n"NOR);
     tell_object(me, HIG"你得到了书剑笑傲江湖，获得 " + MONEY_D->money_str(1000000) + "存款！\n"NOR);
     tell_object(me, HIM"你得到了书剑?Π两淖８＃慊竦昧讼嗟毕嗟背さ墓砉人闶跏奔洌n"NOR);    
     me->add("ggs/left_time",1080000);
	 /*
	 tell_object(me, HIR"你得到了书剑笑傲江湖的祝福，你获得了相当相当长的双倍经验值时间！别当怨妇，赶紧挂机。\n"NOR);    
	 if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 10000);
	 else
                me->add_condition("db_exp", 10000);
*/
     CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) + "从会客室的巫师处获得了一份丰厚的礼物！\n"NOR);
    return 1;
}
int ask_guoqing()
{
  
    object me = this_player(); 
	object obj;
   //if( me->query("start_liwu") ) 
	 if( me->query("liwu/guoqing18") ) 
       {
          command("say 你不是已经领过了？");
          return 1;
       }   

     command("say 为了庆贺书剑笑傲江湖站2018年国庆节+中秋节的到来，巫师组决定给兄弟姐们发奖励！");
	 command("say 恭贺兄弟姐妹中秋佳节，身体健康，全家幸福！");
     command("say 感谢您的支持，希望你玩的开心，玩的长久！");
	 command("say 国！");
	 command("say 庆！");
	 command("say 中！");
	 command("say 秋！");
	 command("say 快！");
	 command("say 乐！");

     me->set("liwu/guoqing18",1);    
	
	obj = new(__DIR__"obj/yuebing");
	 obj->set("owner",me->query("id"));
	 obj->set("date_item",1);//设置礼物标记，避免clone
     obj->move(me);
	 CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) + "从会客室的巫师处获得了一块中秋月饼！\n"NOR);
    return 1;
}
//端午节
int ask_duanwu()
{
	object me = this_player(); 
	object obj;
	 if( me->query("liwu/duanwu") ) 
       {
          command("say 你不是已经领过了？");
          return 1;
       }
	 command("say 为了庆贺书剑笑傲江湖站2017年端午节的到来，巫师组决定给兄弟姐们发奖励！");
	 command("say 恭贺兄弟姐妹端午佳节，身体健康，全家幸福！少撸，多干。");
	 command("say 记住，端午节是中国的传统节日，非高丽原创，在此以正视听。");

     command("say 感谢您的支持，希望你玩的开心，玩的长久！");
	 command("say 端！");
	 command("say 午！");
	 command("say 快！");
	 command("say 乐！");
     me->set("liwu/duanwu",1);
	 obj = new(__DIR__"obj/zongzi");
	 obj->set("owner",me->query("id"));
	 obj->set("date_item",1);//设置礼物标记，避免clone
     obj->move(me);
	 CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) + "从会客室的巫师处获得了一颗端午粽子！\n"NOR);	 
  
   return 1;
}
int ask_zhongqiu()
{
  
    object me = this_player(); 
   //if( me->query("start_liwu") ) 
	 if(me->query("liwu/zhongqiu16") ) 
       {
          command("say 你不是已经领过了？");
          return 1;
       }   

     command("say 为了庆贺书剑笑傲江湖站2016年中秋节的到来，巫师组决定给兄弟姐们发奖励！");
	 command("say 恭贺兄弟姐妹中秋佳节，身体健康，全家幸福！少撸，多干。");
     command("say 感谢您的支持，希望你玩的开心，玩的长久！");
	 command("say 中！");
	 command("say 秋！");
	 command("say 快！");
	 command("say 乐！");
     me->set("liwu/zhongqiu16",1);
     me->add("SJ_Credit",2000);
     //me->add("balance", 10000000);
	 me->add("balance", 10000000);
     tell_object(me, HIR"\n\n\n新的一年特别感谢那些为笑傲江湖提供帮助的玩家，你们是最可爱的人！\n\n\n"NOR);
     tell_object(me, HIC"\n\n\n远离quest,多多运动！照顾家人，关爱自己。\n\n\n"NOR);

     tell_object(me, HIG"你得到了书剑笑傲江湖的祝福，获得"+ HIR + chinese_number(2000) + CYN +"个「"+HIG+"通宝"+CYN+"」！\n"NOR);
     tell_object(me, HIG"你得到了书剑笑傲江湖，获得 " + MONEY_D->money_str(10000000) + "存款！\n"NOR);
     tell_object(me, HIM"你得到了书剑笑傲江湖的祝福，你获得了相当相当长的鬼谷算术时间！\n"NOR);    
   //  me->add("ggs/left_time",1080000);
	 tell_object(me, HIR"你得到了书剑笑傲江湖的祝福，你获得了相当相当长的双倍经验值时间！别pk，赶紧挂机。\n"NOR);    
	 if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 10000);
		else
                me->add_condition("db_exp", 10000);

     CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) + "从会客室的巫师处获得了一份丰厚的礼物！\n"NOR);
    return 1;
}
//元旦
int ask_liwu()
{
  
    object me = this_player(); 
   //if( me->query("start_liwu") ) 
	 if( me->query("yuandan_2018") ) 
       {
          command("say 你不是已经领过了？");
          return 1;
       }


   if( me->query("combat_exp") < 100000 ) 
       {
          command("say 100k后才有奖励，你的实战经验不足，还是抓紧时间去练功吧，到了就可以来了。");
          return 1;
       }

     command("say 为了庆贺书剑笑傲江湖站2018年元旦的到来，巫师组决定给兄弟姐们发奖励！");
	 command("say 恭贺兄弟姐妹再新的一年里，身体健康，全家幸福！");
	// command("say 还有，前一阶段频繁调整服务器底层引起的不正常宕机，一并给予补偿，巫师组决定给兄弟姐们再发奖励！");
     //command("say 感谢您的支持，希望你玩的开心，玩的长久！");
     me->set("yuandan_2018",1);
     me->add("SJ_Credit",1000);
     //me->add("balance", 10000000);
	 //me->add("balance", 10000000);
     tell_object(me, HIR"\n\n\n新的一年特别感谢那些为笑傲江湖提供帮助的玩家，你们是最可爱的人！\n\n\n"NOR);
     tell_object(me, HIC"\n\n\n远离quest,多多运动！照顾家人，关爱自己。\n\n\n"NOR);

     tell_object(me, HIG"你得到了书剑笑傲江湖的祝福，获得"+ HIR + chinese_number(1000) + CYN +"个「"+HIG+"通宝"+CYN+"」！\n"NOR);
   //  tell_object(me, HIG"你得到了书剑笑傲江湖，获得 " + MONEY_D->money_str(10000000) + "存款！\n"NOR);
     tell_object(me, HIM"你得到了书剑笑傲江湖的祝福，你获得了相当相当长的鬼谷算术时间！\n"NOR);    
     me->add("ggs/left_time",1080000);
	 tell_object(me, HIR"你得到了书剑笑傲江湖的祝福，你获得了相当相当长的双倍经验值时间！别pk，赶紧挂机。\n"NOR);    
	 if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 10000);
		else
                me->add_condition("db_exp", 10000);

     CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) + "从会客室的巫师处获得了一份丰厚的元旦礼物！\n"NOR);
    return 1;
}
int ask_qingming()
{
  
    object me = this_player(); 
   //if( me->query("start_liwu") ) 
    if( me->query("liwu/qingming")) 
       {
          command("say 你不是已经领过了？");
          return 1;
       }


   if( me->query("combat_exp") < 150000 ) 
       {
          command("say 150k后才有奖励，你的实战经验不足，还是抓紧时间去练功吧，持续到5.1节，到了就可以来了。");
          return 1;
       }

     command("say 为了纪念那些逝去的祖先，巫师组决定给兄弟姐们发过节礼物！");
	 command("say 恭贺兄弟姐妹在祭祖的同时也能洗心革面，少造杀戮,阿弥陀佛！");
	 command("say 还有，前一阶段频繁调整服务器底层引起的不正常宕机，一并给予补偿！");
     command("say 感谢您的支持，希望你玩的开心，玩的长久！");
     me->set("liwu/qingming",1);
     me->add("SJ_Credit",500);
     //me->add("balance", 10000000);
	 me->add("potential", 100000);
     tell_object(me, HIR"\n\n\n特别感谢那些为笑傲江湖提供帮助的玩家，你们是最可爱的人！\n\n\n"NOR);
     tell_object(me, HIC"\n\n\n远离quest,多多运动！照顾家人，关爱自己。\n\n\n"NOR);

     tell_object(me, HIG"你得到了书剑笑傲江湖的祝福，获得"+ HIR + chinese_number(500) + CYN +"个「"+HIG+"通宝"+CYN+"」！\n"NOR);
	      tell_object(me, HIG"你得到了书剑笑傲江湖的祝福，获得"+ HIR + chinese_number(100000) + CYN +"点「"+HIG+"潜能"+CYN+"」！\n"NOR);

     //tell_object(me, HIG"你得到了书剑笑傲江湖，获得 " + MONEY_D->money_str(10000000) + "存款！\n"NOR);
     tell_object(me, HIM"你得到了书剑笑傲江湖的祝福，你获得了相当相当长的鬼谷算术时间！\n"NOR);    
     me->add("ggs/left_time",1080000);
	 tell_object(me, HIR"你得到了书剑笑傲江湖的祝福，你获得了相当相当长的双倍经验值时间,别pk，赶紧挂机。\n"NOR);    
	 if(!mapp(me->query_conditions_by_type("db_exp")))
        me->apply_condition("db_exp", 10000);
	 else
        me->add_condition("db_exp", 10000);

     CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) + "从会客室的巫师处获得了清明节和宕机补偿的礼物！\n"NOR);
    return 1;
}
int ask_51()
{
  
    object me = this_player(); 
   //if( me->query("start_liwu") ) 
    if( me->query("liwu/1751")) 
    {
          command("say 你不是已经领过了？");
          return 1;
    }


   if( me->query("combat_exp") < 150000 ) 
       {
          command("say 你的实战经验不足150k，还是抓紧时间去练功吧，持续到5.1节，到了就可以来了。");
          return 1;
       }

    // command("say 为了纪念那些逝去的祖先，巫师组决定给兄弟姐们发过节礼物！");
	 command("say 恭贺51劳动节！");
	// command("say 还有，前一阶段频繁调整服务器底层引起的不正常宕机，一并给予补偿！");
     //command("say 感谢您的支持，希望你玩的开心，玩的长久！");
     me->set("liwu/1751",1);
     me->add("SJ_Credit",1000);
	 me->add("potential",15000);
     //me->add("balance", 5000000);
	 //me->add("balance", 10000000);
     tell_object(me, HIR"\n\n\n特别感谢那些为书剑笑傲江湖站提供帮助的玩家，你们是最可爱的人！\n\n\n"NOR);
     tell_object(me, HIC"\n\n\n远离quest,多多运动！照顾家人，多下厨房，关爱自己身体。\n\n\n"NOR);

     tell_object(me, HIG"你得到了书剑笑傲江湖的祝福，获得"+ HIR + chinese_number(1000) + CYN +"个「"+HIG+"通宝"+CYN+"」！\n"NOR);
     //tell_object(me, HIG"你得到了书剑笑傲江湖，获得 " + MONEY_D->money_str(5000000) + "存款！\n"NOR);
	 tell_object(me, HIG"你得到了书剑笑傲江湖的祝福，获得 " +chinese_number(15000) + "潜能！\n"NOR);
     tell_object(me, HIM"你得到了书剑笑傲江湖的祝福，你获得了相当相当长的鬼谷算术时间！\n"NOR);    
 //    me->add("ggs/left_time",1080000);
	 tell_object(me, HIR"你得到了书剑笑傲江湖的祝福，你获得了相当相当长的双倍经验值时间,持续假期3天！别pk，赶紧挂机。\n"NOR);    
	
	 if(!mapp(me->query_conditions_by_type("db_exp"))) 
                me->apply_condition("db_exp", 10000);
		else
                me->add_condition("db_exp", 10000);
	
     CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) + "从会客室的巫师处获得了一份丰厚的劳动节礼物！\n"NOR);
    return 1;
}
//春节礼物
int ask_chunjie()
{
  
   object me = this_player(); 
   if( me->query("liwu_2018") ) 
       {
          command("say 你不是已经领过了？");
          return 1;
       }


   if( me->query("combat_exp") < 500000  ) 
   {
          command("say 你的实战经验不足500000，还是抓紧时间去练功吧，放心挂机吧，安心等你半个月。");
		  command("say 若是真实挂机，可以拿到奖励，利用系统bug来得到，就放手吧。");
          return 1;
   }

     command("wink");

     command("say 您的实战经验终于到500k了，真不容易呀！");
     command("say 为了庆贺书剑笑傲江湖站2018狗年来到，祝愿所有兄弟姐们在现实生活中能心想事成！"HBYEL+HIR"狗年旺运"NOR+HBRED+HIW"大吉大利！"NOR);
	 command("say 春！");
	 command("say 节！");
	 command("say 快！");
	 command("say 乐！");

     command("say 远离quest,多陪家人，锻炼身体，保家卫国！");
     me->set("liwu_2018",1);
     me->add("SJ_Credit",1888);
     me->add("balance", 10000000);
  //   me->add("potential", 500000);

     tell_object(me, HIG"你得到了笑傲江湖巫师们的真心祝福，获得"+ HIR + chinese_number(1888) + CYN +"个「"+HIG+"通宝"+CYN+"」！\n"NOR);
     tell_object(me, HIC"你得到了笑傲江湖巫师们的真心祝福，获得 " + MONEY_D->money_str(10000000) + "存款！\n"NOR);
     tell_object(me, HIM"你得到了笑傲江湖巫师们的真心祝福，你获得了相当相当长的鬼谷算术时间！\n"NOR); 

     tell_object(me, HIY"为了体现新年大礼包的实惠，特决定从除夕日开始，直到正月十五之间，玩家只要路过襄阳丁字路口，即可获得免费的双倍经验！\n"NOR);
	 tell_object(me, HIG"你得到了笑傲江湖巫师们的第一波真心祝福，还有一波！\n"NOR);
	// tell_object(me, HIR"切忌，切忌，本次double时间仅仅截至到正月十五晚上12点！\n"NOR); 
	// tell_object(me, HIR"开放当铺宝盒，玩家！\n"NOR); 
	// tell_object(me, HIY"另外，开放当铺神秘宝箱，玩家慎重，宝箱乃随即数产生宝物，全凭个人运气使然。！\n"NOR);
//	 me->add("ggs/left_time",1080000);
     tell_object(me, HIR"你得到了笑傲江湖巫师们的真心祝福，你获得了相当相当长的双倍经验增长时间！\n"NOR);    
	 if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 10000);
	 else
                me->add_condition("db_exp", 10000);
	 /**/
    CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) + "从会客室的巫师处获得了一份丰厚的2018年春节礼物！\n"NOR);
    return 1;
}
int ask_yuanxiao()
{
  
   object me = this_player(); 
   if( me->query("liwu/yuanxiao") ) 
       {
          command("say 你不是已经领过了？");
          return 1;
       }


   if( me->query("combat_exp") < 160000  ) 
   {
          command("say 你的实战经验不足160000，还是抓紧时间去练功吧，放心挂机吧，安心等你半个月。");
		  command("say 若是真实挂机，可以拿到奖励，利用系统bug来得到，就放手吧。");
          return 1;
   }

     command("wink");

     command("say 您的实战经验终于到160k了，真不容易呀！");
     command("say 为了庆贺书剑笑傲江湖站2015羊年正月十五元宵节来到，祝愿所有兄弟姐们在现实生活中能事事圆满！");
	
     command("say 感谢您的支持，希望你玩的开心，玩的长久！");
     me->set("liwu/yuanxiao",1);
     me->add("SJ_Credit",500);
     //me->add("balance", 10000000);
     //me->add("potential", 500000);

     tell_object(me, HIG"你得到了笑傲江湖巫师们的真心祝福，获得"+ HIR + chinese_number(500) + CYN +"个「"+HIG+"通宝"+CYN+"」！\n"NOR);
    // tell_object(me, HIC"你得到了笑傲江湖巫师们的真心祝福，获得 " + MONEY_D->money_str(10000000) + "存款！\n"NOR);
  //   tell_object(me, HIM"你得到了笑傲江湖巫师们的真心祝福，你获得了相当相当长的鬼谷算术时间！\n"NOR); 
	// tell_object(me, HIG"你得到了笑傲江湖巫师们的真心祝福，获得"+ HIR + chinese_number(500000) + CYN +"点「"+HIG+"潜能"+CYN+"」！\n"NOR);
     //tell_object(me, HIY"为了体现新年大礼包的实惠，特决定从除夕日开始，直到正月十五之间，玩家只要路过襄阳丁字路口，即可获得免费的双倍经验！\n"NOR);
	 tell_object(me, HIR"你得到了笑傲江湖巫师们的祝福，获得一定的双倍获得exp状态！\n"NOR);
	 tell_object(me, HIR"切忌，切忌，不要玩耍，努力挂机！\n"NOR); 
	// tell_object(me, HIR"开放当铺宝盒，玩家！\n"NOR); 
	// tell_object(me, HIY"另外，开放当铺神秘宝箱，玩家慎重，宝箱乃随即数产生宝物，全凭个人运起使然。！\n"NOR);
	// me->add("ggs/left_time",1080000);
 /*    tell_object(me, HIR"你得到了笑傲江湖巫师们的真心祝福，你获得了相当相当长的双倍经验增长时间！\n"NOR);    */
	 if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 10000);
	 else
                me->add_condition("db_exp", 10000);
	
    CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) + "从会客室的巫师处获得了一份丰厚的礼物！\n"NOR);
    return 1;
}
int ask_nianka()
{
	//object vipcard;
	object me = this_player();
	if (me->query("buyvip"))
	{
		command("say 你已经是终身了，想变成年卡么？\n");
		return 1;
	}
	if (me->query("combat_exp")<165000)
	{
		command("say 你的经验值不足165k，先巡城后过阵，再领取年卡\n");
		return 1;
	}
	if (me->query("givevipcard")>1)
	{
		command("kick "+me->query("id"));
		command("say 跟你说了不要随便丢弃，真是始乱终弃,不给你了！");
		return 1;
	}
	if (me->query("y-card-vip") && me->query("vip/vip_time"))
	{
		command("say 对不起，你已经是年卡贵宾了，请不要跟巫师开玩笑。\n");
		//command("say 你现在剩余时间为");
		return 1;
	}
	command("say 乖，年卡快到期了，再给你一张，好好挂。");
	command("say 体验并互动是本游戏的核心思想。");
	command("say 为了维护世界和平，要拿好这张卡。");
	command("say 那张卡要马上使用，别随意丢弃。");


	me->set("registered", 3);    
	me->set("vip/vip_start_time",time());    
	me->set("vip/vip_time",time());       

	me->add("vip/vip_time",365*24*3600);
	me->add("SJ_Credit",3000);
//	me->add("balance",20000000);
	me->set("y-card-vip",1);
	write(HIY"\n你将"HIW"贵宾充值卡"NOR+HIY"往书剑自动收款机里一刷\n"NOR);
	
    write(HIY"\你的书剑通宝增加了三仟个。\n"NOR);
 //   write(HIY"\n你的银行存款增加了贰千两。\n"NOR);
	///write(HIW"\n书剑自动系统为您增加三百六十五天的贵宾VIP，目前等级为"HIR"四"HIW",请输入"HIB"time"HIW"查看，感谢的对书剑的支持。\n"NOR);
	//degree();
	//new("d/wizard/npc/vipcard")->move(me);
	//me->add("givevipcard",1);
	CHANNEL_D->do_channel(this_object(), "sj", HIC"听说" + me->name(1) + "从会客室的巫师处获得了一张"HIR"贵宾年卡"HIC"礼物！\n"NOR);

	return 1;
	
}
int ask_yueka()
{
	//object vipcard;
	object me = this_player();
	if (time()-me->query("vip/vip_time")<0)
	{
		//me->delete("m-card-vip");
		write(HIC"本月你已经领取过月卡贵宾了。\n"NOR);
		return 1;
	}

	if (me->query("m-card-vip"))
	{
		//me->delete("m-card-vip");
		write(HIC"注意，你已经是月卡贵宾了。\n"NOR);
		return 1;
	}
	if (me->query("y-card-vip")||me->query("buyvip"))
	{
		write(HIC"注意，因为现在已经是贵宾了，无需再问月卡。\n"NOR);
		command("kick "+me->query("id"));
		return 1;
	}
	if (me->query("give_mcard")>24)
	{
		command("kick "+me->query("id"));
		command("say 跟你说了不要随便丢弃，真是始乱终弃,不给你了！");
		return 1;
	}

	command("say 乖，月卡快到期了，再给你一张，好好挂，别浪费，只有12次机会。");
	command("say 体验并互动是本游戏的核心思想。");
	command("say 为了维护世界和平，要拿好这张卡。");
	command("say 那张卡要马上使用，别随意丢弃。");

	//new("clone/spec/bak/vipcard-m")->move(me);
	//me->add("give_mcard",1);
	me->set("vip/vip_start_time",time());    
	me->set("vip/vip_time",time());                                       ;
	me->add("vip/vip_time",30*24*3600);
	//me->add("balance",120000);
	me->add("SJ_Credit",100);
	me->set("m-card-vip",1);
	write(HIY"\n你将"HIW"贵宾充值卡"NOR+HIY"往书剑自动收款机里一刷\n"NOR);
	CHANNEL_D->do_channel(this_object(), "sj", HIC"听说" + me->name(1) + "从会客室的巫师处获得了一张"HIR"贵宾月卡"HIC"礼物！\n"NOR);

	return 1;
	
}

int ask_quanfa()
{      
       int i ;
       object me = this_player();
       i = me->query("max_pot",1) -100;

		if(i > 250 ) i= 250;
		if(me->query("askwiz_cuff") <4 ){

         if( me->query_skill("yeqiu-quan",1)< 250 )  me->set_skill("yeqiu-quan", i);
         if( me->query_skill("cuff",1) <250 )        me->set_skill("cuff", i);
    
          me->add("askwiz_cuff",1);
          command("say 好吧，我可以教你一点基本护身的武功。");
          command("say 我最多只教你三遍。你可要看仔细了。到时间学不会可就不要怪我啦！");
            
             return 1;
           }
 else {
                  command("say 你武功已经很高了。我可教不了你什么东西。");  
                  return 1; 
                  }
      
        
}

int ask_jiangli()
{
  
    object me = this_player(); 
  
   if( me->query("5m_jiangli") ) 
       {
          command("say 你不是已经领过了？");
          return 1;
       }


   if( me->query("combat_exp") < 5000000  ) 
       {
          command("say 你的实战经验不足5M，还是抓紧时间去练功吧。");
          return 1;
       }

     command("ah");
     command("say 恭喜你跻身江湖顶尖高手的行列！");
     command("say 这是闪电最后一次对你的帮助了，以后就要靠你自己奋斗了！");
     me->set("5m_jiangli",1);
     me->add("SJ_Credit",2000);
     me->add("balance", 20000000);

     me->add("relife/gifts/now",  2);  
     me->add("relife/gifts/total",  2);  
     me->add("imbue_reward",10);


     tell_object(me, HIC"你得到了闪电的祝福，获得"+ HIR + chinese_number(2000) + HIC +"个「"+HIG+"书剑通宝"+HIC+"」， " + MONEY_D->money_str(20000000) + "存款！\n"NOR);
     tell_object(me, HBBLU"你得到了闪电的祝福，你获得两点可自由分配的参悟天赋点数，请使用addgift指令分配！\n"NOR);  
     tell_object(me, HBBLU"你获得十次额外的打造机会！\n"NOR);   
     me->add("ggs/left_time",1080000);


    tell_object(me, HBBLU"天赋系统开始生效！从下一次登陆开始，你将获得额外的攻防点数，实战中将会产生特殊的效果！\n"NOR);  
 
     CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) + "从会客室的巫师处获得了一份"HIR"高手进阶"HIC"礼物！\n"NOR);
     return 1;     

}


int ask_vip()
{      
     object me = this_player(); 
  
   if( !me->query("buyvip") ) 
       {
          command("say 对不起，你目前还不能使用这项业务。");
          return 1;
       }


   if( me->query("combat_exp")- me->query("buyvip/combat_exp")<1000000  && me->query("buyvip/newbie") ) 
       {
          command("say 对不起，每隔1M才可以使用一次本项业务。");
          return 1;
       }

     command("say 欢迎使用笑傲江湖书剑VIP自助业务！");
     
     command("say 终身VIP玩家每隔1M可以领取1000通宝和1000两黄金的额外奖励！");
     
     command("say 同时VIP玩家可以在0-6M期间免费补满武技五次，请珍惜使用！");
     
     me->set("buyvip/combat_exp",me->query("combat_exp"));
     me->add("SJ_Credit",1000);
     me->add("balance", 10000000);
     me->add("imbue_reward",10);
     me->set("vip/vip_time",time());
     me->add("vip/vip_time",365*24*3600);
     me->set("vip/vip_start_time",time());  
me->set("registered",3);
     me->set("buyvip/newbie",1);
     me->set("y-card-vip",1);
 if(me->query("combat_exp")<6000000 )   command("fullskills "+me->query("id"));

     tell_object(me, HIC"你使用了VIP自助服务，提取了"+ HIR + chinese_number(1000) + HIC +"个「"+HIG+"书剑通宝"+HIC+"」， " + MONEY_D->money_str(10000000) + "存款！\n"NOR);
 if(me->query("combat_exp")<5000000 )     tell_object(me, HBBLU"你已经使用了一次Fullskills指令！\n"NOR);  
     tell_object(me, HBBLU"你获得十次额外的?蛟旎幔n"NOR);   
     tell_object(me, HBBLU"你的VIP使?闷谙拮远刂梦荒辏n"NOR);   
//      CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) + "到会客室的巫师处办理了一次"HIR"VIP专享业务"HIC",获得了不少礼物！\n"NOR)
//      CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1) + "到会客室的巫师处办理了一次"HIR"VIP专享业务"HIC",获得了不少礼物！\n"NOR);
     return 1;     

        
}


