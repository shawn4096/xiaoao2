#include "herb.h"

void create()
{
        set_name(HIW "ѩ��" NOR, ({ "xue lian", "xue", "lian", "herb_xuelian" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "ѩ������Ϊ�������ҩҩ�ġ�\n" NOR);
                set("base_unit", "��");
				set("unit", "��");
                set("base_value", 30000);
                set("base_weight", 40);
        }
        setup();
}
