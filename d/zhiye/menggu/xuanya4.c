//Cracked by Kafei
// road: /zhongnan/xuanya4.c
// by sdong 08/98

inherit ROOM;
#include <ansi.h>
int do_climb(string arg);

void create()
{
		  set("short",HIC"悬崖"NOR);
		  set("long",@LONG
临近崖顶，山势险峻高耸，此时距离崖顶仅数长，崖边积满了皑皑
白雪。山崖左侧突出一块巨石，顺势向南延展,因此地山势陡峭,人际罕
至，山风较小，突出的山岩(shanyan)下传来一阵若隐若现的鹰鸣之声，
放眼望去，但见平烟茫茫，一望无尽的沙漠消失在天边，远处说不尽的
潇潇之意，几只巨大的黑雕在空中来回盘旋。似乎发现了什么。
LONG);

		  set("item_desc",(["shanyan" :
YEL"此地向南突出的岩石下，居然有一个非常大的鹰巢，里面
两只白雕真在不住鸣叫，大白雕外出觅食，不再巢内。\n"NOR,]));
		  set("exits",([
		//	"up": __DIR__"fengdong",
		//"west": __DIR__"bingdong",
							 ])
			  );
		set("cost",4);
		set("outdoors", "menggu");
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


	cost = ( 300-me->query_dex()*me->query_skill("dodge")/20 )/10;
	
	if ( cost<10 )cost = 10;
	cost *= 2;

	if( me->query("jing") < 30)
		return notify_fail("你累的实在爬不动了。\n");
	if(arg == "up" )
	{
		message_vision( HIY"\n$N在悬崖上攀藤附葛，一步步的爬上去。\n"NOR, me);
		me->move(__DIR__"yading");
		message_vision( HIY"\n$N爬了上来。\n"NOR, me);
		me->improve_skill( "dodge",(gain+random( gain ))/2 );
		if( me->query_skill( "jinyan-gong",1) > 0 )
			me->improve_skill( "jinyan-gong",random( gain ) );
		me->add("jing",-cost);
		return 1;
	}
	else if(arg == "down" )
	{
		message_vision( HIY"\n$N在悬崖上攀藤附葛，小心谨慎的爬下去。\n"NOR, me);
		me->move(__DIR__"xuanya3");
		message_vision( HIY"\n$N爬了下来。\n"NOR, me);
		return 1;
	}
	return 1;
}




