inherit ROOM;
#include <ansi.h>
int do_climb(string arg);

void create()
{
        set("short",YEL "摩天崖半山峭壁"NOR);
        set("long", @TEXT
这里是摩天崖的半山峭壁，你抬头看了看这根铁链直达山顶(lian)，喘了口气，
你环顾四周，都是悬崖峭壁，似乎只能一直往上爬(climb)了。
TEXT );
        set("outdoors", "motianya");
        set("exits", ([
               
        ]));
        setup();
}

void init()
{
        add_action("do_climb","climb");
}

int do_climb(string arg)
{
        int n;
        object me;

        if (arg != "lian")
        {
                write("你要爬什么呀? \n");
                return 1;
        }

        me = this_player();
        n = me->query_skill("dodge", 1)/10;
        message_vision(HIC"$N深吸了一口气，慢慢沿着铁链的向上爬。\n"NOR, me);
        if (random(n)*2 > n)
        {
                message_vision(HIY"$N爬了半天，终于爬了上去，$N高兴的"
                               "抹了抹汗。\n"NOR, me);
                me->receive_damage("jingli", 500);
                me->move(__DIR__"mtdating");
                me->start_busy(3);
        } else
        {
                message_vision(HIW"$N爬了一会，一不小心摔了下来。\n"NOR, me);
                me->receive_damage("qi", 2500 +random(2500));
                me->receive_wound("qi", 2500);
                me->move(__DIR__"mtyadi");  
                me->start_busy(3);
        }

        return 1;
}

