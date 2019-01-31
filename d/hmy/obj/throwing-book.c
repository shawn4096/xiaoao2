// throwing.c 暗器要诀
// hmy by sohu@xojh
inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(BLU"暗器手法精要"NOR, ({ "throwing book", "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("treasure", 1);
		set("unit", "本");
		set("long", "这是一本由光明右使曲洋编撰的漫天花雨手法练习要点，供教中弟子学习。\n");
		set("value", 40);
		set("material", "paper");
		set("skill", ([
			"name":	"throwing",		// name of the skill
			"exp_required":	100,	// minimum combat experience required
			"jing_cost":	20,	// jing cost every time study this
			"difficulty":	25,	// the base int to learn this skill
			"max_skill":	100	// the maximum level you can learn
		]) );
	}
}
