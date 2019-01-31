#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "武场");
        set("long", @LONG
这里是全真教的演武场，地下的青砖本来铺的整整齐齐却
不知道被谁踩出了几十个大大小小的凹坑。看的出来，这里成
年累月的有弟子修炼轻功，武场边缘有一排低矮木桩(zhuang)
上面有门中弟子跳跃起纵。
LONG);
        set("outdoors", "quanzhen");
        set("exits", ([
                "south" : __DIR__"wuchang2",
                "north" : __DIR__"houtang2",
                "southeast" : __DIR__"xiuxishi",
        ]));
		set("item_desc", ([
                "zhuang" : HIG "\n这是一排错落有致的梅花桩，竖立在地上。好象"
                          "可以用来练习轻功\n的，你可以试着打(tiao)打看。\n" NOR,

        ]));

        setup();
        replace_program(ROOM);
}

void init()
{
        add_action("do_tiao", "tiao");
    //  add_action("do_cuff", "ci");
}

int do_tiao(string arg)
{
        object me;
        int qi_cost, c_skill,e_skill;

        me = this_player();
        c_skill=me->query_skill("dodge", 1);
		e_skill=c_skill*c_skill*c_skill;

		if (!arg) return notify_fail("你要跳大神？!\n");
		if (arg!="zhuang") return notify_fail("你向空中雀跃!\n");

        message_vision(HIG "$N" HIG "纵身一跃，跳到高低错落的木桩上，辗转腾挪。\n" NOR, me);
        qi_cost = 25;
		if (c_skill>100)
		{
			tell_object(me, HIC "轻轻一纵，飞跃木桩，缓缓落地。\n" NOR);
			return 1;
		}
		if (e_skill/10>me->query("combat_exp"))
		{
			tell_object(me, HIC "经验所限，无法继续提升基本轻功了。\n" NOR);
			return 1;
		}

        if (me->query("jingli") > qi_cost)
        {
                
				if (c_skill < 100 && e_skill/10< me->query("combat_exp"))
				{
                	me->improve_skill("dodge", 1 + random(me->query("dex")));
					me->receive_damage("jingli", qi_cost);
					tell_object(me, HIC "你对「基本轻功」有了新的领悟。\n" NOR);
				}
				else
				{
                 me->receive_damage("jingli", qi_cost);
				 tell_object(me, HIC "经验所限，无法继续提升基本轻功了。\n" NOR);
				}
        }
		else tell_object(me, HIC "你精力不足，无法继续提升基本功了。\n" NOR);
        return 1;
}
