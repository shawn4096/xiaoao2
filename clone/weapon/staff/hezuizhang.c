// hezuizhang ������
// sohu@xojh 2014
#include <ansi.h>
#include <weapon.h>
inherit STAFF;

void create()
{
	set_name(HIB"������"NOR, ({ "hezui zhang","hezui","zhang"}));
	set_weight(10000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��ϸ���ĸ���,����Ϊһ������ĺ���״ͻ�����ǹ��졣\n");
		set("value", 1);
		set("unique", 1);
		set("rigidity", 7);
		set("material", "steel");
		set("weapon_prop/parry", 2);
		set("weapon_prop/dodge", 2);
		set("treasure",1);  
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n��������\n");
	}
	init_staff(90);
	setup();
}
