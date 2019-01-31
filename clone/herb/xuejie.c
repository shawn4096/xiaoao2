#include "herb.h"

void create()
{
        set_name(NOR + RED "Ñª½ß" NOR, ({ "xue jie", "xue", "jie", "herb_xuejie" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + RED "Ñª½ßÊÇ³£¼ûµÄÖÐÒ©Ò©²Ä¡£\n" NOR);
                set("base_unit", "¿é");
				set("unit", "Öê");
                set("base_value", 200);
                set("base_weight", 40);
        }
        setup();
}
