// zhubang.c ���
#include <ansi.h>
#include <weapon.h>
inherit STICK;

void create()
{
        set_name(GRN"���"NOR, ({ "zhubang" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�����Ƶ���������ֳ����ģ��ƺ��൱��ʵ��\n");
set("value", 1000);
                set("material", "steel");
                set("wield_msg", "$N���һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
        }
        init_stick(25);
        setup();
}
