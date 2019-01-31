#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(CYN"易经注解"NOR, ({ "yi jing", "jing", "yi" }));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        "这是一本由陆乘风自己所做的易经注解。上面密密麻麻的记载了很多内容\n");
                set("value", 500);
                set("material", "paper");
                set("unique", 1);
                set("treasure", 1);
                set("skill", ([
                        "name": "qimen-bagua",      // name of the skill
                        "exp_required": 500,  // minimum combat experience required
                        "jing_cost":    20,     // jing cost every time study this
                        "difficulty":   18,     // the base int to learn this skill
                        "min_skill":    50,      // the maximum level you can learn
						"max_skill":    100,
                ]) );
        }
}
