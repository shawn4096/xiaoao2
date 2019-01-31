// blade_book.c
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(RED"血刀经心法入门"NOR, ({ "xuedao xinfa", "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一本讲述血刀经入门心法修炼的书籍，对于基本内功讲述的比较很是透彻。\n算是基本内功中诡异招式集大成，\n");
	//	set("unique", 1);
		set("newbie", 1);
//		set("treasure", 1);
		set("value", 100);
		set("material", "paper");
		set("skill", ([
			"name": "force",	// name of the skill
			"exp_required":	1000,	// minimum combat experience required
			"jing_cost": 10+random(10),	// jing cost every time study this
			"difficulty": 20,	// the base int to learn this skill
			"min_skill": 0,		// the maximum level you can learn
			"max_skill": 50,		// the maximum level you can learn
		]) );
	}
}
