// jianpu.c 六脉剑谱
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(CYN"六脉神剑谱"NOR, ({ "liumai jianpu", "jianpu", "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一套讲解六脉神剑练功诀要的线装书，共六册，古色古香，一看就是年代久远之物。\n");
		set("value", 30);
		set("no_give", 1);
		set("no_drop", 1);
		
		set("material", "paper");
		/*set("skill", ([
			"name":	"finger",	// name of the skill
			"exp_required":	100,	// minimum combat experience required
			"jing_cost":	15,	// jing cost every time study this
			"difficulty":	25,	// the base int to learn this skill
			"max_skill":	30	// the maximum level you can learn
		]) );*/
	}
}
