//tiezhang-xinfa.c 
inherit ITEM;

void create()
{
        set_name("�����ķ���Ҫ(��)", ({ "tiezhang xinfa", "xinfa","shu","book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�����������ķ��ؼ��°벿�֣��������ƪ��\n");
                set("unique", 1);
                set("treasure",1);                              
                set("value", 1000);
                set("material", "paper");
                set("skill", 
                ([
                        "name": "tiezhang-xinfa",          // name of the skill
                        "exp_required": 0,      // minimum combat experience required
                        "jing_cost":    50,     // jing cost every time study this
                        "difficulty":   30,     // the base int to learn this skill
						"min_skill":    100      // the maximum level you can learn
                        "max_skill":    200      // the maximum level you can learn
                ]));
        }
}
