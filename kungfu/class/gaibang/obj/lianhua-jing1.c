// lianhua-jing.c 莲花乞讨经

inherit ITEM;

void create()
{
	set_name("莲花经(上册)", ({ "lianhua jing", "book" }));
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "一本脏兮兮的破书，上面写着一些乞讨秘籍和要领，总共分为十八个要点和二十四个禁忌。\n");
		set("value", 100);
		set("material", "paper");
		set("skill", ([
			"name":  "begging",	// name of the skill
			"exp_required":	1000,	// minimum combat experience required
			"jing_cost":	20,	// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"max_skill":	100	// the maximum level you can learn
		]) );
	}
}
