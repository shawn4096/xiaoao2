//xtg-quest item

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIC"ȫ�潣������"NOR, ({ "quanzhen jianpu", "jianpu", "book" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "ҳ");
		set("long", HIG"����һ�����𴦻����������ȫ�潣����Ҫ��\n"NOR);
		set("unique", 1);
//		set("newbie", 1);
		set("treasure", 1);
		set("value", 500000);
		set("material", "paper");
		set("skill", ([
			"name":	"sword",	// name of the skill
			"exp_required":	100000,	// minimum combat experience required
			"jing_cost":	30,	// jing cost every time study this
			"difficulty":	30,	// the base int to learn this skill
			"max_skill":	120	// the maximum level you can learn
		]) );
	}
}
