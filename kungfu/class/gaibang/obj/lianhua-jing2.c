// lianhua-jing.c �������־�

inherit ITEM;

void create()
{
	set_name("������(�²�)", ({ "lianhua jing", "book" }));
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ������������飬����д��һЩ�����ؼ���Ҫ�죬�ܹ���Ϊʮ�˸�Ҫ��Ͷ�ʮ�ĸ����ɡ�\n");
		set("value", 100);
		set("material", "paper");
		set("skill", ([
			"name":  "begging",	// name of the skill
			"exp_required":	1000,	// minimum combat experience required
			"jing_cost":	40,	// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"min_skill":	100,
			"max_skill":	200,	// the maximum level you can learn
		]) );
	}
}
