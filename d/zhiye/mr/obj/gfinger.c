// cloth3.c

#include <armor.h>
#include <ansi.h>

inherit FINGER;

void create()
{
	set_name(HIY "�ƽ�ָ��" NOR, ({ "gold finger", "finger" , "zhitao"}) );
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "����һ���ƽ�������ָ�ס�\n");
		set("unit", "��");
		set("material", "gold");
        set("value",100000);
		set("armor_prop/armor", 20 );		
		set("wear_msg","$N��$n����ָ�ϡ�\n");
		set("remove_msg","$N��$n��ָ���ÿ���\n");
	}
	setup(); 
}
