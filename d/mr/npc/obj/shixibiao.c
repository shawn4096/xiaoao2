//shixibiao.c 
//by sohu@xojh.sj

inherit ITEM;
#include <ansi.h>
void create()
{
       set_name(HIY"大燕国世袭表"NOR, ({ "shixi biao", "shixibiao" }) );
       set_weight(100);
       if( clonep() )
               set_default_object(__FILE__);
      else {
               set("unit", "卷");
                set("long", "这是一卷黄色绸缎所制作的大燕国的皇家世袭表，颜色有些灰暗，显然是年代久远之物。\n");
               set("value", 100000);
               set("no_get",1);                 
               set("no_give",1);
               set("treasure",1);
               set("no_put",1);
               set("no_drop",1);
               set("material", "silk");
       }
       setup();
}