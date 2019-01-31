inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("水碗", ({ "posun shuiwan", "bowl" }) );
        set_weight(400);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "这是一个水碗，里面有什么呢？当然是水啦。\n");
                set("unit", "个");
                set("value", 0);
				set("no_get", 1);
				set("no_give", 1);
				set("no_drop", 1);
                set("max_liquid", 15);
        }
        set("liquid", ([
                "type": "water",
                "name": "水",
                "remaining": 10,
        ]));
}
