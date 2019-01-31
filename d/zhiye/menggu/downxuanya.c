// Room: /d/menggu/downxuanya.c

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "悬崖下");
	set("long", @LONG
陡峭的山崖壁立,漠北苦寒的风沙侵蚀,山崖更是光滑险峻.几柱矮
树平平从山石中伸出,铁灰色的山石愈行愈高,直与天空中的白云相接.
两头白色的大雕围绕着山崖边的一株松树鸣叫。向上看去，山崖陡峭
极为险峻。
LONG
	);
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/baidiao.c" : 2,
]));
	set("outdoors", "menggu");
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 1 */
	 // "up" : __DIR__"xuanya1",
	  "east" : __DIR__"xiaolu",
	]));

	setup();
	replace_program(ROOM);
}

void init()
{
	object me;
	me=this_player();
	add_action("do_climb", "climb");
	if (me->query_temp("jyg/askma")
		&&me->query_temp("jyg/askstt"))
	{
		message_vision(HIC"$N来到马玉道长所说的山崖下，向上，却见山崖陡峭，极为险要！\n"+
			"稍有不测可能摔下悬崖而亡！你愿意按照马钰道长所说去练习上天梯绝技么？(decide)\n"NOR,me);
		me->delete_temp("jyg/askma");
		me->delete_temp("jyg/askstt");
		me->set_temp("jyg/xuanyadown",1);
		add_action("do_decide","decide");
	}
}
int do_decide()
{
	object me;
	me=this_player();

	if (me->query_temp("jyg/xuanyadown"))
	{
		tell_object(this_player(),"你决定来此练习攀爬悬崖，一遍参悟这上天梯的奥妙！\n");
		me->set_temp("jyg/start",1);
		me->delete_temp("jyg/xuanyadown");
		me->start_busy(2);
	}
	return 1;
}

int do_climb(string arg)
{
	object me = this_player();
	int gain,cost;

	if(me->is_busy())
		return notify_fail("你还在忙着呢。\n");

	if( me->query_skill("dodge") < 135 && arg == "up" )
		return notify_fail("四面光溜溜的崖陡如壁，你轻功不够，怎么也爬不上去。\n");

	cost = ( 300-me->query_dex()*me->query_skill("dodge")/20 )/10;
	if ( cost<10 )cost = 10;
	cost = cost * 3;

	if( me->query("jing") < 30)
		return notify_fail("你累的实在爬不动了。\n");

	me->start_busy( 1 );

	me->add("jing",-cost);

	if( arg != "up" )
		return notify_fail("你已经站在山崖底下，那个方向没法爬。\n");

	gain = me->query("con",1)*2;
	gain *= 3;

	if ( me->query_skill("dodge") > 300 ) gain /= 2;

	me->improve_skill( "dodge",gain/2+random( gain ) );
	if( me->query_skill( "jinyan-gong",1) > 0 )
		me->improve_skill( "jinyan-gong",random( gain ) );


	if(arg == "up" )
	{
		message_vision( HIY"\n$N在悬崖上攀藤附葛，一步步的爬上去。\n"NOR, me);
		me->move(__DIR__"xuanya1");
		message_vision( HIY"\n$N战战兢兢爬了上去。\n"NOR, me);
		me->improve_skill( "dodge",(gain+random( gain ))/2 );
		me->add("jing",-cost);
		return 1;
	}
	
  return notify_fail("那个方向没法爬。\n");
}


