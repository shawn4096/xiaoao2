// hezuizhang 鹤嘴杖
// sohu@xojh 2014
#include <ansi.h>
#include <weapon.h>
inherit STAFF;

void create()
{
	set_name(HIB"鹤嘴杖"NOR, ({ "hezui zhang","hezui","zhang"}));
	set_weight(10000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
		set("long", "这是一柄细长的钢杖,顶端为一个尖锐的鹤嘴状突起，甚是怪异。\n");
		set("value", 1);
		set("unique", 1);
		set("rigidity", 7);
		set("material", "steel");
		set("weapon_prop/parry", 2);
		set("weapon_prop/dodge", 2);
		set("treasure",1);  
		set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
		set("unwield_msg", "$N将手中的$n背到背后。\n");
	}
	init_staff(90);
	setup();
}
