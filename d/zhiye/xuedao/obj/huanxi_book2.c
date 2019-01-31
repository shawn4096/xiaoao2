// huanxi_book1.c
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIM"时轮经"NOR, ({ "shilun jing", "book", "jing" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",HIM
			"封面上写着「时轮经」高级篇\n"NOR);
		set("value", 1000000);
		set("unique", 1);
		set("treasure", 1);
		set("material", "paper");
		set("skill", ([
			"name": 	"huanxi-chan",		// name of the skill
			"exp_required":	100000,			// minimum combat experience required
								// to learn this skill.
			"jing_cost":	50,			// jing cost every time study this
			"difficulty":	40,
			"min_skill":	150,// the base int to learn this skill
								// modify is jing_cost's (difficulty - int)*5%
            "max_skill":    200,         // the maximum level you can learn
								// from this object.
		]) );
	}
}
