#include <ansi.h>;
inherit ITEM;

void create()
{
     set_name(HIY"金钥匙"NOR, ({"jin yaoshi","gold key","key"}));
     set_weight(10);
     if (clonep())
           set_default_object(__FILE__);
     else {
           set("unit", "把");
           set("long", "这是一把纯金打制的钥匙，上书大轮寺字样，似乎和大轮寺的某些秘密有关。\n");
           set("unique", 1);
           set("value", 40000);
     }
     setup();
}
