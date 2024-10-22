
#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "精灵密室");
        set("long", "这里是巫师的小妖精休息的地方，她可以帮助巫师处理很多事情。\n");

        set("exits", ([
                "out": __DIR__"guest_room",
        ]));
        set("no_fight", 1);
        set("sleep_room", 1);
        set("no_sleep_room", 1);

        set("objects", ([
//                 "/d/wizard/npc/shizhe.c" : 1,
                "/d/wizard/npc/fairy.c" : 1,
//                 "/d/wizard/npc/ZPshizhe.c" : 1,
        ]));

        set("coor/x",100);
        set("coor/y",30);
        set("coor/z",0);
        setup();
}

void init()
{
        add_action("action", ({
                "dazuo",
                "du",
                "exercise",
                "lian",
                "practice",
                "respirate",
                "study",
                "tuna"
        }));
}
int action()
{
        write("你无法静下心来修炼。\n");
        return 1;
}
int valid_leave(object me, string dir)
{
        if(me->query("gift_changed") && me->query_temp("gift_change"))
        {
                if (!me->query_temp("confirm")) 
                {
                        me->set_temp("confirm", 1);
                        me->start_busy(2);
                        return notify_fail(HIR"你确定已经将属性调整完毕吗？出去以后就不可以再调整属性了！\n"NOR);
                }
                me->delete_temp("confirm");
                me->delete_temp("gift_change");
        }
        return ::valid_leave(me, dir);
}
