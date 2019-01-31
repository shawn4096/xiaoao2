// shanyeguo.c
#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name(HIR"É½Ò°¹û"NOR, ({"shan yeguo", "yeguo"}));
	set_weight(80);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "¸ö");
		set("value", 50);
		set("food_remaining", 3);
		set("food_supply", 30);
	}
}
