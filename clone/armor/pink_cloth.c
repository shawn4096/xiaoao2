// pink_cloth.c

#include <ansi.h>
#include <armor.h>
inherit CLOTH;

void create()
{
	set_name(HIM"�ۺ����"NOR, ({ "pink cloth", "cloth" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM"����ۺ�ɫ�ĳ����������ż�ֻ��ȵ������������һ�ɵ��㡣\n"NOR);
		set("unit", "��");
		set("value", 600);
		set("material", "cloth");
		set("armor_prop/armor", 1);
		set("armor_prop/personality", 1);
		set("female_only", 1);
	}
	setup();
}
