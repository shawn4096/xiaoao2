// zhubang.c 竹棒

#include <weapon.h>
inherit STICK;

void create()
{
        set_name("竹棒", ({ "zhubang" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "这是一根发黄的竹棒，入手沉甸甸的，似乎相当结实。\n");
                set("value", 200);
                set("material", "bamboo");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回腰间。\n");
        }
        init_stick(20);
        setup();
}

