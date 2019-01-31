#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "兵器室");
        set("long", @LONG
这里是神龙教弟子摆放兵器的禅房，地下杂乱地堆着一些
兵器，有的已经锈纹斑斑了，有的还是锋利透亮，神龙弟子练
功的时候，就到这里来挑选兵刃,一旁的兵器架(jia)上挂了几
付蛇皮软甲。
LONG);
        set("exits", ([
                "north" : __DIR__"road2",
        ]));
        set("objects", ([
                __DIR__"npc/obj/bian" : 2+random(3),
                __DIR__"npc/obj/shejia" : 1+random(2),
                "/clone/weapon/bishou" : 2+random(2),			
				__DIR__"npc/obj/hook" :  2+random(2),
				__DIR__"npc/obj/huxi" :  2+random(2),
        ]));

        setup();
        replace_program(ROOM);
}
