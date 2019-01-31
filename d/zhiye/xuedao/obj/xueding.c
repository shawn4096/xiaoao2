// qinxiu-jiasha.c
 
#include <ansi.h> 
//#include <armor.h> 
 
inherit ITEM; 
 
void create() 
{ 
        set_name( RED "血鼎" NOR, ({ "xue ding", "xueding" , "ding"}) ); 
        set_weight(1000); 
        if( clonep() ) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "个"); 
                set("long", "这是一个神秘的铜鼎，发出幽暗的血泽光芒，有些阴森恐怖。\n"
							+"你无意中看一眼，宛如有一个魔鬼般的将你往里拉扯！甚是邪异！\n"); 
                set("value", 100000); 
				set("no_get", 1); 
				set("no_drop", 1); 

				set("no_give", 1); 
				set("no_sell", 1); 
                set("material", "steel"); 
                set("armor_prop/armor", 50); 
        } 
        setup(); 
} 
