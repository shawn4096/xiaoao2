//shixibiao.c 
//by sohu@xojh.sj

inherit ITEM;
#include <ansi.h>
void create()
{
       set_name(HIY"�������Ϯ��"NOR, ({ "shixi biao", "shixibiao" }) );
       set_weight(100);
       if( clonep() )
               set_default_object(__FILE__);
      else {
               set("unit", "��");
                set("long", "����һ����ɫ����������Ĵ�����Ļʼ���Ϯ������ɫ��Щ�Ұ�����Ȼ�������Զ֮�\n");
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