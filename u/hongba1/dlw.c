//csbl 2010.7.5 Ū��ʲô��tb��Ʒ����������̬��Ʒ
#include <ansi.h>
inherit ITEM; 
void create()
{
     set_name (YEL"�˲�����"NOR, ({ "renshen wawa"}));
     set("long",YEL"����һö����״���ε��˲�,ǧ������,��Ϊ����,����Գ�(eat)������\n"NOR);

     set("unit","ö");
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
                     return notify_fail("��Ҫ��ʲô?\n");
            
          
            me->add("combat_exp",500000);
            me->add("max_neili",500);
            me->add("max_jingli",500);
          //  me->add("SJ_Credit",1000);
          //  me->add("balance",10000000);
    write(HIW"�����һö"YEL"�˲�����"HIW"�о��Լ�������Ŀ,�׽��!\n"NOR);
         return 1;
}    
