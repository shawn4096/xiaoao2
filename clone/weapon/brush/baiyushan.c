//bi.c �йٱ�
#include <weapon.h>
#include <ansi.h>

inherit BRUSH;
inherit F_UNIQUE;

void create()
{
        set_name(HIW"������"NOR,({ "baiyu shan", "shan","brush" }) );
        set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "ֻ");
				set("value", 1500);
                set("material", "steel");
                set("weapon_prop/parry", 50);
                set("wield_msg", "$N�ӻ����ͳ�һֻ�����ȣ�����ҡ�ţ�����������\n");
                set("long", "����һֻ�����������Ϻþ������ƶ��ɵİ����ȡ�\n");                
                set("unwield_msg", "$N�Ѱ����ȷ��뻳�С�\n");                
        }
        init_brush(125);
        setup();
}
