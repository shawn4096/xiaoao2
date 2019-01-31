#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIY"�׽��"NOR, ({ "yijin jing", "ying", "shu", "book" }));
	set_weight(50);
	if( clonep() ) {
		call_out("dest", 1800);
		set_default_object(__FILE__);
	} else {
		set("unit", "��");
		set("long",
			"����һ���Ĳ���϶��ɵ��׽���ؼ�����Ϊ�ڹ�ƪ������ƪ������ƪ������ƪ��������Ҫ���ڹ�����ƪ��\n"
			"�����ڹ�ƪ��������������ѧ������������������Ļ��˲��ٴ������ŵ����ơ����ƣ������ֵ�һ�񹦡���\n"
			"����ƪ������������Ļ��˲��ٷ�Ծ���ߵ����ƣ���������գ����к���һέ�ɽ��񼼡�\n"
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
