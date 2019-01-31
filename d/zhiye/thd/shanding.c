// Room: /u/numa/thd/shanding.c
// Modified by Numa 19980903

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"试剑峰顶"NOR);
        set("long",@LONG
这里就是试剑峰的峰顶，这里岩石林立，绝险之极，要想回去，又
是难度之极。但俯身向下望去，整个桃花岛一览无余。
LONG
        );
        set("no_clean_up", 0);
        set("outdoors","桃花岛");

        setup();
}

void init()
{
	add_action("do_jump","jump");
	add_action("do_jump","yue");
	add_action("do_sit","sit");
	//add_action("do_biguan","lingwu");
	add_action("do_biguan","biguan");
}

int do_jump(string arg)
{
	object me = this_player();
	
	if (me->is_fighting() || me->is_busy())
		return notify_fail("你正忙着呢！\n");
	if (arg!="ya") return 0;
	if(me->query_encumbrance() * 100 / me->query_max_encumbrance() > 20)
	        return notify_fail("你负重过多，恐怕难以跃过去。\n");
        if (me->query_skill("dodge") < 100)
                return notify_fail("你尝试跃向对岸的断崖，但却发现自己无法跃过去！\n");
        tell_room(environment(me), HIC+me->name()+"紧了紧随身物品，随即一招「随波逐流」跃向对岸断崖，稳稳的落在对面。\n" NOR, ({me}));
        write("你内息一提，纵身跃过断崖。\n");
        me->move(__DIR__"shanya");
        return 1;
}
int do_sit()
{
	object me=this_player();
	if (!me->query_temp("quest/thd/biguan/askhuang"))
	{
		return notify_fail("你盘膝做了下来，只觉耳边山风呼啸，景色很美！\n");

	}
	if (me->query_temp("quest/thd/biguan/start"))
	{
		return notify_fail("你已经盘膝做了下来！\n");

	}
	write(HIC"你盘膝做了下来，远眺远方海天一色，顿觉心旷神怡！\n");
	me->set_temp("quest/thd/biguan/start",1);
	return 1;

}

int do_biguan()
{
	int i,count,ht;

	object me=this_player();
	
	if (!me->query_temp("quest/thd/biguan/start"))
	{
		return notify_fail("你心思不静，即便闭关也难以领悟出什么惊天动地的武功！\n");

	}

	if (me->query("family/family_name")!="桃花岛"||me->query("family/master_name")!="黄药师")
	    return notify_fail("你不是桃花岛二代弟子所为何来？\n");
	
	if( time()-me->query("quest/thd/biguan/time")<86400 )
		return notify_fail("你来的也太勤快了点？\n");
    
	if (me->is_busy())
	{
		return notify_fail("你正在忙碌中....\n");
	}
	if (me->query("int")<50 || me->query("con")<50)
	      return notify_fail("你先天根骨或先天悟性不足50，即便闭关也是没有收获？\n");

	if (me->query_skill("qimen-bagua",1)<200 )
	      return notify_fail("你奇门八卦不足200，即便闭关也领悟不了这种奥妙？\n");
	
	message_vision(HIG"你碧海潮生功，默念桃花岛奇门八卦的奥义，开始闭关修炼。\n"NOR,me);
           me->start_busy(999);
		   remove_call_out("thinking");
		   call_out("thinking",1,me);
	return 1;

	
}
int thinking(object me)
{
  int i,j,t; 
  if(!me) return 0;
  i=random(me->query("kar"));
  //j=random(10);
  t = 25;
  if(me->query("m-card-vip")) t =  20;
  if(me->query("y-card-vip")) t =  18;
  if(me->query("buyvip"))     t =  15;
  t=random(t);
  j=me->query("int")+me->query("con");
  j=random(j);
  me->set("quest/thd/biguan/time",time());
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 桃花岛闭关时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("thd_biguan")<(10+random(10)))
  {  
	  me->add_temp("thd_biguan",1);
      if(random(3)==2) tell_object(me,HIG"\n你面对大海，结合黄药师所传授的心法彼此印证，只觉得脑海中一片空灵\n"NOR);
      else if (random(3)==1) tell_object(me,HIC"\n灵光一闪，忽然间你眼前浮现一片奇门八卦所布局的新格局，以前从没想过的境界\n"NOR);
      else tell_object(me,HIY"\n你将自己一生所学融入到碧海潮生功中，顿时有所领悟...\n"NOR);  
	  
	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (i>26
			&& t<3
			&& j>85
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(1);     
         message_vision(HIY"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIC"\n$N经过不断领悟，终于彻底将桃花岛所有武技和心法融为一体，武技更上一层楼。”\n"NOR,me); 
		 message_vision(HIC"\n$N忍不住仰天长啸，顿觉天下尽英豪不过如此而已的感觉。\n"NOR,me); 
		 message_vision(HBWHT+HIR"\n恭喜你，桃花岛闭关参悟一举突破，顿时面前一片坦途，天下虽大，尽可去得！\n"NOR,me); 

         log_file("quest/thdbiguan", sprintf("%s(%s) 第%d次参悟，机缘巧合下，成功闭关参悟桃花岛终极武技，当前幸运值：%d，当前随机数：%d,当前先天悟性和根骨：%d。当前经验：%d\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/thd/biguan/fail"),
		 i,
		 t,
		 j,
         me->query("combat_exp")));

		 //me->set("bhg/flhttime",time());
		 //me->set("bhg/biguan",1);
		 me->set("title",HBWHT+HIG"东邪"NOR);
		 me->set_skill("qimen-bagua",300);
		 me->set("quest/thd/biguan/pass",1);

		 me->delete_temp("thd_biguan");
		 me->delete_temp("quest/thd");
		 return 1;
     }
	 else {
	     message_vision(WHT"\n$N长叹一生，自言自语地说道：“看来又是一无所获啊。”\n"NOR,me); 
		 message_vision(HBYEL+HIR"\n桃花岛闭关失败!\n百尺竿头再进一步着实不易，但一定要坚持不懈。\n"NOR,me); 
         log_file("quest/thdbiguan", sprintf("%s(%s) 第%d次闭关参悟桃花岛武技失败，当前幸运值：%d，当前随机数：%d,当前先天悟性和根骨：%d。当前经验：%d\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/thd/biguan/fail"),
		 i,
		 t,
		 j,
         me->query("combat_exp")));

        
		 me->add("quest/thd/biguan/fail",1);
		 me->set("quest/thd/biguan/time",time());
		 me->start_busy(1);
		 me->delete_temp("thd_biguan");
		 me->delete_temp("quest/thd");
		 return 1;
   }


}	