// ITEM: /d/huashan/npc/obj/letter.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY"�ƽ����"NOR, ({"huangjin baitie","baitie","letter"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
					"���Ǵ����������Ħ�Ǵ�ʦд�����������¿��ٳ��ϵ��ż�,��Ƥ�ɻƽ���죬���������������\n");
                set("material", "gold");
				
        }
}

