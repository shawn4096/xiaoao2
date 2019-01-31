// cloth3.c

#include <armor.h>
#include <ansi.h>
inherit BOOTS;

void create()
{
	set_name(HIY "黄云履" NOR, ({ "huangyun lu", "boot" ,"huangyun" , "xue" }));
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "这是一双金黄色锦缎和软麻制作的靴子，做工极为精良，似乎没有人穿过。\n");
		set("unit", "双");
		set("material", "boots");
		set("armor_prop/armor", 30);
		set("value",100000);
		set("wear_msg","$N将$n穿在脚上，甚是舒服。\n");
		set("remove_msg","$N把$n从脚上脱了下来。\n");
	}
	setup(); 
}
