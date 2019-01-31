#include <ansi.h>
inherit ITEM;
//inherit F_UNIQUE;
void create()
{
        set_name(CYN"皮囊"NOR, ({"pi nang", "pinang" , "nang"}) );
        set_weight(1000);
        set_max_encumbrance(40000);
        if( clonep() )
                set_default_object(__FILE__);
        else{
        set("unit", "个");
        set("long", "这是一个用马皮制作的囊。不仅柔韧型腔，而且坚韧异常，摸上去\n"
"甚是光滑，此袋乃是藏区装酒水以及物品常用之物,具有一定的保鲜之用。\n");
        set("value", 100000);
        set("material","skin");
        set("keep_same",1);
		set("no_give",1);
        set("no_drop",1);

        set("no_steal", 1);
        }        
        setup();
}
