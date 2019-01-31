// jinguan-yusuo
// 金关玉锁二十四诀
// by sohu
inherit ITEM;
#include <ansi.h>
void create()
{
	set_name(HIY"金关玉锁二十四诀【上册】"NOR, ({ "jinguan yusuo", "jinguan" , "yusuo", "book" }));
	set_weight(600);
	if( clonep() )
	set_default_object(__FILE__);
	else
	{
		set("unit", "本");
		set("long", "这是一本线装书，上书《金关玉锁二十四诀（上册）》\n");
		set("value", 5000);
		set("treasure", 1);
		set("unique",1);
		set("no_give",1);
		set("no_drop",1);
		set("no_steal",1);

		set("material", "paper");
		set("skill", ([
			"name":			"jinguan-yusuojue",	// name of the skill
			"exp_required":	0,			// minimum combat experience required
			"jing_cost":	40,			// jing cost every time study this
			"difficulty":	45,			// the base int to learn this skill
			"min_skill":	0,	
			"max_skill":	100,			// the maximum level you can learn
			]) );
	}
}
