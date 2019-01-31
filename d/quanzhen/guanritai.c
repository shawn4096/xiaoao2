inherit ROOM;
#include <ansi.h>


int do_zhan(string arg);
void create()
{
        set("short", "观日台");
        set("long", @LONG
这里是终南山上的观日台，不知哪朝哪代何人在这里修筑
了这个平台，用来观瞻日出的美景。这里的山势非常陡峻，往
下一看，悬崖(cliff)壁立，脚下白云飘过，真不知身在何境。
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
                "north" : __DIR__"shijie9",
        ]));
        set("objects",([
                __DIR__"npc/youke" : 1,
                __DIR__"npc/xiangke" : 1,
        ]));
		
		set("item_desc", ([
                "cliff" : HIG"\n这是终南山观日台最为险峻之处，脚下是万丈深渊，仅容一人单脚独立，地形极为险恶\n"+
								"山下山风呼啸而来，别说单脚，就是双脚能站稳也是一种很了不起的本事，据说铁脚仙王处一\n"+
								"曾在此单脚独立三天三夜期间狂风暴雨雷打不动，以此震慑关中群豪，你可以(duli)练习看看。\n" NOR,
								]));

        setup();
        replace_program(ROOM);
}

void init()
{
        add_action("do_zhan", "duli");
}

int do_zhan(string arg)
{
        object me;
        int qi_cost, c_skill,e_skill;

        me = this_player();
        c_skill=me->query_skill("leg", 1);
		e_skill=c_skill*c_skill*c_skill;

		if (!arg) return notify_fail("你要跳大神？!\n");
		if (arg!="cliff") return notify_fail("你一个金鸡独立亮相!\n");
		
        message_vision(HIG "$N" HIG "纵身一跃，试图金鸡独立站在悬崖边上。\n" NOR, me);
        
		qi_cost = 50;
		if (c_skill<100)
		{
			tell_object(me, HIC "终因功力太浅，悬崖上吹来一股狂风，将你吹会原地。\n" NOR);
			return 1;
		}
		if (c_skill>220)
		{
			tell_object(me, HIC "轻轻一纵，金鸡独立，稳稳站那儿，纹丝不动。\n" NOR);
			return 1;
		}
		if (e_skill/10>me->query("combat_exp"))
		{
			tell_object(me, HIC "经验所限，无法继续提升基本腿法了。\n" NOR);
			return 1;
		}

        if (me->query("jingli") > qi_cost)
        {
                
				if (c_skill < 100 && e_skill/10< me->query("combat_exp"))
				{
                	me->improve_skill("leg", 1 + random(me->query("dex")));
					me->receive_damage("jingli", qi_cost);
					tell_object(me, HIC "你对「基本腿法」有了新的领悟。\n" NOR);
				}else
				{
                 me->receive_damage("jingli", qi_cost);
				 tell_object(me, HIC "经验所限，无法继续提升基本腿法了。\n" NOR);
				}
        }
		else tell_object(me, HIC "你精力不足，无法继续提升基本功了。\n" NOR);
        return 1;
}

