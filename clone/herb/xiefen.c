#include "herb.h"

void create()
{
        set_name(HIM "Ы��" NOR, ({ "xie fen", "xie", "fen", "herb_xiefen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "Ы���ǳ�������ҩҩ�ġ�\n" NOR);
                set("base_unit", "��");
                set("base_value", 500);
                set("base_weight", 35);
				set("unit", "��");				
        }
        setup();
}