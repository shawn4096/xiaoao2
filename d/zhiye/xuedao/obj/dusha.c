#include <ansi.h>
#include <weapon.h>

inherit COMBINED_ITEM;
inherit THROWING;

void create()
{
	set_name(HIB"��ɰ"NOR, ({ "du sha", "sha" , "dusha"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ������ͨͨ����ʯ�ӡ�\n");               
		set("unit", "��");
		set("value", 1);
		set("base_value", 0);
		set("base_unit", "��");
		set("poison", "lansha_poison");

		set("base_weight", 12);
	}
	set_amount(random(70) + 81);
	init_throwing(15);
}

