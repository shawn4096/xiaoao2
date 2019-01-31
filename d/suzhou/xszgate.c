#include <room.h>

inherit ROOM;

void create()
{
	set("short", "玄素庄门口");
	set("long", @LONG
这里是江南闻名的玄素庄，门口雕刻了两尊石狮子，甚是威武
庄内色调以黑白色为主，白墙黑瓦，连接成片。庄内院子内摆放了
不少练武器材，一看就是武林世家，门口有三个大字“玄素庄”

LONG
);
        set("objects",([
        //__DIR__"npc/binv" : 2,
        ]));
	set("exits", ([
	"north" : __DIR__"shizilin",
	"south" :__DIR__"xszyuanzi",
        ]));
 	set("outdoors", "suzhou");
   set("incity",1);
	setup();
}


