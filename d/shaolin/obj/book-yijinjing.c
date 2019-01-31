#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIY"易筋经神功"NOR, ({ "yijin jing", "ying", "shu", "book" }));
	set_weight(50);
	if( clonep() ) {
		call_out("dest", 1800);
		set_default_object(__FILE__);
	} else {
		set("unit", "卷");
		set("long",
			"这是一套四册组合而成的易筋经神功秘籍，分为内功篇、修行篇、轻身篇、兵器篇。本册主要是内功修行篇。\n"
			"其中内功篇乃是整个少林武学根基，里面密密麻麻的画了不少打坐吐呐的姿势。人云：‘少林第一神功’。\n"
			"轻身篇里面密密麻麻的画了不少飞跃奔走的姿势，宛如孤雁横空，其中含有一苇渡江神技。\n"
			);
        set("treasure", 1);
		set("no_give", 1);
		set("no_drop", 1);
		set("no_steal", 1);
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"yijin-jing",	// name of the skill
			"exp_required":	5000000,	// minimum combat experience required
			"jing_cost":	random(50),	// jing cost every time study this
			"difficulty":	40,	// the base int to learn this skill
			"max_skill":	500	// the maximum level you can learn
		]) );
	}
}

void dest()
{
	destruct(this_object());
}
