#include <ansi.h>

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIG"�嶾��"NOR, ({"wudu dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR"����һ�������͵ĵ�ҩ������һ�ɶ�������嶾���ش��Ľⶾʥ����\n"NOR);
                set("value", 100);
                set("no_drop", 1);
				set("no_give", 1);
				set("no_get", 1);
				set("no_steal", 1);
        }
        setup();
}

int do_eat(string arg)
{
        object me = this_player();
         if (!id(arg))
                return notify_fail("��Ҫ��ʲô��\n");
		 if (this_object()->query("owner")!=me->query("id"))
			return notify_fail("�����嶾��ʥ������������ҳԣ�\n");
		  if (me->query("family/family_name")!="�������" )
			return notify_fail("����嶾�̵��ӣ����˴˵��������ɣ�\n");
         me->clear_condition("poison");
         message_vision(HIR"$N����һ���嶾������ɫ�����ö��ˡ�\n"NOR, this_player());
         if (!me->query("hmy/poison"))
         { 
			 me->set("hmy/poison",1);
			 message_vision(HIG"$N�����嶾���󣬸о������嶾���еĶ����������ơ�\n"NOR,me);

         }
		  destruct(this_object());

		 return 1;
}

