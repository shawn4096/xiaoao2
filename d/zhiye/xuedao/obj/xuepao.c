// qinxiu-jiasha.c
 
#include <ansi.h> 
#include <armor.h> 
 
inherit CLOTH; 
 
void create() 
{ 
        set_name( RED "血袍" NOR, ({ "xue pao", "xuepao" ,"pao" ,  "cloth"}) ); 
        set_weight(1000); 
        if( clonep() ) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "件"); 
                set("long", "这是一件血刀门弟子穿的血红色袈裟，上面绣着些梵文。\n"); 
                set("value", 0); 
                set("material", "cloth"); 
                set("armor_prop/armor", 50); 
              } 
        setup(); 
} 
