//  Code of ShenZhou
// /d/zhongnan/obj/qz_force.c �����ڹ��ķ�

inherit ITEM;

void create()
{
	set_name("���������һ�᡿", ({ "dadao jue", "daojue" , "book" }));
	set_weight(600);
	if( clonep() )
	set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("long", "����һ����װ�飬���顶ȫ������(��һ��)��\n");
		set("value", 5000);
		set("treasure", 1);
		set("unique",1);
		set("no_give",1);
		set("no_drop",1);
		set("no_steal",1);

		set("material", "paper");
		set("skill", ([
			"name":			"force",	// name of the skill
			"exp_required":	0,			// minimum combat experience required
			"jing_cost":	10,			// jing cost every time study this
			"difficulty":	15,			// the base int to learn this skill
			"max_skill":	30,			// the maximum level you can learn
			]) );
	}
}
