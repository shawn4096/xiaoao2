#include <ansi.h>
#include <weapon.h>
inherit COMBINED_ITEM;
inherit THROWING;

void create()
{
       set_name(HIY "飞针" NOR, ({"fei zhen", "zhen", "noodle","feizhen" }));
       if( clonep() )
               set_default_object(__FILE__);
       else {
		set("long", "一把亮光闪闪的细针。\n");               
               set("unit", "把");
               set("base_value", 10000);
               set("base_unit", "枚");
               set("base_weight", 10);
       }
       set_amount(350);
       init_throwing(50);
}

