// hookbook

inherit ITEM;

void create()
{
        set_name("��������(�ϲ�)", ({ "hook book", "book" }));
        set_weight(200);
        set("unit", "��");
        set("long", "����һ����������ϲᣬ���滭���˸��ֳ��й��ӳ��ֵ����ơ�\n");
		set("unique", 1);
        set("treasure",1);
        set("value", 3000);
        set("material", "paper");
        set("skill", ([
                        "name": "hook",    // name of the skill
                        "exp_required": 5000,   // minimum combat experience required
                        "jing_cost": 10+random(15),// jing cost every time study this
                        "difficulty":   10, // the base int to learn this skill
                        "max_skill":    50     // the maximum level you can learn
        ]) );
}