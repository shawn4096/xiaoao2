// blade_book.c
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(RED"Ѫ��������Ҫ"NOR, ({ "daofa jingyao", "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ������Ѫ��������Ҫ���鼮�����ڻ������������ıȽϺ���͸����\n���ǵ����й�����ʽ����ɣ�\n");
		set("unique", 1);
		set("newbie", 1);
		set("treasure", 1);
		set("value", 100);
		set("material", "paper");
		set("skill", ([
			"name": "blade",	// name of the skill
			"exp_required":	1000,	// minimum combat experience required
			"jing_cost": 20,	// jing cost every time study this
			"difficulty": 20,	// the base int to learn this skill
			"min_skill": 120,		// the maximum level you can learn
			"max_skill": 220,		// the maximum level you can learn
		]) );
	}
}
