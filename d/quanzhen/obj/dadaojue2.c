//  Code of ShenZhou
// /d/zhongnan/obj/qz_force.c �����ڹ��ķ�

inherit ITEM;

void create()
{
	set_name("��������ڶ��᡿", ({ "dadao jue", "daojue" , "book" }));
	set_weight(600);
	if( clonep() )
	set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("long", "����һ����װ�飬���顶ȫ������(�ڶ���)��\n");
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
			"jing_cost":	15,			// jing cost every time study this
			"difficulty":	25,			// the base int to learn this skill
			"min_skill":	30,	
			"max_skill":	60,			// the maximum level you can learn
			]) );
	}
}
