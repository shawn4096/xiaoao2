#include <ansi.h>
inherit ITEM;
//inherit F_UNIQUE;
void create()
{
        set_name(CYN"Ƥ��"NOR, ({"pi nang", "pinang" , "nang"}) );
        set_weight(1000);
        set_max_encumbrance(40000);
        if( clonep() )
                set_default_object(__FILE__);
        else{
        set("unit", "��");
        set("long", "����һ������Ƥ�������ҡ�����������ǻ�����Ҽ����쳣������ȥ\n"
"���ǹ⻬���˴����ǲ���װ��ˮ�Լ���Ʒ����֮��,����һ���ı���֮�á�\n");
        set("value", 100000);
        set("material","skin");
        set("keep_same",1);
		set("no_give",1);
        set("no_drop",1);

        set("no_steal", 1);
        }        
        setup();
}
