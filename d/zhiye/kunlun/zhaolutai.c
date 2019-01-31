// jingshenfeng.c 惊神峰

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short","朝露台"NOR);
	set("long",@long
这里是昆仑山顶的一个大平台，突兀地斜插天空，走到这里，一览无余
山顶松林掩映，苍松叠翠。空中云卷云舒，但却丝毫感觉不到一丝的风声，
山壁如被人一刀切开，甚是平整，“朝露台”三个大字甚是遒劲。显然是人
以利刃所刻画。山前靠近悬崖边上有一石板，甚是光滑。
long);

        set("objects",([
          //CLASS_D("kunlun")+ "/hezudao" : 1,
        ]));

        set("exits", ([
              "south" : __DIR__"jingshenfeng",
        ]));
	set("outdoors", "昆仑");
	setup();
}
void init()
{

	if (this_player()->query_temp("hundun/askhe",1))
	{
		message_vision(HIC"$N忽觉眼前一片开阔，竟然来到一条人迹罕至的场所来！\n"NOR,this_player());
		add_action("do_guanwu","guanwu");
		add_action("do_sit","sit");

	}else
	{
		message_vision(HIY"$N越走越糊涂，竟然又走了回来！\n"NOR,this_player());
		this_player()->move("d/kunlun/jingshenfeng");
	}

}
int do_sit(string arg)
{
	object me=this_player();
	
	if (me->query_temp("quest/kl/lyj/hundun/pass"))
	{
		return notify_fail("你胸藏剑意，对于山云带来的怪风早已习以为常，岿然不动！\n");
	}
	if (time()-me->query("quest/kl/lyj/hundun/time")<86400)
	{
		me->move("d/kunlun/jingshenfeng");
		return notify_fail("你来的如此频繁，对武功不宜！\n");
	}
	if (me->query_temp("hundun/sit")||!me->query_temp("hundun/askhe"))
	{
		me->start_busy(1);
		return notify_fail("空山寂寥，山风呼啸，空中云卷云舒，你的心境甚是糟糕。\n");

	}
	if (me->is_busy())
	{

		return notify_fail("你现在正忙碌中。\n");
	}
	if (!arg||arg!="石板")
	{
		return notify_fail("你要坐那儿？");
	}
	message_vision("$N坐在石板上，五心向天，进入一种空明状态。\n",me);
	me->start_busy(999);
	
	call_out("thinking",1,me);
	return 1;

}
int thinking(object me)
{
  int i,j,k;
  if(!me) return 0;
	
  if(me->query_temp("liangyi/hundun")<(10+random(10)))
    { 
	  me->add_temp("liangyi/hundun",1);
      if(random(5)) tell_object(me,HIW"\n白云在蓝天上悠然的飘来飘去.\n"NOR);
             else {
				 tell_object(me,HIY"\n突然间，一阵山风吹来，将白云裹将起来，瞬间弥漫在这山石之间，\n"NOR);
				 tell_object(me,HIB"\n你仿佛置身于一朵大棉花之中，如若云中，天地寂寥，神魂皆震。\n"NOR);
				 tell_object(me,HIB"\n你心中巨震，如若将这门技巧融合到剑招之中岂不是会有莫大的威力？。\n"NOR);
				 me->add_temp("liangyi/guanyun",1);
				 }
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
   else
   {  
	  me->delete_temp("liangyi/hundun");
      j = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
	  i= random(i);
	  j=random(me->query("int"));
	  k=random(me->query("kar"));
 
    if(i<4 
		&& j>=40
		&& k>=26
		&& me->query_temp("liangyi/guanyun"))
	 {
		tell_object(me,HIG"\n你按照何足道的指点，对混沌剑网的真正奥妙似乎有些心得。\n"NOR);
        tell_object(me, HIW"\n又一阵横切的山风吹来，和先前那股山风正好相冲相合，你感觉自己宛如处于"+
							"一片混沌网中，前后左右不断摇晃，甚至山风剧烈，要将你抬起身来。你心中大惊。\n"+
							"稍有不慎就将跌入山崖粉身碎骨！\n"NOR);
		tell_object(me, HIB"\n就在此时，你心中一片空明，谨记何足道的教导，守住心关，对抗这团怪异的云团"+
							"虽然精力不断流失，但你却不断琢磨其中的意味。\n"+
							"就在你魂不守舍之际，你心中忽然电闪雷鸣，顿时领悟了这混沌风云的原理！\n"NOR);
		tell_object(me,HIY"\n\n\n恭喜！你历尽千辛挖苦，终于得偿所愿，将混沌剑网绝技融汇贯通。\n"NOR);
       
		me->set("quest/kl/lyj/hundun/pass",1);
		me->set("title",HIG"两仪剑混沌诀真传"NOR);
		me->set("mytitle/quest/lyjtitle",HIG"两仪剑混沌诀真传"NOR);
		me->start_busy(1);
		log_file("quest/klhundun", sprintf("%8s(%8s) 失败%d次后，彻底领悟混沌剑网的绝技。i取值：%d|随机悟性j取值：%d|随机富源k取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/kl/lyj/hundun/fail"),i,j,k,me->query("combat_exp")) );
	 }
	 else
	 {
		me->add("quest/kl/lyj/hudndun/fail",1);
		me->set("quest/kl/lyj/hundun/time",time());
		tell_object(me,HIY"\n\n忽然，一阵怪风吹来，将你的领悟意境打断，你甚是懊恼的站了起来。\n\n"NOR);

		tell_object(me,HIY"\n\n虽然感受到了混沌剑网的奥秘，可是对这门绝技真正奥妙全然不得要领。\n\n"NOR);
		me->start_busy(1);
		me->delete_temp("hundun");
		me->delete_temp("liangyi");
		log_file("quest/klhundun", sprintf("%8s(%8s) 混沌剑网解密失败%d次。i取值：%d|随机悟性j取值：%d|随机富源k取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/kl/lyj/hundun/fail"),i,j,k,me->query("combat_exp")) );
	  }
    	return 1;
  }



}
