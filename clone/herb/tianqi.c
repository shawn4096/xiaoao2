#include "herb.h"

void create()
{
        set_name(NOR + WHT "����" NOR, ({ "tian qi", "tian", "qi", "herb_tianqi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "�����ǳ�������ҩҩ�ġ�\n" NOR);
                set("unit", "��");
                set("base_value", 400);
                set("base_weight", 55);
        }
        setup();
}