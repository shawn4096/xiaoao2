// miandao.c 缅刀

#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name( "缅刀" , ({ "mian dao", "dao", "blade","miandao" }));
        set_weight(12000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "这是江湖闻名丧胆的缅刀，刀背薄身短，刀口锋利，入手轻便。\n");
                set("value", 1500);
                set("material", "iron");
        }
        init_blade(50);
        setup();
}
