// book1.c

inherit ITEM;

void create()
{
	set_name("Ľ���ķ�(����ƪ)", ({ "murong xinfa", "shu", "book" }));
	set_weight(50);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
			"����С��Ľ�������ķ�����ƪ\n"
			"��һ������ɣ�������������Ļ��˲��ٴ������ŵ����ơ�\n");
		set("value", 500);
		set("material", "paper");
		set("skill", ([
			"name":	"murong-xinfa",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost":	15,	// jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
			"max_skill":	100	// the maximum level you can learn
		]) );
	}
}
