// blade_book.c
//����ǰ������
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(RED"Ѫ���������ż���"NOR, ({ "daofa jiqiao", "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����������������ɵ��鼮����������������㵽��\n");
		//set("unique", 1);
		set("newbie", 1);
		//set("treasure", 1);
		set("value", 100);
		set("material", "paper");
		set("skill", ([
			"name": "blade",	// name of the skill
			"exp_required":	1000,	// minimum combat experience required
			"jing_cost": 20,	// jing cost every time study this
			"difficulty": 20,	// the base int to learn this skill
			"min_skill": 0,		// the maximum level you can learn
			"max_skill": 60		// the maximum level you can learn
		]) );
	}
}