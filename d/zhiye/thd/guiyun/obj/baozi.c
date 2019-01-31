// baozi.c

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("小笼包", ({"baozi"}));
	set_weight(30);
	if (clonep())
		set_default_object(__FILE__);
	else {
        set("long", "一碟刚出笼的小笼包子。\n");
		set("unit", "碟");
		set("value", 0);
		set("food_remaining", 5);
		set("food_supply", 30);
	}
}
