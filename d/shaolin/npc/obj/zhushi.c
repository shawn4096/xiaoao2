// zhushi.c ��ʳ

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name("��ʳ", ({"zhu shi", "zhushi"}));
	set_weight(200);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һͰ��ʳ��\n");
		set("unit", "ֻ");
		set("value", 150);
		set("food_remaining", 10);
		set("food_supply", 40);
	}
}
