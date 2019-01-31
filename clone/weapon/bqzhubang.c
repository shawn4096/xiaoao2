// zhubang.c 竹棒

#include <weapon.h>
#include <ansi.h>

inherit STICK;

void create()
{
        set_name(HIY"黄竹棒"NOR, ({ "zhu bang", "zhubang", "bang" }));
        set_weight(1500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "这是一根发着黄油油色泽的竹棒，入手沉甸甸的，相当结实。一看就是被人时常把玩之物。\n");
                set("value", 60000);
                set("no_sell", 1);
                set("material", "bamboo");
                set("wield_msg", "$N抽出一根$n握在手中掂了掂。\n");
                set("unwield_msg", "$N将手中的$n轻轻别回腰间。\n");
        }
        init_stick(50);
        setup();
}

