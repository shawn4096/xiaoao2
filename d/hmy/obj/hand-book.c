// throwing.c ����Ҫ��
// hmy by sohu@xojh
inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(BLU"��ħ�ַ���Ҫ"NOR, ({ "hand book", "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("treasure", 1);
		set("unit", "��");
		set("long", "����һ���ɹ�����ʹ�����׫����ħ�ַ���ϰҪ�㣬�����е���ѧϰ�����ַ�ʹ�á�\n");
		set("value", 40);
		set("material", "paper");
		set("skill", ([
			"name":	"hand",		// name of the skill
			"exp_required":	100,	// minimum combat experience required
			"jing_cost":	20,	// jing cost every time study this
			"difficulty":	25,	// the base int to learn this skill			
			"max_skill":	100	// the maximum level you can learn
		]) );
	}
}
