// hookbook

inherit ITEM;

void create()
{
        set_name("��������(�²�)", ({ "hook book", "book" }));
        set_weight(200);
        set("unit", "��");
        set("long", "����һ����������²ᣬ���滭���˸��ֳ��е����ơ�\n");
		set("unique", 1);
        set("treasure",1);
        set("value", 3000);
        set("material", "paper");
        set("skill", ([
                        "name": "hook",    // name of the skill
                        "exp_required": 150000,   // minimum combat experience required
                        "jing_cost": 20+random(15),// jing cost every time study this
                        "difficulty":   30, // the base int to learn this skill
						 "min_skill":    50,
                        "max_skill":    100,     // the maximum level you can learn
         ]) );
}