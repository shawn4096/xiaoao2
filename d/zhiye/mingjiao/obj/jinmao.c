#include <ansi.h>
inherit ITEM;
void create()
{
       set_name(HIY"金毛"NOR, ({ "jin mao", "jinmao" , "mao"}) );
       set_weight(1000);
       if( clonep() )
               set_default_object(__FILE__);
       else {
               set("unit", "束");
               set("long", "这是一束金毛，色泽金黄，甚是特别，显然是从某人头上剪下的一束。\n");
               set("value", 2000);
               set("no_drop",1);
               set("no_get",1);
               set("no_steal",1);
               set("material", "silk");          
       }
       setup();
}

