// luqi.c 绿绮瑶琴

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIG"绿绮琴"NOR,({"luqi qin","luqi","qin"}));
        set_weight(1000);
        if(clonep())
                set_default_object(__FILE__);
        else{
                set("unit","张");
                set("value",1000);
                set("material","bamboo");
               // set("unique", 1);
                set("rigidity", 6);
				set("qinjian",1);
                //set("treasure",1);
				set("value", 260000);
                set("long","这张绿绮瑶琴颜色暗旧，当是数百年甚至是千年以上的古物，据说乃是司马相如旧物。\n");
                set("wield_msg",GRN"$N伸手一拂将绿绮瑶琴捧在手中,在琴弦上拨了几下。\n"NOR);
                set("unwield_msg",GRN"$N手腕一转，琴音停了下来。\n"NOR);
        }
        init_sword(80);
        setup();
}
