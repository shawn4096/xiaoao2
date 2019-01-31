// Room: /d/tianshan/shishi.c
// By Linux

#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", "秘密石室");
	set("long", @LONG
这里是灵鹫宫的秘密石室，只见石室四壁岩石打磨得甚是光滑，石壁上刻
满了无数径长尺许的圆圈，每个圈中都刻了各种各样的图形，有的是人像，有
的是兽形，有的是残缺不全的文字，更有些只是记号和线条，圆圈旁注著「甲
一」、「甲二」、「子一」、「子二」等数字，圆圈之数若不逾千，至少也有
八九百个，墙上似乎有一行小字(Zi)，南边的墙上覆盖了一层厚厚的冰块。
LONG);   
	 set("item_desc", ([                    
                "zi": HIW"\n此墙左边是吾刻的是天山六阳掌要诀，右边是天山折梅手口诀。把南边墙\n"+
			"上的冰块(south bing)打破可以离开石室。\n\n"+
			"		                        天山童姥字\n\n"NOR,
        ])); 
	setup();
}

void init()
{
	add_action("do_learn", ({"yanxi", "learn"}));    
	add_action("do_break", ({"break", "po"}));
	add_action("do_biguan", ({"biguan", "huantong"}));
}

int do_learn(string arg)
{
	object me;
	int improve, cost;
	
	me = this_player();
	improve = me->query_int() / 10 + random(me->query_int() * 5 / 6);
 
	  
	   if( !arg || arg=="" ) return 0;
    
	
	   if (!me->query("quest/tonglao/pass"))
	      return notify_fail("你没有受到童姥指点，看了半天什么也看不清楚。\n");

	   if (arg == "east wall" ){             
		//if( !me->query("tonglao/ok"))  
		if (!me->query("quest/tonglao/pass"))
			return notify_fail("你看着墙壁看了半天，也不明白上面写的是什么。\n");
		if(me->query_skill("liuyang-zhang", 1) > 220 )  
			return notify_fail("墙上的六阳掌要诀对你来说太浅了。\n");

		cost = 300 / (int)me->query("int");
		cost = 300 / (int)me->query("int");

		if ((int)me->query("jingli") < cost || (int)me->query("jing") < cost){
			message_vision("$N专心的看着墙上的六阳掌要诀，突然头昏脑胀。\n",me);
			me->unconcious();
			return 1;
		} 
		message_vision("$N默诵六阳掌要诀，不由在石室里比划起来。\n",me);  
		me->improve_skill("liuyang-zhang", improve);            
		me->add("jing", -cost);
		me->add("jingli", -cost);                        
		return 1;
	}
	if (arg == "west wall" ){             
		if( !me->query("quest/tonglao/pass"))  
			return notify_fail("你看着墙壁看了半天，也不明白上面写的是什么。\n");
		if(me->query_skill("zhemei-shou", 1) > 220 )  
			return notify_fail("墙上的折梅手口诀对你来说太浅了。\n");

		cost = 300 / (int)me->query("int");
		cost = 300 / (int)me->query("int");

		if ((int)me->query("jingli") < cost || (int)me->query("jing") < cost){
			message_vision("$N专心的看着墙上的折梅手口诀，突然头昏脑胀。\n",me);
			me->unconcious();
			return 1;
		} 
		message_vision("$N默诵折梅手口诀，不由在石室里比划起来。\n",me);  
		me->improve_skill("zhemei-shou", improve);            
		me->add("jing", -cost);
		me->add("jingli", -cost);                        
		return 1;
	}
	return 0;
}

int do_break(string arg)
{
	object me;
	me = this_player();
	if( !arg || arg=="" ) return 0;
	if (arg == "south bing" ){   
		message_vision("冰面应声而碎，现出一个大洞。\n", me); 
		message_vision("$N弯下身子，钻进了那个大洞，外面一阵寒风吹过，大洞又被积雪盖住了。\n", me);                      
		me->move(__DIR__"shanjin1");
		message("vision", me->name() + "从旁边一个不引人注目的大洞里钻了出来。\n",environment(me), ({me}) );
		return 1;
	}
	return 0;
}

int do_biguan()
{
	object me;
	int i,count,ht;
	me = this_player();
	count=me->query("age");
	ht=(int)me->query("bhg/biguan");
	if (me->query("family/family_name")!="灵鹫宫"||me->query("family/master_name")!="虚竹")
	    return notify_fail("你所为何来？\n");
	
	if( time()-me->query("bhg/flhttime")<86400 )
		return notify_fail("你来的也太勤快了点？\n");
    if( ht==3 )
		return notify_fail("英雄，你已经完成返老还童体炼"+ht+"，何须多此一举？\n");
	if (me->is_busy())
	{
		return notify_fail("你正在忙碌中....\n");
	}
	if (!me->query("quest/tonglao/pass"))
	      return notify_fail("你没有受到童姥指点，闭什么关？还什么童？\n");
	if (me->query("age")<20)
	      return notify_fail("你年级轻轻，不足20岁，瞎掺合什么？\n");
	    //30岁以前必须闭关一次，否则永远失去机会
	//message_vision(HIR"biguan="+ht+"\n"NOR,me);
	if (ht<1 && me->query("age")<60) {
		   message_vision(HIR"你运转八荒六合唯我独尊功，开始进行第一次返老还童修炼。\n"NOR,me);
           me->start_busy(999);
		   remove_call_out("thinking");
		   call_out("thinking",1,me);
	}
	else if (me->query("bhg/biguan")==1 )
	{
           if (me->query("age")<30)
              return notify_fail("你已经完成第一次返老还童修炼，30岁后方可以进行第二次修炼。\n");
		   message_vision(HIR"你运转八荒六合唯我独尊功，开始进行第二次返老还童修炼。\n"NOR,me);
           if (me->query("int")<35)
           {
			   return notify_fail("你的先天悟性不足35，请努力修炼\n");
           }
		   me->start_busy(999);
		   remove_call_out("thinking2");
		   call_out("thinking2",1,me);
	}
	else if (me->query("bhg/biguan")==2)
	{
           message_vision(HIR"你运转八荒六合唯我独尊功，开始进行第三次返老还童修炼。\n"NOR,me);
			if (me->query("int")<40)
           {
			   return notify_fail("你的先天悟性不足40，请努力修炼\n");
           }
		   
		   me->set("mytitle/quest/bahuang1title",HIC"天山童姥传人"NOR);
           me->set("mytitle/quest/bahuang2title",HIG"灵鹫宫少主"NOR);			   
		 
		   me->start_busy(999);
		   remove_call_out("thinking3");
		   call_out("thinking3",1,me);
	 }
	
}


int thinking(object me)
{
  int i,j,t; 
  if(!me) return 0;
  i=random(me->query("kar"));
  //j=random(10);
  t = 18;
  if(me->query("m-card-vip")) t =  16;
  if(me->query("y-card-vip")) t =  12;
  if(me->query("buyvip"))     t =  8;
  j=random(t);

  me->set("bhg/flhttime",time());
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟八荒六合唯我独尊功时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_huantong")<(10+random(10)))
   {  
	  me->add_temp("canwu_huantong",1);
      if(random(1)) tell_object(me,HIG"\n你对着墙壁的内容和童姥所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
      else tell_object(me,HIY"\n你将自己一生所学融入到八荒六合唯我独尊功中，心里有所领悟...\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if ((int)me->query("bhg/biguan",1)< 1 
	   && i>=26
	   && j<3
	   && me->query("kar")<31)
 	{ 
        
         me->start_busy(1);     
         message_vision(HIC"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIC"\n$N经过不断领悟，终于领悟了八荒六合唯我独尊功的第一次返老还童修炼，武技更上一层楼。”\n"NOR,me); 
         log_file("quest/bhgbiguan1", sprintf("%s(%s) 第%d次参悟，机缘巧合下，成功参悟八荒六合唯我独尊功的第一次返老还童，当前幸运值：%d,当前经验：%d。年龄：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("bhg/flht/fail1"),
		 i,
         me->query("combat_exp"),
		 me->query("age")));

		 me->set("bhg/flhttime",time());
		 me->set("bhg/biguan",1);
		 me->set("title",HIC"天山童姥传人"NOR);
		 me->set("mytitle/quest/bahuang1title",HIC"天山童姥传人"NOR);	
		 
		 me->delete_temp("canwu_huantong");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来又是一无所获啊。”\n"NOR,me); 
		 message_vision(HIY"\n参悟八荒六合唯我独尊第一次返老还童失败。\n"NOR,me); 
         log_file("quest/bhgbiguan1", sprintf("%s(%s) 第%d次失败参悟八荒六合唯我独尊功的第一次返老还童，当前幸运值：%d,当前经验：%d。年龄：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("bhg/flht/fail1",1),
		 i,
         me->query("combat_exp"),
		 me->query("age")));
        
		 me->add("bhg/flht/fail1",1);
		 me->set("bhg/flhttime",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_huantong");
		 return 1;
   }


}
//参悟2段
int thinking2(object me)
{
  int i,j,t; 
  if(!me) return 0;
  i=random(me->query("kar"));
  t = 20;
  if(me->query("m-card-vip")) t =  18;
  if(me->query("y-card-vip")) t =  15;
  if(me->query("buyvip"))     t =  10;
  j=random(t);

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟八荒六合唯我独尊功时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),         
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_huantong")<(20+random(20)))
   {  
	  me->add_temp("canwu_huantong",1);
      if(random(2)) tell_object(me,HIG"\n你对着墙壁的内容和童姥所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
      else tell_object(me,HIY"\n你将自己一生所学融入到八荒六合唯我独尊功中，心里有所领悟...\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking2");
	  call_out("thinking2",3+random(3), me);

   } 
   else if (me->query("bhg/biguan")==1 && i>26 && j<3)
 	  { 
         me->delete_temp("canwu_biguan");
         me->start_busy(1);     
         message_vision(HIY"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         tell_object(me,HIR"\n你通过本次参悟返老还童，成功的完成第二次返老还童！\n"NOR);
         log_file("quest/bhgbiguan2", sprintf("%s(%s) 第%d次参悟，机缘巧合下，成功参悟八荒六合唯我独尊功的第二次返老还童，当前幸运值：%d,当前随机数:%d,当前经验：%d。年龄：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("bhg/flht/fail2",1),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("age")));
		 me->set("bhg/flhttime",time());
		 me->set("title",HIG"灵鹫宫少主"NOR);
		 me->set("mytitle/quest/bahuang2title",HIG"灵鹫宫少主"NOR);	

		  me->delete_temp("canwu_huantong");
		 me->set("bhg/biguan",2);
		 return 1;
      }
	 else {
	     message_vision(HIC"\n$N长叹一生，自言自语地说道：“看来又是一无所获啊。”\n"NOR,me); 
		 message_vision(HIY"\n参悟八荒六合唯我独尊第二次返老还童失败。\n"NOR,me); 
         log_file("quest/bhgbiguan2", sprintf("%s(%s) 第%d次失败参悟八荒六合唯我独尊功的第二次返老还童，当前幸运值：%d,当前经验：%d。年龄：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("bhg/flht/fail2",1),
		 i,
	     j,
         me->query("combat_exp"),
		 me->query("age")));
        
		 me->add("bhg/flht/fail2",1);
		 me->set("bhg/flhttime",time());

		 me->start_busy(2);
		  me->delete_temp("canwu_huantong");
		 return 1;
   }


}

int thinking3(object me)
{
  int i,j,t; 
  if(!me) return 0;
  i=random(me->query("kar"));
  t = 25;
  if(me->query("m-card-vip")) t =  24;
  if(me->query("y-card-vip")) t =  20;
  if(me->query("buyvip"))     t =  15;
  j=random(t);

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟八荒六合唯我独尊功时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),        
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_huantong")<(10+random(10)))
   {  
	  me->add_temp("canwu_huantong",1);
      if(random(2)) tell_object(me,HIG"\n你对着墙壁的内容和童姥所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
      else tell_object(me,HIY"\n你将自己一生所学融入到八荒六合唯我独尊功中，心里有所领悟...\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking3");
	  call_out("thinking3",3+random(3), me);

   } 
   else if (me->query("bhg/biguan")==2 
	   && i>27
	   && me->query("kar")<30
	   && j<2)
 	  { 
         me->delete_temp("canwu_biguan");
         me->start_busy(1);     
         message_vision(HIC"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         tell_object(me,HIR"\n你通过本次参悟返老还童，成功的完成第三次返老还童！\n"NOR);
         log_file("quest/bhgbiguan3", sprintf("%s(%s)机缘巧合下，在第%d次参悟，成功参悟八荒六合唯我独尊功的第三次返老还童，当前幸运值：%d,当前随机数：%d,当前经验：%d。年龄：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("bhg/flht/fail3",1),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("age")));
		 me->set("bhg/flhttime",time());
		  me->delete_temp("canwu_huantong");
		  me->set("bhg/biguan",3);
		//  me->set("title",HIR"天山童姥传人"NOR);

		  me->set("title",HIY"八荒六合"HIR"唯我独尊"NOR);
		  me->set("mytitle/quest/bahuang3title",HIY"八荒六合"HIR"唯我独尊"NOR);
		 return 1;
      }
	 else {
	     message_vision(HIC"\n$N长叹一生，自言自语地说道：“看来又是一无所获啊。”\n"NOR,me); 
		 message_vision(HIY"\n参悟八荒六合唯我独尊第三次返老还童失败。\n"NOR,me); 
         log_file("quest/bhgbiguan3", sprintf("%s(%s) 第%d次失败参悟八荒六合唯我独尊功的第三次返老还童，当前幸运值：%d,当前随机数:%d,当前经验：%d。年龄：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("bhg/flht/fail3",1),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("age")));
        
		 me->add("bhg/flht/fail3",1);
		 me->set("bhg/flhttime",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_huantong");
		 return 1;
   }


}



