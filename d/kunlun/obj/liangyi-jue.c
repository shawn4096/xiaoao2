// force-book.c

inherit ITEM;

string* titles = ({
	"�����Ǿ�",
});

void create()
{
	set_name(titles[random(sizeof(titles))], ({ "mi ji" ,"miji", "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "�������������Ǿ��ķ����ؼ���\n");
		set("value", 500);
		set("newbie", 1);
		set("unique", 1);
		set("treasure", 1);
		set("material", "paper");
		set("skill", ([
			"name": "liangyi-jue",     // name of the skill
			"exp_required": 1000,      // minimum combat experience required
			"jing_cost":    25,     // jing cost every time study this
			"difficulty":   40,     // the base int to learn this skill
			"max_skill":    200      // the maximum level you learn
		]) );
	}
}
