// stick-book.c

inherit ITEM;

void create()
{
	set_name("�򹷰���", ({ "bang jue", "book" }));
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ���򹷰��ھ���Ҫ�����滭�˲��ٵ�ע�ͣ�һ�����������Զ֮�\n");
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
