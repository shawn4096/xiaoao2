#include <ansi.h>
#include <weapon.h>
inherit COMBINED_ITEM;
inherit THROWING;

void create()
{
       set_name(HIC "����" NOR, ({"qi zi", "qizi", "zi" }));
       if( clonep() )
               set_default_object(__FILE__);
       else {
		set("long", "һ�кڰ����ӣ���������Ө��͸���ڰ׷��������˰������֡�\n");               
               set("unit", "��");
               set("base_value", 10000);
               set("base_unit", "��");
               set("base_weight", 10);
       }
       set_amount(360);
       init_throwing(50);
}

