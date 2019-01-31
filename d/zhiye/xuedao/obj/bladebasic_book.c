// blade_book.c
//刀法中级著作
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(RED"门派刀法大全"NOR, ({ "daofa daquan", "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一本讲述江湖各门派常见刀法招式以及精要的书籍。\n算是刀法中诡异招式集大成著作，\n");
		set("unique", 1);
		set("newbie", 1);
		set("treasure", 1);
		set("value", 100);
		set("material", "paper");
		set("skill", ([
			"name": "blade",	// name of the skill
			"exp_required":	1000,	// minimum combat experience required
			"jing_cost": 20,	// jing cost every time study this
			"difficulty": 20,	// the base int to learn this skill
			"min_skill": 60,		// the maximum level you can learn
			"max_skill": 120,		// the maximum level you can learn
		]) );
	}
}
