#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL"ľ��"NOR, ({ "mu chai","muchai","chai" }));
        set_weight(10);
		if( clonep() )
			set_default_object(__FILE__);
		else {
                set("unit", "��");
				set("long",
                        "һ��������ƫ���ľ��\n");
                set("treasure", 1);
                set("value", 0);
                set("material", "wood");
         }
}
