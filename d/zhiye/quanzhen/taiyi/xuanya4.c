//Cracked by Kafei
// road: /zhongnan/xuanya4.c
// by sdong 08/98

inherit ROOM;
#include <ansi.h>
int do_climb(string arg);

void create()
{
		  set("short",HIW"崖顶"NOR);

		  set("long",@LONG
崖顶是个巨大的平台，积满了皑皑白雪。正中立着一块石碑，上面
似乎刻着一行大字(zi)。站在崖顶往四周望去，但见平烟茫茫，一望无
尽的云雾消失在天边，说不尽的潇潇之意。
LONG);

		  set("item_desc",(["zi" : "冬练三九，夏练三伏！王重阳题\n",]));

		  set("exits",([
			"east": __DIR__"fengdong",
			"west": __DIR__"bingdong",
							 ])
			  );
		  set("cost",4);
		  set("outdoors", "quanzhen");
	      setup();
}

void init()
{
	add_action("do_climb", "climb");
}


int do_climb(string arg)
{
	object me = this_player();
	int gain,cost;

	if(me->is_busy())
		return notify_fail("你还在忙着呢。\n");

	if(arg != "down" )
		return notify_fail("那个方向没法爬。\n");

	cost = ( 300-me->query_dex()*me->query_skill("dodge")/20 )/10;
	if ( cost<10 )cost = 10;
	cost *= 2;

	if( me->query("jing") < 30)
		return notify_fail("你累的实在爬不动了。\n");

	me->add("jing",-cost);
	gain = me->query("con",1)*2;
	gain *= 2;

	if ( me->query_skill("dodge") > 300 ) gain /= 2;

	me->improve_skill( "dodge",random( gain ) );
	if( me->query_skill( "jinyan-gong",1) > 0 )
		me->improve_skill( "jinyan-gong",random( gain ) );


	message_vision( HIY"\n$N在悬崖上攀藤附葛，小心谨慎的爬下去。\n"NOR, me);
	me->move(__DIR__"xuanya3");
	message_vision( HIY"\n$N爬了下来。\n"NOR, me);
	return 1;
}




