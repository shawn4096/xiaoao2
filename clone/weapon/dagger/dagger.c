// tie-ling.c ����
// by snowman@SJ 18/02/2000

#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
        set_name("��ɱذ��", ({ "ansha bishou","bishou", "dagger" }));
		set("long", "����һ�����������İ�ɱذ�ס�\n");		
         set("unit", "��");         
         set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {              
                set("value", 1000);
                set("material", "steel");                
                
        }
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
        set("unwield_msg", "$N�����е�$n������䡣\n");       
        init_dagger(20);
        setup();
}

