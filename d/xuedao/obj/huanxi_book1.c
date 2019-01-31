// huanxi_book1.c
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIC"两情"MAG"相悦"HIG"合欢经"NOR, ({ "hehuan jing", "book", "hehuan", "jing" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long",HIG
			"封面上写着「两情相悦合欢经」入门篇\n"NOR);
		set("value", 10000);
		set("material", "paper");
		set("skill", ([
			"name": 	"huanxi-chan",		// name of the skill
			"exp_required":	0,			// minimum combat experience required
								// to learn this skill.
			"jing_cost":	30,			// jing cost every time study this
			"difficulty":	20,
			"min_skill":	60,// the base int to learn this skill
								// modify is jing_cost's (difficulty - int)*5%
            "max_skill":    150,         // the maximum level you can learn
								// from this object.
		]) );
	}
}
