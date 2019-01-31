#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIC"áÔÑôÐÄ¾÷(ÉÏ²á)"NOR, ({ "songyang xinjue","book","shu" }));
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
			"jing_cost":    15,     
			"exp_required":	60000,	// minimum combat experience required
			"difficulty":   20,     
			//"min_skill":	50,
			"max_skill":    100,
		]) );
	}
}
