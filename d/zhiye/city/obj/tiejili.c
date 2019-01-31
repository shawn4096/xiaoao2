#include <ansi.h>
#include <weapon.h>

inherit COMBINED_ITEM;
inherit THROWING;

void create()
{
	set_name("铁蒺藜", ({ "tie jili","tiejili", "jili" }));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "一堆江湖中人常用的铁蒺藜，乃暗器高手随身携带所用。\n");               
		set("unit", "堆");
		set("base_value", 0);
		set("base_unit", "颗");
		set("base_weight", 50);
		set("value", 5000);
		set("material", "steel");
		set("wield_msg", "$N将手伸入皮囊中随手抓了一把$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n放回到皮囊之中。\n");
	}
	set_amount(random(100) + 200);
	init_throwing(35);
}

