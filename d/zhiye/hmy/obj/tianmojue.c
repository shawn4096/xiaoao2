// hookbook
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC"��ħ��(��)"NOR, ({ "tianmo jue", "book" }));
        set_weight(200);
        set("unit", "��");
        set("long", "����һ����ħ���Ŀھ������й�����ħ�󷨵���ϸ���͡�\n");
		set("unique", 1);
       // set("treasure",1);
        set("value", 3000);
        set("material", "paper");
        set("skill", ([
                        "name": "tianmo-jue",    // name of the skill
                        "exp_required": 5000,   // minimum combat experience required
                        "jing_cost": 15,// jing cost every time study this
                        "difficulty":   20, // the base int to learn this skill
                        "max_skill":    100     // the maximum level you can learn
                      ]) );
}