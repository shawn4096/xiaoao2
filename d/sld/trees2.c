// trees2.c
// 树林南2
//add by sohu, chansishou quest
#include <ansi.h>

inherit ROOM;
int do_guancha(string arg);

void create()
{
	set("short","树林");
	set("long",@long
这里的树长得都又高有大，粗大的树枝伸出来互相交叉在一起遮住了
阳光，地上是茂密的杂草，间杂着许多不知名的野花，散发出阵阵很好闻
的香气，在树上和杂草里有许多蛇在发出嘶嘶的声音。北边隐隐约约地好
象有几间竹屋。
long);
	set("exits",([
		 "north" : __DIR__"kongdi",
          "northeast" : __DIR__"treee1",
          "northwest" : __DIR__"treew1",
          "south" : __DIR__"trees1",
	]));
	set("objects",([
			__DIR__"snake/dushe2" : 2,
	]));
	set("outdoors", "神龙岛");
    set("canfindsnake",1);
    set("coor/x",490);
    set("coor/y",400);
    set("coor/z",0);
    setup();
}
void init()
{
	object me=this_player();
	if (me->query_temp("chansi/asksu"))
	{
		message_vision(HIC"$N站在树林间，想起苏荃的教导缠丝手的奥秘，隐约间似乎抓到了一丝明悟。\n"NOR,me);
		message_vision(HIY"\n\n\n$N思前想后很久，然后决定在树林中观察下，看是否能有心得。\n"NOR,me);
		me->set_temp("chansi/dunwu1",1);
		me->delete_temp("chansi/asksu");
		add_action("do_guancha","guancha");
	}	

}
	    	
int do_guancha(string arg)
{
	object me=this_player();
	me->start_busy(10);
	if (!arg||arg!="蛇")
		return notify_fail("你要观察什么？\n");
	if (me->query("quest/sld/chss/pass"))
		return notify_fail("你已经全部领悟了金蛇缠丝手的奥！\n");
	if (time()-me->query("quest/sld/chss/time")<86400)
		return notify_fail("你来的太勤快了！\n");
	if (me->query_temp("chansi/dunwu1")) 
	{
		   message_vision(HIR"你平心静气，匍匐在草丛中，开始观察树林中蛇的动作。\n"NOR,me);
           me->start_busy(999);
		   remove_call_out("thinking");
		   call_out("thinking",1,me);
		   me->delete_temp("chansi/dunwu1");
	}
	return;
}

int thinking(object me)
{
  int i,j,k; 
  if(!me) return 0;
  k=random(me->query("kar"));
  //杜绝男性，若有作弊，加大难度
  
  if (me->query("gender")=="男性") j=100+random(200);
  if(me->query("m-card-vip")) j =  17;
  if(me->query("y-card-vip")) j =  15;
  if(me->query("buyvip"))     j =  10;
	  i=random(j);
  me->set("quest/sld/chss/time",time());

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_chansi")<(10+random(5)))
   {  
	  me->add_temp("canwu_chansi",1);
      if(random(1)) tell_object(me,HIG"\n忽然，一条蛇窜到树上，缠绕前行。你对着林间蛇行和苏荃所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
      else tell_object(me,HIY"\n\n\n又一条蛇在和飞鹰在搏斗..。。蛇虽然被飞鹰捉住，但蛇猛然一窜将整个鹰卷成一团，...\n"
							+"\n飞鹰无法展翅，随机掉落在地上。蛇虽然溅血，但却得脱性命。\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (k>=22
			&& i<5
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断领悟，终于领悟了教主夫人所传授的金蛇缠丝手的奥秘，缠丝手豁然贯通！”\n"NOR,me); 
         log_file("quest/chansishou", sprintf("%s(%s) 成功！第%d次参悟，机缘巧合下，成功参悟金蛇缠丝手的缠丝奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/chss/fail"),
		 k,
		 i,
         me->query("combat_exp")));

		 me->set("quest/sld/chss/time",time());
		 me->set("quest/sld/chss/pass",1);
		 me->delete_temp("canwu_chansi");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来又是一无所获啊。”\n"NOR,me); 
		 message_vision(HIY"\n参悟金蛇缠丝手解密失败！\n"NOR,me); 
         log_file("quest/chansishou", sprintf("%s(%s) 失败！第%d次失败参悟金蛇缠丝手，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/chss/fail",1),
		 k,
		 i,
         me->query("combat_exp")));
        
		 me->add("quest/sld/chss/fail",1);
		 me->set("quest/sld/chss/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_chansi");
		 return 1;
   }

}