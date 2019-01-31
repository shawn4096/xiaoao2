// Room: /d/huashan/shahong.c
// Date: Look 99/03/25
#include <ansi.h>

inherit ROOM;
int do_jump(string arg);
int do_kang(string arg);
int do_pai(string arg);


void create()
{
        set("short", "山洪瀑布");
        set("long", @LONG
转过一个山峡，水声震耳欲聋，只见山峰间一条白龙似的瀑布奔泻而下，
冲入一条溪流，奔胜雷鸣，湍急异常，水中挟著树枝石块，转眼便流得不知
去向。溪流(river)的中心有一块巨石(stone)。水花飞溅，四顾水气蒙蒙，
蔚为奇观。那山洪势道猛烈，令人颇有惧意，还是别乱来的好。
LONG
        );
       set("exits", ([ 
        "southwest" : __DIR__"shaluo",
	]));
	set("item_desc", ([
        "river" : "山水由瀑布冲入溪流，所以异常湍急。\n",
        "stone" : "一块巨大的岩石，正慢慢地被山洪淹盖吞噬，踹急的水流不时夹裹一些石头冲下来。\n",
	]));
       set("outdoors", "华山" );

       set("coor/x",60);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}

void init()
{
	add_action("do_jump","jump");
	add_action("do_pai","pai");
	add_action("do_kang","kangheng");

}
int do_jump(string arg)
{
		object me=this_player();
		if (arg=="back")
		{
			message_vision(HIC"$N轻身一纵，回到岸边。\n"NOR,me);
			me->delete_temp("shpb");
			return 1;
		}
		if (me->query_skill("dodge",1)<50)
			return notify_fail("水流踹急，你的基本轻功太弱，不足50，迈不过去。\n");
		if (!arg || arg!="river")
			return notify_fail("你要往哪儿迈。\n");
		message_vision(HIC"$N运起轻功，轻轻一纵，越过水流，到达岩石之上。\n"NOR,me);
		tell_object(me,HIC"这是江心的一块大岩石，你站在这里，见水流踹急，可以尝试如下两种行为。\n"NOR);
		tell_object(me,HIC"可以尝试跃入水中以内功抗衡这踹急的水流，（kangheng river）。\n"NOR);
		tell_object(me,HIC"也可以尝试以掌力拍飞上游漂下来的山石，（pai stone）。\n"NOR);
		tell_object(me,HIC"返回岸边指令为，（jump back）。\n"NOR);
		me->set_temp("shpb/yue",1);
		return 1;
}

int do_kang(string arg)
{
		object me=this_player();
		if (!me->query_temp("shpb/yue"))
				return notify_fail("水流踹急，你距离江心太远，无法抗衡这水流。\n");
        if (me->is_busy())
			 return notify_fail("你正在忙碌中。\n");
		if (me->query_skill("force",1)<50)
			return notify_fail("水流踹急，你的基本内功太弱，不足50，迈不过去。\n");
		if (!arg || arg!="river")
			return notify_fail("你要在那里抗衡？。\n");

		message_vision(HIC"$N深吸一口气，从岩石上跳入水中，憋住一口气和踹急的水流抗衡。\n"NOR,me);
		
		me->add_busy(1+random(1));
		
		me->receive_damage("jingli",10+random(10),"莫名其妙而");
		if (me->query_skill("force",1)<120)
		{		
			message_vision(YEL"\n$N受水流的冲刷，体力很快消耗，但内力却得到显著的增长。\n"NOR,me);
			me->improve_skill("force",(int)me->query_int());

		}else {

			message_vision(CYN"$N在水中轻松游走，甚是惬意,显然对于内功修为已经感觉不到丝毫裨益了。\n"NOR,me);

		}
		return 1;

}
int do_pai(string arg)
{
		object me=this_player();
		if (!me->query_temp("shpb/yue"))
				return notify_fail("水流踹急，你距离江心太远，无法拍水中的流石。\n");
        if (me->is_busy())
			 return notify_fail("你正在忙碌中。\n");
		if (me->query_skill("strike",1)<50)
			return notify_fail("你的基本掌法太弱，不足50，拍过去无异于找死啊。\n");
		if (!arg || arg!="stone")
			return notify_fail("你要拍什么？。\n");

		message_vision(HIY"上游在水流的带动下，一块小石头飞速向$N砸来！\n"NOR,me);
		me->add_busy(1+random(1));
		message_vision(HIG"$N运内力与掌，拍向那块小石头（stone），一掌拍飞！\n"NOR,me);
		if (random(me->query("neili"))<200)
		{
			message_vision(RED"上游忽然出现一块比较大点的石头，此时你内力损耗厉害，力有所不及，为这块石块所伤。\n"NOR,me);
			me->receive_damage("qi",20+random(10),"莫名其妙而");
		}
		me->receive_damage("jingli",15+random(10),"莫名其妙而");
		if (me->query_skill("strike",1)<120)
		{		
			
			me->improve_skill("strike",(int)me->query_int());

		}else {

			message_vision(HIC"$N在水中轻松游走，甚是惬意,显然对于内功修为已经感觉不到丝毫裨益了。\n"NOR,me);

		}
		return 1;

}


int valid_leave(object me, string dir)
{
	
	if( dir=="southwest" && me->query_temp("shpb/yue") )
		return notify_fail(CYN"这位"+RANK_D->query_respect(me)+"你正在溪水当中呢。\n"NOR);
	return ::valid_leave(me, dir);
}