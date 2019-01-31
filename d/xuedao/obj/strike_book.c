// huanxi_book1.c
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIR"�����Ʒ���Ҫ"NOR, ({ "zhangfa jingyao", "book"}));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",HIM
			"������д�š������Ʒ���Ҫ������ƪ\n"NOR);
		set("unique", 1);
		set("treasure", 1);
		set("value", 100);
		set("material", "paper");
		set("skill", ([
			"name": 	"strike",		// name of the skill
			"exp_required":	3000,			// minimum combat experience required
								// to learn this skill.
			"jing_cost":	10,			// jing cost every time study this
			"difficulty":	20,
			"min_skill":	0,// the base int to learn this skill
								// modify is jing_cost's (difficulty - int)*5%
            "max_skill":    30,         // the maximum level you can learn
								// from this object.
		]) );
	}
}
