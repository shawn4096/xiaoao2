inherit ITEM;
inherit F_LIQUID;
#include <ansi.h>

void create()
{
        set_name(YEL"铜香炉"NOR, ({ "xiang lu", "lu" }) );
        set_weight(400);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "这是一个大铜香炉，里面插了三根粗大的香，腾起袅袅的烟。\n");
                set("unit", "个");
                set("value", 0);
				set("no_get",1);
                set("max_liquid", 15);
        }
		/*
        set("liquid", ([
                "type": "water",
                "name": "水",
                "remaining": 10,
        ]));
		*/
}
