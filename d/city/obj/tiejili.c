#include <ansi.h>
#include <weapon.h>

inherit COMBINED_ITEM;
inherit THROWING;

void create()
{
	set_name("����޼", ({ "tie jili","tiejili", "jili" }));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ�ѽ������˳��õ�����޼���˰�����������Я�����á�\n");               
		set("unit", "��");
		set("base_value", 0);
		set("base_unit", "��");
		set("base_weight", 50);
		set("value", 5000);
		set("material", "steel");
		set("wield_msg", "$N��������Ƥ��������ץ��һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n�Żص�Ƥ��֮�С�\n");
	}
	set_amount(random(100) + 200);
	init_throwing(35);
}

