#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	  set("short", HIC"三因观"NOR);
	  set("long",@long
这里是昆仑山上的一处道观，门上有一块匾额，上书“三因观”三个大
字据说是不少昆仑名宿不喜热闹，在后山中开辟了这么一处道观，多为门中
长老或核心弟子清修所用，此隐居之地布局非常简单，只有几张床，供修行
者使用，屋子里烤着火，
暖烘烘的。
long);
	  set("exits",([
            "east" : __DIR__"bainiushan",
          ]));

		  set("indoors", "昆仑");
          set("sleep_room",1);
		  set("objects",([
			"kungfu/class/kunlun/fengxifan" : 1,
		]));

          setup();
}
