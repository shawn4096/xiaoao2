//fuchen.c 拂尘 道家之物
//by sohu
#include <weapon.h>
inherit WHIP;

void create()
{
	set_name("拂尘", ({ "fu chen", "fuchen" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
		set("long", "这是一柄道家出家人所常用的普通拂尘，由桃木木柄和松散的丝编织而成。\n");
		set("value", 1000);
		set("material", "wood");
		set("wield_msg", "$N「唰」的一声抖出一柄$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n卷回腰间。\n");
	}
	init_whip(20);
	setup();
}
