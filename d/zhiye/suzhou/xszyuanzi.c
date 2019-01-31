#include <room.h>

inherit ROOM;

void create()
{
	set("short", "玄素庄院子");
	set("long", @LONG
院子甚是宽阔，墙西面摆放了一排排的木桩(zhuang)，上面缠满了棉布
有弟子正在联系掌法，东面放置了不少石锁(shisuo)和沙袋，一排排的兵器
架子摆放了不少剑类武器。
LONG
);
        set("objects",([
        //__DIR__"npc/binv" : 2,
        ]));
	set("exits", ([
	"north" : __DIR__"xszgate",
	"south" :__DIR__"xszdating",
        ]));
 	set("outdoors", "suzhou");
   set("incity",1);
	setup();
}


