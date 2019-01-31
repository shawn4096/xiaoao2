#include <ansi.h>

inherit ITEM;

void create()
{
   set_name("����ɢ", ({"qingxin san", "san"}));
   if (clonep())
      set_default_object(__FILE__);
   else {
      set("unique", 3);
      set("no_give", 1);
      set("no_drop", 1);
      set("no_steal", 1);
      set("no_get", 1);
      set("unit", "��");
      set("value", 1000);
   }
   setup();
}

int init()
{
   add_action("do_eat", "eat");
}

int do_eat(string arg)
{
   object me = this_player();

   if(!id(arg))
       return notify_fail("��Ҫ��ʲô��\n");

   message_vision("$N����һ��" + name() + "��\n", me);
   if ((int)me->query_condition("xx_poison") > 0) {
      me->clear_condition("xx_poison");
   }

   destruct(this_object());
   return 1;
}