// bed.c 合欢大床
// by sohu@xojh
inherit ITEM;
#include <ansi.h>


void create()
{
	set_name(MAG"合欢床"NOR,({"hehuan chuang","bed","chuang"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "修习欢喜禅专用的合欢床，床上铺了厚厚的棉被，\n一个雪白的女人正半裸着趴在棉被中冲你痴痴地笑着，招了招手。\n");
		set("unit", "个");
		set("no_get", 1);
		set("no_drop",1);
		set("no_sell", 1);

		set("value", 100000);
	//	set("remaining", 5);
	//	set("drink_supply", 30);
	}
	setup();
}
