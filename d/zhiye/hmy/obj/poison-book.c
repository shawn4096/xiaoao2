
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(BLU"五毒教毒物详解"NOR, ({ "poison book", "shu", "book" }));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        "这是一本讲述五毒各种毒药毒性道理的入门读物，乃是五毒教之根本。\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name": "poison",      // name of the skill
                        "exp_required": 500,  // minimum combat experience required
                        "jing_cost":    15,     // jing cost every time study this
                        "difficulty":   18,     // the base int to learn this skill
                        "max_skill":    100      // the maximum level you can learn
                ]) );
        }
}
