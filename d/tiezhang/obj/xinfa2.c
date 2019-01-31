//tiezhang-xinfa.c 
inherit ITEM;

void create()
{
        set_name("铁掌心法概要(下)", ({ "tiezhang xinfa", "xinfa","shu","book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "这是一本关于铁掌心法秘籍下半部分，乃是提高篇。\n");
                set("unique", 1);
                set("treasure",1);                              
                set("value", 1000);
                set("material", "paper");
                set("skill", 
                ([
                        "name": "tiezhang-xinfa",          // name of the skill
                        "exp_required": 0,      // minimum combat experience required
                        "jing_cost":    50,     // jing cost every time study this
                        "difficulty":   30,     // the base int to learn this skill
						"min_skill":    100      // the maximum level you can learn
                        "max_skill":    200      // the maximum level you can learn
                ]));
        }
}
