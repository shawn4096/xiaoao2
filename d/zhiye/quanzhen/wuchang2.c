#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "武场");
        set("long", @LONG
这里是全真教的演武场，地下的青砖本来铺的整整齐齐甚是平整
武场的一侧一排排的架子吊装不少的沙袋(shadai)，有不少弟子正在
勤修腿功的基本功法。
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
                "north" : __DIR__"wuchang1",
                "east"  : __DIR__"xiuxishi",
                "south" : __DIR__"wuchang3",
                "southeast" : __DIR__"shantang",
        ]));
		set("item_desc", ([
                "shadai" : HIC "\n这是一排排的木架吊装了数十个沙袋，为教中弟子日常"
                          "可以用来练习基本腿法用\n的，你可以试着踢(ti)打看看。\n" NOR,

        ]));

      //  set("for_family", "全真教");

        setup();
        replace_program(ROOM);
}

void init()
{
        add_action("do_ti", "ti");
}

int do_ti(string arg)
{
        object me;
        int qi_cost, c_skill,e_skill;

        me = this_player();
        c_skill=me->query_skill("leg", 1);
		e_skill=c_skill*c_skill*c_skill;

		if (!arg) return notify_fail("你要踢谁？!\n");
		if (arg!="shadai") return notify_fail("你飞起一脚踢向空中!\n");
		
        message_vision( "$N纵身一跃，一个飞天腿踢向悬吊的沙袋。\n" NOR, me);
        
		qi_cost = 25;
		if (c_skill>100)
		{
			tell_object(me, HIC "轻轻一踢，沙袋飞向远处。\n" NOR);
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
