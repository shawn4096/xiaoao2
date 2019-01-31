// mtyadi.c 崖底

inherit ROOM;
#include <ansi.h>
int do_climb(string arg);

void create()
{
        set("short",YEL "摩天崖底"NOR);
        set("long", @TEXT
你的面前是一座比直的山峰，高若千丈，峰顶在云雾中隐约可见，
山峰光秃秃的，更无置手足处，山峰垂下一条铁链(lian)，仔细一看，
铁链并无锈迹，似乎有人用它爬(climb)上爬下。
TEXT );
        set("outdoors", "motianya");
        set("exits", ([
                "north" : __DIR__"mtroad",
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
       // n = me->query_skill("dodge", 1) /10;
        n=me->query_dex();
		message_vision(HIC"$N深吸了一口气，慢慢沿着铁链的向上爬。\n"NOR, me);
        if (me->query("quest/侠客行/玄铁令/givexieling"))
        {
           message_vision(HIC"$N得到摩天居士谢烟客的指点，对于这山势非常熟悉，几个起纵间就到达崖顶。\n"NOR, me);
		   me->move("d/motianya/mtdating");
		   return 1;
        }
		if (random(n) > 20&& me->query("neili")>500)
        {
                message_vision(HIY"$N爬了半天，终于爬了上去，$N高兴的"
                               "抹了抹汗。\n"NOR, me);
                me->receive_damage("jingli", 300);
                me->start_busy(3);
				me->add("neili",-random(500));
                me->move(__DIR__"mtroad2");
        } else
        {
                message_vision(HIW"$N爬了一会，一不小心摔了下来。\n"NOR, me);
                me->receive_damage("qi", 300 +random(300));
                me->receive_wound("qi", 300);
                me->start_busy(3);
        }

        return 1;
}
