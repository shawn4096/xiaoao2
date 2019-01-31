// Room: /d/wizard/shangu.c
#include <ansi.h>
inherit ROOM; //继承 ROOM 类

void create() // 创建函数;在里面定义各种属性
{
	set("short", HIG"擂鼓山"NOR); // 房间的 短描述
	set("long","山中都是松树，山风过去，松声若涛。但见松荫森森，景色清幽，山涧\n"
		"旁用巨竹搭着一个"HIG"凉亭"NOR"，构筑精雅，极尽巧思，松即是亭，亭即是松，一眼\n"
		"看去，竟分不出是松林还是亭子。\n"
		);// 房间的长描述
	set("exits", ([ "east" : __DIR__"test","west" : __DIR__"yabi"])); // 不同的方向指令,跳转到
	//set("valid_startroom", 1);//使该房间可以成为下一次进来的地方
	set("outdoors","xiaoyao");
	setup(); //不用管它,照抄就是
}