//nianzhu.c

#include <ansi.h>
#include <armor.h>

inherit FINGER;

void create()
{
	set_name(HIM"̴ľ����"NOR, ({ "zitan nianzhu", "nianzhu" , "zhu"}) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
                set("long", "����һ����̴ľ��������飬�������ǳ�Բ����ؾ���������������\n");
		set("value", 0);
		set("no_get",1);
		set("count",1);
		set("material", "hand");
		set("armor_prop/armor", 15);
			}
	setup();
}
