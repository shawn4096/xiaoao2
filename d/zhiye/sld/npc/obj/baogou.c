// baogou.c ����������
#include <ansi.h>

#include <weapon.h>
inherit HOOK;

void create()
{
        set_name(HIC"����������"NOR, ({ "shenlong gou", "hook","gou" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�������ޱȵı���,����������֮��,��˵�ɵ�������˴��졣\n");
                set("value", 30);
                set("material", "steel");
				set("rigidity", 9);
                set("unique", 1);
                set("treasure",1);
                set("wield_maxneili", 1000);
        }
         init_hook(180);
        setup();
}
