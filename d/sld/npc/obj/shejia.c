// shejia.c 蛇皮软甲
// 增加armor防御效果

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIC"蛇皮软甲"NOR, ({ "shepi ruanjia","ruanjia","armor", }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "pi");
                set("value", 12000);
                set("armor_prop/armor", 70);
				
        }
        setup();
}

