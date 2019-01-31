#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "禅房");
        set("long", @LONG
这里是全真弟子修身养性、打熬气力的地方。为了方便练
功，桌椅都没有摆放，仅仅在地下丢了几个小蒲团。乃是在此
地参悟门中重要心法的场所。
LONG);
        set("exits", ([
                "east" : __DIR__"chanfang3",
                "west" : __DIR__"chanfang1",
                "south" : __DIR__"liangong",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
int init()
{

	add_action("do_sit","sit");
	add_action("do_stand","stand");
	add_action("do_canwu","canwu");
	
}
int do_sit()
{
	object me;
	me=this_player();
	if (me->query_temp("marks/sit"))
	{
		return notify_fail("你已经坐下了！\n");
	}
	message_vision(HIY"$N轻声走到一个蒲团前，五心向天，盘膝做了下来！\n"NOR,me);
	me->set_temp("marks/sit",1);
	return 1;

}
int do_stand()
{
	object me;
	me=this_player();
	if (!me->query_temp("marks/sit"))
	{
		return notify_fail("你根本就没有坐下，何谈站起来？！\n");
	}
	message_vision(HIY"$N长长伸了个懒腰，长出一口浊气，站起身来！\n"NOR,me);
	me->delete_temp("marks/sit");
	return 1;

}
int do_canwu(string arg)
{
	object me,*obj;
	int i,j,x,skill;
	me=this_player();
	obj = users();
	x = sizeof(obj);
	
	while(x--) {
		  if ( obj[x]->query_temp("canwu_yusuo")
			  && obj[x]->query_temp("marks/sit")
			  && obj[x]!=me
			  && environment(me)==environment(obj[x]))
			 {
				  message_vision(HIY"$N试图参悟金关玉锁诀，却发现"+obj[x]->query("name") +HIY"已经在哪儿打坐参悟，只得先行退出门外！\n"NOR,me);	
				  me->move("d/quanzhen/liangong");
				  return 1;
			}
			
	}
	
	
	i=(int)me->query("yusuo/degree")+1;
	skill=(int)me->query_skill("jinguan-yusuojue", 1);
	
	if (!arg||!(arg=="金关玉锁诀"||arg=="金关玉锁二十四诀"))
	{
		return notify_fail("你要在此地参悟什么？\n");
	}
	if (!me->query_temp("marks/sit"))
	{
		return notify_fail("你站着参悟？\n");
	}
	if (!present("yusuo jingyao",me))
	{
		return notify_fail("你身上并无金关玉锁诀精要，无从对照，无法参悟？\n");
	}
	
	if ((skill/100)<i) return notify_fail("你金关玉锁诀修炼感悟的太少，目前无法参悟。\n");
	
	
	if (me->query_temp("canwu_yusuo"))
	{
		return notify_fail("你正在参悟金关玉锁二十四诀？\n");
	}
	if (me->is_busy())
	{
		return notify_fail("你正在忙碌中！\n");
	}
	if (time()-me->query("quest/qz/jgysj/pass/time")<86400)
	{
		return notify_fail("参悟需要灵感和机缘，太频繁并不好！\n");
	}
	if (me->query("yusuo/degree")>8)
	{
		return notify_fail("你已经对金关玉锁诀修炼到第九重境界，彻底融会贯通！\n");
	}
	if (!me->query("quest/qz/dichuan"))
	{
		return notify_fail("你非核心弟子，无法参悟！\n");
	}

	if (me->query("party/gongji")<500)
	{
		return notify_fail("你的门派功绩不足500，要好好努力！\n");
	}
	

	me->query("party/gongji",-500);
	
	tell_object(me,HIC"你盘膝而坐，五心向天，对照怀中的《金关玉锁二十四诀》慢慢参悟起来！\n"NOR);
	
	me->set_temp("canwu_yusuo",1);
	me->start_busy(999);
	call_out("yusuo_thinking",1,me);
	return 1;
}
int yusuo_thinking(object me)
{
   int i,j;
   if (!me) return 0;
   i=(int)me->query("yusuo/degree");
   
   if(me->query_temp("canwu_yusuo")<(55+random(5)))
   { 
	  me->add_temp("canwu_yusuo",1);
      if(random(2)) tell_object(me,HIG"\n你一边翻阅手中的《金关玉锁二十四诀精要》一边不断运气冲关，两相印证。\n"NOR);
             else tell_object(me,HIY"\n突然间，你灵光一闪，似乎悟道些诀窍...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，一片平和。\n"NOR, ({}));
	  remove_call_out("yusuo_thinking");
	  call_out("yusuo_thinking",3+random(3), me);
   }
   else
   {  
	  me->delete_temp("canwu_yusuo");
      j = 20;
      if(me->query("m-card-vip")) j =  18;
      if(me->query("y-card-vip")) j =  15;
      if(me->query("buyvip"))     j =  10;
	  j= random(j);
 	
		tell_object(me,HIG"\n你回想着师傅的指点，对金关玉锁二十四诀的真正奥妙似乎有些心得。\n"NOR);
		 //悟性30+300为基础
		if(j<5 
			&& me->query("kar")<31
			&& random(me->query_int(1))>(50+i)
			&& random(me->query("kar"))>(17+i))
		 {
			
			tell_object(me,CYN"\n\n你只觉一股真气浩荡而起，瞬间沿着任督二脉走了一圈，完成一个小循环! \n"NOR);
			me->add("yusuo/degree",1);
			tell_object(me,HBYEL+HIW"\n\n恭喜你顺利参悟金关玉锁诀第"+chinese_number(i+1)+"重境界! \n"NOR);
			me->start_busy(1);
			me->delete_temp("canwu_yusuo");
			log_file("quest/qzyusuo", sprintf("%8s(%8s) 失败%d次后，领悟金关玉锁二十四诀绝技第%d重境界。j取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/qz/jgysj/pass/fail"),me->query("yusuo/degree"),j,me->query("combat_exp")) );
		 }
		 else
		 {
			me->add("quest/qz/jgysj/pass/fail",1);
			me->set("quest/qz/jgysj/pass/time",time());
			
			tell_object(me,HIY"\n\n你参悟半天，虽然知晓金关玉锁诀的奥秘，可是对如何融汇贯通的真正奥妙全然不得要领。\n\n"NOR);
			tell_object(me,HBBLU+HIW"\n\n解密金关玉锁诀失败，再接再厉。\n\n"NOR);
			me->start_busy(1);
			me->delete_temp("canwu_yusuo");
			log_file("quest/qzyusuo", sprintf("%8s(%8s) 金关玉锁第%d重境界时，解密失败%d次。j取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/qz/jgysj/pass/fail"),me->query("yusuo/degree"),j,me->query("combat_exp")) );
		  }

		return 1;
  }

}

int valid_leave(object me, string dir)
{	   

		
		if (dir =="south" && me->query_temp("marks/sit") ) 
		{		   	   
				
				return notify_fail("你坐在地上尚未起身，如何能行动？。\n");
				
		}
		
        return ::valid_leave(me, dir);
}
