// cloth3.c

#include <armor.h>
#include <ansi.h>
inherit BOOTS;

void create()
{
	set_name(HIY "������" NOR, ({ "huangyun lu", "boot" ,"huangyun" , "xue" }));
	set_weight(2000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "����һ˫���ɫ���к�����������ѥ�ӣ�������Ϊ�������ƺ�û���˴�����\n");
		set("unit", "˫");
		set("material", "boots");
		set("armor_prop/armor", 30);
		set("value",100000);
		set("wear_msg","$N��$n���ڽ��ϣ����������\n");
		set("remove_msg","$N��$n�ӽ�������������\n");
	}
	setup(); 
}
