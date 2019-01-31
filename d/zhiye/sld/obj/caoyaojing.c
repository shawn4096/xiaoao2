#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG"草药经"NOR, ({ "caoyao jing", "jing", "caoyao" }));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        "这是一本讲述各类草药的书。\n");
                set("value", 2500);
                set("material", "paper");
                set("skill", ([
                        "name": "poison",      // name of the skill
                        "exp_required": 2000,  // minimum combat experience required
                        "jing_cost":    35,     // jing cost every time study this
                        "difficulty":   30,     // the base int to learn this skill
						"min_skill":   30,     // the base int to learn this skill
                        "max_skill":    80      // the maximum level you can learn
                ]) );
        }
}