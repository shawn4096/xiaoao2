// book1.c

inherit ITEM;

void create()
{
	set_name("慕容心法(入门篇)", ({ "murong xinfa", "shu", "book" }));
	set_weight(50);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",
			"这是小册慕容世家心法修行篇\n"
			"由一束薄绢钉成，里面密密麻麻的画了不少打坐吐呐的姿势。\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"murong-xinfa",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost":	15,	// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"max_skill":	100	// the maximum level you can learn
		]) );
	}
}
