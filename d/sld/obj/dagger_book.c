// legbook

inherit ITEM;

void create()
{
        set_name("刺客匕法精要", ({ "bifa jingyao", "book" }));
        set_weight(200);
        set("unit", "册");
        set("long", "这是一册刺客匕法精要，上面画满了各种刺客刺杀时的技巧。\n");
//      set("treasure",1);
        set("value", 3000);
        set("material", "paper");
        set("skill", ([
                        "name": "dagger",    // name of the skill
                        "exp_required": 5000,   // minimum combat experience required
                        "jing_cost": 10+random(15),// jing cost every time study this
                        "difficulty":   10, // the base int to learn this skill
                        "max_skill":    100     // the maximum level you can learn
                      ]) );
}