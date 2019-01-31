//room: mtdating.c

inherit ROOM;
#include <ansi.h>
#define XKX_QUEST1 "quest/侠客行/摩天崖/"

void create()
{
        set("short", YEL"摩天崖顶"NOR);
        set("long", @LONG
这就是摩天崖了。上面光秃秃的，连一棵小树也没有，峰顶到也
十分开阔，但身周云雾缭绕，当真是置身云端之中，使人心惊肉跳。
东面有一个小木屋。
LONG );
        set("outdoors", "motianya");
        set("exits",([
                "east" : __DIR__"mtxiaowu",
                "down" : __DIR__"mtyadi",
        ]));
        set("objects",([
                __DIR__"npc/xieyan" : 1,
        ]));

        set("outdoors", "摩天崖顶");
        setup();
}

void init()
{
	object me,ob;
	me=this_player();
	ob=present("xie yanke",environment(me));
	if (me->query_temp(XKX_QUEST1+"agree"))
	{
		message_vision(HIY"你刚登上摩天崖顶，就听到远处一个凄厉的声音响了起来！\n"NOR,me);
		if (ob)
		{
			message_vision(HIC"谢烟客喝道，“谁在装神弄鬼！”，说完就追了出去！\n"NOR,me);
			destruct(ob);
		}
	}
}


int valid_leave(object me, string dir)
{
        object ob;

        if (dir == "east" &&
            objectp(ob = present("xie yanke", this_object())) &&
            living(ob))
                return notify_fail("谢烟客把手一拦，喝道：“给我回来！”\n");

        return ::valid_leave(me, dir);
}

