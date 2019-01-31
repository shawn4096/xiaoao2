#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY"郭啸天的首级"NOR, ({ "guoxiaotian shouji"}) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "个");
				set("value", 2500);
                set("material", "leather");
				//set("armor_prop/armor", 6);
        }
        setup();
}

