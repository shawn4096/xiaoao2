// hookbook

inherit ITEM;

void create()
{
        set_name("基本钩法(上册)", ({ "hook book", "book" }));
        set_weight(200);
        set("unit", "册");
        set("long", "这是一册基本钩法上册，上面画满了各种出招钩子出手的姿势。\n");
		set("unique", 1);
        set("treasure",1);
        set("value", 3000);
        set("material", "paper");
        set("skill", ([
                        "name": "hook",    // name of the skill
                        "exp_required": 5000,   // minimum combat experience required
                        "jing_cost": 10+random(15),// jing cost every time study this
                        "difficulty":   10, // the base int to learn this skill
                        "max_skill":    50     // the maximum level you can learn
        ]) );
}