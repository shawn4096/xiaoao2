// blade.c ����Ҫ��
// hmy by sohu@xojh
inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIC"����Ҫ����Ҫ"NOR, ({ "blade book", "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("treasure", 1);
		set("unit", "��");
		set("long", "����һ���ɽ��г����������µ������ɵĵ���Ҫ�����������������е���ѧϰ��\n");
		set("value", 100);
		set("material", "paper");
		set("skill", ([
			"name":	"blade",		// name of the skill
			"exp_required":	100,	// minimum combat experience required
			"jing_cost":	20,	// jing cost every time study this
			"difficulty":	25,	// the base int to learn this skill
			"max_skill":	150	// the maximum level you can learn
		]) );
	}
}
