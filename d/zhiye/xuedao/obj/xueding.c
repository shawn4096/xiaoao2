// qinxiu-jiasha.c
 
#include <ansi.h> 
//#include <armor.h> 
 
inherit ITEM; 
 
void create() 
{ 
        set_name( RED "Ѫ��" NOR, ({ "xue ding", "xueding" , "ding"}) ); 
        set_weight(1000); 
        if( clonep() ) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "��"); 
                set("long", "����һ�����ص�ͭ���������İ���Ѫ���â����Щ��ɭ�ֲ���\n"
							+"�������п�һ�ۣ�������һ��ħ���Ľ�����������������а�죡\n"); 
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
