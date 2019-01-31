// Room: /d/jiaxing/yanyu.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", YEL"贵宾房"NOR);
	set("long", @LONG
站在二楼，登高远望，湖面终年不断的水气把它笼罩得迷迷蒙蒙的。
经常有文人墨客到这里游玩，凭栏远眺，观赏嘉兴的湖光山色。店小二正
在忙碌着。楼内有不少侠客，彼此间好像在谈论什么事，神情有些紧张。
LONG
	);
	//set("group", 1);
	set("exits", ([
		"west" :  "/d/jiaxing/jxyanyu2",
	]));
	set("objects", ([ 
                "d/thd/niujia/npc/wanyan" : 1,
	 ]) );

	set("outdoors", "嘉兴城");
	setup();
}
