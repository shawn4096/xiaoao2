// 清凉扇秘籍
// sohu 

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIC"清凉扇秘籍"NOR, ({ "qingliang miji", "miji" , "book" }));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一枚昆仑旁支三因观绝技清凉扇的秘籍，秘籍比较陈旧，封面上写了“朱子柳”三个字。\n");
		set("value", 1);
		set("no_sell", 1);
		set("no_steal", 1);
		set("no_give", 1);
		set("no_drop", 1);
		set("unique", 1);
		set("treasure", 1);

		set("material", "paper");
		set("base_weight", 50);
	}
	setup();
}
