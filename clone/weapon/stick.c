// zhubang.c ���

#include <weapon.h>
inherit STICK;

void create()
{
        set_name("���", ({ "zhubang" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�����Ƶ���������ֳ����ģ��ƺ��൱��ʵ��\n");
                set("value", 200);
                set("material", "bamboo");
                set("wield_msg", "$N���һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
        }
        init_stick(20);
        setup();
}
