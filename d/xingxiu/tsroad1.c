
#include <ansi.h>
inherit ROOM;


void create()
{
        set("short", "峡谷小道");
        set("long", @LONG
这里是通往天山山后的一条羊肠小道，平时几乎没有人光顾，阴气森森
甚是寒冷，路两旁冰雪皑皑。
LONG
        );
        set("exits", ([
          "southeast" : __DIR__"duchonggu-out",
          "northwest" : __DIR__"tsroad2",
        ]));

        set("outdoors", "tianshan");

      
		setup();
}
void init()
{
	object me=this_player();
	message_vision("一阵山风吹过，你忍不住打了个哆嗦\n",me);
	me->receive_damage("qi",100,"寒气冻死");
	me->receive_wound("qi",50,"寒气冻死");
}