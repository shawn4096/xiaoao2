// cloth3.c

#include <armor.h>
#include <ansi.h>

inherit HEAD;

void create()
{
	set_name(HIY "紫金冠" NOR, ({ "zijin guan", "crown" , "guan"}) );
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "这是一件散发着淡紫色皇冠，由纯金打造而成，一看就是年代久远之物。\n");
		set("unit", "个");
		set("material", "gold");
        set("value",1000000);
		set("armor_prop/armor", 50 );
		set("wear_msg","$N将$n轻轻戴在头上。\n");
		set("remove_msg","$N把$n从头上摘了下来。\n");
	}
	setup(); 
}
