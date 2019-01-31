inherit ITEM;

void create()
{
        set_name("蛇毒经(上)", ({ "shedu jing", "jing" }));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        "这是一本由洪教主亲自手书的蛇毒经，讲述各类蛇毒以及解药配置的书。\n");
                set("value", 5500);
                set("material", "paper");
                set("skill", ([
                        "name": "poison",      // name of the skill
                        "exp_required": 100000,  // minimum combat experience required
                        "jing_cost":    40,     // jing cost every time study this
                        "difficulty":   25,     // the base int to learn this skill
						"max_skill":    80,
                        "max_skill":    120      // the maximum level you can learn
                ]) );
        }
}