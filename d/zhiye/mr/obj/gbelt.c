// cloth3.c

#include <armor.h>
#include <ansi.h>

inherit WAIST;

void create()
{
	set_name(HIY "�ƽ�����" NOR, ({ "huangjin baiyudai", "belt" , "yaodai"}) );
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "����һ���а���ͻƽ���Ƕ���ɵ���������һ�����ǲ���֮�\n");
		set("unit", "��");
		set("material", "gold");
        set("value",100000);
		set("armor_prop/armor", 40 );
		set("wear_msg","$N��$n����������ϣ���ʱ�о�������ˬ��\n");
		set("remove_msg","$N��$n����������⿪��\n");
	}
	setup(); 
}
