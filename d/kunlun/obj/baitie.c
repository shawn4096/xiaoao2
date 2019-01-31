// ITEM: /d/huashan/npc/obj/letter.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(CYN"拜帖"NOR, ({"bai tie","letter"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long",
					"这是一封昆仑掌门“昆仑三圣”何足道送给少林说明内情的一封信。\n");
                set("material", "paper");
				set("value",50000);
				set("no_drop",1);
				set("no_give",1);
				
        }
}

