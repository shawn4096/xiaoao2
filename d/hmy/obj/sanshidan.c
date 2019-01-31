#include <ansi.h>
inherit ITEM;

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIR"三尸"+HIG+"脑神丹"NOR, ({"sanshi dan", "sanshi", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("value", 30000);
                set("unit", "粒");
                set("long", "这是一粒日月神教特产三尸脑神丹，含剧毒，需要服用解药，否则毒发无救。\n");
        }
}

int do_eat(string arg)
{
        object me = this_player();
        if (!id(arg))
                return notify_fail("你要吃什么？\n");
        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");
        //if (me->query("eff_qi") >= me->query("max_qi"))
          //      return notify_fail("你现在不需要用金创药。\n");
        me->receive_damage("jing", random(400));
       // me->receive_wound("jing", random(2000));
		message_vision(HIY"$N吃下一粒三尸脑神丹，似乎脑子中有小虫在爬动似得，感觉有些头晕。\n"NOR, me);
        me->start_busy(2);
        destruct(this_object());
		me->apply_condition("sanshi_poison",5+random(5));
        return 1;
}