// ITEM: /d/huashan/npc/obj/letter.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(CYN"����"NOR, ({"bai tie","letter"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
					"����һ���������š�������ʥ��������͸�����˵�������һ���š�\n");
                set("material", "paper");
				set("value",50000);
				set("no_drop",1);
				set("no_give",1);
				
        }
}

