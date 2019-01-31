// blade_book.c
//刀法前级著作
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(RED"血刀刀法入门技巧"NOR, ({ "daofa jiqiao", "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一本讲述刀法基本技巧的书籍，基本功讲述面面俱到。\n");
		//set("unique", 1);
		set("newbie", 1);
		//set("treasure", 1);
		set("value", 100);
		set("material", "paper");
		set("skill", ([
			"name": "blade",	// name of the skill
			"exp_required":	1000,	// minimum combat experience required
			"jing_cost": 20,	// jing cost every time study this
			"difficulty": 20,	// the base int to learn this skill
			"min_skill": 0,		// the maximum level you can learn
			"max_skill": 60		// the maximum level you can learn
		]) );
	}
}