// baogou.c 神龙夺命钩
#include <ansi.h>

#include <weapon.h>
inherit HOOK;

void create()
{
        set_name(HIC"神龙夺命钩"NOR, ({ "shenlong gou", "hook","gou" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "这是一对锐利无比的宝钩,是神龙岛镇岛之宝,据说由岛主请高人打造。\n");
                set("value", 30);
                set("material", "steel");
				set("rigidity", 9);
                set("unique", 1);
                set("treasure",1);
                set("wield_maxneili", 1000);
        }
         init_hook(180);
        setup();
}
