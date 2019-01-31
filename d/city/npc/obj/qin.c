//qin.c 普通五弦琴

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
	set_name("木琴",({"mu qin","qin", "muqin"}));
	set_weight(10000);
	if(clonep())
		set_default_object(__FILE__);
	else{
		set("unit","张");
		set("value",3000);
		set("material","wood");
		set("unique", 1);
		set("rigidity", 1);
		set("treasure",1);
		set("qinjian",1);
		set("long","这是一把民间常用的木质五弦琴。\n");
		set("wield_msg",HIY"$N伸手在$n上以此按了几下，发出叮咚的声音。\n"NOR);
		set("unwield_msg",HIY"$N十指一拂，琴声曳然而止。\n"NOR);
	}
	init_sword(10);
	setup();
}
