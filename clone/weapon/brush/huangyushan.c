//bi.c �йٱ�
#include <weapon.h>
#include <ansi.h>

inherit BRUSH;
inherit F_UNIQUE;

void create()
{
        set_name(HIY"������"NOR,({ "huangyu shan", "shan","brush" }) );
        set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "ֻ");
				set("value", 1500);
                set("material", "steel");
                set("weapon_prop/parry", 50);
                set("wield_msg", "$N�ӻ����ͳ�һֻ�����ȣ�����ҡ�ţ�����������\n");
                set("long", "����һֻ�����������Ϻþ������ƶ��ɵĻ����ȡ�\n");                
                set("unwield_msg", "$N�ѻ����ȷ��뻳�С�\n");                
        }
        init_brush(80);
        setup();
}
