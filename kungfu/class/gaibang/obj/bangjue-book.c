// stick-book.c

inherit ITEM;

void create()
{
	set_name("打狗棒诀", ({ "bang jue", "book" }));
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "一本打狗棒口诀精要，上面画了不少的注释，一看就是年代久远之物。\n");
		//set("value", 100);
		set("no_drop",1);
		set("no_give",1);
		set("value", 1);
        set("unique", 1);
		set("treasure",1);
		set("material", "paper");
		set("skill", ([
			"name":  "bangjue",	// name of the skill
			"exp_required":	1000,	// minimum combat experience required
			"jing_cost":	50,	// jing cost every time study this
			"difficulty":	25,	// the base int to learn this skill
			"max_skill":	150	// the maximum level you can learn
		]) );
	}
}
