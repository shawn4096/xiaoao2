// Room: /d/suzhou/bingying.c
// Date: May 31, 98  Java
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "第六指挥所");
	set("long", @LONG
这里是兵营，密密麻麻到处都是官兵，有的在武将的指挥下列队操
练，有的独自在练功，有的坐着、躺着正在休息。南墙下坐着主帅，不
动声色地寻视着四周。看到你进来，他们全都向你包围了过来，形势看
来不太妙。
LONG );
	set("outdoors", "杭州");
	set("exits", ([
		"north"  : __DIR__"bingyinggate",

	]));
	set("objects", ([
		"/d/city/npc/wujiang": 1,
		"/d/hz/npc/duantiande": 1,
		"/d/city/npc/bing": 4,
	]));
	setup();
	//replace_program(ROOM);
}

int init()
{
	add_action("do_zhua",({"zhuazhu","zhua","catch","sha"}));
	
}

int do_zhua(string arg)
{
	object me,duan;
	me=this_player();
	if (me->is_fighting())
	{
		return notify_fail("你正在战斗中，如何来刺杀段天德？\n");
	}
	if (present("jinguo gaoshou",this_object()))
	{
		return notify_fail("金国高手正在和你战斗中，如何来刺杀段天德？\n");
	}
	if (!objectp(duan=present("duan tiande",this_object())))
	{
		return notify_fail("段天德不在此地，如何来刺杀段天德？\n");
	}
	if ((arg=="duan"||arg=="duan tiande"||arg=="tiande")
		&&me->query_temp("quest/射雕英雄传/江南七怪/findduan"))	
	{
		message_vision(HIY"段天德心中大惊，急忙抓其周围的士兵推向$N，试图阻挡片刻！\n"NOR,me);
		message_vision(HIC"\n$N仔细辨认，发现这段天德去的方向似乎是杭州净慈寺的方向？\n"NOR,me);
		me->delete_temp("quest/射雕英雄传/江南七怪");
		
		me->set_temp("quest/射雕英雄传/江南七怪/jingcisi",1);
		destruct(duan);
	}
	
    return 1;
}
