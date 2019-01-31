// Room: /d/wizard/shandong.c
#include <ansi.h>
inherit ROOM; //继承 ROOM 类
void create()
{
	set("short", HIB"山洞"NOR); 
	set("long", @LONG
此处是崖壁背面的山洞，透过崖壁有一丝丝亮光照了进来，此地空间不大但空气
颇为清新，你没头没脑的跌落此处。等你稍微适应了此处暗淡的光线抬头一看，发现
在半空中居然飘着一个人！
LONG );
	set("exits", ([
		//"south" : __DIR__"midao3",
		"out" : __DIR__"yabiqian",
		//"west" : __DIR__"midao2",
		//"north" : __DIR__"midao1",
	]));
	set("no_fight",1);
	set("objects", (["/d/xiaoyao/leigushan/npc/wuyazi" : 1 ]) );
	setup();
	replace_program(ROOM);
}

int init()
{
	object me=this_player();	
		message_vision(HIC"一个苍老的声音在暗处一声轻叹！\n$N吓了一大跳！喝道，“谁”？\n"NOR,me);		
}