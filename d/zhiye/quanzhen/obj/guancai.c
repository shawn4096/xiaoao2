inherit ITEM;
//inherit F_LIQUID;
#include <ansi.h>

void create()
{
        set_name(HIB"重阳真人棺椁"NOR, ({ "chongyan guanguo", "guanguo" }) );
        set_weight(400);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "这是一个由坚硬的木材制作棺椁，全真教祖师重阳真人躺在里面，虽死犹生。\n");
                set("unit", "个");
                set("value", 0);
				set("no_get",1);
				set("zhenren",1);
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
