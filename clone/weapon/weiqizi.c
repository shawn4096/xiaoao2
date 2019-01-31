#include <ansi.h>
#include <weapon.h>
inherit COMBINED_ITEM;
inherit THROWING;

void create()
{
       set_name(HIC "棋子" NOR, ({"qi zi", "qizi", "zi" }));
       if( clonep() )
               set_default_object(__FILE__);
       else {
		set("long", "一盒黑白棋子，看起来晶莹剔透，黑白分明，令人爱不释手。\n");               
               set("unit", "盒");
               set("base_value", 10000);
               set("base_unit", "颗");
               set("base_weight", 10);
       }
       set_amount(360);
       init_throwing(50);
}

