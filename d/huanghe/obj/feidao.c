
#include <ansi.h>

#include <weapon.h>

inherit COMBINED_ITEM;
inherit THROWING;

void create()
{
	set_name(WHT"�ɵ�"NOR, ({ "fei dao", "feidao", "dao" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ������Ϊ����ʹ�õ���Ҷ�ɵ���\n");
		set("base_value", 1000);
		set("base_unit", "��");
        set("base_weight", 20);		
	}
	set_amount(25);
    init_throwing(80);
}
