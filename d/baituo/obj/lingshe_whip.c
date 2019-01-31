inherit ITEM;

void create()
{
        set_name("灵蛇鞭法(上)", ({ "lingshe bianfa", "bianfa", "book" }));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        "这是一本关于<<灵蛇鞭法>>的书籍，乃是欧阳锋从灵蛇变化中而来，犀利异常。\n");
                set("value", 500);
                set("material", "paper");
                set("unique", 1);
                set("treasure", 1);
                set("skill", ([
                        "name": "lingshe-bianfa",      // name of the skill
                        "exp_required": 500,  // minimum combat experience required
                        "jing_cost":    15,     // jing cost every time study this
                        "difficulty":   18,     // the base int to learn this skill
                        "max_skill":    100,      // the maximum level you can learn
                ]) );
        }
}
