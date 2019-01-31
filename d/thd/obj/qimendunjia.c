#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIB"奇门遁甲"NOR, ({ "qimen dunjia", "qimen", "book","shu" }));
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
				set("long", "一本由东邪黄药师亲手著作的关于奇门遁甲的精要，非核心弟子不传。\n");               

                set("value", 5000);
                set("treasure",1);
                set("unique",1);
                set("newbie", 1);
                set("material", "paper");
                set("skill", ([
			"name": "qimen-bagua",  
			"jing_cost":    55,
			"exp_required":	100000,	// minimum combat experience required
                        "difficulty":   60,
			"min_skill":    150,
             "max_skill":    200,
                ]) );
        }
}

