#include <ansi.h>
inherit ITEM;
void create()
{
       set_name(HIY"��ë"NOR, ({ "jin mao", "jinmao" , "mao"}) );
       set_weight(1000);
       if( clonep() )
               set_default_object(__FILE__);
       else {
               set("unit", "��");
               set("long", "����һ����ë��ɫ���ƣ������ر���Ȼ�Ǵ�ĳ��ͷ�ϼ��µ�һ����\n");
               set("value", 2000);
               set("no_drop",1);
               set("no_get",1);
               set("no_steal",1);
               set("material", "silk");          
       }
       setup();
}

