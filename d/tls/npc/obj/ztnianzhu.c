//nianzhu.c

#include <ansi.h>
#include <armor.h>

inherit FINGER;

void create()
{
	set_name(HIM"檀木念珠"NOR, ({ "zitan nianzhu", "nianzhu" , "zhu"}) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "副");
                set("long", "这是一副紫檀木所雕刻念珠，看起来非常圆润，想必经常被抚摸滚动。\n");
		set("value", 0);
		set("no_get",1);
		set("count",1);
		set("material", "hand");
		set("armor_prop/armor", 15);
			}
	setup();
}
