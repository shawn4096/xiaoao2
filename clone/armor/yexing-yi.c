#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("ҹ����", ({ "yexing yi", "yi", "cloth"}) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ����ɫ��ҹ���¡�\n");
                set("material", "cloth");
                set("armor_prop/armor", 100);
                set("value", 1000);
        }
        setup();
}
