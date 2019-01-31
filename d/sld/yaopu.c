// yaopu1.c
// 药圃
inherit ROOM;
#include <ansi.h>

string* pos=({(["id":"northwest","name":"西北"]),(["id":"northwest","name":"西北"]),
	(["id":"north","name":"北方"]),(["id":"south","name":"南方"]),
	(["id":"west","name":"西方"]),(["id":"east","name":"东方"]),
	(["id":"southeast","name":"东南"]),(["id":"southwest","name":"西南"]),
});
string* pos1=({"northwest","north","northeast","east","southeast","south","southwest","west"}); 

void create()
{
	set("short","药圃入口");
	set("long",@long
这里是神龙岛的药圃，远远望去，药圃形似八卦图排列，每块
药圃旁边插了一个牌子，这里靠海，灵气充沛,适合奇珍药材成长。
此地药香扑鼻。
long);
	set("exits",([
		"south" : __FILE__,
		"north" : __FILE__,
		"west" : __FILE__,
		"east" : __FILE__,
		"southeast" : __FILE__,
		"southwest" : __FILE__,
		"northwest" : __FILE__,
		"northeast" : __FILE__,
		"out" : "/d/sld/zl1",
	]));
	set("no_clean_up",1);
	
	set("outdoors", "神龙岛");
	setup();
}	    	
void init()
{
		object me=this_player();
		if (me->query("family/family_name")=="神龙教")
		{        
			message_vision(CYN"远处是一片药圃，药香扑鼻，但此处有迷阵，$N忍不住想用鼻子闻闻！\n"NOR,me);
     		add_action("do_wen", ({"wen","xiu","smell",}));
		}
     	me->delete_temp("yaopu");
		
}
int do_wen()
{
	object me;
	string fx,arg;
	me=this_player();
	fx=pos1[random(sizeof(pos1))];
	if (me->is_busy())
		return notify_fail("你正在忙碌中\n");
	switch (fx)
	{
		case "east":
			//me->set_temp("yaopu/path/");
			arg="东方";
			break;
		case "west":
			arg="西方";
			break;
		case "north":
			arg="北方";
			break;
		case "south":
			arg="南方";
			break;
		case "northwest":
			arg="西北方";
			break;
		case "northeast":
			arg="东北方";
			break;
		case "southeast":
			arg="东南方";
			break;
		case "southwest":
			arg="西南方";
			break;
	}

	tell_object(me,CYN"你感觉是从"HIY+arg+CYN"方向传来的药香!\n"NOR);
	me->set_temp("yaopu/path",fx);
	me->start_busy(1);
	return 1;
}

int valid_leave(object me, string dir)
{
	
	if (dir == me->query_temp("yaopu/path"))
		me->add_temp("mark/lvl",1);
	else me->delete_temp("mark/lvl");
	
	if (me->query_temp("mark/lvl") == 5 )
	{
		me->move(__DIR__"yaopu1");
		me->delete_temp("mark");
		me->delete_temp("yaopu");
		return notify_fail("你闻着药香一路走了，终于走到这片隐藏在竹林后的药圃中。\n");
	}
	
	return ::valid_leave(me, dir);
}
