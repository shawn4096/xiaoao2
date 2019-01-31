// zhushi.c 猪食

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("猪食", ({"zhu shi", "zhushi"}));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一桶猪食。\n");
		set("unit", "只");
		set("value", 150);
		set("food_remaining", 10);
		set("food_supply", 40);
	}
}
