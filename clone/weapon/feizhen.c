#include <ansi.h>
#include <weapon.h>
inherit COMBINED_ITEM;
inherit THROWING;

void create()
{
       set_name(HIY "����" NOR, ({"fei zhen", "zhen", "noodle","feizhen" }));
       if( clonep() )
               set_default_object(__FILE__);
       else {
		set("long", "һ������������ϸ�롣\n");               
               set("unit", "��");
               set("base_value", 10000);
               set("base_unit", "ö");
               set("base_weight", 10);
       }
       set_amount(350);
       init_throwing(50);
}

