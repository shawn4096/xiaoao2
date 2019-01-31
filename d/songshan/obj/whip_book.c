// Code of ShenZhou
// /d/zhongnan/obj/whip_book.c
inherit ITEM;

void create()
{
	set_name("��ɽ�޷���Ҫ", ({ "songshan bianfa", "book","shu" }));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
                        "����ɽ�޷��� -- �Ͼ�\n");
		set("value", 200);
		set("material", "paper");
		set("skill", ([
			"name":         "whip",		        // name of the skill
			"exp_required":	150000,			// minimum combat experience required
						                // to learn this skill.
			"jing_cost":    20,	                // jing cost every time study this
			"difficulty":	30,		        // the base int to learn this skill
							        // modify is jing_cost's (difficulty - int)*5%
			"max_skill":	100		        // the maximum level you can learn						        // from this object.
		]) );
	}
}
