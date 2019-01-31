#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIC"áÔÑôÐÄ¾÷(ÏÂ²á)"NOR, ({ "songyang xinjue","book","shu" }));
	set_weight(300);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "±¾");
		set("value", 5000);
		set("treasure",1);
		set("unique",1);
		set("newbie", 1);
		set("material", "paper");
		set("skill", ([
			"name": "songyang-jue",  
			"jing_cost":    25,     
			"exp_required":	60000,	// minimum combat experience required
			"difficulty":   30,     
			"min_skill":	100,
			"max_skill":    200,
		]) );
	}
}
