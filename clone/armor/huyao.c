//Cracked by Kafei
// huyao.c

#include <ansi.h>
#include <armor.h>

inherit WAIST;

void create()
{
	set_name( WHT"铁护腰"NOR, ({ "hu yao", "huyao" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "条");
                set("long", "这是一件皮质的护腰，上面满布铁钉，用以保护腰部。\n");
		set("value", 500);
		set("material", "iron");
		set("armor_prop/armor", 30);
		set("shaolin",1);
	}
	setup();
}
