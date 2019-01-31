// shandong2.c
// Modified by Java Apr.27 1998
//设定为血刀门起点

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short",WHT"洞口"NOR);
        set("long",@LONG
山谷里积雪被拢成几个雪堆，这里时常有人扫除积雪。你前面的峭
壁下隐隐约约有一个山洞。
LONG );
        set("exits",([
                "enter" : __DIR__"shandong3",
                "west"  : __DIR__"sroad9",
        ]));
       set("objects", ([
                "/kungfu/class/xuedao/shengxiong" :1,
        ]));
        set("outdoors", "xuedao");
		set("valid_startroom", 1);

       
		setup();
       replace_program(ROOM); 
}

int valid_leave(object me, string dir)
{
	mapping fam;
	fam = (mapping)me->query("family");

	if (fam
		&&fam["family_name"] != "血刀门"
		&& dir == "enter"
		&& objectp(present("sheng xiong", environment(me))))
	    return notify_fail(CYN"胜雄一把拦住你，说道：这里是血刀门的地盘，不要随意乱闯！\n"NOR);
	  return ::valid_leave(me, dir);
}/**/

