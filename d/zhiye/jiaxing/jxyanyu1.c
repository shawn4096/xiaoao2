// Room: /d/jiaxing/yanyu.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIC"烟雨楼"NOR);
	set("long", @LONG
烟雨楼建在嘉兴的风景圣地南湖中央的一个小岛上，湖面终年不断的水气
把它笼罩得迷迷蒙蒙的。经常有文人墨客到这里游玩，凭栏远眺，观赏嘉兴的
湖光山色。
LONG
	);
	set("group", 1);
	set("exits", ([
		"north" :  "/d/jiaxing/nanhu1",
		"up" :  "/d/jiaxing/jxyanyu2",
	]));
	set("objects", ([ 
                "d/jiaxing/npc/xiaoer" : 1,
	 ]) );

	set("outdoors", "嘉兴城");
	setup();
}
int init()
{
	object me;
	me=this_player();
	
	if (me->query_temp("quest/射雕英雄传/江南七怪/askjiaomu")
		&&me->query_temp("quest/射雕英雄传/江南七怪/jugang"))
	{
		message_vision(HIY"$N将手中的铜缸往地上一放，顿时地动山摇!\n$N对店小二喝道，“小二，将这铜缸的给我装满了酒，我要招待今天的客人”\n"NOR,me);
		//开始烟雨楼大战的接口了
		me->delete_temp("quest/射雕英雄传/江南七怪/askjiaomu");
		me->set_temp("quest/射雕英雄传/江南七怪/fanggang",1);
		
	}
}