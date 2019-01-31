// cloth3.c

#include <armor.h>
#include <ansi.h>

inherit FINGER;

void create()
{
	set_name(HIY "黄金指套" NOR, ({ "gold finger", "finger" , "zhitao"}) );
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "这是一个黄金制作的指套。\n");
		set("unit", "条");
		set("material", "gold");
        set("value",100000);
		set("armor_prop/armor", 20 );		
		set("wear_msg","$N将$n戴在指上。\n");
		set("remove_msg","$N把$n从指上拿开。\n");
	}
	setup(); 
}
