//fuchen.c ���� ����֮��
//by sohu
#include <weapon.h>
inherit WHIP;

void create()
{
	set_name("����", ({ "fu chen", "fuchen" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����ҳ����������õ���ͨ����������ľľ������ɢ��˿��֯���ɡ�\n");
		set("value", 1000);
		set("material", "wood");
		set("wield_msg", "$N��ৡ���һ������һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n������䡣\n");
	}
	init_whip(20);
	setup();
}
