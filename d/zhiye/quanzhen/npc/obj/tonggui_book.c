// tonggui-jianpu.c
//ͬ�齣������
// by sohu@xojh

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( "ͬ�齣��", ({ "tonggui jianpu", "jianpu", "book"  }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ��ȫ��������������ͬ�齣����Ҫ������ȫ����ӶԸ�ǿ��ʱ���ý�����ʽ��\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name": "tonggui-jian",       // name of the skill
                        "exp_required": 100000,      // minimum combat experience required
                        "jing_cost": 20,        // jing cost every time study this
                        "difficulty":   20,     // the base int to learn this skill
                        "max_skill":    100,     // the maximum level you can learn
                ]) );
        }
}
