//csbl 2010.7.5 弄个什么破tb物品啊，纯属变态物品
#include <ansi.h>
inherit ITEM; 
void create()
{
     set_name (YEL"人参娃娃"NOR, ({ "renshen wawa"}));
     set("long",YEL"这是一枚娃娃状人形的人参,千年生成,极为罕见,你可以吃(eat)下它。\n"NOR);

     set("unit","枚");
     set_weight(100);
     set("value",3000000);
     set("no_give",1);
     set("no_drop",1);
     set("no_get",1);
          setup(); 

 }
 
void init()
 {
    add_action("do_eat","eat");
   
 }

int do_eat(string arg)
 {
     object me=this_player();
     
         
     if (arg!="renshen wawa")
                     return notify_fail("你要吃什么?\n");
            
          
            me->add("combat_exp",500000);
            me->add("max_neili",500);
            me->add("max_jingli",500);
          //  me->add("SJ_Credit",1000);
          //  me->add("balance",10000000);
    write(HIW"你吃下一枚"YEL"人参娃娃"HIW"感觉自己轻身明目,易筋换骨!\n"NOR);
         return 1;
}    
