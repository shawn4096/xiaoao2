// jianpu.c ��������
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(CYN"��������"NOR, ({ "liumai jianpu", "jianpu", "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�׽���������������Ҫ����װ�飬�����ᣬ��ɫ���㣬һ�����������Զ֮�\n");
		set("value", 30);
		set("no_give", 1);
		set("no_drop", 1);
		
		set("material", "paper");
		/*set("skill", ([
			"name":	"finger",	// name of the skill
			"exp_required":	100,	// minimum combat experience required
			"jing_cost":	15,	// jing cost every time study this
			"difficulty":	25,	// the base int to learn this skill
			"max_skill":	30	// the maximum level you can learn
		]) );*/
	}
}
