// bangzhuling.c 长乐帮主令
// By sohu@xojh

#include <ansi.h>

inherit ITEM;
object ppl;

void create()
{
	set_name(HIW"帮主令"NOR, ({ "bangzhu ling", "ling" }) );
	set_weight(50);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "块");
		set("material", "stone");
		set("long", "一块和田羊脂白玉做成的令牌，呈月牙形，中心雕刻一个令字，背后写了“长乐帮”帮主几个字。\n");
		set("value", 0);
		set("treasure",1);
		set("no_drop",1);
		set("no_cun",1);
		set("no_get",1);
		set("no_steal", 1);
	}
	setup();
}
