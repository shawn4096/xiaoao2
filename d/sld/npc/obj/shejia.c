// shejia.c ��Ƥ���
// ����armor����Ч��

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIC"��Ƥ���"NOR, ({ "shepi ruanjia","ruanjia","armor", }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "pi");
                set("value", 12000);
                set("armor_prop/armor", 70);
				
        }
        setup();
}

