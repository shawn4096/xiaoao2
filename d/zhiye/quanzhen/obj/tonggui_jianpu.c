//tonggui-jian 
//by sohu
//ͬ�齣�����Ի��

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HBRED"ͬ�齣��"NOR, ({ "tonggui jianpu", "jianpu", "book" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "ҳ");
		set("long", HIR"����ȫ������Ϊ�˷�ֹ�䵥��ǿ����Ϯ���´��ġ�ͬ�齣�����ؼ���\n"
					"��Ȼ����ȫ�潣���������ʱ���ڿ������������������ս������ֵ���о�\n"NOR);
		set("unique", 1);
		set("owner",1);
		set("unique",1);
		set("treasure", 1);
		set("value", 10);
		set("no_give",1);
		set("no_drop",1);
		set("no_steal",1);
		set("no_sell",1);
		set("material", "paper");
		set("skill", ([
			"name":	"tonggui-jian",	// name of the skill
			"exp_required":	200000,	// minimum combat experience required
			"jing_cost":	30+random(10),	// jing cost every time study this
			"difficulty":	30,	// the base int to learn this skill
			"max_skill":	220	// the maximum level you can learn
		]) );
	}
}
