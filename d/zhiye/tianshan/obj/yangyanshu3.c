// fojing.c

inherit ITEM;

string* titles = ({
	"养颜术(下)",

});

void create()
{
	set_name(titles[random(sizeof(titles))], ({ "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一册讲解美容养颜的书籍，内容及其丰富，多为外界所不知的种种秘方。\n");
		set("value", 500);
		set("treasure",1);
		set("unique", 1);

		set("material", "paper");
		set("skill", ([
			"name":	"yangyanshu",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost":	50,	// jing cost every time study this
			"difficulty":	50,	// the base int to learn this skill
			"min_skill":	200,	// the maximum level you can learn
			"max_skill":	220	// the maximum level you can learn
		]) );
	}
}
