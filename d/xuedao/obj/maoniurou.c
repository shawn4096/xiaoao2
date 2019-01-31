// niurou.c 原笼粉蒸牛肉

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name(HIY "牦牛肉条" NOR, ({"maoniu routiao","maoniu","routiao"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一条晒干的牦牛肉条，乃是藏民日常食用之物\n");
		set("unit", "条");
		set("value", 190);
		set("food_remaining", 2);
		set("food_supply", 50);
	}
}