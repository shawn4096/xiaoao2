// by sohu
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW"天山冰蚕"NOR, ({"tianshan bingcan", "bingcan", "can"}));
        set("unit", "只");
		set("unique", 1);
		set("poison", 100);
        set("treasure",1);
        set("long", WHT"这蚕虫纯白如玉，微带青色，比寻常蚕儿大了一倍有余，便似一条蚯蚓，身子透明直如水晶。\n"NOR);
        set("value", 2000000);
        setup();
}

