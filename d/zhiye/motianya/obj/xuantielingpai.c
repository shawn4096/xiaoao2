#include <ansi.h>

inherit ITEM;

void create()
{
      set_name(CYN "玄铁令牌" NOR, ({ "xuantie lingp","ling pai","ling" }));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "枚");
		set("long", CYN"这是一枚"HIG"谢烟客"CYN"发散到江湖上的玄铁令牌。\n"NOR);
		set("value", 0);
		set("treasure",1);
		set("unique",1);
		set("material", "xuantie");
				set("no_drop",1);
		set("no_cun",1);
		set("no_get",1);

    }
	setup();
}
