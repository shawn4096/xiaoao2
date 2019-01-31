// Room: lwhole.c

#include <ansi.h>;

inherit ROOM;

void create()
{
     set("short", "石壁岩洞");
     set("long", @LONG
这是一天然石洞，不是很深，当太阳升起时能直射全洞。象是有人在
此住过，正面有一石床，左边放有一些石碗，右面的石壁(wall)十分平整。
LONG
        );
     set("exits", ([
         "out" : __DIR__"wanniansong",
             ]));    
     set("item_desc", ([
          "wall" : HIW "彼之力方碍我之皮毛，我之意已入彼骨里。双手支撑，一气贯通。太极者，道也；两仪者，阴阳也。\n"
						+"阴阳一道也，太极无极也。气发则为窍，而气发至本原处，则为生死窍，化无极之真，二五之精，\n"
						+"生生而化，妙合而凝，真气游走全身，生死窍亦随之转移。乃参大衍之数五十，其用四十有九，虚\n"
						+"其一，变化始生之道也。以形气转续为己息，以静穆无穷为内义，阴阳相依，纠缠相转，气淡而神凝，\n"
						+"沉而不浮，敛而不露，凝而不滞，收四海于囊中，含八荒于意下，是以太极真气得以源源不息，浩浩\n"
						+"乎若涌泉之凝聚，渺渺乎若烟湖之深溟，柔而纳万物，浑而吞天下，生死窍圆环游走，清静而微，其来\n"
						+"不可逢，其往不可追，迅即自身体境清明，脱胎换骨而力抵天下。.....左重则左虚，而右已去，右重\n"
						+"则右虚，而左已去......\n"NOR,
             ]));
     set("no_fight", 1);
     setup();
}

void init()
{
     
	 add_action("do_study", "yanjiu");
}

int do_study(string arg)
{
     object me;
     me = this_player();

     if ( !living(me) ) return 0;

     if ((int)me->query_skill("literate", 1) < 200)
		return notify_fail("你字也不认识几个(200),如何研读无上心法。\n");
	 if (me->query("family/family_name")!="武当派"||me->query("family/master_name")!="张三丰")
	 {
		 return notify_fail("你不是张真人的弟子，来此非奸即盗。\n");
	 }
	 if (!me->query_temp("tjsg/askzhang"))
	 {
		 return notify_fail("此处乃是张真人精修之所，你是如何来到的？没有张真人的指点，你是来不了此地的。\n");
	 }
	 if (time()-me->query("quest/wd/yyzq/taiji/time")<86400)
	 {
		 return notify_fail("你来的也太勤快了，真是武当好弟子。\n");
	 }
	 if (me->is_busy())
	 {
		 return notify_fail("你在忙碌中。\n");

	 }
	  if (me->quest_temp("tjsg/canwu"))
	 {
		 return notify_fail("你在参悟中，不得分心。\n");

	 }
     if ( arg =="wall" )
	 {
		if ( (int)me->query("jing")<30) 
		{ 
			write("你太累了，还是歇会再研读吧！\n");
			return 1;
		}
		if (me->query("quest/wd/yyzq/taiji/pass"))
		{
			write("你对着石壁研习一会，只觉所述早已尽藏心胸。\n");
			return 1;
		}
		if (me->query("quest/wd/yyzq/taiji/pass"))
		{
			write("你对着石壁研习一会，只觉所述早已尽藏心胸。\n");
			return 1;
		}
		message_vision("$N按照张真人的提醒开始面壁，两相印证，不断琢磨。\n", me);
		write("你静心研习石壁上的秘籍，对氤氲紫气的内功心法有些领悟。\n");
		me->receive_damage("jing", 40);
		me->receive_damage("jingli", 15);
		me->improve_skill("yinyun-ziqi", (int)me->query("int"));
		me->start_busy(999);
		me->set_temp("tjsg/canwu",1);
		call_out("thinking",1,me);
		
		return 1;
   }
}

int thinking(object me)
{
  int i,j,total;
  if(!me) return 0;
	
 if(me->query_temp("wdtaiji_canwu")<(10+random(10)))
    { 
	  me->add_temp("wdtaiji_canwu",1);
      if(random(2)) tell_object(me,HIG"\n你认真回想着刚才张真人你指点的内功心法奥秘并和墙上文字不断印证.\n"NOR);
             else tell_object(me,HIY"\n你聚精会神研究墙上的文字，突然间，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("wdtaiji_canwu");
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  23;
      if(me->query("y-card-vip")) j =  20;
      if(me->query("buyvip"))     j =  18;
	  i= random(j);
 
 
    if(i=2 
		&& random(total)>120
		&& random(me->query("kar"))>28)
	 {
		tell_object(me,HIC"\n你按照张三丰的指点，对照石壁上的经文彼此印证似乎有些心得。\n"NOR);
        tell_object(me, HIW"你按照张三丰所言，内息起自“长强穴”，随后自腰俞、阳关、命门、悬枢\n+"+
"诸穴，一路沿着脊椎上升，走的都是背上督任各个要穴，然后是脊中、中枢、筋缩、至阳、\n"+
"灵台、神道、身柱、陶道、大椎、痖门、风府、脑户、强间、后顶、而至顶门的“百会穴”。\n"NOR);
		tell_object(me,HIY"\n\n你历尽千辛万苦，终于得偿所愿，将太极神功融汇贯通。\n"NOR);
	
		me->set("quest/wd/yyzq/taiji/pass",1);
		me->set("title",HIC"太极宗师"NOR);
		me->set("mytitle/quest/taijititle",HBMAG+HIW"太极宗师"NOR);
		me->delete_temp("tjsg");
		me->start_busy(1);
		log_file("quest/yyzqtaiji", sprintf("%8s(%8s) 失败%d次后，彻底领悟氤氲紫气之太极神功的奥秘。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/wd/yyzq/taiji/fail"),i,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/wd/yyzq/taiji/fail",1);
		me->set("quest/wd/yyzq/taiji/time",time());
		
		tell_object(me,HIG"\n\n参悟太极神功失败！！\n"+HIY+"你经过自己的不断参悟，虽然听说过这武当太极神功的奥秘，可是对这氤氲紫气的太极真谛奥妙全然不得要领。\n\n"NOR);
		me->delete_temp("tjsg");
		me->start_busy(1);
		log_file("quest/yyzqtaiji", sprintf("%8s(%8s) 氤氲紫气之太极神功解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/wd/yyzq/taiji/fail"),i,me->query("combat_exp")) );
	  }
    	return 1;
  }

}

	

