// miandao.c �嵶

#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name( "�嵶" , ({ "mian dao", "dao", "blade","miandao" }));
        set_weight(12000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "���ǽ�������ɥ�����嵶����������̣����ڷ�����������㡣\n");
                set("value", 1500);
                set("material", "iron");
        }
        init_blade(50);
        setup();
}
