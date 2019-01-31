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
        set_name(HIG"五毒丹"NOR, ({"wudu dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "颗");
                set("long", HIR"这是一颗绿油油的丹药，传来一股恶臭，是五毒教秘传的解毒圣丹。\n"NOR);
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
                return notify_fail("你要吃什么？\n");
		 if (this_object()->query("owner")!=me->query("id"))
			return notify_fail("这是五毒教圣丹，不能随便乱吃！\n");
		  if (me->query("family/family_name")!="日月神教" )
			return notify_fail("你非五毒教弟子，吃了此丹必死无疑！\n");
         me->clear_condition("poison");
         message_vision(HIR"$N吃下一颗五毒丹，脸色看来好多了。\n"NOR, this_player());
         if (!me->query("hmy/poison"))
         { 
			 me->set("hmy/poison",1);
			 message_vision(HIG"$N吃下五毒丹后，感觉对于五毒教中的毒性有所克制。\n"NOR,me);

         }
		  destruct(this_object());

		 return 1;
}

