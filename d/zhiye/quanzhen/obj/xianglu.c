inherit ITEM;
inherit F_LIQUID;
#include <ansi.h>

void create()
{
        set_name(YEL"ͭ��¯"NOR, ({ "xiang lu", "lu" }) );
        set_weight(400);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "����һ����ͭ��¯��������������ִ���㣬�����������̡�\n");
                set("unit", "��");
                set("value", 0);
				set("no_get",1);
                set("max_liquid", 15);
        }
		/*
        set("liquid", ([
                "type": "water",
                "name": "ˮ",
                "remaining": 10,
        ]));
		*/
}
