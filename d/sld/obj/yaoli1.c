// hookbook

inherit ITEM;

void create()
{
        set_name("神龙药理(一)", ({ "shenlong yaoli", "book" }));
        set_weight(200);
        set("unit", "册");
        set("long", "这是一册神龙药理秘籍，上面描述了神龙岛如何调药以及如何进行运气疗法。\n");
		set("unique", 1);
       // set("treasure",1);
        set("value", 3000);
        set("material", "paper");
        set("skill", ([
                        "name": "shenlong-yaoli",    // name of the skill
                        "exp_required": 5000,   // minimum combat experience required
                        "jing_cost": 15,// jing cost every time study this
                        "difficulty":   20, // the base int to learn this skill
                        "max_skill":    100     // the maximum level you can learn
                      ]) );
}