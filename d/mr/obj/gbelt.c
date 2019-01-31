// cloth3.c

#include <armor.h>
#include <ansi.h>

inherit WAIST;

void create()
{
	set_name(HIY "黄金白玉带" NOR, ({ "huangjin baiyudai", "belt" , "yaodai"}) );
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "这是一件有白玉和黄金镶嵌而成的软腰带，一看就是不凡之物。\n");
		set("unit", "条");
		set("material", "gold");
        set("value",100000);
		set("armor_prop/armor", 40 );
		set("wear_msg","$N将$n轻轻缠在腰上，顿时感觉神清气爽。\n");
		set("remove_msg","$N把$n从腰上轻轻解开。\n");
	}
	setup(); 
}
