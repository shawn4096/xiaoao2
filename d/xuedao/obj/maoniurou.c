// niurou.c ԭ������ţ��

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name(HIY "��ţ����" NOR, ({"maoniu routiao","maoniu","routiao"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ��ɹ�ɵ���ţ���������ǲ����ճ�ʳ��֮��\n");
		set("unit", "��");
		set("value", 190);
		set("food_remaining", 2);
		set("food_supply", 50);
	}
}