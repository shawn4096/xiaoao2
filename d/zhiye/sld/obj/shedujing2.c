inherit ITEM;

void create()
{
        set_name("蛇毒经(下)", ({ "shedu jing", "jing"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        "这是一本洪教主亲自手书的蛇毒经下卷，里面详细记录了各种蛇的习性和毒性。\n");
                set("value", 10000);
                set("material", "paper");
                set("skill", ([
                        "name": "poison",      // name of the skill
                        "exp_required": 300000,  // minimum combat experience required
                        "jing_cost":    50,     // jing cost every time study this
                        "difficulty":   25,     // the base int to learn this skill
						"max_skill":    120,
                        "max_skill":    150      // the maximum level you can learn
                ]) );
        }
}