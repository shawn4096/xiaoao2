//bi.c 判官笔
#include <weapon.h>
#include <ansi.h>

inherit BRUSH;
inherit F_UNIQUE;

void create()
{
        set_name(HIW"白玉扇"NOR,({ "baiyu shan", "shan","brush" }) );
        set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
				set("value", 1500);
                set("material", "steel");
                set("weapon_prop/parry", 50);
                set("wield_msg", "$N从怀中掏出一只白玉扇，轻轻摇着，甚是潇洒。\n");
                set("long", "这是一只白玉做成以上好精铁打制而成的白玉扇。\n");                
                set("unwield_msg", "$N把白玉扇放入怀中。\n");                
        }
        init_brush(125);
        setup();
}
