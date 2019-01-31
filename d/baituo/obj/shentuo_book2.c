inherit ITEM;

void create()
{
        set_name("神驼雪山掌法(下)", ({ "shentuo zhangfa", "zhangfa", "book" }));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                        "这是一本关于<<神驼雪山掌法>>的书籍，乃是欧阳锋所创，犀利异常。\n");
                set("value", 500);
                set("material", "paper");
                set("unique", 1);
			//	set("no_drop", "这么珍贵的武林秘籍，你可不能随意丢弃！\n");
              //  set("no_get", "这样东西是那人的宝贝，连睡觉都要当枕头垫，你无法拿取！\n");
                set("no_give", "这么珍贵的武林秘籍，你可不能随意给人！\n");

                set("treasure", 1);
                set("skill", ([
                        "name": "shentuo-zhang",      // name of the skill
                        "exp_required": 500,  // minimum combat experience required
                        "jing_cost":    25,     // jing cost every time study this
                        "difficulty":   30,     // the base int to learn this skill
						"min_skill":    100,
                        "max_skill":    200,      // the maximum level you can learn
                ]) );
        }
}
