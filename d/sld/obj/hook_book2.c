// hookbook

inherit ITEM;

void create()
{
        set_name("基本钩法(下册)", ({ "hook book", "book" }));
        set_weight(200);
        set("unit", "册");
        set("long", "这是一册基本钩法下册，上面画满了各种出招的姿势。\n");
		set("unique", 1);
        set("treasure",1);
        set("value", 3000);
        set("material", "paper");
        set("skill", ([
                        "name": "hook",    // name of the skill
                        "exp_required": 150000,   // minimum combat experience required
                        "jing_cost": 20+random(15),// jing cost every time study this
                        "difficulty":   30, // the base int to learn this skill
						 "min_skill":    50,
                        "max_skill":    100,     // the maximum level you can learn
         ]) );
}