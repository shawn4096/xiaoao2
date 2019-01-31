// tiechan

#include <weapon.h>
inherit BLADE;

void create()
{
        set_name("小铁铲", ({ "xiao tiechan", "tiechan" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "这是一把很普通的小铁铲。\n");
                set("value", 30);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一把$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回腰间。\n");
        }
        init_blade(4);
        setup();
}
