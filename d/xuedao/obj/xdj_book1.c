// blade_book.c
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(RED"Ѫ�����ķ�����"NOR, ({ "xuedao xinfa", "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ������Ѫ���������ķ��������鼮�����ڻ����ڹ������ıȽϺ���͸����\n���ǻ����ڹ��й�����ʽ����ɣ�\n");
	//	set("unique", 1);
		set("newbie", 1);
//		set("treasure", 1);
		set("value", 100);
		set("material", "paper");
		set("skill", ([
			"name": "force",	// name of the skill
			"exp_required":	1000,	// minimum combat experience required
			"jing_cost": 10+random(10),	// jing cost every time study this
			"difficulty": 20,	// the base int to learn this skill
			"min_skill": 0,		// the maximum level you can learn
			"max_skill": 50,		// the maximum level you can learn
		]) );
	}
}
