
#include <ansi.h>

#include <weapon.h>

inherit COMBINED_ITEM;
inherit THROWING;

void create()
{
	set_name(WHT"飞刀"NOR, ({ "fei dao", "feidao", "dao" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "叠");
		set("long", "这是一叠可作为暗器使用的柳叶飞刀。\n");
		set("base_value", 1000);
		set("base_unit", "把");
        set("base_weight", 20);		
	}
	set_amount(25);
    init_throwing(80);
}
