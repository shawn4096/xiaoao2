
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIB"ҩ����ƪ"NOR, ({ "yaowang shenpian", "shenpian","book"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
                        "����һ����ҩ���ȶ���ҩ������ľ��顶ҩ����ƪ��,���������ҩ��һ����ѧ��\n");
                set("value", 10000);
                set("material", "paper");
                set("skill", ([
                        "name": "poison",      // name of the skill
                        "exp_required": 2000000,  // minimum combat experience required
                        "jing_cost":    50,     // jing cost every time study this
                        "difficulty":   35,     // the base int to learn this skill
						"min_skill":    100, 
                        "max_skill":    150      // the maximum level you can learn
                ]) );
        }
}