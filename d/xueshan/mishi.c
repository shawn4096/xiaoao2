// Room: mishi.c
// sohu@xojh 2014

#include <ansi.h>
#include <room.h>

inherit ROOM;
int do_open(string arg);
void create()
{
	set("short", HIC"塔楼密室"NOR);
	set("long", @LONG
这是一间小屋，北面是一个窗户，空气清新无比，
看样子应该是在高空之中。四面墙壁上绘制了大量的
佛教壁画，风声吹过，铃声不经意间响起，甚是幽静
房间西侧放置大量的书柜，密密麻麻地排满了书架。
一张桌子上放了一个佛龛，青烟袅袅，甚是庄重肃穆。
佛龛前供奉了一本经书(jingshu)。
LONG
	);
	//set("down", (["south" : __DIR__"fatang2",]));
	setup();
}
void init()
{
  object me,obj;
  me = this_player();
  me->start_busy(1);
  if (me->query_temp("lxbr/start"))
  {
   		tell_object(me,WHT"\n\n这是一间干净的禅房，空气流动，甚是干净，宛如空灵，面对经书忍不住想翻看（fankan）。\n"NOR);
		add_action("do_fan","fankan");
		add_action("do_open", "open");
   }      
   
}
//翻看经书

int do_fan(string arg)
{
    object me=this_player();
	if (!arg)
	{
		return notify_fail("你要翻看什么？\n");

	}
	if (arg !="jingshu" && arg !="经书")
		return notify_fail("你没事别乱动翻看？\n");
	
	if (me->query_temp("lxbr/start"))
	{
		tell_object(me,WHT"\n\n这是一本"HIY"《龙象般若经》"WHT"，表皮比较久远，看似已经存放很久了。\n"NOR);
		tell_object(me,HIC"\n\n你小心翼翼的翻开一页，之间扉页中有一行小字，龙象神功源自此经---金轮法王。\n"NOR);
		tell_object(me,HIY"\n\n这功夫循序渐进，本来绝无不能练成之理，若有人得享数千岁高龄，最终必臻第十三层境界，。\n"NOR);
		tell_object(me,HIY"只人寿有限，大轮寺中的高僧修士欲在天年终了之前练到第七层、第八层，便非得躁进不可。\n"NOR);
		tell_object(me,HIY"据历代笔记记载，北宋年间，吐番曾有一位高僧练到了第九层，继续勇猛精进，待练到第十层时，心魔骤起，\n"NOR);
		tell_object(me,HIY"无法自制，终于狂舞七日七夜，自绝经脉而死。甚憾甚憾！后辈中人当以此为鉴。\n"NOR);
		tell_object(me,HIY"\n\n有此经验，我自觉不负与其他人，潜修苦学，进境奇速，竟尔冲破第九层难关，此时已到第十层的境界，\n"NOR);
		tell_object(me,HIY"据那《龙象般若经》言道，此时每一掌击出，均具十龙十象的大力，吾自知再求进境，此生已属无望，\n"NOR);
		tell_object(me,HIY"但既已自信天下无敌手，即令练到第十一层，也已多余。但自从败于龙女和杨过夫妇后，吾以此为奇耻大辱。\n"NOR);
		tell_object(me,HIY"此去中原，不知何日能归，但吾修行之心得记录于此，望后辈小子能突破至更高的境界。\n"NOR);
        tell_object(me,HIY"\n\n后辈小子当可在此参悟(canwu)此经，龙象般若功乃天下第一神功。\n"NOR);
		
		me->set_temp("quest/lx/fan",1);
		//me->delete_temp("lxbr/start");
		add_action("do_canwu", "canwu");
		return 1;
	}
    else tell_object(me,HIC"这是一本《龙象般若经》,极为珍贵之物，不可随便翻看。\n"NOR);
	return 1;

}



int do_canwu(string arg)
{
	object me;
	int i,count,ht;

	me = this_player();

	ht=(int)me->query("lx/gree");
	if (!me->query_temp("quest/lx/fan") || !arg ||arg !="龙象般若经")
	{
		return notify_fail("你要参悟什么？\n");

	}
	if (me->query("family/family_name")!="大轮寺")
	    return notify_fail("你非我大轮寺弟子，所为何来？\n");
	if( time()-me->query("quest/dls/longxiang/time")<86400 )
		return notify_fail("你来的也太勤快了点？\n");
    if( ht==13 )
		return notify_fail("英雄，你已经完成龙象神功第"+ht+"层体炼，何须多此一举？\n");
	  

	if (me->query_skill("longxiang-boruo",1)<500)
	      return notify_fail("你龙象般若功太弱，参悟也没用。\n");

	if (ht==10 ) {
		   message_vision(HIC"你平心静气，开始不断翻阅《龙象般若经》并按照经中所载法门开始参悟第十一层龙象。\n"NOR,me);
           me->start_busy(999);
		   remove_call_out("thinking");
		   call_out("thinking",1,me);
	}
	else if (ht==11 )
	{
		   message_vision(HIY"你平心静气，开始翻阅《龙象般若经》并按照经中所载法门开始参悟第十二层龙象。\n"NOR,me);           
		   //me->set("title",HIY"大轮寺"HIM"龙象般若功初阶"NOR);
		   //me->set("mytitle/quest/banruo1title",HIY"大轮寺"HIM"龙象般若功初阶"NOR);
		   me->start_busy(999);
		   remove_call_out("thinking2");
		   call_out("thinking2",1,me);
	}
	else if (ht==12)
	{
		  message_vision(HIR"你平心静气，开始翻阅《龙象般若经》并按照经中所载法门开始参悟第十三层龙象。\n"NOR,me);

		  me->start_busy(999);
		  remove_call_out("thinking3");
		  call_out("thinking3",1,me); 
	 }
	return 1;

}

//第十一层
int thinking(object me)
{
  int i,j,x,lx; 
  if(!me) return 0;
  i=random(me->query("kar"));
  j = 20;
  if(me->query("m-card-vip")) j =  18;
  if(me->query("y-card-vip")) j =  15;
  if(me->query("buyvip"))     j =  10;
  j=random(j);

  me->set("quest/dls/longxiang/time",time());
  x=random(me->query("int"));
  lx=(int)me->query("lx/gree");
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟龙象般若功11层时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_longxiang")<(10+random(10)))
   {  
	  me->add_temp("canwu_longxiang",1);
      if(random(3)) tell_object(me,HIG"\n你对着《龙象般若经》的内容和法王所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
      else tell_object(me,HIY"\n你将自己一生所学实战经验融入到龙象般若经中，心里有所领悟...\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，超然物外，一幅高僧大德之态，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if ( me->query("lx/gree")==10
	   && i>=20
	   && j<6
	   && x>32
	   && me->query("kar")<31)
 	  { 
        
         me->start_busy(1);     
         message_vision(HIY"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断参悟，终于领悟了龙象般若功的第十一层修炼，龙象般若功更上一层楼，具有十一龙象之力。”\n"NOR,me); 
         log_file("quest/longxiang11", sprintf("%s(%s) 第%d次参悟失败后，机缘巧合下，成功参悟龙象般若功的第11层修炼，取值幸运值i：%d,当前随机值j：%d,当前经验：%d。当前富源kar：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/dls/longxiang/fail1"),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("kar")));

		 me->set("quest/dls/longxiang/time",time());
		 me->set("quest/dls/longxiang/pass",11);
		 me->set("lx/gree",11);
		 me->set("title",HIY"大轮寺"HIM"龙象般若功初阶"NOR);
		 me->set("mytitle/quest/banruo1title",HIY"大轮寺"HIM"龙象般若功初阶"NOR);
		 me->delete_temp("canwu_longxiang");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N参悟半天，忽觉全身龙象般若功劲气翻涌，顿时陷入走火入魔之态。”\n"NOR,me);
		 me->start_busy(10);
		 me->receive_wound("qi",random(5000),"走火入魔而");
		 me->apply_condition("hot_poison",2);

		 log_file("quest/longxiang11", sprintf("%s(%s) 龙象第11层参悟失败第%d次，取值幸运值i：%d,当前随机值j：%d,当前经验：%d。当前富源kar：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/dls/longxiang/fail1"),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("kar")));

		 me->set("quest/dls/longxiang/time",time());
		 me->add("quest/dls/longxiang/fail1",1);
		      
		 me->delete_temp("canwu_longxiang");
		 return 1;
   }


}
//参悟2段

int thinking2(object me)
{
  int i,j,x; 
  if(!me) return 0;
  i=random(me->query("kar"));
  j = 20;
  if(me->query("m-card-vip")) j =  18;
  if(me->query("y-card-vip")) j =  15;
  if(me->query("buyvip"))     j =  10;
  j=random(j);

  x=random(me->query("int"));
  me->set("quest/dls/longxiang/time",time());
  
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟龙象般若功12层时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_longxiang")<(10+random(10)))
   {  
	  me->add_temp("canwu_longxiang",1);
      if(random(3)) tell_object(me,HIG"\n你对着《龙象般若经》的内容和法王所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
      else tell_object(me,HIY"\n你将自己一生所学实战经验融入到龙象般若经中，心里有所领悟...\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，超然物外，一幅高僧大德之态，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking2");
	  call_out("thinking2",3+random(3), me);

   } 
   else if ((int)me->query("lx/gree",1)==11
	   && i>=25
	   && j<5
	   && x>35
	   && me->query("kar")<31)
 	  { 
        
         me->start_busy(1);     
         message_vision(HIY"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断参悟，终于领悟了龙象般若功的第十二层修炼，龙象般若功更上一层楼，具有十二龙象之力。”\n"NOR,me); 
         log_file("quest/longxiang12", sprintf("%s(%s) 第%d次参悟失败后，机缘巧合下，成功参悟龙象般若功的第12层修炼，取值幸运值i：%d,当前随机值j：%d,当前经验：%d。当前富源kar：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/dls/longxiang/fail2"),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("kar")));

		 me->set("quest/dls/longxiang/time",time());
		 me->set("quest/dls/longxiang/pass",12);
		 me->set("lx/gree",12);
		 me->set("title",HIY"大轮寺"HIM"龙象般若功中阶"NOR);
		 me->set("mytitle/quest/banruo1title",HIY"大轮寺"HIM"龙象般若功中阶"NOR);
		 me->delete_temp("canwu_longxiang");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N参悟半天，忽觉全身龙象般若功劲气翻涌，顿时陷入走火入魔之态。”\n"NOR,me);
		 me->start_busy(10);
		 me->receive_wound("qi",random(5000),"走火入魔而");
		 me->apply_condition("hot_poison",4);

		 log_file("quest/longxiang11", sprintf("%s(%s) 龙象第12层参悟失败第%d次，取值幸运值i：%d,当前随机值j：%d,当前经验：%d。当前富源kar：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/dls/longxiang/fail2"),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("kar")));

		 me->set("quest/dls/longxiang/time",time());
		 me->add("quest/dls/longxiang/fail2",1);
		      
		 me->delete_temp("canwu_longxiang");
		 return 1;
   }


}
//第十三层
int thinking3(object me)
{
  int i,j,x; 
  if(!me) return 0;
  i=random(me->query("kar"));
   j = 20;
  if(me->query("m-card-vip")) j =  18;
  if(me->query("y-card-vip")) j =  15;
  if(me->query("buyvip"))     j =  10;
  j=random(j);
  x=random(me->query("int"));
  me->set("quest/dls/longxiang/time",time());
  
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟龙象般若功13层时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_longxiang")<(10+random(10)))
   {  
	  me->add_temp("canwu_longxiang",1);
      if(random(3)) tell_object(me,HIG"\n你对着《龙象般若经》的内容和法王所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
      else tell_object(me,HIY"\n你将自己一生所学实战经验融入到龙象般若经中，心里有所领悟...\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，超然物外，一幅高僧大德之态，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking3");
	  call_out("thinking3",3+random(3), me);

   } 
   else if ((int)me->query("lx/gree",1)==12
	   && i>=27
	   && j==4
	   && x>=38
	   && me->query("kar")<31)
 	  { 
        
         me->start_busy(1);     
         message_vision(HIY"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断参悟，终于领悟了龙象般若功的第十三层修炼，龙象般若功更上一层楼，具有十三龙象之力。”\n"NOR,me); 
         log_file("quest/longxiang12", sprintf("%s(%s) 第%d次参悟失败后，机缘巧合下，成功参悟龙象般若功的第13层修炼，取值幸运值i：%d,当前随机值j：%d,当前经验：%d。当前富源kar：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/dls/longxiang/fail3"),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("kar")));

		 me->set("quest/dls/longxiang/time",time());
		 me->set("quest/dls/longxiang/pass",13);
		 me->set("lx/gree",13);
		 me->set("title",HIY"大轮寺"HIM"十三龙象真传"NOR);
		 me->set("mytitle/quest/banruo1title",HIY"大轮寺"HIM"十三龙象真传"NOR);
		 me->delete_temp("canwu_longxiang");
		 return 1;
     }
	 else {
	     message_vision(HIY"\n$N参悟半天，忽觉全身龙象般若功劲气翻涌，顿时陷入走火入魔之态。”\n"NOR,me);
		 me->start_busy(10);
		 me->receive_wound("qi",random(5000),"走火入魔而");
		 me->apply_condition("hot_poison",6);

		 log_file("quest/longxiang11", sprintf("%s(%s) 龙象第13层参悟失败第%d次，取值幸运值i：%d,当前随机值j：%d,当前经验：%d。当前富源kar：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/dls/longxiang/fail3"),
		 i,
		 j,
         me->query("combat_exp"),
		 me->query("kar")));

		 me->set("quest/dls/longxiang/time",time());
		 me->add("quest/dls/longxiang/fail3",1);
		      
		 me->delete_temp("canwu_longxiang");
		 return 1;
   }


}


int do_open(string arg)
{
       object gkey;
		object me=this_player();
		if (!me->query_temp("lxbr/start"))
			return notify_fail("你是怎么进来？\n");
		
		 if (!objectp(gkey=present("jin yaoshi",me)))
		{
			return notify_fail("你把掌门给你这么重要的钥匙都弄丢了，在这等着吧。\n");
		}
		if( arg == "door"||arg == "men" || arg == "门" || arg == "锁")
        {
			
			message_vision("$N将金钥匙拿出来，插入锁中，吱吱响后，推开这堵墙，打开出口。\n",me);
			if( !query("exits/down") ) 
			{
				set("exits/down", "/d/xueshan/jingtang");
				remove_call_out("close_path");
				message_vision(HIR"\n\n这把钥匙一不小心被$N掰断了。\n",me);
				destruct(gkey);
				call_out("close_path", 15);
			}
		}else return notify_fail("你要开什么？\n");

		
      
}
void close_path()
{
        if( !query("exits/down") ) return;
		message("vision","一会会，嗵的一声，墙又恢复原样。\n", this_object() );
		delete("exits/down");
}
