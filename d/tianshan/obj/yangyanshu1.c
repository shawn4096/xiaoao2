// fojing.c

inherit ITEM;

string* titles = ({
	"养颜术(上)",

});

void create()
{
	set_name(titles[random(sizeof(titles))], ({ "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一册讲解美容养颜的书籍，内容较为浅，为初学者选用。\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"yangyanshu",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost":	20,	// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"max_skill":	100	// the maximum level you can learn
		]) );
	}
}
