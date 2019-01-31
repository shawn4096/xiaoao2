// hookbook
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC"天魔决(上)"NOR, ({ "tianmo jue", "book" }));
        set_weight(200);
        set("unit", "册");
        set("long", "这是一册天魔诀的口诀，内有关于天魔大法的详细解释。\n");
		set("unique", 1);
       // set("treasure",1);
        set("value", 3000);
        set("material", "paper");
        set("skill", ([
                        "name": "tianmo-jue",    // name of the skill
                        "exp_required": 5000,   // minimum combat experience required
                        "jing_cost": 15,// jing cost every time study this
                        "difficulty":   20, // the base int to learn this skill
                        "max_skill":    100     // the maximum level you can learn
                      ]) );
}