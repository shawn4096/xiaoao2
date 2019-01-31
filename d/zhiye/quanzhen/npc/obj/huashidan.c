// huashidan.c 化石丹
// By sohu

inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY"化石丹"NOR, ({"huashi dan","dan"}));
        set_weight(800);
        set("unit", "块");
        set("long", "这是一块化石丹，可以将石头表层轻微融化。\n");
        setup();
}


