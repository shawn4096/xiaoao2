#include <ansi.h>
inherit ITEM;

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIR"��ʬ"+HIG+"����"NOR, ({"sanshi dan", "sanshi", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("value", 30000);
                set("unit", "��");
                set("long", "����һ����������ز���ʬ���񵤣����綾����Ҫ���ý�ҩ�����򶾷��޾ȡ�\n");
        }
}

int do_eat(string arg)
{
        object me = this_player();
        if (!id(arg))
                return notify_fail("��Ҫ��ʲô��\n");
        if (me->is_busy())
                return notify_fail("����æ���ء�\n");
        //if (me->query("eff_qi") >= me->query("max_qi"))
          //      return notify_fail("�����ڲ���Ҫ�ý�ҩ��\n");
        me->receive_damage("jing", random(400));
       // me->receive_wound("jing", random(2000));
		message_vision(HIY"$N����һ����ʬ���񵤣��ƺ���������С���������Ƶã��о���Щͷ�Ρ�\n"NOR, me);
        me->start_busy(2);
        destruct(this_object());
		me->apply_condition("sanshi_poison",5+random(5));
        return 1;
}