#include <room.h>

inherit ROOM;

void create()
{
	set("short", "玄素庄大厅");
	set("long", @LONG
这是玄素庄主夫妇所居之地，厅堂甚是高大，屋内正面摆放
一排排字画，一看就是书香门第，庄主和夫人正在喝茶，厅堂西
侧放置了三清画像，一个香案燃起檀香袅袅升起，甚是素雅。
LONG
);
        set("objects",([
			"d/motianya/npc/shiqing" : 1,
			"d/motianya/npc/minrou" : 1,
        ]));
		set("exits", ([
			"north" : __DIR__"xszyuanzi",
		]));
		//set("outdoors", "suzhou");
	    set("incity",1);
		setup();
}


