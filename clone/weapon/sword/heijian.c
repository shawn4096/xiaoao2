// heijian.c
//石清专属剑 

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
	set_name(HIB"黑剑"NOR,({ "hei jian", "jian", "sword" }) );
	set_weight(8000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "口");
		set("long", "这是一口"HIB"黑剑"NOR"，通体黝黑的长剑，乃黑白双剑石清所专属。\n剑气冷森，浸入肌扶，果然是一口罕见的稀世宝剑。\n"NOR);
		set("value", 1);
		set("rigidity", 5);
		set("sharpness", 5);
		set("unique", 1);
		set("treasure", 1);
		set("material", "steel");
		set("weapon_prop/parry", 20);
		set("wield_neili", 500);
		set("wield_maxneili", 800);
		set("wield_str", 25);
		set("wield_msg", HIM"随着$N挥出的右手，$n"HIM"闪出了一抹残虹。\n"NOR);
		set("unwield_msg", HIY"$N手一招，$n"HIY"幻化成一道闪电，更似孤云白鹤般消失了。\n" NOR);
	}
	init_sword(130);
	setup();
}
