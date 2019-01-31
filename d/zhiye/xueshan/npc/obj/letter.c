// ITEM: /d/huashan/npc/obj/letter.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY"黄金拜帖"NOR, ({"huangjin baitie","baitie","letter"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
                set("long",
					"这是大轮寺掌门鸠摩智大师写给大理天龙寺枯荣长老的信件,封皮由黄金打造，看起来金光闪闪。\n");
                set("material", "gold");
				
        }
}

