//axe_book.c 斧法概要
inherit ITEM;

void create()
{
        set_name("斧法概要", ({ "fufa gaiyao", "gaiyao","shu","book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "这是一本裂天斧法的入门概要。\n");
                set("unique", 1);
                set("treasure",1);                              
                set("value", 1000);
                set("material", "paper");
                set("skill", 
                ([
                        "name": "axe",          // name of the skill
                        "exp_required": 0,      // minimum combat experience required
                        "jing_cost":    20,     // jing cost every time study this
                        "difficulty":   10,     // the base int to learn this skill
                        "max_skill":    100      // the maximum level you can learn
                ]));
        }
}
