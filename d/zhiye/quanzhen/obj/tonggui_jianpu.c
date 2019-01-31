//tonggui-jian 
//by sohu
//同归剑法可以获得

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HBRED"同归剑谱"NOR, ({ "tonggui jianpu", "jianpu", "book" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "页");
		set("long", HIR"这是全真七子为了防止落单遭强敌所袭而新创的《同归剑法》秘籍。\n"
					"虽然不如全真剑法精妙，但短时间内可以牺牲防御大幅提升战力还是值得研究\n"NOR);
		set("unique", 1);
		set("owner",1);
		set("unique",1);
		set("treasure", 1);
		set("value", 10);
		set("no_give",1);
		set("no_drop",1);
		set("no_steal",1);
		set("no_sell",1);
		set("material", "paper");
		set("skill", ([
			"name":	"tonggui-jian",	// name of the skill
			"exp_required":	200000,	// minimum combat experience required
			"jing_cost":	30+random(10),	// jing cost every time study this
			"difficulty":	30,	// the base int to learn this skill
			"max_skill":	220	// the maximum level you can learn
		]) );
	}
}
