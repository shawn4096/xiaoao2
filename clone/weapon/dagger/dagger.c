// tie-ling.c 铁令
// by snowman@SJ 18/02/2000

#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
        set_name("暗杀匕首", ({ "ansha bishou","bishou", "dagger" }));
		set("long", "这是一柄两尺来长的暗杀匕首。\n");		
         set("unit", "柄");         
         set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {              
                set("value", 1000);
                set("material", "steel");                
                
        }
		set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
        set("unwield_msg", "$N将手中的$n插回腰间。\n");       
        init_dagger(20);
        setup();
}

