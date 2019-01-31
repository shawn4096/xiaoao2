// ITEM: /d/huashan/obj/staff_book.c
// Date: Look 99/03/25

inherit ITEM;

void create()
{
	set_name("华山气宗内功图解", ({ "neigong book", "book" }));
	set_weight(200);
	set("unit", "册");
	set("long", "这是一册为华山气宗入门弟子准备的内功修炼图解，总共有九式。\n");
        set("treasure",1);
	set("value", 500);
	set("material", "paper");
	set("skill", ([
			"name":	"force",	// name of the skill
			"exp_required":	1000,	// minimum combat experience required
			"jing_cost": 10,// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"max_skill":	50	// the maximum level you can learn
		      ]) );
}
