// yideng.c 一灯大师 By River@SJ 2002.6.6

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

int ask_hr();
int ask_qiu();
int ask_xtg();
int ask_ronghe();
int ask_yinggu();
int check_yideng(object me);

void create()
{
	set_name("一灯大师", ({ "yideng dashi", "yideng", "dashi" }) );
	set("title",HIR"南帝"NOR);
	set("gender", "男性" );
	set("class", "bonze");
	set("age", 78);
	set("str", 45);
	set("con", 40);
	set("dex", 35);
	set("int", 35);
	set("per", 28);
	set("unique", 1);
    set("no_get", 1);

	set("max_qi", 45000);
	set("max_jing", 7500);
	set("eff_jingli", 8500);
	set("neili", 32000);
	set("max_neili", 32000);
	set("jiali", 250);
	set("combat_exp", 15500000);
	set("score", 20000);
	//绝世
    set("yideng/ronghe","pass");
	create_family("天龙寺", 12, "俗家弟子");

	set("long", "一个身穿粗布僧袍，两道长长的白眉从眼角垂了下来，面目慈祥，\n"+
		"眉间虽隐含愁苦，但一番雍容高华的神色，却是一望而知。\n");

	set_skill("parry", 500);
	set_skill("dodge", 500);
	set_skill("qingyan-zhang", 500);
	set_skill("strike", 500);
	set_skill("buddhism",200);
	set_skill("force", 500);
	set_skill("literate", 350);
	set_skill("sword", 500);
	set_skill("duanjia-jianfa", 500);
	//set_skill("cuff", 500);
	//set_skill("axe",500);
	//set_skill("pangen-fu",500);
	//set_skill("duanjia-quan", 500);
	set_skill("yiyang-zhi", 550);
	set_skill("finger", 550);
	set_skill("qiantian-yiyang", 530);
	set_skill("tianlong-xiang", 500);

	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "yiyang-zhi");
	map_skill("sword", "duanjia-jianfa");
	map_skill("force", "qiantian-yiyang");
	//map_skill("cuff", "duanjia-quan");
	map_skill("strike", "qingyan-zhang");
	map_skill("finger","yiyang-zhi");
	prepare_skill("finger","yiyang-zhi");
	set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
				(: exert_function, "yiyang" :),
                (: perform_action, "finger.yizhisanmai" :),
				(: perform_action, "finger.sandie" :),
				//(: perform_action, "brush.yiyangshu" :),
        	    //(: perform_action, "brush.shiguwen" :),        
	    }));
	
	set("inquiry", ([
		"here": "这里便是石屋。",
		"黄蓉": (: ask_hr :),
        "慈恩": (: ask_qiu :),
      	"先天功": (: ask_xtg :),
    	"大理绝技": (: ask_ronghe :),
		"刘贵妃": (: ask_yinggu :),
	]));

	setup();
	carry_object("/d/tls/obj/jiasha")->wear();
	carry_object("/d/tls/obj/sengxie")->wear();
}

void attempt_apprentice(object ob)
{
/*	if (!ob->query("quest/tls/yideng")) 
	{
		command("buddhi");
		command("say 你虽辛苦到此，但老衲迫于大理族规，无法收你为徒，还请谅解！\n");
        return;
	}*/
	if ( ob->query_skill("qiantian-yiyang",1) < 450 ){
		command ("hmm");
		command ("say 你乾天一阳功如此之差,不足450，我可不收你！");
		return;
	}
	if( ob->query_int() < 60){
		command("say 武学之道必须悟性高，依我看" + RANK_D->query_respect(ob) + "的资质似乎不够60？");
		return;
	}
	if(ob->query("shen") < 2000000){
		command("say 大理乃堂堂皇室，而这位" + RANK_D->query_respect(ob) + "不到2m正神，我看不适合在我大理呆下去了。");
		return;
	}
	if(ob->query_skill("liumai-shenjian", 1)){
		command("say 这位" + RANK_D->query_respect(ob) +"已经学会了六脉神剑，不再适合拜我为师了。");
		return;
	}

	if (ob->query("tls")) {
		command ("say 你已经是天龙寺出家弟子了，我不能再收你了！");
		return;
	}
	command("smile");
	command("say 很好，" + RANK_D->query_respect(ob) + "多加努力，他日必定有成。");
	command("recruit " + ob->query("id") );
	//ob->delete("tls"); //和后面的冲突，暂时屏蔽掉
    //ob->delete("tls"); 
	//ob->delete("class");
	ob->set("title",HIY"大理国南帝座下弟子"NOR);
}

int ask_hr()
{
	object me= this_player();
	if (me->query_temp("quest/jindaoheijian/huangrong3")!=1) {
		command("say 小姑娘还好吧？");
		command("haha");
		return 1;
	}

	command("say 都20多年了，裘千尺还记着呢。");
	command("say 不知道我能帮忙吗？");
	message_vision(WHT"你将在黄蓉求见大师的请求告诉了一灯大师!\n"NOR,me); 
	command("say 好吧，你先去绝情谷，我随后就带慈恩就去。");
	command("say 哎！冤冤相报何时能了！");
	me->delete_temp("quest/jindaoheijian/huangrong3");
	me->set_temp("quest/jindaoheijian/yideng",1);
	return 1;
}

int ask_qiu()
{   
    object me= this_player();
    if (me->query("quest/tzauto/pass")|| me->query("family/family_name")!="铁掌帮")
                 {   
                    command(" say 慈恩心愿已了，不愿再沾染尘世之事，施主请回吧。");
                    return 1;
                  }
    command("say 近来风声频传，说道蒙古大军久攻襄阳不下，发兵绕道南攻大理，以便回军迂回，还拔襄阳。\n");
    command("say 慈恩见老衲心念故国，出去打探消息，已经两天两夜没回来了。\n");
    me->set_temp("quest/tzauto/yideng",1); 
  return 1;

}

int accept_object(object me, object ob) 
{
   if (userp(ob)) return 0;
 
   if( ob->query("id") == "lingwen" 
	  && me->query("quest/qz/xtg/dingyang/start")
	  && ob->query("owner")==me->query("id")
      && me->query("family/family_name")=="全真教"
      && me->query_temp("quanzhen/force") 
      && !me->query("quanzhen/force")    )
   	   {
               command("ah ");
               command("say 想不到有生之年还能目睹重阳真人的手迹。 "); 
               me->delete_temp("quanzhen/force");
               message_vision(HIM"一灯大师看着手中的《五篇灵文另》，沉默了半响，不由得深深叹了一口气，讲出一段尘封多年的往事来。\n"NOR+
                          HIG"原来当年华山论剑之后，重阳真人对南帝段王爷的一阳指甚为佩服，第二年就和他师弟南下大理，与南帝互相切磋功夫。\n"+
                               "南帝将一阳指的要旨诀窍，尽数说给了重阳真人知道，重阳真人十分喜欢，竟将他最厉害的先天功功夫传给了段王爷。\n"+
                               "重阳真人临别之际言道：“近来我旧疾又发，想是不久人世，好在先天功已有传人，再加上皇爷的一阳指神功，世上已\n"+
                               "有克制蛤蟆功之人，就不怕他横行作怪了。“ \n"NOR, me);
               command("say 那时老衲方才明白，重阳真人千里迢迢来到大理，主旨是要将先天功传给老衲，要在他身死之后，留下一个克制西毒欧阳锋之人。 ");         
               command("sigh ");     
           
               me->set_temp("xtg1",1);
               me->set("give_book",1);
			   destruct(ob);
              // call_out("destructing", 1, ob); 
                return 1; 
      }
   else return 0;
             }

int ask_xtg()
{
	object me= this_player();
	if (!me->query_temp("xtg1")&& !me->query("give_book")) {
		command("say 先天功是王重阳传于我的内功绝技。");
		return 1;
	}
	if (me->query("int")<42) {
		command("say 你的先天悟性不够42。");
		return 1;
	}
  if( me->query("quanzhen/force")== "pass")
  {   command("say 看样子小友已经完全掌握了先天功的要旨诀窍了。");
      command("haha ");
      return 1;
  }

	if(me->query("quanzhen/force")== "try"   )
	{
				command("say 看样子小友还得多加练习才行。");
						return 1;
		}

    if( time()-me->query("xtg/dyz/time")<86400)		
   		{
				command("say 小友还是去休息一下吧。");
			    return 1;
		}
	if( me->is_busy())		
   		{
				command("say 小友太忙碌了，还是去休息一下吧。");
			    return 1;
		}
	command("say 重阳真人学到一阳指后，在世不久，并未研习，听说也没传给徒弟。");
    command("say 老衲年事已高，想来也活不了多久了。听说西毒欧阳锋已有传人，当世之上，唯先天功和一阳指两大神技才能克制蛤蟆功。");
    command("say 既然你得到了重阳真人的先天功精要，老衲便将这一阳指传授给你，你当精心研习，勿要让西毒传人横行于世。");


     message_vision(HIY"一灯大师左掌抚胸，右手食指点出，来势虽缓，$N上半身正面大穴却已全在一指笼罩之下，竟不知要点的是那一处穴道，九处大穴皆大指之虞！\n"NOR+
                        HIG"一灯大师招数未完，抢上数步，又是一指点出，这次却是指向$N小腹，这一指所盖罩的要穴更广，肚腹间冲脉十二大穴，自幽门\n"+
                               "通谷，下至中注、四满，直抵横骨、会阴，尽处于这一指威力之下。\n"+
                        HIM"跟着一灯大师第三指又出，这一指迅如闪电，直指$N眉心，指尖闪动，似乎头部太阳，人中，百会．．等各大要穴尽在这一指笼罩。 \n"NOR, me);
    command("smile ");
    command("say 你可看明白了？");
    me->delete_temp("xtg1");
    tell_object(me,HIY"\n你开始认真的回忆一灯大师的一招一式。。\n"NOR);
       me->start_busy(999);              
       remove_call_out("thinking");
       call_out("thinking",5, me );
	return 1;
}


int thinking(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("try_yyz")<(3+random(3)))
    { me->add_temp("try_yyz",1);
          if(random(2)) tell_object(me,HIG"\n你认真回想着刚才一灯大师的一招一式...\n"NOR);
             else tell_object(me,HIY"\n突然间，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("try_yyz");
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  17;
      i=random(j);

      if (i<2 
		 && random(me->query("int")) >= 40 
	     && me->query("kar")<31
		 && random(me->query("kar"))>28)
	  {       
          tell_object(me,HIM"\n你先天功真气由膻中，入缺盆，过阳池外关，交与三焦手少阳之脉，一呼一吸，引而不发，在体内流转不休！\n"NOR);
          message_vision(HIC"\n$N对如何使用一阳指指法驱动先天功内力似乎有些了解了。”\n"NOR,me); 
          tell_object(me,HIR"你对如何使用一阳指指法驱动先天功内力似乎有些了解了，剩下的就是勤加练习了！\n"NOR);
          me->set("quanzhen/force", "try" );
          me->set("title",HIC"全真教 先天功传人"NOR);
          log_file("quest/dingyang", sprintf("%s(%s) 失败%d次成功解开定阳针。富源：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query("xtg/dyz/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
        }
        else
        {
         tell_object(me,HIG"\n你沉思许久，不得要领。\n"NOR);
         message_vision(HIC"\n$N摇了摇头，深深地叹了口气。\n"NOR,me); 
         tell_object(me,HBBLU"\n很可惜，你本次尝试先天功定阳针秘密失败！\n"NOR);
         tell_object(me,HBBLU"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
         tell_object(me,HBBLU"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
		 log_file("quest/dingyang", sprintf("%s(%s) 解密定阳针失败%d次。富源：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query("xtg/dyz/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
         me->add("xtg/dyz/fail",1);
         me->set("xtg/dyz/exp", me->query("combat_exp") );
         me->start_busy(1);
         me->set("xtg/dyz/time",time());
        }

     }

}

//一阳指和先天功融合

int ask_ronghe()
{
	object me= this_player();
	int total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
	if (!me->query_temp("yyzjx")) {
		command("say 一阳指和先天功的融合是我大理段家的家传绝技。\n");
		return 1;
	}
    if (me->query_skill("yiyang-zhi",1)<450) {
		command("say 你功力太低了，还是把你的一阳指提升上来再说吧。\n");
		return 1;
	}
	if (me->query("int")<40) 
	{
		command("say 你的先天悟性太低了，还是把把悟性提升上来再说吧。\n");
		return 1;
	}

    if( me->query("yideng/ronghe")== "pass")
    {   
		command("say 看样子小友已经完全掌握了一阳指的要旨诀窍了。");
        command("haha ");
		me->set("title",HIR"南帝"+HIY"一阳指传人"NOR);
        return 1;
    }
    if( me->is_busy())		
   		{
				command("say 小友太忙碌了，还是去休息一下吧。");
			    return 1;
		}
    if( time()-me->query("ydrh/time")<86400)		
   	{
		command("say 你来的也太勤快了耶，小友还是去休息一下吧。");
		return 1;
	}
	command("say “一阳指”乃是大理绝学，当时五绝于华山绝顶论剑，并不弱于任何人！");
    command("say 后来重阳真人和他的师弟周伯通一起来到大理，我从真人哪儿学到先天功，对于其领悟更加深刻。");
    command("say 既然老衲年事已高，既然有缘，我就将我多年的心得传授于你,你当精心研习，勿要让一阳指绝学发扬光大。");
    me->delete_temp("yyzjx");
	me->set_temp("juexue");

     message_vision(HIY"一灯大师左掌抚胸，右手食指点出，来势虽缓，$N上半身正面大穴却已全在一指笼罩之下，竟不知要点的是那一处穴道，九处大穴皆大指之虞！\n"NOR+
                        HIG"一灯大师招数未完，抢上数步，又是一指点出，这次却是指向$N小腹，这一指所盖罩的要穴更广，肚腹间冲脉十二大穴，自幽门\n"+
                               "通谷，下至中注、四满，直抵横骨、会阴，尽处于这一指威力之下。\n"+
                        HIM"跟着一灯大师第四指又出，这一指迅如闪电，直指$N眉心，指尖闪动，似乎头部太阳，人中，百会．．等各大要穴尽在这一指笼罩。 \n"NOR, me);
    command("smile ");
    command("say 你可看明白了？");
    
    tell_object(me,HIY"\n你开始认真的回忆一灯大师的一招一式。。\n"NOR);
    me->start_busy(999);              
    remove_call_out("tkjx");
    call_out("tkjx",2, me );

	return 1;
}

int tkjx(object me)
{
  
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("try_juexue")<(5+random(3)))
    { 
	  me->add_temp("try_juexue",1);
      if(random(2)) tell_object(me,HIG"\n你认真回想着刚才一灯大师的一招一式...\n"NOR);
      else tell_object(me,HIY"\n突然间，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("tkjx");
	  call_out("tkjx",2+random(3), me);
	}

   else
   {  
	  me->delete_temp("try_juexue");
    //  total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  15;
      i=random(j);
//参悟后解开？
     if (random(me->query("kar"))>27
		 &&random(me->query("int"))>40
		 &&i<3 )
       {
       tell_object(me,HIM"\n跟随一灯指引，你的先天真气和乾天一阳彻底融合在一起。由膻中，入缺盆，过阳池外关，交与三焦手少阳\n之脉，一呼一吸，引而不发，在体内流转不休！\n"NOR);
       message_vision(HIC"$n对$N笑道，想当初重阳真人传授我这先天功的本意就是以一阳指力和先天功融合，既然你我有缘，我就传授于你!\n"NOR,me,this_object());
	   message_vision(HIC"也不枉当初重阳真人的一片苦心，当然我们大理有个大对头叫做欧阳锋的,你见到他的传人一定不能饶了他。\n"NOR,me,this_object());
	   message_vision(HIR"$n将王重阳所传授给自己的先天功奥秘一股脑传授给$N。\n"NOR,me,this_object());

	   message_vision(HIC"\n\n$N对如何使用一阳指指法驱动先天功内力似乎有些了解了。”\n"NOR,me); 
       tell_object(me,HIR"你对如何使用一阳指彻底明白掌握！\n"NOR);
       me->set("yideng/ronghe","pass");
	   //me->set_skill("xiantian-gong",200);
	   //tell_object(me,HIC"你领悟了一灯的教诲，你的先天功进步了！\n"NOR);

       me->set("title",HIR"南帝"+HIY"一阳指传人"NOR);
	   
       log_file("quest/yyzronghe", sprintf("%s(%s) 失败%d次后成功解开一阳指融合。富源：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query("ydrh/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
          me->start_busy(1);
       }
     else
       {
       tell_object(me,HIG"\n你沉思许久，不得要领。\n"NOR);
       message_vision(HIC"\n$N摇了摇头，深深地叹了口气。\n"NOR,me); 
       tell_object(me,HBBLU"\n很可惜，你本次尝试一阳指绝学秘密失败！\n"NOR);
       tell_object(me,HBBLU"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
       tell_object(me,HBBLU"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
       me->add("ydrh/fail",1);
       me->set("ydrh/exp", me->query("combat_exp") );
       me->start_busy(1);
       me->set("ydrh/time",time());
	   log_file("quest/yyzronghe", sprintf("%s(%s) 解密一阳指融合失败%d次。富源：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query("ydrh/fail"),
          me->query("kar"),
          me->query("combat_exp")) );
       } 
     }
}

int ask_yinggu()
{
	object me= this_player();
	if (!me->query_temp("nqg/askyingok")) {
		command("say 冤冤相报何时了？");
		command("sigh ");
		return 1;
	}

	command("say 都20多年了，还记着呢。");
	command("say 段皇爷已经不在人世了，现在有的是一灯大师，就是我。");
	message_vision(WHT"你将在瑛姑处听到的见闻和情况告诉了一灯大师!\n"NOR,me); 
	
	command("say 哎！冤冤相报何时能了！");
	command("say 好吧，就让我来承担这份冤孽吧。");
	command("say 好吧，动手吧。");
	write(HIG"你是否想杀了一灯大师？想(yes)还是不想(no)？\n");
	write(HIR"请慎重回答，若杀了一灯大师会遭到整个正派人士的唾弃！\n");
	add_action("do_huida","answer");
	return 1; 

}

int do_huida(string arg)
{
	object yideng;
	object me=this_player();
	
	if (!objectp(yideng=present("yideng dashi",environment(me))))
	{
		yideng=new("d/dali/yideng/npc/yideng");
		yideng->move(environment(me));
	}
	if (!arg) return notify_fail("你回答什么？");
	if (arg=="yes")
	{
		command("say 老秃驴，废话少说，杀人偿命，欠债还钱，你纳命来吧！\n");
		command("say 不杀你,我对不住瑛姑的承诺和我的泥鳅功啊。！\n");
		me->set_temp("nqg/killyideng",1);

		me->kill_ob(yideng);
		yideng->kill_ob(me);
    
		me->delete_temp("nqg/askyingok");
		//call_out("check_yideng",1,me);
		return 1;
	}else if(arg=="no")
	{
		command("say 好吧，既然你不愿意下手，那就先回去吧！\n");
		me->delete_temp("nqg/askyingok");
		return 1;
	}	
}
/*
int check_yideng(object me)
{

	object yideng;
	yideng=present("yideng dashi",environment(me));
    if (objectp(yideng)&& me->is_fighting(yideng))
    {
		remove_call_out("check_yideng");
		call_out("check_yideng",2,me);
		return 0;
    }
	if (!objectp(me)) return 0;
	
	me->set_temp("yideng/kill_yideng", 1);
	me->add("shen",-random(2000000));
	me->set("tls/killyideng",1);

	message_vision("\n\n你哼了一声道，再厉害的秃驴我照样是我手下败将。\n", me);

	message_vision("\n\n看来是该到了回去给瑛姑交差的时间了。\n", me);

	return 1;

}*/